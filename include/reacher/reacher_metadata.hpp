#pragma once

#include "reacher_ids.hpp"

#include <array>
#include <cstdint>
#include <span>
#include <string_view>

namespace reacher {

struct MessageMeta {
    MessageId id;
    std::uint32_t frame_id;
    std::uint8_t dlc;
    bool is_extended;
    std::uint32_t cycle_time_ms;
    std::string_view dbc_name;
    std::string_view cpp_name;
    std::uint16_t signal_offset;
    std::uint16_t signal_count;
};

struct SignalMeta {
    SignalId id;
    MessageId message_id;
    std::uint16_t start_bit;
    std::uint8_t bit_length;
    ByteOrder byte_order;
    bool is_signed;
    double scale;
    double offset;
    SignalType type;
    bool has_choices;
    std::string_view dbc_name;
    std::string_view cpp_name;
    std::string_view message_dbc_name;
    std::string_view unit;
    std::string_view choice_enum_name;
};

inline constexpr std::array<MessageMeta, kMessageCount> kMessagesById{ {
    MessageMeta{
        .id = MessageId::reacher_ctrl,
        .frame_id = 0x00000200u,
        .dlc = 8,
        .is_extended = false,
        .cycle_time_ms = 0,
        .dbc_name = "REACHER_CTRL",
        .cpp_name = "reacher_ctrl",
        .signal_offset = 0,
        .signal_count = 7,
    },
    MessageMeta{
        .id = MessageId::reacher_engine_feedback,
        .frame_id = 0x00000202u,
        .dlc = 8,
        .is_extended = false,
        .cycle_time_ms = 0,
        .dbc_name = "REACHER_ENGINE_FEEDBACK",
        .cpp_name = "reacher_engine_feedback",
        .signal_offset = 7,
        .signal_count = 3,
    },
    MessageMeta{
        .id = MessageId::export_0,
        .frame_id = 0x00000300u,
        .dlc = 8,
        .is_extended = false,
        .cycle_time_ms = 0,
        .dbc_name = "EXPORT_0",
        .cpp_name = "export_0",
        .signal_offset = 10,
        .signal_count = 3,
    },
    MessageMeta{
        .id = MessageId::export_3,
        .frame_id = 0x00000303u,
        .dlc = 8,
        .is_extended = false,
        .cycle_time_ms = 0,
        .dbc_name = "EXPORT_3",
        .cpp_name = "export_3",
        .signal_offset = 13,
        .signal_count = 1,
    },
    MessageMeta{
        .id = MessageId::export_8,
        .frame_id = 0x00000308u,
        .dlc = 8,
        .is_extended = false,
        .cycle_time_ms = 0,
        .dbc_name = "EXPORT_8",
        .cpp_name = "export_8",
        .signal_offset = 14,
        .signal_count = 1,
    },
    MessageMeta{
        .id = MessageId::export_b,
        .frame_id = 0x0000030Bu,
        .dlc = 8,
        .is_extended = false,
        .cycle_time_ms = 0,
        .dbc_name = "EXPORT_B",
        .cpp_name = "export_b",
        .signal_offset = 15,
        .signal_count = 4,
    },
    MessageMeta{
        .id = MessageId::servo_batt,
        .frame_id = 0x00000501u,
        .dlc = 8,
        .is_extended = false,
        .cycle_time_ms = 0,
        .dbc_name = "SERVO_BATT",
        .cpp_name = "servo_batt",
        .signal_offset = 19,
        .signal_count = 1,
    },
} };

inline constexpr std::array<SignalMeta, kSignalCount> kSignalsById{ {
    SignalMeta{
        .id = SignalId::reacher_ctrl__eng_on,
        .message_id = MessageId::reacher_ctrl,
        .start_bit = 0,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "eng_on",
        .cpp_name = "eng_on",
        .message_dbc_name = "REACHER_CTRL",
        .unit = "",
        .choice_enum_name = "ReacherCtrlEngOnState",
    },
    SignalMeta{
        .id = SignalId::reacher_ctrl__start,
        .message_id = MessageId::reacher_ctrl,
        .start_bit = 8,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "start",
        .cpp_name = "start",
        .message_dbc_name = "REACHER_CTRL",
        .unit = "",
        .choice_enum_name = "ReacherCtrlStartState",
    },
    SignalMeta{
        .id = SignalId::reacher_ctrl__arm,
        .message_id = MessageId::reacher_ctrl,
        .start_bit = 16,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "arm",
        .cpp_name = "arm",
        .message_dbc_name = "REACHER_CTRL",
        .unit = "",
        .choice_enum_name = "ReacherCtrlArmState",
    },
    SignalMeta{
        .id = SignalId::reacher_ctrl__test,
        .message_id = MessageId::reacher_ctrl,
        .start_bit = 24,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = true,
        .dbc_name = "test",
        .cpp_name = "test",
        .message_dbc_name = "REACHER_CTRL",
        .unit = "",
        .choice_enum_name = "ReacherCtrlTestState",
    },
    SignalMeta{
        .id = SignalId::reacher_ctrl__aux_1,
        .message_id = MessageId::reacher_ctrl,
        .start_bit = 32,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "aux_1",
        .cpp_name = "aux_1",
        .message_dbc_name = "REACHER_CTRL",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::reacher_ctrl__throttle_rpm,
        .message_id = MessageId::reacher_ctrl,
        .start_bit = 40,
        .bit_length = 16,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u16,
        .has_choices = false,
        .dbc_name = "throttle_rpm",
        .cpp_name = "throttle_rpm",
        .message_dbc_name = "REACHER_CTRL",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::reacher_ctrl__aux_2,
        .message_id = MessageId::reacher_ctrl,
        .start_bit = 56,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "aux_2",
        .cpp_name = "aux_2",
        .message_dbc_name = "REACHER_CTRL",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::reacher_engine_feedback__ecu_on,
        .message_id = MessageId::reacher_engine_feedback,
        .start_bit = 8,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "ecu_on",
        .cpp_name = "ecu_on",
        .message_dbc_name = "REACHER_ENGINE_FEEDBACK",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::reacher_engine_feedback__f_pump_on,
        .message_id = MessageId::reacher_engine_feedback,
        .start_bit = 16,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "f_pump_on",
        .cpp_name = "f_pump_on",
        .message_dbc_name = "REACHER_ENGINE_FEEDBACK",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::reacher_engine_feedback__st_solenoid_on,
        .message_id = MessageId::reacher_engine_feedback,
        .start_bit = 24,
        .bit_length = 8,
        .byte_order = ByteOrder::little_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u8,
        .has_choices = false,
        .dbc_name = "st_solenoid_on",
        .cpp_name = "st_solenoid_on",
        .message_dbc_name = "REACHER_ENGINE_FEEDBACK",
        .unit = "",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::export_0__eng_speed,
        .message_id = MessageId::export_0,
        .start_bit = 7,
        .bit_length = 16,
        .byte_order = ByteOrder::big_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u16,
        .has_choices = false,
        .dbc_name = "eng_speed",
        .cpp_name = "eng_speed",
        .message_dbc_name = "EXPORT_0",
        .unit = "rpm",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::export_0__actual_throttle,
        .message_id = MessageId::export_0,
        .start_bit = 23,
        .bit_length = 8,
        .byte_order = ByteOrder::big_endian,
        .is_signed = false,
        .scale = 0.00392156862745,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "actual_throttle",
        .cpp_name = "actual_throttle",
        .message_dbc_name = "EXPORT_0",
        .unit = "n%",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::export_0__manifold_press,
        .message_id = MessageId::export_0,
        .start_bit = 39,
        .bit_length = 16,
        .byte_order = ByteOrder::big_endian,
        .is_signed = false,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::u16,
        .has_choices = false,
        .dbc_name = "manifold_press",
        .cpp_name = "manifold_press",
        .message_dbc_name = "EXPORT_0",
        .unit = "mBar",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::export_3__fuel_rail_pressure,
        .message_id = MessageId::export_3,
        .start_bit = 55,
        .bit_length = 16,
        .byte_order = ByteOrder::big_endian,
        .is_signed = true,
        .scale = 1.0,
        .offset = 0.0,
        .type = SignalType::i16,
        .has_choices = false,
        .dbc_name = "fuel_rail_pressure",
        .cpp_name = "fuel_rail_pressure",
        .message_dbc_name = "EXPORT_3",
        .unit = "Bar",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::export_8__battery_bus_voltage,
        .message_id = MessageId::export_8,
        .start_bit = 7,
        .bit_length = 16,
        .byte_order = ByteOrder::big_endian,
        .is_signed = false,
        .scale = 0.0175953079179,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "battery_bus_voltage",
        .cpp_name = "battery_bus_voltage",
        .message_dbc_name = "EXPORT_8",
        .unit = "0 = 0V, 1023 = 18V",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::export_b__coolant_temp,
        .message_id = MessageId::export_b,
        .start_bit = 7,
        .bit_length = 8,
        .byte_order = ByteOrder::big_endian,
        .is_signed = false,
        .scale = 1.12941176471,
        .offset = 14.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "coolant_temp",
        .cpp_name = "coolant_temp",
        .message_dbc_name = "EXPORT_B",
        .unit = "F",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::export_b__oil_temp,
        .message_id = MessageId::export_b,
        .start_bit = 15,
        .bit_length = 16,
        .byte_order = ByteOrder::big_endian,
        .is_signed = false,
        .scale = 1.8,
        .offset = 32.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "oil_temp",
        .cpp_name = "oil_temp",
        .message_dbc_name = "EXPORT_B",
        .unit = "F",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::export_b__oil_pressure,
        .message_id = MessageId::export_b,
        .start_bit = 39,
        .bit_length = 8,
        .byte_order = ByteOrder::big_endian,
        .is_signed = false,
        .scale = 0.580152,
        .offset = 0.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "oil_pressure",
        .cpp_name = "oil_pressure",
        .message_dbc_name = "EXPORT_B",
        .unit = "PSI",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::export_b__exhaust_gas_temp,
        .message_id = MessageId::export_b,
        .start_bit = 55,
        .bit_length = 16,
        .byte_order = ByteOrder::big_endian,
        .is_signed = false,
        .scale = 1.8,
        .offset = 32.0,
        .type = SignalType::f64,
        .has_choices = false,
        .dbc_name = "exhaust_gas_temp",
        .cpp_name = "exhaust_gas_temp",
        .message_dbc_name = "EXPORT_B",
        .unit = "F",
        .choice_enum_name = "",
    },
    SignalMeta{
        .id = SignalId::servo_batt__servo_bus_voltage,
        .message_id = MessageId::servo_batt,
        .start_bit = 15,
        .bit_length = 16,
        .byte_order = ByteOrder::big_endian,
        .is_signed = false,
        .scale = 100.0,
        .offset = 0.0,
        .type = SignalType::u16,
        .has_choices = false,
        .dbc_name = "servo_bus_voltage",
        .cpp_name = "servo_bus_voltage",
        .message_dbc_name = "SERVO_BATT",
        .unit = "V",
        .choice_enum_name = "",
    },
} };

inline constexpr std::array<SignalId, kSignalCount> kMessageSignalsFlat{ {
    SignalId::reacher_ctrl__eng_on,
    SignalId::reacher_ctrl__start,
    SignalId::reacher_ctrl__arm,
    SignalId::reacher_ctrl__test,
    SignalId::reacher_ctrl__aux_1,
    SignalId::reacher_ctrl__throttle_rpm,
    SignalId::reacher_ctrl__aux_2,
    SignalId::reacher_engine_feedback__ecu_on,
    SignalId::reacher_engine_feedback__f_pump_on,
    SignalId::reacher_engine_feedback__st_solenoid_on,
    SignalId::export_0__eng_speed,
    SignalId::export_0__actual_throttle,
    SignalId::export_0__manifold_press,
    SignalId::export_3__fuel_rail_pressure,
    SignalId::export_8__battery_bus_voltage,
    SignalId::export_b__coolant_temp,
    SignalId::export_b__oil_temp,
    SignalId::export_b__oil_pressure,
    SignalId::export_b__exhaust_gas_temp,
    SignalId::servo_batt__servo_bus_voltage,
} };

template <SignalId Id>
struct signal_traits;

template <>
struct signal_traits<SignalId::reacher_ctrl__eng_on> {
    using value_type = std::uint8_t;
    static constexpr SignalId signal_id = SignalId::reacher_ctrl__eng_on;
    static constexpr MessageId message_id = MessageId::reacher_ctrl;
    static constexpr MessageId parent_message_id = MessageId::reacher_ctrl;
    static constexpr SignalType signal_type = SignalType::u8;
};
template <>
struct signal_traits<SignalId::reacher_ctrl__start> {
    using value_type = std::uint8_t;
    static constexpr SignalId signal_id = SignalId::reacher_ctrl__start;
    static constexpr MessageId message_id = MessageId::reacher_ctrl;
    static constexpr MessageId parent_message_id = MessageId::reacher_ctrl;
    static constexpr SignalType signal_type = SignalType::u8;
};
template <>
struct signal_traits<SignalId::reacher_ctrl__arm> {
    using value_type = std::uint8_t;
    static constexpr SignalId signal_id = SignalId::reacher_ctrl__arm;
    static constexpr MessageId message_id = MessageId::reacher_ctrl;
    static constexpr MessageId parent_message_id = MessageId::reacher_ctrl;
    static constexpr SignalType signal_type = SignalType::u8;
};
template <>
struct signal_traits<SignalId::reacher_ctrl__test> {
    using value_type = std::uint8_t;
    static constexpr SignalId signal_id = SignalId::reacher_ctrl__test;
    static constexpr MessageId message_id = MessageId::reacher_ctrl;
    static constexpr MessageId parent_message_id = MessageId::reacher_ctrl;
    static constexpr SignalType signal_type = SignalType::u8;
};
template <>
struct signal_traits<SignalId::reacher_ctrl__aux_1> {
    using value_type = std::uint8_t;
    static constexpr SignalId signal_id = SignalId::reacher_ctrl__aux_1;
    static constexpr MessageId message_id = MessageId::reacher_ctrl;
    static constexpr MessageId parent_message_id = MessageId::reacher_ctrl;
    static constexpr SignalType signal_type = SignalType::u8;
};
template <>
struct signal_traits<SignalId::reacher_ctrl__throttle_rpm> {
    using value_type = std::uint16_t;
    static constexpr SignalId signal_id = SignalId::reacher_ctrl__throttle_rpm;
    static constexpr MessageId message_id = MessageId::reacher_ctrl;
    static constexpr MessageId parent_message_id = MessageId::reacher_ctrl;
    static constexpr SignalType signal_type = SignalType::u16;
};
template <>
struct signal_traits<SignalId::reacher_ctrl__aux_2> {
    using value_type = std::uint8_t;
    static constexpr SignalId signal_id = SignalId::reacher_ctrl__aux_2;
    static constexpr MessageId message_id = MessageId::reacher_ctrl;
    static constexpr MessageId parent_message_id = MessageId::reacher_ctrl;
    static constexpr SignalType signal_type = SignalType::u8;
};
template <>
struct signal_traits<SignalId::reacher_engine_feedback__ecu_on> {
    using value_type = std::uint8_t;
    static constexpr SignalId signal_id = SignalId::reacher_engine_feedback__ecu_on;
    static constexpr MessageId message_id = MessageId::reacher_engine_feedback;
    static constexpr MessageId parent_message_id = MessageId::reacher_engine_feedback;
    static constexpr SignalType signal_type = SignalType::u8;
};
template <>
struct signal_traits<SignalId::reacher_engine_feedback__f_pump_on> {
    using value_type = std::uint8_t;
    static constexpr SignalId signal_id = SignalId::reacher_engine_feedback__f_pump_on;
    static constexpr MessageId message_id = MessageId::reacher_engine_feedback;
    static constexpr MessageId parent_message_id = MessageId::reacher_engine_feedback;
    static constexpr SignalType signal_type = SignalType::u8;
};
template <>
struct signal_traits<SignalId::reacher_engine_feedback__st_solenoid_on> {
    using value_type = std::uint8_t;
    static constexpr SignalId signal_id = SignalId::reacher_engine_feedback__st_solenoid_on;
    static constexpr MessageId message_id = MessageId::reacher_engine_feedback;
    static constexpr MessageId parent_message_id = MessageId::reacher_engine_feedback;
    static constexpr SignalType signal_type = SignalType::u8;
};
template <>
struct signal_traits<SignalId::export_0__eng_speed> {
    using value_type = std::uint16_t;
    static constexpr SignalId signal_id = SignalId::export_0__eng_speed;
    static constexpr MessageId message_id = MessageId::export_0;
    static constexpr MessageId parent_message_id = MessageId::export_0;
    static constexpr SignalType signal_type = SignalType::u16;
};
template <>
struct signal_traits<SignalId::export_0__actual_throttle> {
    using value_type = double;
    static constexpr SignalId signal_id = SignalId::export_0__actual_throttle;
    static constexpr MessageId message_id = MessageId::export_0;
    static constexpr MessageId parent_message_id = MessageId::export_0;
    static constexpr SignalType signal_type = SignalType::f64;
};
template <>
struct signal_traits<SignalId::export_0__manifold_press> {
    using value_type = std::uint16_t;
    static constexpr SignalId signal_id = SignalId::export_0__manifold_press;
    static constexpr MessageId message_id = MessageId::export_0;
    static constexpr MessageId parent_message_id = MessageId::export_0;
    static constexpr SignalType signal_type = SignalType::u16;
};
template <>
struct signal_traits<SignalId::export_3__fuel_rail_pressure> {
    using value_type = std::int16_t;
    static constexpr SignalId signal_id = SignalId::export_3__fuel_rail_pressure;
    static constexpr MessageId message_id = MessageId::export_3;
    static constexpr MessageId parent_message_id = MessageId::export_3;
    static constexpr SignalType signal_type = SignalType::i16;
};
template <>
struct signal_traits<SignalId::export_8__battery_bus_voltage> {
    using value_type = double;
    static constexpr SignalId signal_id = SignalId::export_8__battery_bus_voltage;
    static constexpr MessageId message_id = MessageId::export_8;
    static constexpr MessageId parent_message_id = MessageId::export_8;
    static constexpr SignalType signal_type = SignalType::f64;
};
template <>
struct signal_traits<SignalId::export_b__coolant_temp> {
    using value_type = double;
    static constexpr SignalId signal_id = SignalId::export_b__coolant_temp;
    static constexpr MessageId message_id = MessageId::export_b;
    static constexpr MessageId parent_message_id = MessageId::export_b;
    static constexpr SignalType signal_type = SignalType::f64;
};
template <>
struct signal_traits<SignalId::export_b__oil_temp> {
    using value_type = double;
    static constexpr SignalId signal_id = SignalId::export_b__oil_temp;
    static constexpr MessageId message_id = MessageId::export_b;
    static constexpr MessageId parent_message_id = MessageId::export_b;
    static constexpr SignalType signal_type = SignalType::f64;
};
template <>
struct signal_traits<SignalId::export_b__oil_pressure> {
    using value_type = double;
    static constexpr SignalId signal_id = SignalId::export_b__oil_pressure;
    static constexpr MessageId message_id = MessageId::export_b;
    static constexpr MessageId parent_message_id = MessageId::export_b;
    static constexpr SignalType signal_type = SignalType::f64;
};
template <>
struct signal_traits<SignalId::export_b__exhaust_gas_temp> {
    using value_type = double;
    static constexpr SignalId signal_id = SignalId::export_b__exhaust_gas_temp;
    static constexpr MessageId message_id = MessageId::export_b;
    static constexpr MessageId parent_message_id = MessageId::export_b;
    static constexpr SignalType signal_type = SignalType::f64;
};
template <>
struct signal_traits<SignalId::servo_batt__servo_bus_voltage> {
    using value_type = std::uint16_t;
    static constexpr SignalId signal_id = SignalId::servo_batt__servo_bus_voltage;
    static constexpr MessageId message_id = MessageId::servo_batt;
    static constexpr MessageId parent_message_id = MessageId::servo_batt;
    static constexpr SignalType signal_type = SignalType::u16;
};

template <SignalId Id>
using signal_value_t = typename signal_traits<Id>::value_type;

constexpr auto message_meta(MessageId id) -> const MessageMeta& {
    return kMessagesById[to_index(id)];
}

constexpr auto signal_meta(SignalId id) -> const SignalMeta& {
    return kSignalsById[to_index(id)];
}

constexpr auto message_name(MessageId id) -> std::string_view {
    return message_meta(id).dbc_name;
}

constexpr auto signal_name(SignalId id) -> std::string_view {
    return signal_meta(id).dbc_name;
}

constexpr auto signal_unit(SignalId id) -> std::string_view {
    return signal_meta(id).unit;
}

constexpr auto signal_parent_message_name(SignalId id) -> std::string_view {
    return signal_meta(id).message_dbc_name;
}

constexpr auto parent_message_id(SignalId id) -> MessageId {
    return signal_meta(id).message_id;
}

constexpr auto message_cycle_time_ms(MessageId id) -> std::uint32_t {
    return message_meta(id).cycle_time_ms;
}

constexpr auto message_signals(MessageId id) -> std::span<const SignalId> {
    const auto& mm = message_meta(id);
    return std::span<const SignalId>{
        kMessageSignalsFlat.data() + mm.signal_offset,
        mm.signal_count
    };
}

constexpr auto find_message_by_frame_id(std::uint32_t frame_id) -> const MessageMeta* {
    for (const auto& msg : kMessagesById) {
        if (msg.frame_id == frame_id) {
            return &msg;
        }
    }
    return nullptr;
}

} // namespace reacher