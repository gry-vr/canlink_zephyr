#pragma once

#include <zephyr/device.h>
#include <zephyr/drivers/can.h>
#include <zephyr/kernel.h>

#include "can_endpoint.hpp"
#include "tx_schedule.hpp"
#include "can_diagnostics_runtime.hpp"

// Lightweight TX-path trace, fully compile-time gated. Build with
// -DCANFW_TX_TRACE=1 to emit one printk line per scheduler decision, send
// attempt, and wait choice -- enough to prove on-bus periodicity end to end:
//
//   TX_WAIT  now=123440 wait_ms=10 rx=0 cmd=0
//   TX_SCHED now=123450 id=0x0C000031 due=yes next_due=123450 period=10
//   TX_SEND  now=123450 id=0x0C000031 rc=0
//   TX_DROP  now=123450 id=0x0C000031 stage=validate signal=115 err=1
//
// Default off: the macro expands to nothing, so the hot path carries zero
// cost and no printk. Do not enable on target builds that are timing-
// sensitive; it is intended for native_sim bring-up.
#ifndef CANFW_TX_TRACE
#define CANFW_TX_TRACE 0
#endif
#if CANFW_TX_TRACE
#include <zephyr/sys/printk.h>
#define CANFW_TX_TRACE_LOG(...) printk(__VA_ARGS__)
#else
#define CANFW_TX_TRACE_LOG(...) ((void)0)
#endif

#include <array>
#include <atomic>
#include <cstdint>
#include <expected>
#include <optional>
#include <type_traits>
#include <utility>
#include <variant>

namespace canfw {

enum class InitError : std::uint8_t {
    device_not_ready,
    rx_filter_install_failed,
    can_start_failed,
    already_started,
    can_mode_failed,
    unsupported_diagnostic_channel,
};

enum class SendError : std::uint8_t {
    build_failed,
    validation_failed,
    encode_failed,
    tx_rejected,
    tx_suppressed,
};

template <typename Hooks, typename Msg, typename Db>
concept HasOnRxMessage =
    requires(Hooks& h, const Msg& msg, typename Db::ValueStore& store, std::uint32_t now_ms) {
        { h.on_rx_message(msg, store, now_ms) };
    };

template <typename Hooks, typename Msg, typename Db>
void dispatch_on_rx(Hooks& hooks,
                    const Msg& msg,
                    typename Db::ValueStore& rx_store,
                    std::uint32_t now_ms)
{
    if constexpr (HasOnRxMessage<Hooks, Msg, Db>) {
        hooks.on_rx_message(msg, rx_store, now_ms);
    }
}

template <typename Hooks, typename Msg, typename Db>
concept HasBeforeSend =
    requires(Hooks& h, Msg& msg, typename Db::ValueStore& store, std::uint32_t now_ms) {
        { h.on_before_send(msg, store, now_ms) };
    };

template <typename Hooks, typename Msg, typename Db>
void dispatch_before_send(Hooks& hooks, Msg& msg, typename Db::ValueStore& tx_store, std::uint32_t now_ms)
{
    if constexpr (HasBeforeSend<Hooks, Msg, Db>) {
        hooks.on_before_send(msg, tx_store, now_ms);
    }
}

template <typename Db, typename Hooks>
class CanActiveObject {
public:
    using MessageId = typename Db::MessageId;
    using MessageVariant = typename Db::MessageVariant;
    using ValueStore = typename Db::ValueStore;
    using Command = typename TxCommand<Db>::Variant;
    using Endpoint = canfw::CanEndpoint<Db>;
    using Snapshot = canfw::SnapshotReply<Db>;
    using TxCommandType = TxCommand<Db>;
    using TxPolicyType = TxPolicy;
    using SignalPhysicalValue = typename Db::SignalPhysicalValue;
    using ValidationIssue = typename Db::ValidationIssue;

    static constexpr std::size_t RxQueueDepth = 64;
    static constexpr std::size_t TxQueueDepth = 16;
    static constexpr std::size_t ThreadStackSize = 8192;
    static constexpr int ThreadPriority = 5;

