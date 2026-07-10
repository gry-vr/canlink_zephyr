#pragma once

#include <zephyr/device.h>
#include <zephyr/drivers/can.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "can_endpoint.hpp"

#include <array>
#include <cstdint>
#include <expected>
#include <type_traits>
#include <utility>
#include <variant>

namespace canfw {

enum class InitError : std::uint8_t {
    device_not_ready,
    rx_filter_install_failed,
    can_start_failed,
    already_started,
};


template <typename Db>
struct TxScheduleSlot {
    bool enabled{};
    std::uint32_t period_ms{};
    std::uint32_t last_tx_ms{};
};

template <typename Db>
class TxScheduler {
public:
    using MessageId = typename Db::MessageId;

    std::array<TxScheduleSlot<Db>, Db::kMessageCount> slots{};
    std::array<MessageId, Db::kMessageCount> active_ids{};
    std::size_t active_count{0};

    void enable(MessageId id, std::uint32_t period_ms) {
        auto& s = slots[Db::to_index(id)];
        if (!s.enabled) {
            s.enabled = true;
            s.period_ms = period_ms;
            s.last_tx_ms = 0;
            active_ids[active_count++] = id;
        } else {
            s.period_ms = period_ms;
        }
    }

    void disable(MessageId id) {
        auto& s = slots[Db::to_index(id)];
        if (!s.enabled) {
            return;
        }

        s.enabled = false;

        // TODO :: check on the validity of this action
        // after doing the swap we would need to go down the  rest
        // of the array and shift all the stuff over. 
        for (std::size_t i = 0; i < active_count; ++i) {
            if (active_ids[i] == id) {
                active_ids[i] = active_ids[active_count - 1];
                --active_count;
                break;
            }
        }
    }
};

template <typename Hooks, typename Msg, typename Db>
concept HasOnRxMessage =
    requires(Hooks& h, const Msg& msg, typename Db::ValueStore& store, std::uint32_t now_ms) {
        { h.on_rx_message(msg, store, now_ms) };
    };

template <typename Hooks, typename Msg, typename Db>
static void dispatch_on_rx(Hooks& hooks,
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
    requires(Hooks& h, Msg& msg, typename Db::ValueStore& store, std::uint32_t now_ms){
        { h.on_before_send(msg, store, now_ms)};
    };

template <typename Hooks, typename Msg, typename Db>
static void dispatch_before_send(Hooks& hooks, Msg& msg, typename Db::ValueStore& tx_store, std::uint32_t now_ms)
{
    if constexpr (HasBeforeSend<Hooks, Msg, Db>){
        hooks.on_before_send(msg, tx_store, now_ms);
    }
}



template <typename Db>
concept HasMessageIdOfTemplate = requires {
    Db::template message_id_of<typename Db::MessageVariant>();
};

template <typename Db>
concept HasMessageIdOfValue = requires(const typename Db::MessageVariant& mv) {
    { Db::message_id_of(mv) } -> std::same_as<typename Db::MessageId>;
};

template <typename Db, typename Msg>
static auto db_message_id_of(const Msg& msg) -> typename Db::MessageId
{
    using M = std::decay_t<Msg>;
    return M::id; 

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

    static constexpr std::size_t RxQueueDepth = 64;
    static constexpr std::size_t TxQueueDepth = 16;
    static constexpr std::size_t ThreadStackSize = 8192;
    static constexpr int ThreadPriority = 5;

    Snapshot snapshot_scratch_{};

    static auto create(const device* can_device, Hooks hooks = {}, bool extended_id = false)
        -> std::expected<CanActiveObject*, InitError>
    {
        if (can_device == nullptr || !device_is_ready(can_device)) {
            return std::unexpected{InitError::device_not_ready};
        }

        static CanActiveObject ao{can_device, std::move(hooks), extended_id};

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

        int rc = k_msgq_put(&tx_cmd_msgq_, &cmd, timeout);
        return rc;
    }

    const ValueStore& rx_store() const { return rx_store_; }
    ValueStore get_rx_store_copy()  { return this->rx_store_; }
    const ValueStore& tx_store() const { return tx_store_; }

    [[nodiscard]] std::uint32_t decode_failures() const { return decode_failures_; }
    [[nodiscard]] std::uint32_t tx_build_failures() const { return tx_build_failures_; }
    [[nodiscard]] std::uint32_t tx_encode_failures() const { return tx_encode_failures_; }
    [[nodiscard]] std::uint32_t tx_validation_failures() const { return tx_validation_failures_; }

    void run_forever() {
        while (true) {
            printk("AO stack size = %zu\n", K_KERNEL_STACK_SIZEOF(thread_stack_));
            const std::uint32_t now_ms = k_uptime_get_32();
            const k_timeout_t timeout = time_until_next_due_tx(now_ms);

            for (auto& ev : events_) {
                ev.state = K_POLL_STATE_NOT_READY;
            }

            const int rc = k_poll(events_.data(), events_.size(), timeout);
            
            const std::uint32_t wake_ms = k_uptime_get_32();

            if (rc == 0) {
                if (events_[0].state == K_POLL_STATE_MSGQ_DATA_AVAILABLE) {
                    drain_rx(wake_ms);
                }
                if (events_[1].state == K_POLL_STATE_MSGQ_DATA_AVAILABLE) {
                    drain_tx_commands(wake_ms);
                }
            }

            run_due_tx(wake_ms);
        }
    }

    Endpoint endpoint() {
    return Endpoint{&tx_cmd_msgq_};
    }

    Endpoint endpoint() const {
        return Endpoint{const_cast<k_msgq*>(&tx_cmd_msgq_)};
    }

private:
    explicit CanActiveObject(const device* can_device, Hooks hooks, bool extended_id)
        : can_bus_{can_device}, hooks_{std::move(hooks)}, extended_id_{extended_id}
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
    }

    auto start() -> std::expected<void, InitError> {
        const can_filter filter = make_rx_filter(extended_id_);

        rx_filter_id_ = can_add_rx_filter_msgq(can_bus_, &rx_msgq_, &filter);
        if (rx_filter_id_ < 0) {
            return std::unexpected{InitError::rx_filter_install_failed};
        }

        if (const int rc = can_start(can_bus_); rc != 0) {
            return std::unexpected{InitError::can_start_failed};
        }

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

    static constexpr can_filter make_rx_filter(bool extended_id) {
        can_filter filter{};
        filter.flags = (extended_id) ? CAN_FILTER_IDE : 0U;
        filter.id = 0U;
        filter.mask = 0U;
        return filter;
    }

    k_timeout_t time_until_next_due_tx(std::uint32_t now_ms) const {
        bool found = false;
        std::uint32_t min_wait_ms = UINT32_MAX;

        for (std::size_t i = 0; i < tx_scheduler_.active_count; ++i) {
            const auto id = tx_scheduler_.active_ids[i];
            const auto& slot = tx_scheduler_.slots[Db::to_index(id)];

            if (!slot.enabled || slot.period_ms == 0U) {
                continue;
            }

            const std::uint32_t elapsed = now_ms - slot.last_tx_ms;
            const std::uint32_t wait_ms =
                (elapsed >= slot.period_ms) ? 0U : (slot.period_ms - elapsed);

            if (!found || wait_ms < min_wait_ms) {
                found = true;
                min_wait_ms = wait_ms;
            }
        }

        return found ? K_MSEC(min_wait_ms) : K_FOREVER;
    }

    void drain_rx(std::uint32_t now_ms) {
        can_frame frame{};

        while (k_msgq_get(&rx_msgq_, &frame, K_NO_WAIT) == 0) {
            auto decoded = Db::decode(frame.id, frame.data, frame.dlc);
            if (!decoded) {
                ++decode_failures_;
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

        while (k_msgq_get(&tx_cmd_msgq_, &cmd, K_NO_WAIT) == 0) {
            std::visit([&](const auto& c) {
                handle_tx_command(c, now_ms);
            }, cmd);
        }
    }

    void handle_tx_command(const typename TxCommand<Db>::SendMessage& cmd, std::uint32_t now_ms) {
        std::visit([&](const auto& msg) {
            Db::apply_to_store(tx_store_, msg, now_ms);
            const auto id = db_message_id_of<Db>(msg);
            handle_message_policy(id, cmd.policy, cmd.period_ms_override, now_ms);
        }, cmd.message);
    }

    void handle_tx_command(const typename TxCommand<Db>::UpdateSignal& cmd, std::uint32_t now_ms) {
        auto res = Db::set_signal_physical(tx_store_, cmd.signal_id, cmd.value, now_ms);
        if (!res) {
            ++tx_build_failures_;
            return;
        }

        const auto parent = Db::parent_message_id(cmd.signal_id);
        if (cmd.trigger_parent_send) {
            (void)send_one(parent, now_ms);
        }
    }

    void handle_tx_command(const typename TxCommand<Db>::DisableMessage& cmd, std::uint32_t) {
        tx_scheduler_.disable(cmd.message_id);
    }

    void handle_tx_command(const typename TxCommand<Db>::RequestSnapshot& cmd,
                       std::uint32_t now_ms)
    {
        if (cmd.reply_q == nullptr) {
            return;
        }

        snapshot_scratch.store = rx_store_;
        snapshot_scratch.valid = true;
        snapshot_scratch_.timestamp_ms = now_ms;

        (void)k_msgq_put(cmd.reply_q, &snapshot_scratch_, K_NO_WAIT);
    }

    void handle_message_policy(MessageId id,
                               TxPolicy policy,
                               std::uint32_t period_override,
                               std::uint32_t now_ms)
    {
        switch (policy) {
        case TxPolicy::send_once:
            (void)send_one(id, now_ms);
            break;
        case TxPolicy::periodic_enable: {
            auto period = period_override ? period_override : Db::message_cycle_time_ms(id);
            tx_scheduler_.enable(id, period);
            break;
        }
        case TxPolicy::periodic_disable:
            tx_scheduler_.disable(id);
            break;
        }
    }

    void run_due_tx(std::uint32_t now_ms) {
    for (std::size_t i = 0; i < tx_scheduler_.active_count; ++i) {
        const auto id = tx_scheduler_.active_ids[i];
        auto& slot = tx_scheduler_.slots[Db::to_index(id)];

        if (!slot.enabled || slot.period_ms == 0U) {
            continue;
        }

        if ((now_ms - slot.last_tx_ms) < slot.period_ms) {
            continue;
        }

        const int rc = send_one(id, now_ms);
        slot.last_tx_ms = now_ms;

        (void)rc;
    }
}

    int send_one(MessageId id, std::uint32_t now_ms) {
        auto built = Db::build_message_from_store(id, tx_store_);
        if (!built) {
            ++tx_build_failures_;
            return -EINVAL;
        }

        can_frame frame{};
        const auto& meta = Db::message_meta(id);

        frame.id = meta.frame_id;
        frame.flags = meta.is_extended ? CAN_FRAME_IDE : 0U;

        auto encoded = std::visit(
            [&](auto& msg) -> std::expected<std::uint8_t, typename Db::EncodeError> {
                using Msg = std::decay_t<decltype(msg)>;

                dispatch_before_send<Hooks, Msg, Db>(hooks_, msg, tx_store_, now_ms);

                auto validated = Db::validate_message(msg);
                if (!validated) {
                    ++tx_validation_failures_;
                    printk("validation failed for msg idx=%u signal idx=%u err=%d\n",
                        static_cast<unsigned>(Db::to_index(id)),
                        static_cast<unsigned>(Db::to_index(validated.error().signal_id)),
                        static_cast<int>(validated.error().error));
                    return std::unexpected(Db::EncodeError::value_out_of_range);
                }

                return Db::encode(msg, frame.data, sizeof(frame.data));
            },
            *built
        );

        if (!encoded) {
            ++tx_encode_failures_;
            return -EINVAL;
        }

        frame.dlc = *encoded;
        return can_send(can_bus_, &frame, K_NO_WAIT, nullptr, nullptr);
    }

private:
    const device* can_bus_{nullptr};
    Hooks hooks_{};
    bool started_{false};
    bool extended_id_;

    ValueStore rx_store_{};
    ValueStore tx_store_{};

    k_msgq rx_msgq_{};
    alignas(can_frame) std::array<can_frame, RxQueueDepth> rx_queue_storage_{};

    k_msgq tx_cmd_msgq_{};
    alignas(Command) std::array<Command, TxQueueDepth> tx_cmd_storage_{};

    std::array<k_poll_event, 2> events_{};
    TxScheduler<Db> tx_scheduler_{};

    K_KERNEL_STACK_MEMBER(thread_stack_, ThreadStackSize);
    k_thread thread_{};

    int rx_filter_id_{-1};
    std::uint32_t decode_failures_{0};
    std::uint32_t tx_build_failures_{0};
    std::uint32_t tx_encode_failures_{0};
    std::uint32_t tx_validation_failures_{0};

};

} // namespace canfw
