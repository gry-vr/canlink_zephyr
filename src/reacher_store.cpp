#include "reacher/reacher_store.hpp"
#include "reacher/reacher_types.hpp"

namespace reacher {

void update_from(ValueStore& store, const ReacherCtrl& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::reacher_ctrl, now_ms);

    store.template set<SignalId::reacher_ctrl__eng_on>(m.eng_on, now_ms);
    store.template set<SignalId::reacher_ctrl__start>(m.start, now_ms);
    store.template set<SignalId::reacher_ctrl__arm>(m.arm, now_ms);
    store.template set<SignalId::reacher_ctrl__test>(m.test, now_ms);
    store.template set<SignalId::reacher_ctrl__aux_1>(m.aux_1, now_ms);
    store.template set<SignalId::reacher_ctrl__throttle_rpm>(m.throttle_rpm, now_ms);
    store.template set<SignalId::reacher_ctrl__aux_2>(m.aux_2, now_ms);
}

void update_from(ValueStore& store, const ReacherEngineFeedback& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::reacher_engine_feedback, now_ms);

    store.template set<SignalId::reacher_engine_feedback__ecu_on>(m.ecu_on, now_ms);
    store.template set<SignalId::reacher_engine_feedback__f_pump_on>(m.f_pump_on, now_ms);
    store.template set<SignalId::reacher_engine_feedback__st_solenoid_on>(m.st_solenoid_on, now_ms);
}

void update_from(ValueStore& store, const Export0& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::export_0, now_ms);

    store.template set<SignalId::export_0__eng_speed>(m.eng_speed, now_ms);
    store.template set<SignalId::export_0__actual_throttle>(m.actual_throttle, now_ms);
    store.template set<SignalId::export_0__manifold_press>(m.manifold_press, now_ms);
}

void update_from(ValueStore& store, const Export3& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::export_3, now_ms);

    store.template set<SignalId::export_3__fuel_rail_pressure>(m.fuel_rail_pressure, now_ms);
}

void update_from(ValueStore& store, const Export8& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::export_8, now_ms);

    store.template set<SignalId::export_8__battery_bus_voltage>(m.battery_bus_voltage, now_ms);
}

void update_from(ValueStore& store, const ExportB& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::export_b, now_ms);

    store.template set<SignalId::export_b__coolant_temp>(m.coolant_temp, now_ms);
    store.template set<SignalId::export_b__oil_temp>(m.oil_temp, now_ms);
    store.template set<SignalId::export_b__oil_pressure>(m.oil_pressure, now_ms);
    store.template set<SignalId::export_b__exhaust_gas_temp>(m.exhaust_gas_temp, now_ms);
}

void update_from(ValueStore& store, const ServoBatt& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::servo_batt, now_ms);

    store.template set<SignalId::servo_batt__servo_bus_voltage>(m.servo_bus_voltage, now_ms);
}

} // namespace reacher