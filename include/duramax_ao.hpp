#pragma once

#include <zephyr/device.h>
#include <zephyr/drivers/can.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include <array>
#include <cstdint>
#include <expected>
#include <memory>
#include <variant>

#include "duramax_build.hpp"
#include "duramax_choices.hpp"
#include "duramax_codec.hpp"
#include "duramax_ids.hpp"
#include "duramax_metadata.hpp"
#include "duramax_store.hpp"
#include "duramax_types.hpp"

enum class InitError : std::uint8_t {
    device_not_ready,
    rx_filter_install_failed,
    can_start_failed,
};

enum class TxPolicy : std::uint8_t {
    send_once,
    periodic_enable,
    periodic_disable,
};

struct TxCommand {
    duramax::MessageVariant message;
    TxPolicy policy{TxPolicy::periodic_enable};
    std::uint32_t period_ms_override{0};
};

struct TxScheduleSlot {
    bool enabled{};
    std::uint32_t period_ms{};
    std::uint32_t last_tx_ms{};
};

class TxScheduler {
public:
    std::array<TxScheduleSlot, duramax::kMessageCount> slots{};
    std::array<duramax::MessageId, duramax::kMessageCount> active_ids{};
    std::size_t active_count{0};

    void enable(duramax::MessageId id, std::uint32_t period_ms) {
        auto& s = slots[duramax::to_index(id)];
        if (!s.enabled) {
            s.enabled = true;
            s.period_ms = period_ms;
            s.last_tx_ms = 0;
            active_ids[active_count++] = id;
        } else {
            s.period_ms = period_ms;
        }
    }

    void disable(duramax::MessageId id) {
        auto& s = slots[duramax::to_index(id)];
        if (!s.enabled) {
            return;
        }

        s.enabled = false;

        for (std::size_t i = 0; i < active_count; ++i) {
            if (active_ids[i] == id) {
                active_ids[i] = active_ids[active_count - 1];
                --active_count;
                break;
            }
        }
    }
};

class DuramaxCanAo {
public:
    static constexpr std::size_t RxQueueDepth = 64;
    static constexpr std::size_t TxQueueDepth = 16;
    static constexpr std::size_t ThreadStackSize = 3072;
    static constexpr int ThreadPriority = 5;

    static auto create(const struct device* can_device)
        -> std::expected<std::unique_ptr<DuramaxCanAo>, InitError>
    {
        if (can_device == nullptr || !device_is_ready(can_device)) {
            return std::unexpected{InitError::device_not_ready};
        }

        auto ao = std::unique_ptr<DuramaxCanAo>(new DuramaxCanAo{can_device});

        if (auto started = ao->start(); !started) {
            return std::unexpected{started.error()};
        }

        return ao;
    }

    DuramaxCanAo(const DuramaxCanAo&) = delete;
    auto operator=(const DuramaxCanAo&) -> DuramaxCanAo& = delete;
    DuramaxCanAo(DuramaxCanAo&&) = delete;
    auto operator=(DuramaxCanAo&&) -> DuramaxCanAo& = delete;

    [[nodiscard]] auto rx_store() const -> const duramax::ValueStore& {
        return rx_store_;
    }

    [[nodiscard]] auto tx_store() const -> const duramax::ValueStore& {
        return tx_store_;
    }

    auto post_tx(const TxCommand& cmd, k_timeout_t timeout = K_NO_WAIT) -> int {
        return k_msgq_put(&tx_cmd_msgq_, &cmd, timeout);
    }

    void run_forever() {
        printk("thread started!");
        while (true) {
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
            } else if (rc != -EAGAIN) {
                // optional logging/counter
            }

            run_due_tx(wake_ms);
        }
    }

