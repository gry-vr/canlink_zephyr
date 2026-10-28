#pragma once

#include <array>
#include <cstdint>

#include <zephyr/sys/printk.h>

#include "duramax_db.hpp"
#include "can_commands.hpp"
#include <zephyr/sys/util.h>

struct DuramaxHooks {
    static_assert(IS_ENABLED(CONFIG_CANLINK_THROTTLE_STALE_OVERRIDE_DISABLED),
                  "Only the approved disabled/zero stale fallback is implemented");
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

    bool on_signal_updated(duramax::SignalId id,
                           const duramax::SignalPhysicalValue& value,
                           const canfw::throttle::Source& source, std::uint32_t) {
        if (id != duramax::SignalId::tsc1_31__engrequestedspeed_speedlimit) return true;
        // Match the generated store's f64 variant contract before changing policy
        // state; a type-mismatched update must not bypass set_signal_physical().
        const auto* rpm = std::get_if<double>(&value);
        if (!rpm) { ++throttle_.rejected; return false; }
        return throttle_.accept(*rpm, source);
    }

    void on_before_send(duramax::Tsc131& msg,
                        duramax::DuramaxDb::ValueStore&, std::uint32_t now) {
        output_ = throttle_.evaluate(now, IS_ENABLED(CONFIG_CANLINK_THROTTLE_BAND_MAPPING),
            IS_ENABLED(CONFIG_CANLINK_THROTTLE_STALE_TIMEOUT_ENABLE),
            CONFIG_CANLINK_THROTTLE_STALE_TIMEOUT_MS);
        msg.engrequestedspeed_speedlimit = output_.raw * 0.125;
        // Keep the typed intermediate valid. Legacy NA/reserved bytes are applied
        // only after validation/encoding; checksum is computed over final bytes.
        msg.engoverridectrlmode = output_.enabled ? 1 : 0;
        msg.messagecounter = 0;
        msg.messagechecksum = 0;
    }

    void on_after_encode(const duramax::Tsc131&, std::uint8_t* bytes,
                         std::uint8_t, std::uint32_t) {
        canfw::throttle::finish_frame(bytes, output_, tsc1_counter_);
        // Called only after validation, encoding and TX-context reservation,
        // immediately before can_send. Driver rejection still consumes the ARC.
        tsc1_counter_ = (tsc1_counter_ + 1U) % 8U;
    }
    void on_snapshot(canfw::SnapshotReply<duramax::DuramaxDb>& reply) const {
        reply.rejected_throttle_inputs = throttle_.rejected;
        reply.stale_timeout_events = throttle_.stale_events;
    }

private:
    // Hook state lives in the instance (the AO owns its Hooks by value),
    // not in function-local statics: statics are shared across all
    // instances and invisible to unit tests.
    canfw::throttle::Policy throttle_{};
    canfw::throttle::Output output_{};
    std::uint8_t tsc1_counter_{0};
    std::uint32_t last_rpm_print_ms_{0};
    std::uint32_t last_coolant_print_ms_{0};
};