    // Anything that fits in a Command may legitimately live in a stack local
    // (drain_tx_commands holds one), so it gets an explicit budget. Measured
    // today: duramax = 88 bytes, reacher = 56 bytes. If a regenerated DBC
    // blows past this, the build fails here instead of the stack failing in
    // the field.
    static constexpr std::size_t kMaxCommandBytes = 256;

    // --- k_msgq memcpy contract -------------------------------------------
    // k_msgq transports messages with raw memcpy. Every type that crosses a
    // queue must therefore be trivially copyable; anything else is silent UB
    // the day someone adds a non-trivial member to a generated type.
    static_assert(std::is_trivially_copyable_v<Command>,
                  "Command crosses k_msgq by memcpy and must stay trivially copyable");
    static_assert(std::is_trivially_copyable_v<can_frame>,
                  "can_frame crosses k_msgq by memcpy and must stay trivially copyable");
    static_assert(std::is_trivially_copyable_v<Snapshot>,
                  "SnapshotReply crosses k_msgq by memcpy and must stay trivially copyable");

    // --- stack budget ------------------------------------------------------
    static_assert(sizeof(Command) <= kMaxCommandBytes,
                  "Command outgrew its stack budget; audit drain_tx_commands and "
                  "the k_msgq storage sizing before raising kMaxCommandBytes");
    // Note: sizeof(Snapshot) is ~7.1 KB for duramax -- it must NEVER be a
    // stack local. That property cannot be expressed as a static_assert
    // (storage duration is invisible to the type system); it is enforced by
    // the -Wframe-larger-than build flag plus the snapshot_scratch_ member
    // below being the only Snapshot instance this class ever creates.

    static auto create(const device* can_device, Hooks hooks = {}, bool extended_id = false)
        -> std::expected<CanActiveObject*, InitError>
    {
        if (can_device == nullptr || !device_is_ready(can_device)) {
            return std::unexpected{InitError::device_not_ready};
        }

        auto* region = retained_diagnostics(can_device);
        if (!region) return std::unexpected{InitError::unsupported_diagnostic_channel};
        static CanActiveObject ao{can_device, std::move(hooks), extended_id, *region};

        if (ao.started_) {
            return &ao;
        }

        if (auto started = ao.start(); !started) {
            return std::unexpected{started.error()};
        }

        ao.started_ = true;
        return &ao;
    }

    CanActiveObject(const CanActiveObject&) = delete;
    auto operator=(const CanActiveObject&) -> CanActiveObject& = delete;
    CanActiveObject(CanActiveObject&&) = delete;
    auto operator=(CanActiveObject&&) -> CanActiveObject& = delete;

    int post_tx(const Command& cmd, k_timeout_t timeout = K_NO_WAIT) {
        return k_msgq_put(&tx_cmd_msgq_, &cmd, timeout);
    }

    // AO-thread-only views. These reference state the AO thread mutates
    // freely; reading them from any other thread is a data race. Cross-thread
    // consumers must use the snapshot command path (Endpoint::
    // request_snapshot_into), which serializes the copy onto the AO thread.
    const ValueStore& rx_store() const { return rx_store_; }
    const ValueStore& tx_store() const { return tx_store_; }

    [[nodiscard]] std::uint32_t decode_failures() const {
        return decode_failures_.load(std::memory_order_relaxed);
    }
    [[nodiscard]] std::uint32_t tx_build_failures() const {
        return tx_build_failures_.load(std::memory_order_relaxed);
    }
    [[nodiscard]] std::uint32_t tx_encode_failures() const {
        return tx_encode_failures_.load(std::memory_order_relaxed);
    }
    [[nodiscard]] std::uint32_t tx_validation_failures() const {
        return tx_validation_failures_.load(std::memory_order_relaxed);
    }
    // Frames accepted by can_send (queued to a TX mailbox). Compare against
    // grid expectations to spot silent drops: for a lone 10 ms message this
    // should advance by ~100/s.
    [[nodiscard]] std::uint32_t tx_frames_sent() const {
        return tx_frames_sent_.load(std::memory_order_relaxed);
    }
    [[nodiscard]] std::uint32_t tx_send_failures() const {
        return tx_send_failures_.load(std::memory_order_relaxed) + diagnostics_.async_errors();
    }
    [[nodiscard]] std::uint32_t tx_immediate_rejections() const { return tx_send_failures_.load(std::memory_order_relaxed); }
    [[nodiscard]] std::uint32_t tx_completion_errors() const { return diagnostics_.async_errors(); }
    [[nodiscard]] std::uint32_t rx_drops() const { return diagnostics_.rx_drops(); }
    [[nodiscard]] std::uint32_t tx_schedule_failures() const {
        return tx_schedule_failures_.load(std::memory_order_relaxed);
    }

