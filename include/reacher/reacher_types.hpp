#pragma once

#include "reacher_ids.hpp"

#include <cstdint>
#include <variant>

namespace reacher {

struct ReacherCtrl {
    static constexpr MessageId id = MessageId::reacher_ctrl;

    std::uint8_t eng_on{};
    std::uint8_t start{};
    std::uint8_t arm{};
    std::uint8_t test{};
    std::uint8_t aux_1{};
    std::uint16_t throttle_rpm{};
    std::uint8_t aux_2{};
};

struct ReacherEngineFeedback {
    static constexpr MessageId id = MessageId::reacher_engine_feedback;

    std::uint8_t ecu_on{};
    std::uint8_t f_pump_on{};
    std::uint8_t st_solenoid_on{};
};

struct Export0 {
    static constexpr MessageId id = MessageId::export_0;

    std::uint16_t eng_speed{};
    double actual_throttle{};
    std::uint16_t manifold_press{};
};

struct Export3 {
    static constexpr MessageId id = MessageId::export_3;

    std::int16_t fuel_rail_pressure{};
};

struct Export8 {
    static constexpr MessageId id = MessageId::export_8;

    double battery_bus_voltage{};
};

struct ExportB {
    static constexpr MessageId id = MessageId::export_b;

    double coolant_temp{};
    double oil_temp{};
    double oil_pressure{};
    double exhaust_gas_temp{};
};

struct ServoBatt {
    static constexpr MessageId id = MessageId::servo_batt;

    std::uint16_t servo_bus_voltage{};
};

using MessageVariant = std::variant<
    ReacherCtrl,
    ReacherEngineFeedback,
    Export0,
    Export3,
    Export8,
    ExportB,
    ServoBatt
>;

constexpr auto message_id_of(const ReacherCtrl&) -> MessageId {
    return MessageId::reacher_ctrl;
}
constexpr auto message_id_of(const ReacherEngineFeedback&) -> MessageId {
    return MessageId::reacher_engine_feedback;
}
constexpr auto message_id_of(const Export0&) -> MessageId {
    return MessageId::export_0;
}
constexpr auto message_id_of(const Export3&) -> MessageId {
    return MessageId::export_3;
}
constexpr auto message_id_of(const Export8&) -> MessageId {
    return MessageId::export_8;
}
constexpr auto message_id_of(const ExportB&) -> MessageId {
    return MessageId::export_b;
}
constexpr auto message_id_of(const ServoBatt&) -> MessageId {
    return MessageId::servo_batt;
}

template <typename Msg>
struct message_id_of_type;

template <>
struct message_id_of_type<ReacherCtrl> {
    static constexpr MessageId value = MessageId::reacher_ctrl;
};
template <>
struct message_id_of_type<ReacherEngineFeedback> {
    static constexpr MessageId value = MessageId::reacher_engine_feedback;
};
template <>
struct message_id_of_type<Export0> {
    static constexpr MessageId value = MessageId::export_0;
};
template <>
struct message_id_of_type<Export3> {
    static constexpr MessageId value = MessageId::export_3;
};
template <>
struct message_id_of_type<Export8> {
    static constexpr MessageId value = MessageId::export_8;
};
template <>
struct message_id_of_type<ExportB> {
    static constexpr MessageId value = MessageId::export_b;
};
template <>
struct message_id_of_type<ServoBatt> {
    static constexpr MessageId value = MessageId::servo_batt;
};

template <typename Msg>
constexpr auto message_id_of() -> MessageId {
    return message_id_of_type<Msg>::value;
}

} // namespace reacher