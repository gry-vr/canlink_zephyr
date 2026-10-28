#pragma once
// Pure C++ diagnostic format and policy. No Zephyr headers or dynamic storage.
#include <array>
#include <atomic>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>

namespace canfw::diag {
enum class State : std::uint8_t { active, warning, passive, bus_off, stopped, unknown = 255 };
enum class Event : std::uint8_t {
    boot,
    transition,
    tx_rejected,
    tx_completion_error,
    recovery_attempt,
    recovery_result,
    recovery_complete,
    queue_overflow,
    rx_overflow,
    filter_failure,
    state_query_error,
    cleared,
    recovery_wait_expired
};
// Layout v1: native little-endian on both supported targets. 40 bytes, no padding.
// uptime_ms [0:8], cycles [8:12], CAN id [12:16], errno [16:20],
// arg0/arg1/aux [20:32], kind/old/new/TEC/REC/DLC/flags/reserved [32:40].
struct [[gnu::packed]] Record {
    std::uint64_t uptime_ms;
    std::uint32_t cycles, can_id;
    std::int32_t error;
    std::uint32_t arg0, arg1, aux;
    Event kind;
    State old_state, new_state;
    std::uint8_t tec, rec, dlc, flags, reserved;
};
static_assert(sizeof(Record) == 40 && offsetof(Record, kind) == 32);
static_assert(std::is_trivially_copyable_v<Record>);
static_assert(std::endian::native == std::endian::little);

template <class T, std::size_t N> struct Ring {
    static_assert(N > 0);
    std::array<T, N> entries;
    std::uint32_t head, count, overwritten;
    constexpr void push(const T &entry) {
        entries[head] = entry;
        head = (head + 1) % N;
        if (count < N)
            ++count;
        else
            ++overwritten;
    }
    constexpr const T &at(std::size_t i) const { return entries[(head + N - count + i) % N]; }
};
struct RawFrame {
    std::uint64_t uptime_ms;
    std::uint32_t id;
    std::uint8_t dlc, flags, tx, reserved;
    std::array<std::uint8_t, 8> bytes;
};
static_assert(sizeof(RawFrame) == 24);
template <std::size_t N> struct RawHistory : Ring<RawFrame, N> {};
template <> struct RawHistory<0> {};

struct Counters {
    std::array<std::uint32_t, 5> transitions;
    std::uint32_t bus_offs, recovery_attempts, recovery_successes, recovery_failures;
    std::uint32_t tx_accepted, tx_rejected, tx_completion_errors, tx_completed;
    std::uint32_t rx_frames, decode_failures, rx_drops, event_drops, tx_suppressed, filter_failures;
    std::uint32_t context_exhausted, recovery_timeouts;
    std::uint64_t last_bus_off_ms, longest_bus_off_ms, bus_off_start_ms, last_good_rx_ms,
        last_decoded_rx_ms;
    std::uint32_t episode_attempts, last_rx_id, last_tx_id;
    std::uint8_t last_rx_dlc, last_tx_dlc, entry_tec, entry_rec, exit_tec, exit_rec;
    State state;
    std::uint8_t episode_open;
};
struct DriverSnapshot {
    // stats order: bit0, bit1, stuff, CRC, form, ACK, RX overrun.
    std::array<std::uint32_t, 7> stats;
    // bxCAN order: MCR, MSR, TSR, RF0R, RF1R, IER, ESR, BTR.
    std::array<std::uint32_t, 8> registers;
    std::uint32_t core_clock_hz, capabilities, mode, configured_bitrate, sample_point;
    std::uint32_t reset_cause;
    std::int32_t state_error, core_clock_error, capabilities_error, reset_cause_error;
    std::uint8_t stats_available, registers_available, reserved[2];
};

inline constexpr auto crc_table = [] {
    std::array<std::uint32_t, 256> table{};
    for (std::uint32_t i = 0; i < 256; ++i) {
        auto c = i;
        for (int bit = 0; bit < 8; ++bit)
            c = (c >> 1) ^ ((c & 1) ? 0xEDB88320U : 0U);
        table[i] = c;
    }
    return table;
}();
constexpr std::uint32_t crc32_byte(std::uint32_t crc, std::uint8_t byte) {
    return (crc >> 8) ^ crc_table[(crc ^ byte) & 255];
}
constexpr const char *state_name(State s) {
    switch (s) {
    case State::active:
        return "ERROR_ACTIVE";
    case State::warning:
        return "ERROR_WARNING";
    case State::passive:
        return "ERROR_PASSIVE";
    case State::bus_off:
        return "BUS_OFF";
    case State::stopped:
        return "STOPPED";
    default:
        return "UNKNOWN";
    }
}
constexpr const char *event_name(Event e) {
    switch (e) {
    case Event::boot:
        return "BOOT";
    case Event::transition:
        return "STATE";
    case Event::tx_rejected:
        return "TX_REJECTED";
    case Event::tx_completion_error:
        return "TX_COMPLETION_ERROR";
    case Event::recovery_attempt:
        return "RECOVERY_ATTEMPT";
    case Event::recovery_result:
        return "RECOVERY_RESULT";
    case Event::recovery_complete:
        return "RECOVERY_COMPLETE";
    case Event::queue_overflow:
        return "EVENT_OVERFLOW";
    case Event::rx_overflow:
        return "RX_OVERFLOW";
    case Event::filter_failure:
        return "FILTER_FAILURE";
    case Event::state_query_error:
        return "STATE_QUERY_ERROR";
    case Event::cleared:
        return "CLEARED";
    case Event::recovery_wait_expired:
        return "RECOVERY_UNCONFIRMED";
    default:
        return "UNKNOWN";
    }
}
constexpr std::uint32_t crc32(const std::uint8_t *data, std::size_t len) {
    std::uint32_t c = 0xFFFFFFFFU;
    for (std::size_t i = 0; i < len; ++i)
        c = crc32_byte(c, data[i]);
    return ~c;
}
constexpr bool reached(std::uint32_t now, std::uint32_t deadline) {
    return static_cast<std::int32_t>(now - deadline) >= 0;
}
constexpr std::uint32_t until(std::uint32_t now, std::uint32_t deadline) {
    return reached(now, deadline) ? 0 : deadline - now;
}
enum class Action : std::uint8_t { none, recover, start, observe };
// One action may be in flight. A successful driver return is not recovery:
// only an observed active/warning/passive state confirms leaving bus-off.
class RecoveryPolicy {
  public:
    constexpr RecoveryPolicy(std::uint32_t initial = 100, std::uint32_t cap = 5000,
                             std::uint32_t confirmation = 100)
        : initial_(initial), cap_(cap), confirmation_(confirmation), delay_(initial) {}
    constexpr void observe(State s, std::uint32_t now) {
        if (s == state_)
            return;
        state_ = s;
        if (healthy()) {
            pending_ = false;
            delay_ = initial_;
        } else if (s == State::bus_off || s == State::stopped) {
            deadline_ = now;
            delay_ = initial_;
        }
    }
    constexpr Action due(std::uint32_t now, bool manual) {
        if (healthy() || pending_ || !reached(now, deadline_))
            return Action::none;
        if (state_ == State::unknown)
            return Action::none;
        pending_ = true;
        return state_ == State::stopped ? Action::start
                                        : (manual ? Action::recover : Action::observe);
    }
    constexpr void result(std::uint32_t now, bool success) {
        pending_ = false;
        deadline_ = now + (success && confirmation_ > delay_ ? confirmation_ : delay_);
        delay_ = delay_ > cap_ / 2 ? cap_ : delay_ * 2;
    }
    constexpr std::uint32_t wait(std::uint32_t now, std::uint32_t fallback) const {
        if (healthy() || pending_ || state_ == State::unknown)
            return fallback;
        const auto v = until(now, deadline_);
        return v < fallback ? v : fallback;
    }
    constexpr bool healthy() const {
        return state_ == State::active || state_ == State::warning || state_ == State::passive;
    }
    constexpr bool suppress() const { return state_ == State::bus_off || state_ == State::stopped; }
    constexpr State state() const { return state_; }

