#pragma once

#include <cstdint>

#include <zephyr/sys/printk.h>

#include "duramax_db.hpp"

enum class ByteOrder : unsigned char; // harmless forward if project defines another one elsewhere

struct DuramaxHooks {
    template <typename Msg>
    void on_rx_message(const Msg&, duramax::DuramaxDb::ValueStore&, std::uint32_t) {
        // default no-op
    }

    void on_rx_message(const duramax::Eec1ElectronicEngineControl1&,
                       duramax::DuramaxDb::ValueStore& rx_store,
                       std::uint32_t now_ms)
    {
        constexpr auto rpm_sid =
            duramax::SignalId::eec1_electronic_engine_control_1__engine_speed;

        if (auto rpm = rx_store.template get<rpm_sid>(); rpm) {
            printk("RPM = %d @ %u ms\n", static_cast<int>(*rpm), now_ms);
        }
    }

    void on_rx_message(const duramax::Et1EngineTemperature1&,
                       duramax::DuramaxDb::ValueStore& rx_store,
                       std::uint32_t now_ms)
    {
        constexpr auto coolant_sid =
            duramax::SignalId::et1_engine_temperature_1__engcoolanttemp;

        if (auto temp_c = rx_store.template get<coolant_sid>(); temp_c) {
            printk("Coolant = %d C @ %u ms\n", static_cast<int>(*temp_c), now_ms);
        }
    }
};
