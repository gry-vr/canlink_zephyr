#include "reacher/reacher_build.hpp"

#include <expected>

namespace reacher {

auto build_reacher_ctrl_from_store(const ValueStore& store)
    -> std::expected<ReacherCtrl, BuildError>
{
    ReacherCtrl msg{};

    {
        auto v = store.template get<SignalId::reacher_ctrl__eng_on>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.eng_on = *v;
    }
    {
        auto v = store.template get<SignalId::reacher_ctrl__start>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.start = *v;
    }
    {
        auto v = store.template get<SignalId::reacher_ctrl__arm>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.arm = *v;
    }
    {
        auto v = store.template get<SignalId::reacher_ctrl__test>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.test = *v;
    }
    {
        auto v = store.template get<SignalId::reacher_ctrl__aux_1>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.aux_1 = *v;
    }
    {
        auto v = store.template get<SignalId::reacher_ctrl__throttle_rpm>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.throttle_rpm = *v;
    }
    {
        auto v = store.template get<SignalId::reacher_ctrl__aux_2>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.aux_2 = *v;
    }

    return msg;
}

auto build_reacher_engine_feedback_from_store(const ValueStore& store)
    -> std::expected<ReacherEngineFeedback, BuildError>
{
    ReacherEngineFeedback msg{};

    {
        auto v = store.template get<SignalId::reacher_engine_feedback__ecu_on>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.ecu_on = *v;
    }
    {
        auto v = store.template get<SignalId::reacher_engine_feedback__f_pump_on>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.f_pump_on = *v;
    }
    {
        auto v = store.template get<SignalId::reacher_engine_feedback__st_solenoid_on>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.st_solenoid_on = *v;
    }

    return msg;
}

auto build_export_0_from_store(const ValueStore& store)
    -> std::expected<Export0, BuildError>
{
    Export0 msg{};

    {
        auto v = store.template get<SignalId::export_0__eng_speed>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.eng_speed = *v;
    }
    {
        auto v = store.template get<SignalId::export_0__actual_throttle>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.actual_throttle = *v;
    }
    {
        auto v = store.template get<SignalId::export_0__manifold_press>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.manifold_press = *v;
    }

    return msg;
}

auto build_export_3_from_store(const ValueStore& store)
    -> std::expected<Export3, BuildError>
{
    Export3 msg{};

    {
        auto v = store.template get<SignalId::export_3__fuel_rail_pressure>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.fuel_rail_pressure = *v;
    }

    return msg;
}

auto build_export_8_from_store(const ValueStore& store)
    -> std::expected<Export8, BuildError>
{
    Export8 msg{};

    {
        auto v = store.template get<SignalId::export_8__battery_bus_voltage>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.battery_bus_voltage = *v;
    }

    return msg;
}

auto build_export_b_from_store(const ValueStore& store)
    -> std::expected<ExportB, BuildError>
{
    ExportB msg{};

    {
        auto v = store.template get<SignalId::export_b__coolant_temp>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.coolant_temp = *v;
    }
    {
        auto v = store.template get<SignalId::export_b__oil_temp>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.oil_temp = *v;
    }
    {
        auto v = store.template get<SignalId::export_b__oil_pressure>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.oil_pressure = *v;
    }
    {
        auto v = store.template get<SignalId::export_b__exhaust_gas_temp>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.exhaust_gas_temp = *v;
    }

    return msg;
}

auto build_servo_batt_from_store(const ValueStore& store)
    -> std::expected<ServoBatt, BuildError>
{
    ServoBatt msg{};

    {
        auto v = store.template get<SignalId::servo_batt__servo_bus_voltage>();
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.servo_bus_voltage = *v;
    }

    return msg;
}

auto build_message_from_store(MessageId id, const ValueStore& store)
    -> std::expected<MessageVariant, BuildError>
{
    switch (id) {
    case MessageId::reacher_ctrl: {
        auto built = build_reacher_ctrl_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::reacher_engine_feedback: {
        auto built = build_reacher_engine_feedback_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::export_0: {
        auto built = build_export_0_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::export_3: {
        auto built = build_export_3_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::export_8: {
        auto built = build_export_8_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::export_b: {
        auto built = build_export_b_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::servo_batt: {
        auto built = build_servo_batt_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    default:
        return std::unexpected(BuildError::unsupported_message);
    }
}

auto validate_message_buildable(MessageId id, const ValueStore& store)
    -> std::expected<void, BuildError>
{
    auto built = build_message_from_store(id, store);
    if (!built) {
        return std::unexpected(built.error());
    }
    return {};
}

} // namespace reacher