  private:
    std::uint32_t initial_, cap_, confirmation_, delay_, deadline_{};
    State state_{State::unknown};
    bool pending_{};
};

template <std::size_t Depth, std::size_t RawDepth = 0> struct Payload {
    Counters counters;
    DriverSnapshot driver;
    Ring<Record, Depth> events;
    [[no_unique_address]] RawHistory<RawDepth> raw;
};
template <std::size_t Depth, std::size_t RawDepth = 0> struct Bank {
    std::uint32_t magic, version, bytes, boot, sequence, crc;
    Payload<Depth, RawDepth> data;
};
template <std::size_t Depth, std::size_t RawDepth = 0> struct RetainedRegion {
    std::array<Bank<Depth, RawDepth>, 3> banks;
};
// Three banks: one previous boot is immutable; two alternate current commits.
// CRC covers header (except magic/CRC) and full payload. Torn commits retain
// the preceding valid current bank. Storage must not be zeroed by startup.
template <std::size_t Depth, std::size_t RawDepth = 0> class Journal {
  public:
    using Image = Bank<Depth, RawDepth>;
    using Region = RetainedRegion<Depth, RawDepth>;
    static constexpr std::uint32_t Magic = 0x43414E4CU, Version = 1;
    static_assert(std::is_trivially_copyable_v<Image>);
    explicit Journal(Region &region) : region_(region) {}
    static std::uint32_t checksum(const Image &b) {
        std::uint32_t c = 0xFFFFFFFFU;
        const auto *p = reinterpret_cast<const std::uint8_t *>(&b);
        for (std::size_t i = 4; i < sizeof(b); ++i)
            if (i < 20 || i >= 24)
                c = crc32_byte(c, p[i]);
        return ~c;
    }
    static bool valid(const Image &b) {
        return b.magic == Magic && b.version == Version && b.bytes == sizeof(Image) &&
               b.data.events.head < Depth && b.data.events.count <= Depth && b.crc == checksum(b);
    }
    void boot(const Record &record) {
        previous_ = -1;
        for (int i = 0; i < 3; ++i)
            if (valid(region_.banks[i])) {
                if (previous_ < 0 || newer(region_.banks[i], region_.banks[previous_]))
                    previous_ = i;
            }
        std::memset(&working_, 0, sizeof(working_));
        working_.version = Version;
        working_.bytes = sizeof(Image);
        working_.boot = previous_ < 0 ? 1 : region_.banks[previous_].boot + 1;
        working_.data.counters.state = State::unknown;
        working_.data.events.push(record);
        target_ = 0;
        commit();
    }
    void clear(const Record &record) {
        for (auto &b : region_.banks)
            b.magic = 0;
        std::atomic_thread_fence(std::memory_order_seq_cst);
        boot(record);
    }
    void commit() {
        while (target_ == previous_)
            target_ = (target_ + 1) % 3;
        auto &target = region_.banks[target_];
        ++working_.sequence;
        working_.magic = 0;
        working_.crc = checksum(working_);
        target.magic = 0;
        std::atomic_thread_fence(std::memory_order_seq_cst);
        std::memcpy(&target, &working_, sizeof(target));
        std::atomic_thread_fence(std::memory_order_seq_cst);
        target.magic = Magic;
        std::atomic_thread_fence(std::memory_order_seq_cst);
        working_.magic = Magic;
        target_ = (target_ + 1) % 3;
    }
    void append(const Record &r) { working_.data.events.push(r); }
    Payload<Depth, RawDepth> &data() { return working_.data; }
    const Image &current() const { return working_; }
    const Image &previous() const {
        static constexpr Image empty{};
        return previous_ < 0 ? empty : region_.banks[previous_];
    }

  private:
    static bool newer(const Image &a, const Image &b) {
        return a.boot == b.boot ? static_cast<std::int32_t>(a.sequence - b.sequence) > 0
                                : static_cast<std::int32_t>(a.boot - b.boot) > 0;
    }
    Region &region_;
    Image working_{};
    int previous_{-1}, target_{};
};
} // namespace canfw::diag