private:
    explicit DuramaxCanAo(const struct device* can_device)
        : can_bus_{can_device}
    {
        k_msgq_init(
            &rx_msgq_,
            reinterpret_cast<char*>(rx_queue_storage_.data()),
            sizeof(can_frame),
            RxQueueDepth);

        k_msgq_init(
            &tx_cmd_msgq_,
            reinterpret_cast<char*>(tx_cmd_storage_.data()),
            sizeof(TxCommand),
            TxQueueDepth);

        k_poll_event_init(&events_[0],
            K_POLL_TYPE_MSGQ_DATA_AVAILABLE,
            K_POLL_MODE_NOTIFY_ONLY,
            &rx_msgq_
            );
        events_[0].tag = 0;


        k_poll_event_init(&events_[1],
            K_POLL_TYPE_MSGQ_DATA_AVAILABLE,
            K_POLL_MODE_NOTIFY_ONLY,
            &tx_cmd_msgq_
            );
        events_[1].tag = 0;
    }

    auto start() -> std::expected<void, InitError> {
        const can_filter filter = make_rx_filter();

        rx_filter_id_ = can_add_rx_filter_msgq(can_bus_, &rx_msgq_, &filter);
        if (rx_filter_id_ < 0) {
            return std::unexpected{InitError::rx_filter_install_failed};
        }

        if (const int rc = can_start(can_bus_); rc != 0) {
            return std::unexpected{InitError::can_start_failed};
        }

        k_thread_create(
            &thread_,
            thread_stack_,
            K_KERNEL_STACK_SIZEOF(thread_stack_),
            &DuramaxCanAo::thread_entry_,
            this,
            nullptr,
            nullptr,
            ThreadPriority,
            0,
            K_NO_WAIT);

        k_thread_name_set(&thread_, "duramax_can_ao");
        return {};
    }

    static void thread_entry_(void* p1, void*, void*) {
        static_cast<DuramaxCanAo*>(p1)->run_forever();
    }

    static constexpr auto make_rx_filter() -> can_filter {
        can_filter filter{};
        filter.flags = CAN_FILTER_IDE;
        filter.id = 0U;
        filter.mask = 0U;
        return filter;
    }

    auto time_until_next_due_tx(std::uint32_t now_ms) const -> k_timeout_t {
        bool found = false;
        std::uint32_t min_wait_ms = UINT32_MAX;

        for (std::size_t i = 0; i < tx_scheduler_.active_count; ++i) {
            const auto id = tx_scheduler_.active_ids[i];
            const auto& slot = tx_scheduler_.slots[duramax::to_index(id)];

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
            auto decoded = duramax::Codec::decode(frame.id, frame.data, frame.dlc);
            if (!decoded) {
                ++decode_failures_;
                continue;
            }

            std::visit([&](const auto& msg) {
                duramax::update_from(rx_store_, msg, now_ms);
                on_rx_message(msg, now_ms);
            }, *decoded);
        }
    }

    void drain_tx_commands(std::uint32_t now_ms) {
        TxCommand cmd{};

        while (k_msgq_get(&tx_cmd_msgq_, &cmd, K_NO_WAIT) == 0) {
            std::visit([&](const auto& msg) {
                const auto id = duramax::message_id_of(msg);
                duramax::apply_to_store(tx_store_, msg, now_ms);

                switch (cmd.policy) {
                case TxPolicy::send_once:
                    (void)send_one(id, now_ms);
                    break;

                case TxPolicy::periodic_enable: {
                    auto period = cmd.period_ms_override;
                    if (period == 0U) {
                        period = duramax::message_cycle_time_ms(id);
                    }
                    tx_scheduler_.enable(id, period);
                    break;
                }

                case TxPolicy::periodic_disable:
                    tx_scheduler_.disable(id);
                    break;
                }
            }, cmd.message);
        }
    }

    void run_due_tx(std::uint32_t now_ms) {
        printk("gonna send\n");
        for (std::size_t i = 0; i < tx_scheduler_.active_count; ++i) {
            const auto id = tx_scheduler_.active_ids[i];
            auto& slot = tx_scheduler_.slots[duramax::to_index(id)];

            if (!slot.enabled || slot.period_ms == 0U) {
                continue;
            }

            if ((now_ms - slot.last_tx_ms) < slot.period_ms) {
                continue;
            }

            if (send_one(id, now_ms) == 0) {
                slot.last_tx_ms = now_ms;
            }
        }
    }

    auto send_one(duramax::MessageId id, std::uint32_t now_ms) -> int {
        auto built = duramax::build_message_from_store(id, tx_store_);
        if (!built) {
            ++tx_build_failures_;
            return -EINVAL;
        }

        can_frame frame{};
        frame.id = duramax::message_meta(id).frame_id;
        frame.flags = duramax::message_meta(id).is_extended ? CAN_FRAME_IDE : 0U;

        auto encoded = duramax::Codec::encode(*built, frame.data, sizeof(frame.data));
        if (!encoded) {
            ++tx_encode_failures_;
            return -EINVAL;
        }

        frame.dlc = *encoded;
        return can_send(can_bus_, &frame, K_NO_WAIT, nullptr, nullptr);
    }

private:
    template <typename Msg>
    void on_rx_message(const Msg&, std::uint32_t) {
        // default no-op
    }

    void on_rx_message(const duramax::Eec1ElectronicEngineControl1&, std::uint32_t now_ms) {
        constexpr auto rpm_sid =
            duramax::SignalId::eec1_electronic_engine_control_1__engine_speed;

        if (auto rpm = rx_store_.try_get_f64(rpm_sid); rpm) {
            printk("RPM = %d @ %u ms\n", static_cast<int>(*rpm), now_ms);
        }
    }

    void on_rx_message(const duramax::Et1EngineTemperature1&, std::uint32_t now_ms) {
        constexpr auto coolant_sid =
            duramax::SignalId::et1_engine_temperature_1__engcoolanttemp;

        if (auto temp_c = rx_store_.try_get_f64(coolant_sid); temp_c) {
            printk("Coolant = %d C @ %u ms\n", static_cast<int>(*temp_c), now_ms);
        }
    }

private:
    const struct device* can_bus_{nullptr};

    duramax::ValueStore rx_store_{};
    duramax::ValueStore tx_store_{};

    k_msgq rx_msgq_{};
    alignas(can_frame) std::array<can_frame, RxQueueDepth> rx_queue_storage_{};

    k_msgq tx_cmd_msgq_{};
    alignas(TxCommand) std::array<TxCommand, TxQueueDepth> tx_cmd_storage_{};

    std::array<k_poll_event, 2> events_{};

    TxScheduler tx_scheduler_{};

    K_KERNEL_STACK_MEMBER(thread_stack_, ThreadStackSize);
    k_thread thread_{};

    int rx_filter_id_{-1};
    std::uint32_t decode_failures_{0};
    std::uint32_t tx_build_failures_{0};
    std::uint32_t tx_encode_failures_{0};
};