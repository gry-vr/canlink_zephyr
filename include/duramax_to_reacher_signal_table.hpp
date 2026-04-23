#pragma once

#include "signal_table.hpp"
#include <zephyr/sys/printk.h>

struct identity_u8 {
    constexpr auto operator()(std::uint8_t v) const -> std::uint8_t { return v; }
};

struct identity_u16 {
    constexpr auto operator()(std::uint16_t v) const -> std::uint16_t { return v; }
};

struct identity_i16 {
    constexpr auto operator()(std::int16_t v) const -> std::int16_t { return v; }
};

struct identity_f64 {
    constexpr auto operator()(double v) const -> double { return v; }
};

struct kpa_to_psi {
    constexpr auto operator()(double v) const -> double {
        return v * 0.1450377377;
    }
};

struct kpa_to_millibar {
    constexpr auto operator()(double v) const -> double {
        return v * 10;
    }
};

struct megapascal_to_bar {
    constexpr auto operator()(double v) const -> double {
        return v * 10;
    }
};

struct c_to_f {
    constexpr auto operator()(double v) const -> double {
        return v * 9.0 / 5.0 + 32.0;
    }
};

struct int_to_percent {
    constexpr auto operator()(double v) const -> double {
        return v / 100;
    }
};

template <typename DuramaxDb, typename ReacherDb>
struct DuramaxToReacherTranslations
{
    using type = std::tuple<
        SignalTranslation<
            DuramaxDb,
            ReacherDb,
            DuramaxDb::SignalId::eec1_electronic_engine_control_1__engine_speed,
            ReacherDb::SignalId::export_0__eng_speed,
            identity_f64,
            false,
            OverflowPolicy::reject
        >,
        SignalTranslation<
            DuramaxDb,
            ReacherDb,
            DuramaxDb::SignalId::eec2_electronic_engine_control_2__remoteaccelpedalpos,
            ReacherDb::SignalId::export_0__actual_throttle,
            identity_f64,
            false,
            OverflowPolicy::reject
        >,
        SignalTranslation<
            DuramaxDb,
            ReacherDb,
            DuramaxDb::SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1press,
            ReacherDb::SignalId::export_0__manifold_press,
            kpa_to_millibar,
            false,
            OverflowPolicy::reject
        >,

        SignalTranslation<
            DuramaxDb,
            ReacherDb,
            DuramaxDb::SignalId::eec9_electronic_engine_control_9__commanded_fuel_rail_pressure,
            ReacherDb::SignalId::export_3__fuel_rail_pressure,
            megapascal_to_bar,
            false,
            OverflowPolicy::reject
        >,

        SignalTranslation<
            DuramaxDb,
            ReacherDb,
            DuramaxDb::SignalId::vep1_vehicle_electrical_power_1__keyswitch_battery_potential_158,
            ReacherDb::SignalId::export_8__battery_bus_voltage,
            identity_f64,
            false,
            OverflowPolicy::reject
        >,

        SignalTranslation<
            DuramaxDb,
            ReacherDb,
            DuramaxDb::SignalId::et1_engine_temperature_1__engcoolanttemp,
            ReacherDb::SignalId::export_b__coolant_temp,
            c_to_f,
            false,
            OverflowPolicy::reject
        >,
        SignalTranslation<
            DuramaxDb,
            ReacherDb,
            DuramaxDb::SignalId::et1_engine_temperature_1__engoiltemp1,
            ReacherDb::SignalId::export_b__oil_temp,
            c_to_f,
            false,
            OverflowPolicy::reject
        >,
        SignalTranslation<
            DuramaxDb,
            ReacherDb,
            DuramaxDb::SignalId::efl_p1_eng_fluid_level_press_1__engoilpress,
            ReacherDb::SignalId::export_b__oil_pressure,
            kpa_to_psi,
            false,
            OverflowPolicy::reject
        >,
        SignalTranslation<
            DuramaxDb,
            ReacherDb,
            DuramaxDb::SignalId::tci5_turbocharger_information_5__engine_turbocharger_1_turbine_ou,
            ReacherDb::SignalId::export_b__exhaust_gas_temp,
            c_to_f,
            false,
            OverflowPolicy::reject
        >
    >;
};


/*

EEC1
 - eng_speed 

EEC2
 - actualthrottle

EEC9
 - commanded fuel rail pressure 

ET1
 - eng coolant temp 
 - eng oil temp 1

EFLp1
 - eng oil press

TCI5
 - engine turbocharger 1 turbine ou

*/

/* SIGNAL MAPPING

EEC1::eng_speed -> Export_0 :: eng_speed
EEC2:: actual_throttle -> Export_0 :: actual_throttle
IC1::engintakemanifold1press -> Export_0 :: manifold_press

EEC9::commandedfuelrailPress -> Export_3 :: fuel_rail_pressure

ET1

*/