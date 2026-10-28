#pragma once
#include "can_diagnostics.hpp"
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/can.h>
#include <zephyr/drivers/hwinfo.h>
#include <zephyr/linker/section_tags.h>
#include <zephyr/sys/sys_io.h>
#include <zephyr/sys/printk.h>
#include <algorithm>
#include <cerrno>

// External test applications must select the project's Kconfig root too.
#ifndef CONFIG_CANLINK_LOG_DEPTH
#error "Use CANLink Kconfig as KCONFIG_ROOT for this application"
#endif
namespace canfw {
using DiagnosticJournal = diag::Journal<CONFIG_CANLINK_LOG_DEPTH, CONFIG_CANLINK_RAW_FRAME_DEPTH>;
using DiagnosticSnapshot = DiagnosticJournal::Image;
static_assert(CONFIG_CANLINK_RECOVERY_INITIAL_MS <= CONFIG_CANLINK_RECOVERY_MAX_MS);
static_assert(CONFIG_CANLINK_RECOVERY_CONFIRM_MS <= CONFIG_CANLINK_RECOVERY_MAX_MS);
static_assert(std::atomic<std::uint32_t>::is_always_lock_free);
static_assert(std::atomic<bool>::is_always_lock_free);
static_assert(static_cast<int>(diag::State::stopped) == CAN_STATE_STOPPED);

// Defined in a non-template translation unit: GCC can ignore section attributes
// on function-template local statics. Only the two devicetree CAN aliases own
// retained regions. nullptr means the controller is not a configured channel.
DiagnosticJournal::Region *retained_diagnostics(const device *bus);

class CanDiagnostics {
  public:
    struct TxContext {
        CanDiagnostics *owner{};
        std::uint32_t id{};
        std::uint8_t dlc{};
        std::atomic<bool> busy{false};
    };
    CanDiagnostics(const device *bus, DiagnosticJournal::Region &region)
        : bus_(bus), journal_(region),
          policy_(CONFIG_CANLINK_RECOVERY_INITIAL_MS, CONFIG_CANLINK_RECOVERY_MAX_MS,
                  CONFIG_CANLINK_RECOVERY_CONFIRM_MS) {
        k_msgq_init(&events_, reinterpret_cast<char *>(event_storage_.data()), sizeof(diag::Record),
                    event_storage_.size());
        k_msgq_init(&jobs_, reinterpret_cast<char *>(&job_storage_), sizeof(diag::Action), 1);
        for (auto &c : contexts_)
            c.owner = this;
    }
    // Startup only, before CAN worker exists. No log writes here.
    int prepare() {
        can_mode_t caps{};
        const int rc = can_get_capabilities(bus_, &caps);
        manual_ = rc == 0 && (caps & CAN_MODE_MANUAL_RECOVERY);
        if (manual_) {
            const int mode_rc = can_set_mode(bus_, can_get_mode(bus_) | CAN_MODE_MANUAL_RECOVERY);
            if (mode_rc)
                return mode_rc;
        }
        can_set_state_change_callback(bus_, state_changed, this);
        return 0;
    }
    void cancel_startup() { can_set_state_change_callback(bus_, nullptr, nullptr); }
    void launch_executor() {
        k_thread_create(&executor_, executor_stack_, K_KERNEL_STACK_SIZEOF(executor_stack_),
                        executor_entry, this, nullptr, nullptr, 6, 0, K_NO_WAIT);
    }
    k_msgq *event_queue() { return &events_; }
    // Begin and all remaining non-callback methods run only on owning CAN worker.
    void begin() {
        auto r = record(diag::Event::boot);
        std::uint32_t cause = 0;
#ifdef CONFIG_HWINFO
        const int rc = hwinfo_get_reset_cause(&cause);
#else
        const int rc = -ENOSYS;
#endif
        capture_controller_state(r);
        r.arg0 = cause;
        r.error = rc;
        journal_.boot(r);
        journal_.data().driver.reset_cause = cause;
        journal_.data().driver.reset_cause_error = rc;
        health_due_ = k_uptime_get_32();
        service(k_uptime_get_32());
    }
    std::uint32_t wait_ms(std::uint32_t now) const {
        return policy_.wait(now, diag::until(now, health_due_));
    }
    bool suppress() const {
        // bxCAN send(K_NO_WAIT) still takes inst_mutex with K_FOREVER.
        // A state callback can announce recovery before recover()/start()
        // releases that mutex. Never submit TX until executor completion.
        if (job_busy_)
            return true;
        const auto s = static_cast<diag::State>(published_.load(std::memory_order_relaxed) & 0xff);
        return IS_ENABLED(CONFIG_CANLINK_SUPPRESS_UNHEALTHY_TX) &&
               (policy_.suppress() || s == diag::State::bus_off || s == diag::State::stopped);
    }
    void suppressed() { ++journal_.data().counters.tx_suppressed; }
    void filter_failure(int error) {
        filter_failures_.fetch_add(1, std::memory_order_relaxed);
        auto r = record(diag::Event::filter_failure);
        r.error = error;
        post(r);
    }
    // Custom RX callback replaces can_add_rx_filter_msgq's unobservable overflow.
    void rx_arrived(const can_frame &frame, k_msgq *q) {
        rx_time_.store(k_uptime_get_32(), std::memory_order_relaxed);
        rx_frames_.fetch_add(1, std::memory_order_release);
        if (k_msgq_put(q, &frame, K_NO_WAIT) != 0)
            rx_drops_.fetch_add(1, std::memory_order_relaxed);
    }
    void rx_processed(const can_frame &frame, bool decoded, std::uint32_t) {
        auto &c = journal_.data().counters;
        c.last_rx_id = frame.id;
        c.last_rx_dlc = frame.dlc;
        if (decoded)
            c.last_decoded_rx_ms = k_uptime_get();
        else
            ++c.decode_failures;
        raw(frame, false);
    }
    TxContext *reserve(const can_frame &frame) {
        for (auto &c : contexts_) {
            bool free = false;
            if (c.busy.compare_exchange_strong(free, true, std::memory_order_acquire)) {
                c.id = frame.id;
                c.dlc = frame.dlc;
                return &c;
            }
        }
        ++journal_.data().counters.context_exhausted;
        return nullptr;
    }
    void rejected(const can_frame &frame, int error) {
        ++journal_.data().counters.tx_rejected;
        auto r = record(diag::Event::tx_rejected);
        r.can_id = frame.id;
        r.dlc = frame.dlc;
        r.error = error;
        append(r);
        journal_.commit();
    }
    void accepted(const can_frame &frame) {
        auto &c = journal_.data().counters;
        ++c.tx_accepted;
        c.last_tx_id = frame.id;
        c.last_tx_dlc = frame.dlc;
        raw(frame, true);
    }
    std::uint32_t async_errors() const {
        return completion_errors_.load(std::memory_order_relaxed);
    }
    std::uint32_t rx_drops() const { return rx_drops_.load(std::memory_order_relaxed); }
    static void tx_done(const device *, int error, void *user) {
        auto *ctx = static_cast<TxContext *>(user);
        auto &self = *ctx->owner;
        if (error) {
            self.completion_errors_.fetch_add(1, std::memory_order_relaxed);
            auto r = self.record(diag::Event::tx_completion_error);
            r.can_id = ctx->id;
            r.dlc = ctx->dlc;
            r.error = error;
            self.capture_controller_state(r);
            self.post(r);
        } else
            self.completed_.fetch_add(1, std::memory_order_relaxed);
        ctx->busy.store(false, std::memory_order_release);
    }
    void service(std::uint32_t now) {
        diag::Record r{};
        // Bounded drains let recovery and TX run during continuous event/RX input.
        for (std::size_t i = 0;
             i < event_storage_.size() && k_msgq_get(&events_, &r, K_NO_WAIT) == 0; ++i) {
            if (r.kind == diag::Event::recovery_result && r.flags == 2)
                continue;
            if (r.kind == diag::Event::transition)
                transition(r);
            else
                append(r);
        }
        if (result_ready_.load(std::memory_order_acquire)) {
            const int rc = result_code_.load(std::memory_order_relaxed);
            result_ready_.store(false, std::memory_order_relaxed);
            job_busy_ = false;
            r = record(diag::Event::recovery_result);
            r.error = rc;
            r.arg0 = static_cast<unsigned>(job_action_);
            append(r);
            if (rc != 0 && rc != -EALREADY)
                ++journal_.data().counters.recovery_failures;
            if (rc == -ETIMEDOUT)
                ++journal_.data().counters.recovery_timeouts;
            awaiting_confirmation_ = (rc == 0 || rc == -EALREADY) && !policy_.healthy();
            policy_.result(now, rc == 0 || rc == -EALREADY);
            health_due_ = now; // can_start() does not promise a state callback.
        }
        const auto dropped = event_drops_.load(std::memory_order_relaxed);
        const auto rxdrop = rx_drops_.load(std::memory_order_relaxed);
        auto &counts = journal_.data().counters;
        if (dropped != counts.event_drops) {
            r = record(diag::Event::queue_overflow);
            r.arg0 = dropped - counts.event_drops;
            append(r);
            health_due_ = now;
        }
        if (rxdrop != counts.rx_drops) {
            r = record(diag::Event::rx_overflow);
            r.arg0 = rxdrop - counts.rx_drops;
            append(r);
        }
        counts.event_drops = dropped;
        counts.rx_drops = rxdrop;
        const auto received = rx_frames_.load(std::memory_order_acquire);
        if (received != counts.rx_frames) {
            const auto stamp = rx_time_.load(std::memory_order_relaxed);
            counts.last_good_rx_ms = static_cast<std::uint64_t>(k_uptime_get()) -
                                     static_cast<std::uint32_t>(k_uptime_get_32() - stamp);
        }
        counts.rx_frames = received;
        counts.tx_completion_errors = completion_errors_.load(std::memory_order_relaxed);
        counts.tx_completed = completed_.load(std::memory_order_relaxed);
        counts.filter_failures = filter_failures_.load(std::memory_order_relaxed);
        if (diag::reached(now, health_due_)) {
            sample(now);
            health_due_ = now + CONFIG_CANLINK_DIAGNOSTIC_POLL_MS;
        }
        if (!job_busy_) {
            const auto action = policy_.due(now, manual_);
            if (action != diag::Action::none) {
                if (awaiting_confirmation_) {
                    ++counts.recovery_timeouts;
                    r = record(diag::Event::recovery_wait_expired);
                    append(r);
                    awaiting_confirmation_ = false;
                }
                ++counts.recovery_attempts;
                if (counts.episode_open)
                    ++counts.episode_attempts;
                r = record(diag::Event::recovery_attempt);
                r.arg0 = counts.episode_attempts;
                r.arg1 = static_cast<unsigned>(action);
                append(r);
                if (action == diag::Action::observe) {
                    // Hardware automatic recovery fallback: observation, not a fake
                    // successful manual attempt. No controller reset is invented.
                    policy_.result(now, false);
                } else {
                    job_action_ = action;
                    if (k_msgq_put(&jobs_, &action, K_NO_WAIT) == 0)
                        job_busy_ = true;
                    else {
                        policy_.result(now, false);
                        ++counts.recovery_failures;
                    }
                }
            }
        }
        journal_.commit();
    }
    void reply(k_msgq *q, bool previous, bool clear) {
        if (!q || q->msg_size != sizeof(DiagnosticSnapshot))
            return;
        if (clear) {
            const auto counters = journal_.data().counters;
            const auto driver = journal_.data().driver;
            auto r = record(diag::Event::cleared);
            journal_.clear(r);
            journal_.data().counters = counters;
            journal_.data().driver = driver;
            journal_.commit();
        } else
            journal_.commit();
        const auto &image = previous ? journal_.previous() : journal_.current();
        (void)k_msgq_put(q, &image, K_NO_WAIT);
    }