    // Diagnostic breadcrumb for the most recent validation failure (replaces
    // the printk that used to live in the TX hot path). Written only by the
    // AO thread; a cross-thread read may observe a torn pair, which is
    // acceptable for a debug aid but not for control decisions.
    [[nodiscard]] ValidationIssue last_validation_issue() const {
        return last_validation_issue_;
    }

    void run_forever() {
        diagnostics_.begin();
        while (true) {
            const std::uint32_t now_ms = k_uptime_get_32();
            const auto wait_ms = next_due_wait_ms(now_ms);
            const k_timeout_t timeout = wait_ms.has_value() ? K_MSEC(*wait_ms) : K_FOREVER;

            for (auto& ev : events_) {
                ev.state = K_POLL_STATE_NOT_READY;
            }

            const int rc = k_poll(events_.data(), events_.size(), timeout);

            const std::uint32_t wake_ms = k_uptime_get_32();
            const bool rx_ready  = events_[0].state == K_POLL_STATE_MSGQ_DATA_AVAILABLE;
            const bool cmd_ready = events_[1].state == K_POLL_STATE_MSGQ_DATA_AVAILABLE;

            CANFW_TX_TRACE_LOG("TX_WAIT now=%u wait_ms=%d rx=%d cmd=%d\n",
                               now_ms, wait_ms.has_value() ? (int)*wait_ms : -1,
                               (int)rx_ready, (int)cmd_ready);

            diagnostics_.service(wake_ms);
            if (rc == 0) {
                if (rx_ready) {
                    drain_rx(wake_ms);
                }
                if (cmd_ready) {
                    drain_tx_commands(wake_ms);
                }
            }

            // Re-sample the clock: draining (and hooks) may have consumed
            // real time, and deadlines that matured during the drains should
            // be honored on this pass, not next iteration.
            run_due_tx(k_uptime_get_32());
        }
    }

    Endpoint endpoint() {
        return Endpoint{&tx_cmd_msgq_};
    }

private:
    explicit CanActiveObject(const device* can_device, Hooks hooks, bool extended_id,
                             DiagnosticJournal::Region& region)
        : can_bus_{can_device}, hooks_{std::move(hooks)}, extended_id_{extended_id},
          diagnostics_{can_device, region}
    {
        k_msgq_init(&rx_msgq_,
                    reinterpret_cast<char*>(rx_queue_storage_.data()),
                    sizeof(can_frame),
                    RxQueueDepth);

        k_msgq_init(&tx_cmd_msgq_,
                    reinterpret_cast<char*>(tx_cmd_storage_.data()),
                    sizeof(Command),
                    TxQueueDepth);

        k_poll_event_init(&events_[0],
                          K_POLL_TYPE_MSGQ_DATA_AVAILABLE,
                          K_POLL_MODE_NOTIFY_ONLY,
                          &rx_msgq_);

        k_poll_event_init(&events_[1],
                          K_POLL_TYPE_MSGQ_DATA_AVAILABLE,
                          K_POLL_MODE_NOTIFY_ONLY,
                          &tx_cmd_msgq_);
        k_poll_event_init(&events_[2], K_POLL_TYPE_MSGQ_DATA_AVAILABLE,
                          K_POLL_MODE_NOTIFY_ONLY, diagnostics_.event_queue());
    }

