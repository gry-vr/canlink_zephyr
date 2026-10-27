#pragma once

#include <array>
#include <cstdint>

#include <zephyr/sys/printk.h>

#include "duramax_db.hpp"

struct DuramaxHooks {
    // These hooks execute on the CAN active object's thread, inside
    // drain_rx() / send_one(). Anything slow here (printk spin-polls the
    // UART at ~87 us per character) is jitter injected directly into the
    // 10 ms TSC1 schedule, so debug prints are rate-limited to 1 Hz.
    static constexpr std::uint32_t kPrintPeriodMs = 1000;

    template <typename Msg>
    void on_rx_message(const Msg&, duramax::DuramaxDb::ValueStore&, std::uint32_t) {
        // default no-op
    }

    void on_rx_message(const duramax::Eec1ElectronicEngineControl1&,
                       duramax::DuramaxDb::ValueStore& rx_store,
                       std::uint32_t now_ms)
    {
        // EEC1 broadcasts every 10-20 ms on the engine bus; printing each
        // one would consume most of the AO thread's time budget.
        if (now_ms - last_rpm_print_ms_ < kPrintPeriodMs) {
            return;
        }
        last_rpm_print_ms_ = now_ms;

        constexpr auto rpm_sid =
            duramax::SignalId::eec1_electronic_engine_control_1__engine_speed;

        //if (auto rpm = rx_store.template get<rpm_sid>(); rpm) {
        //    printk("RPM = %d @ %u ms\n", static_cast<int>(*rpm), now_ms);
        //}
    }

    void on_rx_message(const duramax::Et1EngineTemperature1&,
                       duramax::DuramaxDb::ValueStore& rx_store,
                       std::uint32_t now_ms)
    {
        if (now_ms - last_coolant_print_ms_ < kPrintPeriodMs) {
            return;
        }
        last_coolant_print_ms_ = now_ms;

        constexpr auto coolant_sid =
            duramax::SignalId::et1_engine_temperature_1__engcoolanttemp;

        //if (auto temp_c = rx_store.template get<coolant_sid>(); temp_c) {
        //    printk("Coolant = %d C @ %u ms\n", static_cast<int>(*temp_c), now_ms);
        //}
    }

    template <typename Msg, typename Store>
    void on_before_send(Msg&, Store&, std::uint32_t) {}

    // GM TSC1 rolling counter + checksum.
    //
    // The counter wrap is derived from the generated DBC metadata rather
    // than hardcoded: the signal occupies a 4-bit field, but the DBC
    // declares maximum = 7, and validate_message() enforces that. A
    // hardcoded "% 16" here put counters 8..15 on the wire attempt, every
    // one of which validation rejected -- producing the 8-frames-then-90-ms
    // burst pattern on the bus. Deriving the modulus from signal_traits
    // makes the hook and the validator agree by construction: if the DBC
    // changes, both move together.
    using Tsc1CounterTraits =
        duramax::signal_traits<duramax::SignalId::tsc1_31__messagecounter>;
    static_assert(Tsc1CounterTraits::has_maximum,
                  "TSC1 MessageCounter must declare a DBC maximum to derive its wrap");
    static constexpr std::uint8_t kTsc1CounterWrap =
        static_cast<std::uint8_t>(Tsc1CounterTraits::maximum) + 1U;  // today: 8
    static_assert(kTsc1CounterWrap > 0U && kTsc1CounterWrap <= 16U,
                  "TSC1 MessageCounter wrap must fit its 4-bit field");

    // The checksum covers data bytes 0..6 plus the new counter (ARC) plus
    // the four CAN ID bytes; counter and checksum both live in byte 7,
    // which the sum correctly excludes. send_one() runs this hook BEFORE
    // validate/encode, so the frame that reaches the bus carries the
    // freshly written counter and checksum.
    void on_before_send(duramax::Tsc131& msg,
                        duramax::DuramaxDb::ValueStore&,
                        std::uint32_t)
    {
        std::array<std::uint8_t, 8> encoded_msg{};
        auto could_be = duramax::Codec::encode(msg, encoded_msg.data(), encoded_msg.size());
        if (!could_be) {
            return;
        }

        auto calc_checksum = [](std::uint32_t id, const std::uint8_t* data,
                                std::uint8_t arc) -> std::uint8_t {
            std::uint32_t sum = 0x00;

            // Sum up the first 7 bytes of the message
            for (int i = 0; i < 7; i++) {
                sum += data[i];
            }

            // Add ARC (lower 4 bits), and each byte of the ID
            sum += (arc & 0x0F);
            sum += static_cast<std::uint8_t>(id);
            sum += static_cast<std::uint8_t>(id >> 8);
            sum += static_cast<std::uint8_t>(id >> 16);
            sum += static_cast<std::uint8_t>(id >> 24);

            // Compute checksum (3 bits)
            return (((sum >> 6) & 0x03) + (sum >> 3) + sum) & 0x07;
        };

        const std::uint32_t tsc1_31_frame_id = duramax::message_meta(msg.id).frame_id;

        msg.messagecounter = tsc1_counter_;
        msg.messagechecksum = calc_checksum(tsc1_31_frame_id,
                                            encoded_msg.data(),
                                            tsc1_counter_);

        tsc1_counter_ = static_cast<std::uint8_t>((tsc1_counter_ + 1U) % kTsc1CounterWrap);
    }

private:
    // Hook state lives in the instance (the AO owns its Hooks by value),
    // not in function-local statics: statics are shared across all
    // instances and invisible to unit tests.
    std::uint8_t tsc1_counter_{0};
    std::uint32_t last_rpm_print_ms_{0};
    std::uint32_t last_coolant_print_ms_{0};
};