  private:
    diag::Record record(diag::Event kind) const {
        diag::Record r{};
        r.kind = kind;
        r.flags = 8; // fallback: last published state/counters
        r.uptime_ms = k_uptime_get();
        r.cycles = k_cycle_get_32();
        const auto p = published_.load(std::memory_order_relaxed);
        r.old_state = r.new_state = static_cast<diag::State>(p & 255);
        r.tec = (p >> 8) & 255;
        r.rec = (p >> 16) & 255;
        return r;
    }
    void post(const diag::Record &r) {
        if (k_msgq_put(&events_, &r, K_NO_WAIT) != 0)
            event_drops_.fetch_add(1, std::memory_order_relaxed);
    }
    static void state_changed(const device *, can_state state, can_bus_err_cnt err, void *user) {
        auto &self = *static_cast<CanDiagnostics *>(user);
        auto r = self.record(diag::Event::transition);
        const std::uint32_t p = static_cast<unsigned>(state) |
                                (std::uint32_t(err.tx_err_cnt) << 8) |
                                (std::uint32_t(err.rx_err_cnt) << 16);
        r.old_state =
            static_cast<diag::State>(self.published_.exchange(p, std::memory_order_relaxed) & 255);
        r.new_state = static_cast<diag::State>(state);
        r.tec = err.tx_err_cnt;
        r.rec = err.rx_err_cnt;
        r.flags = 0; // authoritative state callback arguments
        self.post(r);
    }
    // Verified bxCAN, native-linux, and loopback get_state implementations
    // only read registers/driver fields: no mutex, timeout, or allocation.
    // This is also used for TX completions because their callback precedes
    // bxCAN's state-change callback in the error ISR.
    void capture_controller_state(diag::Record &r) const {
        can_state state;
        can_bus_err_cnt counts{};
        if (can_get_state(bus_, &state, &counts) == 0) {
            r.old_state = r.new_state = static_cast<diag::State>(state);
            r.tec = counts.tx_err_cnt;
            r.rec = counts.rx_err_cnt;
            r.flags = 4;
        }
    }
    void append(diag::Record r) {
        if (r.kind != diag::Event::transition && r.flags == 8)
            capture_controller_state(r);
        journal_.append(r);
    }
    void transition(const diag::Record &r) {
        auto &c = journal_.data().counters;
        append(r);
        const auto idx = static_cast<unsigned>(r.new_state);
        if (idx < 5)
            ++c.transitions[idx];
        c.state = r.new_state;
        if (r.new_state == diag::State::active || r.new_state == diag::State::warning ||
            r.new_state == diag::State::passive)
            awaiting_confirmation_ = false;
        policy_.observe(r.new_state, static_cast<std::uint32_t>(r.uptime_ms));
        if (r.new_state == diag::State::bus_off && !c.episode_open) {
            ++c.bus_offs;
            c.episode_open = 1;
            c.bus_off_start_ms = r.uptime_ms;
            c.episode_attempts = 0;
            c.entry_tec = r.tec;
            c.entry_rec = r.rec;
        } else if (c.episode_open &&
                   (r.new_state == diag::State::active || r.new_state == diag::State::warning ||
                    r.new_state == diag::State::passive)) {
            c.episode_open = 0;
            c.last_bus_off_ms = r.uptime_ms - c.bus_off_start_ms;
            c.longest_bus_off_ms = std::max(c.longest_bus_off_ms, c.last_bus_off_ms);
            ++c.recovery_successes;
            c.exit_tec = r.tec;
            c.exit_rec = r.rec;
            auto done = r;
            done.kind = diag::Event::recovery_complete;
            done.arg0 = static_cast<std::uint32_t>(c.last_bus_off_ms);
            done.arg1 = c.episode_attempts;
            done.aux = std::uint32_t(c.entry_tec) | (std::uint32_t(c.entry_rec) << 8);
            append(done);
        }
    }
    void sample(std::uint32_t now) {
        auto &d = journal_.data().driver;
        can_state state;
        can_bus_err_cnt err{};
        auto prior = published_.load(std::memory_order_relaxed);
        d.state_error = can_get_state(bus_, &state, &err);
        if (d.state_error == 0) {
            // Reconcile missed callbacks/STOPPED without modifying driver state.
            const auto observed = static_cast<diag::State>(state);
            if (observed != policy_.state()) {
                auto r = record(diag::Event::transition);
                r.old_state = policy_.state();
                r.new_state = observed;
                r.tec = err.tx_err_cnt;
                r.rec = err.rx_err_cnt;
                r.flags = 1;
                transition(r);
            }
            const auto current = static_cast<unsigned>(state) |
                                 (std::uint32_t(err.tx_err_cnt) << 8) |
                                 (std::uint32_t(err.rx_err_cnt) << 16);
            (void)published_.compare_exchange_strong(prior, current, std::memory_order_relaxed);
        } else {
            auto r = record(diag::Event::state_query_error);
            r.error = d.state_error;
            append(r);
        }
        d.core_clock_error = can_get_core_clock(bus_, &d.core_clock_hz);
        can_mode_t cap{};
        d.capabilities_error = can_get_capabilities(bus_, &cap);
        d.capabilities = cap;
        d.mode = can_get_mode(bus_);
        const auto *cfg = static_cast<const can_driver_config *>(bus_->config);
        d.configured_bitrate = cfg->bitrate;
        d.sample_point = cfg->sample_point;
#ifdef CONFIG_CAN_STATS
        d.stats_available = 1;
        d.stats = {can_stats_get_bit0_errors(bus_),  can_stats_get_bit1_errors(bus_),
                   can_stats_get_stuff_errors(bus_), can_stats_get_crc_errors(bus_),
                   can_stats_get_form_errors(bus_),  can_stats_get_ack_errors(bus_),
                   can_stats_get_rx_overruns(bus_)};
#endif
#if defined(CONFIG_CAN_STM32_BXCAN)
#define CANLINK_CAPTURE_REGS(node)                                                                 \
    if (bus_ == DEVICE_DT_GET(node)) {                                                             \
        for (unsigned i = 0; i < 8; ++i)                                                           \
            d.registers[i] = sys_read32(DT_REG_ADDR(node) + i * 4);                                \
        d.registers_available = 1;                                                                 \
    }
        DT_FOREACH_STATUS_OKAY(st_stm32_bxcan, CANLINK_CAPTURE_REGS)
#undef CANLINK_CAPTURE_REGS
#endif
        (void)now;
    }
    void raw(const can_frame &frame, bool tx) {
#if CONFIG_CANLINK_RAW_FRAME_DEPTH > 0
        diag::RawFrame r{};
        r.uptime_ms = k_uptime_get();
        r.id = frame.id;
        r.dlc = frame.dlc;
        r.flags = frame.flags;
        r.tx = tx;
        std::memcpy(r.bytes.data(), frame.data, std::min<std::size_t>(8, frame.dlc));
        journal_.data().raw.push(r);
#else
        (void)frame;
        (void)tx;
#endif
    }
    static void executor_entry(void *p, void *, void *) {
        auto &self = *static_cast<CanDiagnostics *>(p);
        diag::Action action;
        for (;;) {
            k_msgq_get(&self.jobs_, &action, K_FOREVER);
            const int rc = action == diag::Action::start ? can_start(self.bus_)
                                                         : can_recover(self.bus_, K_NO_WAIT);
            self.result_code_.store(rc, std::memory_order_relaxed);
            self.result_ready_.store(true, std::memory_order_release);
            auto r = self.record(diag::Event::recovery_result);
            r.flags = 2;
            // Wake only; actual result is an atomic mailbox so queue overflow
            // cannot strand the worker waiting for a completion forever.
            self.post(r);
        }
    }
    const device *bus_;
    DiagnosticJournal journal_;
    diag::RecoveryPolicy policy_;
    k_msgq events_{}, jobs_{};
    std::array<diag::Record, CONFIG_CANLINK_EVENT_QUEUE_DEPTH> event_storage_{};
    diag::Action job_storage_{};
    std::array<TxContext, CONFIG_CANLINK_TX_CONTEXTS> contexts_{};
    K_KERNEL_STACK_MEMBER(executor_stack_, CONFIG_CANLINK_RECOVERY_STACK_SIZE);
    k_thread executor_{};
    std::atomic<std::uint32_t> published_{255}, rx_time_{0}, event_drops_{0}, rx_drops_{0},
        rx_frames_{0}, completion_errors_{0}, completed_{0}, filter_failures_{0};
    std::atomic<int> result_code_{0};
    std::atomic<bool> result_ready_{false};
    bool manual_{false}, job_busy_{false}, awaiting_confirmation_{false};
    diag::Action job_action_{};
    std::uint32_t health_due_{};
};

// Caller-owned static buffers. One client thread per instance; do not destroy
// while a request may still be queued. No direct access to worker-owned logs.
class DiagnosticClient {
  public:
    DiagnosticClient() {
        k_msgq_init(&queue_, reinterpret_cast<char *>(&storage_), sizeof(storage_), 1);
    }
    k_msgq *reply_queue() { return &queue_; }
    const DiagnosticSnapshot &snapshot() const { return result_; }
    int receive(k_timeout_t timeout) { return k_msgq_get(&queue_, &result_, timeout); }
    void print() const {
        if (!DiagnosticJournal::valid(result_)) {
            printk("No valid retained log\n");
            return;
        }
        const auto &c = result_.data.counters;
        printk("boot=%u records=%u overwritten=%u state=%u bus_off=%u recoveries=%u/%u rx=%u "
               "tx_accepted=%u tx_rejected=%u tx_completion_errors=%u rx_drops=%u event_drops=%u "
               "suppressed=%u\n",
               result_.boot, result_.data.events.count, result_.data.events.overwritten,
               unsigned(c.state), c.bus_offs, c.recovery_successes, c.recovery_attempts,
               c.rx_frames, c.tx_accepted, c.tx_rejected, c.tx_completion_errors, c.rx_drops,
               c.event_drops, c.tx_suppressed);
        const auto &d = result_.data.driver;
        printk("state=%s transitions active/warning/passive/off/stopped=%u/%u/%u/%u/%u\n",
               diag::state_name(c.state), c.transitions[0], c.transitions[1], c.transitions[2],
               c.transitions[3], c.transitions[4]);
        printk("bus-off open=%u start_ms=%llu last_ms=%llu longest_ms=%llu attempts=%u entry "
               "TEC/REC=%u/%u exit=%u/%u failures=%u unconfirmed=%u\n",
               c.episode_open, (unsigned long long)c.bus_off_start_ms,
               (unsigned long long)c.last_bus_off_ms, (unsigned long long)c.longest_bus_off_ms,
               c.episode_attempts, c.entry_tec, c.entry_rec, c.exit_tec, c.exit_rec,
               c.recovery_failures, c.recovery_timeouts);
        printk("last RX=%08x DLC=%u good_rx_ms=%llu decoded_rx_ms=%llu last accepted TX=%08x "
               "DLC=%u completed=%u decode_failures=%u filter_failures=%u context_exhausted=%u\n",
               c.last_rx_id, c.last_rx_dlc, (unsigned long long)c.last_good_rx_ms,
               (unsigned long long)c.last_decoded_rx_ms, c.last_tx_id, c.last_tx_dlc,
               c.tx_completed, c.decode_failures, c.filter_failures, c.context_exhausted);
        printk("driver bitrate=%u sample_point=%u core_hz=%u capabilities=%08x mode=%08x "
               "reset=%08x API errno state/clock/capabilities/reset=%d/%d/%d/%d\n",
               d.configured_bitrate, d.sample_point, d.core_clock_hz, d.capabilities, d.mode,
               d.reset_cause, d.state_error, d.core_clock_error, d.capabilities_error,
               d.reset_cause_error);
        printk("stats available=%u bit0/bit1/stuff/CRC/form/ACK/overrun=%u/%u/%u/%u/%u/%u/%u\n",
               d.stats_available, d.stats[0], d.stats[1], d.stats[2], d.stats[3], d.stats[4],
               d.stats[5], d.stats[6]);
        if (d.registers_available)
            printk(
                "bxCAN MCR/MSR/TSR/RF0R/RF1R/IER/ESR/BTR=%08x/%08x/%08x/%08x/%08x/%08x/%08x/%08x\n",
                d.registers[0], d.registers[1], d.registers[2], d.registers[3], d.registers[4],
                d.registers[5], d.registers[6], d.registers[7]);
#if CONFIG_CANLINK_RAW_FRAME_DEPTH > 0
        for (unsigned i = 0; i < result_.data.raw.count; ++i) {
            const auto &f = result_.data.raw.at(i);
            printk("raw %s ms=%llu id=%08x DLC=%u flags=%u data=", f.tx ? "TX-accepted" : "RX",
                   (unsigned long long)f.uptime_ms, f.id, f.dlc, f.flags);
            for (unsigned j = 0; j < std::min<unsigned>(8, f.dlc); ++j)
                printk("%02x", f.bytes[j]);
            printk("\n");
        }
#endif
        for (std::uint32_t i = 0; i < result_.data.events.count; ++i) {
            const auto &r = result_.data.events.at(i);
            printk("ms=%llu cyc=%u event=%s state=%s->%s TEC=%u REC=%u id=%08x dlc=%u errno=%d "
                   "arg=%u,%u aux=%u flags=%u\n",
                   static_cast<unsigned long long>(r.uptime_ms), r.cycles, diag::event_name(r.kind),
                   diag::state_name(r.old_state), diag::state_name(r.new_state), r.tec, r.rec,
                   r.can_id, r.dlc, r.error, r.arg0, r.arg1, r.aux, r.flags);
        }
    }

  private:
    k_msgq queue_{};
    DiagnosticSnapshot storage_{}, result_{};
};
} // namespace canfw