    auto start() -> std::expected<void, InitError> {
        if (diagnostics_.prepare() != 0) return std::unexpected{InitError::can_mode_failed};
        const can_filter filter = make_rx_filter(extended_id_);

        rx_filter_id_ = can_add_rx_filter(can_bus_, rx_callback_, this, &filter);
        if (rx_filter_id_ < 0) {
            diagnostics_.filter_failure(rx_filter_id_);
            diagnostics_.cancel_startup();
            return std::unexpected{InitError::rx_filter_install_failed};
        }

        if (const int rc = can_start(can_bus_); rc != 0) {
            can_remove_rx_filter(can_bus_, rx_filter_id_);
            rx_filter_id_ = -1;
            diagnostics_.cancel_startup();
            return std::unexpected{InitError::can_start_failed};
        }

        diagnostics_.launch_executor();
        k_thread_create(&thread_,
                        thread_stack_,
                        K_KERNEL_STACK_SIZEOF(thread_stack_),
                        &CanActiveObject::thread_entry_,
                        this, nullptr, nullptr,
                        ThreadPriority,
                        0,
                        K_NO_WAIT);

        return {};
    }

    static void thread_entry_(void* p1, void*, void*) {
        static_cast<CanActiveObject*>(p1)->run_forever();
    }

    static void rx_callback_(const device*, can_frame* frame, void* user_data) {
        auto& self = *static_cast<CanActiveObject*>(user_data);
        self.diagnostics_.rx_arrived(*frame, &self.rx_msgq_);
    }

    static constexpr can_filter make_rx_filter(bool extended_id) {
        can_filter filter{};
        filter.flags = (extended_id) ? CAN_FILTER_IDE : 0U;
        filter.id = 0U;
        filter.mask = 0U;
        return filter;
    }

    // Milliseconds until the earliest enabled slot is due; nullopt when no
    // periodic TX is active (poll forever on commands/RX alone).
    std::optional<std::uint32_t> next_due_wait_ms(std::uint32_t now_ms) const {
        std::optional<std::uint32_t> min_wait_ms{diagnostics_.wait_ms(now_ms)};

        for (std::size_t i = 0; i < tx_scheduler_.active_count; ++i) {
            const auto id = tx_scheduler_.active_ids[i];
            const auto& slot = tx_scheduler_.slots[Db::to_index(id)];

            if (!slot.enabled || slot.period_ms == 0U) {
                continue;
            }

            const std::uint32_t wait_ms = slot.until_due_ms(now_ms);

            if (!min_wait_ms.has_value() || wait_ms < *min_wait_ms) {
                min_wait_ms = wait_ms;
            }
        }

        return min_wait_ms;
    }

    void drain_rx(std::uint32_t now_ms) {
        can_frame frame{};

        for (std::size_t n = 0; n < RxQueueDepth && k_msgq_get(&rx_msgq_, &frame, K_NO_WAIT) == 0; ++n) {
            auto decoded = Db::decode(frame.id, frame.data, frame.dlc);
            diagnostics_.rx_processed(frame, decoded.has_value(), now_ms);
            if (!decoded) {
                decode_failures_.fetch_add(1, std::memory_order_relaxed);
                continue;
            }

            MessageVariant decoded_t = *decoded;

            Db::apply_to_store(rx_store_, decoded_t, now_ms);

            std::visit([&](const auto& msg) {
                dispatch_on_rx<Hooks, std::decay_t<decltype(msg)>, Db>(
                    hooks_, msg, rx_store_, now_ms);
            }, decoded_t);
        }
    }

    void drain_tx_commands(std::uint32_t now_ms) {
        Command cmd{};

        for (std::size_t n = 0; n < TxQueueDepth && k_msgq_get(&tx_cmd_msgq_, &cmd, K_NO_WAIT) == 0; ++n) {
            std::visit([&](const auto& c) {
                handle_tx_command(c, now_ms);
            }, cmd);
        }
    }

    void handle_tx_command(const typename TxCommandType::SendMessage& cmd, std::uint32_t now_ms) {
        std::visit([&](const auto& msg) {
            using Msg = std::decay_t<decltype(msg)>;
            Db::apply_to_store(tx_store_, msg, now_ms);
            handle_message_policy(Msg::id, cmd.policy, cmd.period_ms_override, now_ms);
        }, cmd.message);
    }

