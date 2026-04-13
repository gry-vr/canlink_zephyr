#pragma once

#include <zephyr/kernel.h>
#include <zephyr/drivers/can.h>
#include <zephyr/device.h>
#include <zephyr/sys/printk.h>

#include <array>
#include <cstdint>
#include <expected>
#include <memory>
#include <variant>

#include "duramax_ids.hpp"
#include "duramax_metadata.hpp"
#include "duramax_types.hpp"
#include "duramax_store.hpp"
#include "duramax_choices.hpp"
#include "duramax_codec.hpp"

enum class InitError : std::uint8_t {
    device_not_ready,
    rx_filter_install_failed,
};

class DuramaxRxAo {
public:
    static constexpr std::size_t RxQueueDepth = 64;
    static constexpr std::size_t ThreadStackSize = 2048;
    static constexpr int ThreadPriority = 5;

    static auto create(const struct device* can_device)
        -> std::expected<std::unique_ptr<DuramaxRxAo>, InitError>
    {
        if (can_device == nullptr || !device_is_ready(can_device)) {
            return std::unexpected{InitError::device_not_ready};
        }

        auto ao = std::unique_ptr<DuramaxRxAo>(new DuramaxRxAo{can_device});

        if (auto started = ao->start(); !started) {
            return std::unexpected{started.error()};
        }

        return ao;
    }

    DuramaxRxAo(const DuramaxRxAo&) = delete;
    auto operator=(const DuramaxRxAo&) -> DuramaxRxAo& = delete;
    DuramaxRxAo(DuramaxRxAo&&) = delete;
    auto operator=(DuramaxRxAo&&) -> DuramaxRxAo& = delete;

    [[nodiscard]] auto store() const -> const duramax::ValueStore& {
        return store_;
    }

    [[nodiscard]] auto decode_failures() const -> std::uint32_t {
        return decode_failures_;
    }

    [[nodiscard]] auto filter_id() const -> int {
        return rx_filter_id_;
    }

    void run_forever() {
        while (true) {
            can_frame frame{};

            if (k_msgq_get(&rx_msgq_, &frame, K_FOREVER) != 0) {
                continue;
            }

            const std::uint32_t now_ms = k_uptime_get_32();

            auto decoded = duramax::Codec::decode(frame.id, frame.data, frame.dlc);
            if (!decoded) {
                ++decode_failures_;
                continue;
            }

            std::visit(
                [&](const auto& msg) {
                    duramax::update_from(store_, msg, now_ms);
                    on_message(msg, now_ms);
                },
                *decoded);
        }
    }

private:
    explicit DuramaxRxAo(const struct device* can_device)
        : can_bus_{can_device}
    {
        k_msgq_init(
            &rx_msgq_,
            reinterpret_cast<char*>(rx_queue_storage_.data()),
            sizeof(can_frame),
            RxQueueDepth);
    }

    auto start() -> std::expected<void, InitError> {
        const can_filter filter = make_rx_filter();

        rx_filter_id_ = can_add_rx_filter_msgq(can_bus_, &rx_msgq_, &filter);
        if (rx_filter_id_ < 0) {
            return std::unexpected{InitError::rx_filter_install_failed};
        }

        can_start(can_bus_);

        k_thread_create(
            &thread_,
            thread_stack_,
            K_KERNEL_STACK_SIZEOF(thread_stack_),
            &DuramaxRxAo::thread_entry_,
            this,
            nullptr,
            nullptr,
            ThreadPriority,
            0,
            K_NO_WAIT);

        k_thread_name_set(&thread_, "duramax_rx_ao");
        return {};
    }

    static void thread_entry_(void* p1, void*, void*) {
        auto* self = static_cast<DuramaxRxAo*>(p1);
        self->run_forever();
    }

    static constexpr auto make_rx_filter() -> can_filter {
        can_filter filter{};
        filter.flags = CAN_FILTER_IDE; // all extended 29-bit IDs
        filter.id = 0U;
        filter.mask = 0U;              // accept everything that matches flags
        return filter;
    }

private:
    template <typename Msg>
    void on_message(const Msg&, std::uint32_t) {
        // default no-op
    }

    void on_message(const duramax::Eec1ElectronicEngineControl1&, std::uint32_t now_ms) {
        constexpr auto rpm_sid =
            duramax::SignalId::eec1_electronic_engine_control_1__engine_speed;


            printk("hi...\n");
        if (auto rpm = store_.try_get_f64(rpm_sid); rpm) {
             printk("RPM = %d @ %u ms\n", static_cast<int>(*rpm), now_ms);
        }

        (void)now_ms;
    }

    void on_message(const duramax::Et1EngineTemperature1&, std::uint32_t now_ms) {
        constexpr auto coolant_sid =
            duramax::SignalId::et1_engine_temperature_1__engcoolanttemp;

        if (auto temp_c = store_.try_get_f64(coolant_sid); temp_c) {
             printk("Coolant = %d C @ %u ms\n", static_cast<int>(*temp_c), now_ms);
        }

        (void)now_ms;
    }

private:
    const struct device* can_bus_{nullptr};
    duramax::ValueStore store_{};

    k_msgq rx_msgq_{};
    alignas(can_frame) std::array<can_frame, RxQueueDepth> rx_queue_storage_{};

    K_KERNEL_STACK_MEMBER(thread_stack_, ThreadStackSize);
    k_thread thread_{};

    int rx_filter_id_{-1};
    std::uint32_t decode_failures_{0};
};