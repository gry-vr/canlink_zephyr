#pragma once

#include <cstddef>
#include <cstdint>

namespace reacher {

enum class ByteOrder : std::uint8_t {
    little_endian,
    big_endian
};

enum class SignalType : std::uint8_t {
    u8,
    u16,
    i16,
    u32,
    f64,
    boolean
};

enum class MessageId : std::uint16_t {
    reacher_ctrl = 0,
    reacher_engine_feedback = 1,
    export_0 = 2,
    export_3 = 3,
    export_8 = 4,
    export_b = 5,
    servo_batt = 6,
    count
};

enum class SignalId : std::uint16_t {
    reacher_ctrl__eng_on = 0,
    reacher_ctrl__start = 1,
    reacher_ctrl__arm = 2,
    reacher_ctrl__test = 3,
    reacher_ctrl__aux_1 = 4,
    reacher_ctrl__throttle_rpm = 5,
    reacher_ctrl__aux_2 = 6,
    reacher_engine_feedback__ecu_on = 7,
    reacher_engine_feedback__f_pump_on = 8,
    reacher_engine_feedback__st_solenoid_on = 9,
    export_0__eng_speed = 10,
    export_0__actual_throttle = 11,
    export_0__manifold_press = 12,
    export_3__fuel_rail_pressure = 13,
    export_8__battery_bus_voltage = 14,
    export_b__coolant_temp = 15,
    export_b__oil_temp = 16,
    export_b__oil_pressure = 17,
    export_b__exhaust_gas_temp = 18,
    servo_batt__servo_bus_voltage = 19,
    count
};

constexpr auto to_index(MessageId id) -> std::size_t {
    return static_cast<std::size_t>(id);
}

constexpr auto to_index(SignalId id) -> std::size_t {
    return static_cast<std::size_t>(id);
}

inline constexpr std::size_t kMessageCount =
    static_cast<std::size_t>(MessageId::count);

inline constexpr std::size_t kSignalCount =
    static_cast<std::size_t>(SignalId::count);

} // namespace reacher