    void handle_tx_command(const typename TxCommandType::UpdateSignal& cmd, std::uint32_t now_ms) {
        auto res = Db::set_signal_physical(tx_store_, cmd.signal_id, cmd.value, now_ms);
        if (!res) {
            tx_build_failures_.fetch_add(1, std::memory_order_relaxed);
            return;
        }

        if (cmd.trigger_parent_send) {
            const auto parent = Db::parent_message_id(cmd.signal_id);
            (void)send_one(parent, now_ms);  // failure classes counted inside
        }
    }

    void handle_tx_command(const typename TxCommandType::DisableMessage& cmd, std::uint32_t) {
        tx_scheduler_.disable(cmd.message_id);
    }

    // The 7+ KB Snapshot is copied through the member scratch buffer, never
    // a stack local. snapshot_scratch_ is touched exclusively by the AO
    // thread (this handler runs in run_forever's context), so it needs no
    // synchronization; k_msgq_put then memcpys it into the caller's queue.
    void handle_tx_command(const typename TxCommandType::RequestSnapshot& cmd,
                           std::uint32_t now_ms)
    {
        if (cmd.reply_q == nullptr) {
            return;
        }

        snapshot_scratch_.store = rx_store_;
        snapshot_scratch_.valid = true;
        snapshot_scratch_.timestamp_ms = now_ms;

        (void)k_msgq_put(cmd.reply_q, &snapshot_scratch_, K_NO_WAIT);
    }

    void handle_tx_command(const typename TxCommandType::RequestDiagnostics& cmd, std::uint32_t) {
        diagnostics_.reply(cmd.reply_q, cmd.previous_boot, cmd.clear);
    }

    void handle_message_policy(MessageId id,
                               TxPolicy policy,
                               std::uint32_t period_override,
                               std::uint32_t now_ms)
    {
        switch (policy) {
        case TxPolicy::send_once:
            (void)send_one(id, now_ms);  // failure classes counted inside
            break;
        case TxPolicy::periodic_enable: {
            const auto period =
                period_override ? period_override : Db::message_cycle_time_ms(id);
            if (auto enabled = tx_scheduler_.enable(id, period, now_ms); !enabled) {
                tx_schedule_failures_.fetch_add(1, std::memory_order_relaxed);
            }
            break;
        }
        case TxPolicy::periodic_disable:
            tx_scheduler_.disable(id);
            break;
        }
    }

    // Services every due slot in one pass, then run_forever recomputes the
    // next wait. Fixed-rate grid semantics (drift-free advance, resync when
    // >1 period behind) live in TxScheduleSlot -- see tx_schedule.hpp and
    // its compile-time tests.
    //
    // A failed send still advances the deadline: the failure is counted in
    // send_one and the slot retries on its normal grid, which deliberately
    // avoids a tight retry spin against a sick bus.
    void run_due_tx(std::uint32_t now_ms) {
        for (std::size_t i = 0; i < tx_scheduler_.active_count; ++i) {
            const auto id = tx_scheduler_.active_ids[i];
            auto& slot = tx_scheduler_.slots[Db::to_index(id)];

            if (!slot.due(now_ms)) {
                continue;
            }

            CANFW_TX_TRACE_LOG("TX_SCHED now=%u id=0x%08X due=yes next_due=%u period=%u\n",
                               now_ms, Db::message_meta(id).frame_id,
                               slot.next_due_ms, slot.period_ms);

            (void)send_one(id, now_ms);  // failure classes counted inside

            slot.advance_after_send(now_ms);
        }
    }

    auto send_one(MessageId id, std::uint32_t now_ms)
        -> std::expected<void, SendError>
    {
        if (diagnostics_.suppress()) {
            diagnostics_.suppressed();
            return std::unexpected{SendError::tx_suppressed};
        }
        auto built = Db::build_message_from_store(id, tx_store_);
        if (!built) {
            tx_build_failures_.fetch_add(1, std::memory_order_relaxed);
            return std::unexpected{SendError::build_failed};
        }

        can_frame frame{};
        const auto& meta = Db::message_meta(id);

        frame.id = meta.frame_id;
        frame.flags = meta.is_extended ? CAN_FRAME_IDE : 0U;

        auto encoded = std::visit(
            [&](auto& msg) -> std::expected<std::uint8_t, SendError> {
                using Msg = std::decay_t<decltype(msg)>;

                dispatch_before_send<Hooks, Msg, Db>(hooks_, msg, tx_store_, now_ms);

                if (auto validated = Db::validate_message(msg); !validated) {
                    tx_validation_failures_.fetch_add(1, std::memory_order_relaxed);
                    last_validation_issue_ = validated.error();
                    CANFW_TX_TRACE_LOG(
                        "TX_DROP now=%u id=0x%08X stage=validate signal=%u err=%u\n",
                        now_ms, meta.frame_id,
                        static_cast<unsigned>(Db::to_index(validated.error().signal_id)),
                        static_cast<unsigned>(validated.error().error));
                    return std::unexpected{SendError::validation_failed};
                }

                auto n = Db::encode(msg, frame.data, sizeof(frame.data));
                if (!n) {
                    tx_encode_failures_.fetch_add(1, std::memory_order_relaxed);
                    return std::unexpected{SendError::encode_failed};
                }
                return *n;
            },
            *built
        );

        if (!encoded) {
            return std::unexpected{encoded.error()};
        }

        frame.dlc = *encoded;

        // Fire-and-forget: with a callback installed, can_send returns as
        // soon as the frame is queued to a TX mailbox. K_NO_WAIT means a
        // full mailbox set rejects immediately (-EAGAIN) instead of parking
        // the AO thread, and a dead/error-passive bus can no longer hang
        // this loop -- on-bus failures arrive asynchronously via
        // tx_done_callback_.
        auto* context = diagnostics_.reserve(frame);
        const int rc = context ? can_send(can_bus_, &frame, K_NO_WAIT,
                                &CanDiagnostics::tx_done, context) : -ENOBUFS;
        CANFW_TX_TRACE_LOG("TX_SEND now=%u id=0x%08X rc=%d\n",
                           now_ms, frame.id, rc);
        if (rc != 0) {
            if (context) context->busy.store(false, std::memory_order_release);
            diagnostics_.rejected(frame, rc);
            tx_send_failures_.fetch_add(1, std::memory_order_relaxed);
            return std::unexpected{SendError::tx_rejected};
        }

        diagnostics_.accepted(frame);
        tx_frames_sent_.fetch_add(1, std::memory_order_relaxed);
        return {};
    }

private:
    const device* can_bus_{nullptr};
    Hooks hooks_{};
    bool started_{false};
    bool extended_id_;
    CanDiagnostics diagnostics_;

    ValueStore rx_store_{};
    ValueStore tx_store_{};

    // AO-thread-only staging buffer for snapshot replies. Lives in the
    // object (.bss for the create() static), keeping the ~7 KB copy off
    // every stack. See handle_tx_command(RequestSnapshot).
    Snapshot snapshot_scratch_{};

    k_msgq rx_msgq_{};
    alignas(can_frame) std::array<can_frame, RxQueueDepth> rx_queue_storage_{};

    k_msgq tx_cmd_msgq_{};
    alignas(Command) std::array<Command, TxQueueDepth> tx_cmd_storage_{};

    std::array<k_poll_event, 3> events_{};
    TxScheduler<Db> tx_scheduler_{};

    K_KERNEL_STACK_MEMBER(thread_stack_, ThreadStackSize);
    k_thread thread_{};

    int rx_filter_id_{-1};

    // These counters are written by the AO thread. ISR completion counters
    // live in CanDiagnostics; the combined getter adds both. Relaxed atomics
    // make those cross-context accesses well-defined; they impose no
    // ordering, which is all a monotonic counter needs.
    std::atomic<std::uint32_t> tx_frames_sent_{0};
    std::atomic<std::uint32_t> decode_failures_{0};
    std::atomic<std::uint32_t> tx_build_failures_{0};
    std::atomic<std::uint32_t> tx_encode_failures_{0};
    std::atomic<std::uint32_t> tx_validation_failures_{0};
    std::atomic<std::uint32_t> tx_send_failures_{0};
    std::atomic<std::uint32_t> tx_schedule_failures_{0};

    ValidationIssue last_validation_issue_{};
};

} // namespace canfw
