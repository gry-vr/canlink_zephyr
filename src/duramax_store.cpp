#include "duramax_store.hpp"
#include "duramax_types.hpp"

namespace duramax {

void update_from(ValueStore& store, const Eec5ElectronicEngineControl5& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::eec5_electronic_engine_control_5, now_ms);

    store.set_signal_f64(SignalId::eec5_electronic_engine_control_5__engine_turbocharger_1_calculated, m.engine_turbocharger_1_calculated, now_ms);
    store.set_signal_f64(SignalId::eec5_electronic_engine_control_5__commanded_vgt_position, m.commanded_vgt_position, now_ms);
    store.set_signal_u8(SignalId::eec5_electronic_engine_control_5__engine_variable_geometry_turboch, m.engine_variable_geometry_turboch, now_ms);
    store.set_signal_u8(SignalId::eec5_electronic_engine_control_5__engine_fuel_control_control_mode, m.engine_fuel_control_control_mode, now_ms);
    store.set_signal_u8(SignalId::eec5_electronic_engine_control_5__engine_vgt_control_mode, m.engine_vgt_control_mode, now_ms);
    store.set_signal_f64(SignalId::eec5_electronic_engine_control_5__actual_vgt_position, m.actual_vgt_position, now_ms);
}

void update_from(ValueStore& store, const Eec9ElectronicEngineControl9& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::eec9_electronic_engine_control_9, now_ms);

    store.set_signal_f64(SignalId::eec9_electronic_engine_control_9__engine_exhaust_gas_recirculation, m.engine_exhaust_gas_recirculation, now_ms);
    store.set_signal_f64(SignalId::eec9_electronic_engine_control_9__commanded_fuel_rail_pressure, m.commanded_fuel_rail_pressure, now_ms);
    store.set_signal_f64(SignalId::eec9_electronic_engine_control_9__commanded_engine_fuel_injection, m.commanded_engine_fuel_injection, now_ms);
}

void update_from(ValueStore& store, const EbccEngineExhaustBrakeCont& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::ebcc_engine_exhaust_brake_cont, now_ms);

    store.set_signal_u8(SignalId::ebcc_engine_exhaust_brake_cont__actual_boost_pressure, m.actual_boost_pressure, now_ms);
    store.set_signal_u8(SignalId::ebcc_engine_exhaust_brake_cont__desired_boost_pressure, m.desired_boost_pressure, now_ms);
    store.set_signal_f64(SignalId::ebcc_engine_exhaust_brake_cont__engine_exhaust_brake_actuator_co, m.engine_exhaust_brake_actuator_co, now_ms);
    store.set_signal_u8(SignalId::ebcc_engine_exhaust_brake_cont__engine_turbocharger_2_turbine_ou, m.engine_turbocharger_2_turbine_ou, now_ms);
    store.set_signal_u8(SignalId::ebcc_engine_exhaust_brake_cont__desired_engine_turbocharger_2_tu, m.desired_engine_turbocharger_2_tu, now_ms);
}

void update_from(ValueStore& store, const Et3EngineTemperature3& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::et3_engine_temperature_3, now_ms);

    store.set_signal_f64(SignalId::et3_engine_temperature_3__engine_intake_manifold_1_air_tem, m.engine_intake_manifold_1_air_tem, now_ms);
    store.set_signal_f64(SignalId::et3_engine_temperature_3__engine_coolant_temperature_high, m.engine_coolant_temperature_high, now_ms);
    store.set_signal_f64(SignalId::et3_engine_temperature_3__engine_intake_valve_actuation_sy, m.engine_intake_valve_actuation_sy, now_ms);
    store.set_signal_f64(SignalId::et3_engine_temperature_3__engine_cac_outlet_temperature, m.engine_cac_outlet_temperature, now_ms);
}

void update_from(ValueStore& store, const Dm21DiagnosticReadiness2& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::dm21_diagnostic_readiness_2, now_ms);

    store.set_signal_u16(SignalId::dm21_diagnostic_readiness_2__engine_run_time_with_mil_on, m.engine_run_time_with_mil_on, now_ms);
}

void update_from(ValueStore& store, const Dm26DiagnosticReadiness3& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::dm26_diagnostic_readiness_3, now_ms);

    store.set_signal_u16(SignalId::dm26_diagnostic_readiness_3__time_since_engine_start, m.time_since_engine_start, now_ms);
}

void update_from(ValueStore& store, const Ic1IntakeExhaustCond1& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::ic1_intake_exhaust_cond_1, now_ms);

    store.set_signal_f64(SignalId::ic1_intake_exhaust_cond_1__aft1dpfinpress, m.aft1dpfinpress, now_ms);
    store.set_signal_u8(SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1press, m.engintakemanifold1press, now_ms);
    store.set_signal_f64(SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1temp, m.engintakemanifold1temp, now_ms);
    store.set_signal_u8(SignalId::ic1_intake_exhaust_cond_1__engairintakepress, m.engairintakepress, now_ms);
    store.set_signal_f64(SignalId::ic1_intake_exhaust_cond_1__engairfilter1diffpress, m.engairfilter1diffpress, now_ms);
    store.set_signal_f64(SignalId::ic1_intake_exhaust_cond_1__engexhaustgastemp, m.engexhaustgastemp, now_ms);
    store.set_signal_f64(SignalId::ic1_intake_exhaust_cond_1__engcoolantfilterdiffpress, m.engcoolantfilterdiffpress, now_ms);
}

void update_from(ValueStore& store, const AmbAmbientConditions& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::amb_ambient_conditions, now_ms);

    store.set_signal_f64(SignalId::amb_ambient_conditions__barometric_pressurebarometric_pr, m.barometric_pressurebarometric_pr, now_ms);
    store.set_signal_f64(SignalId::amb_ambient_conditions__cabinteriortemp, m.cabinteriortemp, now_ms);
    store.set_signal_f64(SignalId::amb_ambient_conditions__ambient_air_temperature, m.ambient_air_temperature, now_ms);
    store.set_signal_f64(SignalId::amb_ambient_conditions__engine_air_intake_temperature, m.engine_air_intake_temperature, now_ms);
    store.set_signal_f64(SignalId::amb_ambient_conditions__roadsurfacetemp, m.roadsurfacetemp, now_ms);
}

void update_from(ValueStore& store, const Eec1ElectronicEngineControl1& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::eec1_electronic_engine_control_1, now_ms);

    store.set_signal_u8(SignalId::eec1_electronic_engine_control_1__engine_torque_mode, m.engine_torque_mode, now_ms);
    store.set_signal_u8(SignalId::eec1_electronic_engine_control_1__actlengprcnttorquehighresolution, m.actlengprcnttorquehighresolution, now_ms);
    store.set_signal_f64(SignalId::eec1_electronic_engine_control_1__drivers_demand_engine_prcnt_torq, m.drivers_demand_engine_prcnt_torq, now_ms);
    store.set_signal_f64(SignalId::eec1_electronic_engine_control_1__actual_engine_percent_torque, m.actual_engine_percent_torque, now_ms);
    store.set_signal_f64(SignalId::eec1_electronic_engine_control_1__engine_speed, m.engine_speed, now_ms);
    store.set_signal_u8(SignalId::eec1_electronic_engine_control_1__srcaddrssofcntrllngdvcforengctrl, m.srcaddrssofcntrllngdvcforengctrl, now_ms);
    store.set_signal_u8(SignalId::eec1_electronic_engine_control_1__engstartermode, m.engstartermode, now_ms);
    store.set_signal_f64(SignalId::eec1_electronic_engine_control_1__engine_demand_percent_torque, m.engine_demand_percent_torque, now_ms);
}

void update_from(ValueStore& store, const Eec2ElectronicEngineControl2& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::eec2_electronic_engine_control_2, now_ms);

    store.set_signal_u8(SignalId::eec2_electronic_engine_control_2__accelpedal1lowidleswitch, m.accelpedal1lowidleswitch, now_ms);
    store.set_signal_u8(SignalId::eec2_electronic_engine_control_2__accelpedalkickdownswitch, m.accelpedalkickdownswitch, now_ms);
    store.set_signal_u8(SignalId::eec2_electronic_engine_control_2__roadspeedlimitstatus, m.roadspeedlimitstatus, now_ms);
    store.set_signal_u8(SignalId::eec2_electronic_engine_control_2__accelpedal2lowidleswitch, m.accelpedal2lowidleswitch, now_ms);
    store.set_signal_f64(SignalId::eec2_electronic_engine_control_2__accelpedalpos1, m.accelpedalpos1, now_ms);
    store.set_signal_u8(SignalId::eec2_electronic_engine_control_2__engpercentloadatcurrentspeed, m.engpercentloadatcurrentspeed, now_ms);
    store.set_signal_f64(SignalId::eec2_electronic_engine_control_2__remoteaccelpedalpos, m.remoteaccelpedalpos, now_ms);
    store.set_signal_f64(SignalId::eec2_electronic_engine_control_2__accelpedalpos2, m.accelpedalpos2, now_ms);
    store.set_signal_u8(SignalId::eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus, m.vhcleaccelerationratelimitstatus, now_ms);
    store.set_signal_u8(SignalId::eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback, m.mmntaryengmaxpowerenablefeedback, now_ms);
    store.set_signal_u8(SignalId::eec2_electronic_engine_control_2__dpfthermalmanagementactive, m.dpfthermalmanagementactive, now_ms);
    store.set_signal_u8(SignalId::eec2_electronic_engine_control_2__scrthermalmanagementactive, m.scrthermalmanagementactive, now_ms);
    store.set_signal_f64(SignalId::eec2_electronic_engine_control_2__actlmaxavailableengpercenttorque, m.actlmaxavailableengpercenttorque, now_ms);
    store.set_signal_f64(SignalId::eec2_electronic_engine_control_2__estpumpingpercenttorque, m.estpumpingpercenttorque, now_ms);
}

void update_from(ValueStore& store, const Eec3ElectronicEngineControl3& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::eec3_electronic_engine_control_3, now_ms);

    store.set_signal_f64(SignalId::eec3_electronic_engine_control_3__nominalfrictionpercenttorque, m.nominalfrictionpercenttorque, now_ms);
    store.set_signal_f64(SignalId::eec3_electronic_engine_control_3__enginesdesiredoperatingspeed, m.enginesdesiredoperatingspeed, now_ms);
    store.set_signal_u8(SignalId::eec3_electronic_engine_control_3__engnsdsrdoprtngspdasymmtryadjstm, m.engnsdsrdoprtngspdasymmtryadjstm, now_ms);
    store.set_signal_f64(SignalId::eec3_electronic_engine_control_3__estengprsiticlossespercenttorque, m.estengprsiticlossespercenttorque, now_ms);
    store.set_signal_f64(SignalId::eec3_electronic_engine_control_3__aft1exhgasmfr, m.aft1exhgasmfr, now_ms);
    store.set_signal_u8(SignalId::eec3_electronic_engine_control_3__aft1indewpoint, m.aft1indewpoint, now_ms);
    store.set_signal_u8(SignalId::eec3_electronic_engine_control_3__aft1exhdewpoint, m.aft1exhdewpoint, now_ms);
    store.set_signal_u8(SignalId::eec3_electronic_engine_control_3__aft2indewpoint, m.aft2indewpoint, now_ms);
    store.set_signal_u8(SignalId::eec3_electronic_engine_control_3__aft2exhdewpoint, m.aft2exhdewpoint, now_ms);
}

void update_from(ValueStore& store, const EflP1EngFluidLevelPress1& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::efl_p1_eng_fluid_level_press_1, now_ms);

    store.set_signal_u8(SignalId::efl_p1_eng_fluid_level_press_1__engfueldeliverypress, m.engfueldeliverypress, now_ms);
    store.set_signal_f64(SignalId::efl_p1_eng_fluid_level_press_1__engexcrankcaseblowbypress, m.engexcrankcaseblowbypress, now_ms);
    store.set_signal_f64(SignalId::efl_p1_eng_fluid_level_press_1__engoillevel, m.engoillevel, now_ms);
    store.set_signal_u8(SignalId::efl_p1_eng_fluid_level_press_1__engoilpress, m.engoilpress, now_ms);
    store.set_signal_f64(SignalId::efl_p1_eng_fluid_level_press_1__engcrankcasepress, m.engcrankcasepress, now_ms);
    store.set_signal_u8(SignalId::efl_p1_eng_fluid_level_press_1__engcoolantpress, m.engcoolantpress, now_ms);
    store.set_signal_f64(SignalId::efl_p1_eng_fluid_level_press_1__engcoolantlevel, m.engcoolantlevel, now_ms);
}

void update_from(ValueStore& store, const EflP2EngFluidLevelPress2& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::efl_p2_eng_fluid_level_press_2, now_ms);

    store.set_signal_f64(SignalId::efl_p2_eng_fluid_level_press_2__enginjectionctrlpress, m.enginjectionctrlpress, now_ms);
    store.set_signal_f64(SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail1press, m.enginjectormeteringrail1press, now_ms);
    store.set_signal_f64(SignalId::efl_p2_eng_fluid_level_press_2__enginjectortimingrail1press, m.enginjectortimingrail1press, now_ms);
    store.set_signal_f64(SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail2press, m.enginjectormeteringrail2press, now_ms);
}

void update_from(ValueStore& store, const Et1EngineTemperature1& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::et1_engine_temperature_1, now_ms);

    store.set_signal_f64(SignalId::et1_engine_temperature_1__engcoolanttemp, m.engcoolanttemp, now_ms);
    store.set_signal_f64(SignalId::et1_engine_temperature_1__engfueltemp1, m.engfueltemp1, now_ms);
    store.set_signal_f64(SignalId::et1_engine_temperature_1__engoiltemp1, m.engoiltemp1, now_ms);
    store.set_signal_f64(SignalId::et1_engine_temperature_1__engturbooiltemp, m.engturbooiltemp, now_ms);
    store.set_signal_f64(SignalId::et1_engine_temperature_1__engintercoolertemp, m.engintercoolertemp, now_ms);
    store.set_signal_f64(SignalId::et1_engine_temperature_1__engintercoolerthermostatopening, m.engintercoolerthermostatopening, now_ms);
}

void update_from(ValueStore& store, const Lfe1FuelEconomyLiquid1& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::lfe1_fuel_economy_liquid_1, now_ms);

    store.set_signal_f64(SignalId::lfe1_fuel_economy_liquid_1__engfuelrate, m.engfuelrate, now_ms);
    store.set_signal_f64(SignalId::lfe1_fuel_economy_liquid_1__enginstantaneousfueleconomy, m.enginstantaneousfueleconomy, now_ms);
    store.set_signal_f64(SignalId::lfe1_fuel_economy_liquid_1__engaveragefueleconomy, m.engaveragefueleconomy, now_ms);
    store.set_signal_f64(SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve1pos, m.engthrottlevalve1pos, now_ms);
    store.set_signal_f64(SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve2pos, m.engthrottlevalve2pos, now_ms);
}

void update_from(ValueStore& store, const TransportprotocolHeader& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::transportprotocol_header, now_ms);

    store.set_signal_u8(SignalId::transportprotocol_header__controlbyte, m.controlbyte, now_ms);
    store.set_signal_u16(SignalId::transportprotocol_header__totalmessagesizeeoma, m.totalmessagesizeeoma, now_ms);
    store.set_signal_u8(SignalId::transportprotocol_header__connectionabortreason, m.connectionabortreason, now_ms);
    store.set_signal_u16(SignalId::transportprotocol_header__totalmessagesize, m.totalmessagesize, now_ms);
    store.set_signal_u8(SignalId::transportprotocol_header__numberofpacketsthatcanbesent, m.numberofpacketsthatcanbesent, now_ms);
    store.set_signal_u16(SignalId::transportprotocol_header__totalmessagesizebam, m.totalmessagesizebam, now_ms);
    store.set_signal_u8(SignalId::transportprotocol_header__nextpacketnumbertobesent, m.nextpacketnumbertobesent, now_ms);
    store.set_signal_u8(SignalId::transportprotocol_header__totalnumberofpackets, m.totalnumberofpackets, now_ms);
    store.set_signal_u8(SignalId::transportprotocol_header__totalnumberofpacketseoma, m.totalnumberofpacketseoma, now_ms);
    store.set_signal_u8(SignalId::transportprotocol_header__totalnumberofpacketsbam, m.totalnumberofpacketsbam, now_ms);
    store.set_signal_u8(SignalId::transportprotocol_header__maximumnumberofpackets, m.maximumnumberofpackets, now_ms);
    store.set_signal_u32(SignalId::transportprotocol_header__pgnumber, m.pgnumber, now_ms);
}

void update_from(ValueStore& store, const TransportprotocolData& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::transportprotocol_data, now_ms);

    store.set_signal_u8(SignalId::transportprotocol_data__sequencenumber, m.sequencenumber, now_ms);
}

void update_from(ValueStore& store, const Dm01ActiveDiagnostics& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::dm01_active_diagnostics, now_ms);

    store.set_signal_u8(SignalId::dm01_active_diagnostics__protectlampstatus, m.protectlampstatus, now_ms);
    store.set_signal_u8(SignalId::dm01_active_diagnostics__amberwarninglampstatus, m.amberwarninglampstatus, now_ms);
    store.set_signal_u8(SignalId::dm01_active_diagnostics__redstoplampstate, m.redstoplampstate, now_ms);
    store.set_signal_u8(SignalId::dm01_active_diagnostics__malfunctionindicatorlampstatus, m.malfunctionindicatorlampstatus, now_ms);
    store.set_signal_u8(SignalId::dm01_active_diagnostics__flashprotectlamp, m.flashprotectlamp, now_ms);
    store.set_signal_u8(SignalId::dm01_active_diagnostics__flashamberwarninglamp, m.flashamberwarninglamp, now_ms);
    store.set_signal_u8(SignalId::dm01_active_diagnostics__flashredstoplamp, m.flashredstoplamp, now_ms);
    store.set_signal_u8(SignalId::dm01_active_diagnostics__flashmalfuncindicatorlamp, m.flashmalfuncindicatorlamp, now_ms);
    store.set_signal_u32(SignalId::dm01_active_diagnostics__dtc1, m.dtc1, now_ms);
}

void update_from(ValueStore& store, const Tsc131& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::tsc1_31, now_ms);

    store.set_signal_u8(SignalId::tsc1_31__engoverridectrlmode, m.engoverridectrlmode, now_ms);
    store.set_signal_u8(SignalId::tsc1_31__engrequestedspeedctrlconditions, m.engrequestedspeedctrlconditions, now_ms);
    store.set_signal_u8(SignalId::tsc1_31__overridectrlmodepriority, m.overridectrlmodepriority, now_ms);
    store.set_signal_f64(SignalId::tsc1_31__engrequestedspeed_speedlimit, m.engrequestedspeed_speedlimit, now_ms);
    store.set_signal_f64(SignalId::tsc1_31__engrequestedtorque_torquelimit, m.engrequestedtorque_torquelimit, now_ms);
    store.set_signal_u8(SignalId::tsc1_31__tsc1transrate, m.tsc1transrate, now_ms);
    store.set_signal_u8(SignalId::tsc1_31__tsc1ctrlpurpose, m.tsc1ctrlpurpose, now_ms);
    store.set_signal_u8(SignalId::tsc1_31__engrequestedtorquehighresolution, m.engrequestedtorquehighresolution, now_ms);
    store.set_signal_u8(SignalId::tsc1_31__messagecounter, m.messagecounter, now_ms);
    store.set_signal_u8(SignalId::tsc1_31__messagechecksum, m.messagechecksum, now_ms);
}

void update_from(ValueStore& store, const Cac1ChargeAirCooler1& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::cac1_charge_air_cooler_1, now_ms);

    store.set_signal_f64(SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_intak, m.engine_charge_air_cooler_1_intak, now_ms);
    store.set_signal_f64(SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_ambie, m.engine_charge_air_cooler_1_ambie, now_ms);
    store.set_signal_f64(SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_effic, m.engine_charge_air_cooler_1_effic, now_ms);
}

void update_from(ValueStore& store, const HoursEngineHoursRevolutions& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::hours_engine_hours_revolutions, now_ms);

    store.set_signal_f64(SignalId::hours_engine_hours_revolutions__engine_total_hours_of_operation, m.engine_total_hours_of_operation, now_ms);
    store.set_signal_u32(SignalId::hours_engine_hours_revolutions__engine_total_revolutions_249, m.engine_total_revolutions_249, now_ms);
}

void update_from(ValueStore& store, const Tci5TurbochargerInformation5& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::tci5_turbocharger_information_5, now_ms);

    store.set_signal_f64(SignalId::tci5_turbocharger_information_5__engine_turbocharger_1_turbine_ou, m.engine_turbocharger_1_turbine_ou, now_ms);
    store.set_signal_f64(SignalId::tci5_turbocharger_information_5__engine_turbocharger_2_turbine_ou, m.engine_turbocharger_2_turbine_ou, now_ms);
    store.set_signal_f64(SignalId::tci5_turbocharger_information_5__engine_turbocharger_3_turbine_ou, m.engine_turbocharger_3_turbine_ou, now_ms);
    store.set_signal_f64(SignalId::tci5_turbocharger_information_5__engine_turbocharger_4_turbine_ou, m.engine_turbocharger_4_turbine_ou, now_ms);
}

void update_from(ValueStore& store, const Vep1VehicleElectricalPower1& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::vep1_vehicle_electrical_power_1, now_ms);

    store.set_signal_f64(SignalId::vep1_vehicle_electrical_power_1__net_battery_current_114, m.net_battery_current_114, now_ms);
    store.set_signal_u8(SignalId::vep1_vehicle_electrical_power_1__alternator_current_115, m.alternator_current_115, now_ms);
    store.set_signal_f64(SignalId::vep1_vehicle_electrical_power_1__charging_system_potential_volta, m.charging_system_potential_volta, now_ms);
    store.set_signal_f64(SignalId::vep1_vehicle_electrical_power_1__battery_potential_power_input_1, m.battery_potential_power_input_1, now_ms);
    store.set_signal_f64(SignalId::vep1_vehicle_electrical_power_1__keyswitch_battery_potential_158, m.keyswitch_battery_potential_158, now_ms);
}

void update_from(ValueStore& store, const Eec20ElectronicEngineControl& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::eec20_electronic_engine_control, now_ms);

    store.set_signal_f64(SignalId::eec20_electronic_engine_control__absolute_engine_load, m.absolute_engine_load, now_ms);
}

void update_from(ValueStore& store, const EasiEngineAirSystemInfo& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::easi_engine_air_system_info, now_ms);

    store.set_signal_f64(SignalId::easi_engine_air_system_info__engine_intake_maf, m.engine_intake_maf, now_ms);
}

void update_from(ValueStore& store, const Tsc103& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::tsc1_03, now_ms);

    store.set_signal_u8(SignalId::tsc1_03__engoverridectrlmode, m.engoverridectrlmode, now_ms);
    store.set_signal_u8(SignalId::tsc1_03__engrequestedspeedctrlconditions, m.engrequestedspeedctrlconditions, now_ms);
    store.set_signal_u8(SignalId::tsc1_03__overridectrlmodepriority, m.overridectrlmodepriority, now_ms);
    store.set_signal_f64(SignalId::tsc1_03__engrequestedspeed_speedlimit, m.engrequestedspeed_speedlimit, now_ms);
    store.set_signal_f64(SignalId::tsc1_03__engrequestedtorque_torquelimit, m.engrequestedtorque_torquelimit, now_ms);
    store.set_signal_u8(SignalId::tsc1_03__tsc1transrate, m.tsc1transrate, now_ms);
    store.set_signal_u8(SignalId::tsc1_03__tsc1ctrlpurpose, m.tsc1ctrlpurpose, now_ms);
    store.set_signal_u8(SignalId::tsc1_03__engrequestedtorquehighresolution, m.engrequestedtorquehighresolution, now_ms);
    store.set_signal_u8(SignalId::tsc1_03__messagecounter, m.messagecounter, now_ms);
    store.set_signal_u8(SignalId::tsc1_03__messagechecksum, m.messagechecksum, now_ms);
}

void update_from(ValueStore& store, const Tsc10b& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::tsc1_0b, now_ms);

    store.set_signal_u8(SignalId::tsc1_0b__engoverridectrlmode, m.engoverridectrlmode, now_ms);
    store.set_signal_u8(SignalId::tsc1_0b__engrequestedspeedctrlconditions, m.engrequestedspeedctrlconditions, now_ms);
    store.set_signal_u8(SignalId::tsc1_0b__overridectrlmodepriority, m.overridectrlmodepriority, now_ms);
    store.set_signal_f64(SignalId::tsc1_0b__engrequestedspeed_speedlimit, m.engrequestedspeed_speedlimit, now_ms);
    store.set_signal_f64(SignalId::tsc1_0b__engrequestedtorque_torquelimit, m.engrequestedtorque_torquelimit, now_ms);
    store.set_signal_u8(SignalId::tsc1_0b__tsc1transrate, m.tsc1transrate, now_ms);
    store.set_signal_u8(SignalId::tsc1_0b__tsc1ctrlpurpose, m.tsc1ctrlpurpose, now_ms);
    store.set_signal_u8(SignalId::tsc1_0b__engrequestedtorquehighresolution, m.engrequestedtorquehighresolution, now_ms);
    store.set_signal_u8(SignalId::tsc1_0b__messagecounter, m.messagecounter, now_ms);
    store.set_signal_u8(SignalId::tsc1_0b__messagechecksum, m.messagechecksum, now_ms);
}

void update_from(ValueStore& store, const Dm07& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::dm07, now_ms);

    store.set_signal_u8(SignalId::dm07__testidentifier, m.testidentifier, now_ms);
    store.set_signal_u16(SignalId::dm07__spn1, m.spn1, now_ms);
    store.set_signal_u8(SignalId::dm07__failuremodeidentifier1, m.failuremodeidentifier1, now_ms);
    store.set_signal_u8(SignalId::dm07__spn1high, m.spn1high, now_ms);
}

void update_from(ValueStore& store, const Dm08& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::dm08, now_ms);

    store.set_signal_u8(SignalId::dm08__testidentifier, m.testidentifier, now_ms);
    store.set_signal_u8(SignalId::dm08__testtype, m.testtype, now_ms);
    store.set_signal_u16(SignalId::dm08__testvalue, m.testvalue, now_ms);
    store.set_signal_u16(SignalId::dm08__testlimitmaximum, m.testlimitmaximum, now_ms);
    store.set_signal_u16(SignalId::dm08__testlimitminimum, m.testlimitminimum, now_ms);
}

void update_from(ValueStore& store, const Erc1ElectronicRetarderCntrl& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::erc1_electronic_retarder_cntrl, now_ms);

    store.set_signal_u8(SignalId::erc1_electronic_retarder_cntrl__retardertorquemode, m.retardertorquemode, now_ms);
    store.set_signal_u8(SignalId::erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch, m.retarderenablebrakeassistswitch, now_ms);
    store.set_signal_u8(SignalId::erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch, m.retarderenableshiftassistswitch, now_ms);
    store.set_signal_f64(SignalId::erc1_electronic_retarder_cntrl__actualretarderpercenttorque, m.actualretarderpercenttorque, now_ms);
    store.set_signal_f64(SignalId::erc1_electronic_retarder_cntrl__intendedretarderpercenttorque, m.intendedretarderpercenttorque, now_ms);
    store.set_signal_u8(SignalId::erc1_electronic_retarder_cntrl__engcoolantloadincrease, m.engcoolantloadincrease, now_ms);
    store.set_signal_u8(SignalId::erc1_electronic_retarder_cntrl__retarderrequestingbrakelight, m.retarderrequestingbrakelight, now_ms);
    store.set_signal_u8(SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch, m.retarderroadspeedlimitswitch, now_ms);
    store.set_signal_u8(SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus, m.retarderroadspeedexceededstatus, now_ms);
    store.set_signal_u8(SignalId::erc1_electronic_retarder_cntrl__srcaddrssofcntrllngdvcfrrtrdrctr, m.srcaddrssofcntrllngdvcfrrtrdrctr, now_ms);
    store.set_signal_f64(SignalId::erc1_electronic_retarder_cntrl__drvrsdemandretarderpercenttorque, m.drvrsdemandretarderpercenttorque, now_ms);
    store.set_signal_f64(SignalId::erc1_electronic_retarder_cntrl__retarderselectionnonengine, m.retarderselectionnonengine, now_ms);
    store.set_signal_f64(SignalId::erc1_electronic_retarder_cntrl__actlmxavlblretarderpercenttorque, m.actlmxavlblretarderpercenttorque, now_ms);
}

void update_from(ValueStore& store, const Etc1ElectronicTransCntrl1& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::etc1_electronic_trans_cntrl_1, now_ms);

    store.set_signal_u8(SignalId::etc1_electronic_trans_cntrl_1__transdrivelineengaged, m.transdrivelineengaged, now_ms);
    store.set_signal_u8(SignalId::etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged, m.trnstorqueconverterlockupengaged, now_ms);
    store.set_signal_u8(SignalId::etc1_electronic_trans_cntrl_1__transshiftinprocess, m.transshiftinprocess, now_ms);
    store.set_signal_u8(SignalId::etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess, m.trnstrqcnvrtrlckptrnstninprocess, now_ms);
    store.set_signal_f64(SignalId::etc1_electronic_trans_cntrl_1__transoutputshaftspeed, m.transoutputshaftspeed, now_ms);
    store.set_signal_f64(SignalId::etc1_electronic_trans_cntrl_1__percentclutchslip, m.percentclutchslip, now_ms);
    store.set_signal_u8(SignalId::etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable, m.engmomentaryoverspeedenable, now_ms);
    store.set_signal_u8(SignalId::etc1_electronic_trans_cntrl_1__progressiveshiftdisable, m.progressiveshiftdisable, now_ms);
    store.set_signal_u8(SignalId::etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable, m.momentaryengmaxpowerenable, now_ms);
    store.set_signal_f64(SignalId::etc1_electronic_trans_cntrl_1__transinputshaftspeed, m.transinputshaftspeed, now_ms);
    store.set_signal_u8(SignalId::etc1_electronic_trans_cntrl_1__srcaddrssofcntrllngdvcfrtrnsctrl, m.srcaddrssofcntrllngdvcfrtrnsctrl, now_ms);
}

void update_from(ValueStore& store, const Etc2ElectronicTransCntrl2& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::etc2_electronic_trans_cntrl_2, now_ms);

    store.set_signal_f64(SignalId::etc2_electronic_trans_cntrl_2__transselectedgear, m.transselectedgear, now_ms);
    store.set_signal_f64(SignalId::etc2_electronic_trans_cntrl_2__transactualgearratio, m.transactualgearratio, now_ms);
    store.set_signal_f64(SignalId::etc2_electronic_trans_cntrl_2__transcurrentgear, m.transcurrentgear, now_ms);
    store.set_signal_u16(SignalId::etc2_electronic_trans_cntrl_2__transrequestedrange, m.transrequestedrange, now_ms);
    store.set_signal_u16(SignalId::etc2_electronic_trans_cntrl_2__transcurrentrange, m.transcurrentrange, now_ms);
}

void update_from(ValueStore& store, const Rqst005e& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::rqst_00_5e, now_ms);

    store.set_signal_u32(SignalId::rqst_00_5e__parametergroupnumber, m.parametergroupnumber, now_ms);
}

void update_from(ValueStore& store, const Rqst0021& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::rqst_00_21, now_ms);

    store.set_signal_u32(SignalId::rqst_00_21__parametergroupnumber, m.parametergroupnumber, now_ms);
}

void update_from(ValueStore& store, const RqstGlobal5e& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::rqst_global_5e, now_ms);

    store.set_signal_u32(SignalId::rqst_global_5e__parametergroupnumber, m.parametergroupnumber, now_ms);
}

void update_from(ValueStore& store, const RqstGlobal03& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::rqst_global_03, now_ms);

    store.set_signal_u32(SignalId::rqst_global_03__parametergroupnumber, m.parametergroupnumber, now_ms);
}

void update_from(ValueStore& store, const TciTransferCaseInformation& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::tci_transfer_case_information, now_ms);

    store.set_signal_u8(SignalId::tci_transfer_case_information__transfercasestatus, m.transfercasestatus, now_ms);
    store.set_signal_u8(SignalId::tci_transfer_case_information__dirstatus, m.dirstatus, now_ms);
    store.set_signal_f64(SignalId::tci_transfer_case_information__actualgearratio, m.actualgearratio, now_ms);
    store.set_signal_u8(SignalId::tci_transfer_case_information__messagecounter, m.messagecounter, now_ms);
    store.set_signal_u8(SignalId::tci_transfer_case_information__messagechecksum, m.messagechecksum, now_ms);
}

void update_from(ValueStore& store, const Trf1TransmissionFluids1& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::trf1_transmission_fluids_1, now_ms);

    store.set_signal_u8(SignalId::trf1_transmission_fluids_1__clutchpress, m.clutchpress, now_ms);
    store.set_signal_f64(SignalId::trf1_transmission_fluids_1__transoillevel1, m.transoillevel1, now_ms);
    store.set_signal_u8(SignalId::trf1_transmission_fluids_1__transfilterdiffpress, m.transfilterdiffpress, now_ms);
    store.set_signal_u8(SignalId::trf1_transmission_fluids_1__transoilpress, m.transoilpress, now_ms);
    store.set_signal_f64(SignalId::trf1_transmission_fluids_1__transoiltemp1, m.transoiltemp1, now_ms);
    store.set_signal_f64(SignalId::trf1_transmission_fluids_1__transoillevel1high_low, m.transoillevel1high_low, now_ms);
    store.set_signal_u8(SignalId::trf1_transmission_fluids_1__transoillevel1countdowntimer, m.transoillevel1countdowntimer, now_ms);
    store.set_signal_u8(SignalId::trf1_transmission_fluids_1__transoillevel1measurementstatus, m.transoillevel1measurementstatus, now_ms);
}

void update_from(ValueStore& store, const CcssCruiseControlVehicleSpd& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::ccss_cruise_control_vehicle_spd, now_ms);

    store.set_signal_u8(SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit, m.maxvehiclespeedlimit, now_ms);
    store.set_signal_u8(SignalId::ccss_cruise_control_vehicle_spd__cruisectrlhighsetlimitspeed, m.cruisectrlhighsetlimitspeed, now_ms);
    store.set_signal_u8(SignalId::ccss_cruise_control_vehicle_spd__cruisectrllowsetlimitspeed, m.cruisectrllowsetlimitspeed, now_ms);
    store.set_signal_f64(SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit6808, m.maxvehiclespeedlimit6808, now_ms);
    store.set_signal_u8(SignalId::ccss_cruise_control_vehicle_spd__ctrlsyslowsetlmtspd, m.ctrlsyslowsetlmtspd, now_ms);
    store.set_signal_u8(SignalId::ccss_cruise_control_vehicle_spd__ctrldiscmdsupport, m.ctrldiscmdsupport, now_ms);
    store.set_signal_u8(SignalId::ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport, m.ctrlresumecmdsupport, now_ms);
    store.set_signal_u8(SignalId::ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport, m.ctrlpausecmdsupport, now_ms);
    store.set_signal_u8(SignalId::ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport, m.ctrlsetcmdsupport, now_ms);
    store.set_signal_u8(SignalId::ccss_cruise_control_vehicle_spd__powertrainadaptivecctype, m.powertrainadaptivecctype, now_ms);
}

void update_from(ValueStore& store, const Ccvs1CruiseControlVehspd& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::ccvs1_cruise_control_vehspd, now_ms);

    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__twospeedaxleswitch, m.twospeedaxleswitch, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__parkingbrakeswitch, m.parkingbrakeswitch, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlpauseswitch, m.cruisectrlpauseswitch, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq, m.parkbrakereleaseinhibitrq, now_ms);
    store.set_signal_f64(SignalId::ccvs1_cruise_control_vehspd__wheelbasedvehiclespeed, m.wheelbasedvehiclespeed, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlactive, m.cruisectrlactive, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlenableswitch, m.cruisectrlenableswitch, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__brakeswitch, m.brakeswitch, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__clutchswitch, m.clutchswitch, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetswitch, m.cruisectrlsetswitch, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlcoastswitch, m.cruisectrlcoastswitch, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlresumeswitch, m.cruisectrlresumeswitch, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch, m.cruisectrlaccelerateswitch, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetspeed, m.cruisectrlsetspeed, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__ptogovernorstate, m.ptogovernorstate, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlstates, m.cruisectrlstates, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__engidleincrementswitch, m.engidleincrementswitch, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__engidledecrementswitch, m.engidledecrementswitch, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__engtestmodeswitch, m.engtestmodeswitch, now_ms);
    store.set_signal_u8(SignalId::ccvs1_cruise_control_vehspd__engshutdownoverrideswitch, m.engshutdownoverrideswitch, now_ms);
}

void update_from(ValueStore& store, const Ebc1ElectronicBrakeCntrl& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::ebc1_electronic_brake_cntrl, now_ms);

    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__asrengctrlactive, m.asrengctrlactive, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__asrbrakectrlactive, m.asrbrakectrlactive, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__antilockbrakingactive, m.antilockbrakingactive, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__ebsbrakeswitch, m.ebsbrakeswitch, now_ms);
    store.set_signal_f64(SignalId::ebc1_electronic_brake_cntrl__brakepedalpos, m.brakepedalpos, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__absoffroadswitch, m.absoffroadswitch, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__asroffroadswitch, m.asroffroadswitch, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__asrhillholderswitch, m.asrhillholderswitch, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__tractionctrloverrideswitch, m.tractionctrloverrideswitch, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__accelinterlockswitch, m.accelinterlockswitch, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__engderateswitch, m.engderateswitch, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__engauxshutdownswitch, m.engauxshutdownswitch, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__remoteaccelenableswitch, m.remoteaccelenableswitch, now_ms);
    store.set_signal_f64(SignalId::ebc1_electronic_brake_cntrl__engretarderselection, m.engretarderselection, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__absfullyoperational, m.absfullyoperational, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__ebsredwarningsignal, m.ebsredwarningsignal, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal, m.abs_ebsamberwarningsignal, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__atc_asrinformationsignal, m.atc_asrinformationsignal, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__srcaddrssofcntrllngdvcfrbrkectrl, m.srcaddrssofcntrllngdvcfrbrkectrl, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__railroadmodesw, m.railroadmodesw, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__haltbrakeswitch, m.haltbrakeswitch, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__trailerabsstatus, m.trailerabsstatus, now_ms);
    store.set_signal_u8(SignalId::ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal, m.trctrmntdtrailerabswarningsignal, now_ms);
}

void update_from(ValueStore& store, const Shutdn& m, std::uint32_t now_ms)
{
    store.mark_message_rx(MessageId::shutdn, now_ms);

    store.set_signal_u8(SignalId::shutdn__engidleshutdownhasshutdowneng, m.engidleshutdownhasshutdowneng, now_ms);
    store.set_signal_u8(SignalId::shutdn__engidleshutdowndriveralertmode, m.engidleshutdowndriveralertmode, now_ms);
    store.set_signal_u8(SignalId::shutdn__engidleshutdowntimeroverride, m.engidleshutdowntimeroverride, now_ms);
    store.set_signal_u8(SignalId::shutdn__engidleshutdowntimerstate, m.engidleshutdowntimerstate, now_ms);
    store.set_signal_u8(SignalId::shutdn__engidleshutdowntimerfunction, m.engidleshutdowntimerfunction, now_ms);
    store.set_signal_u8(SignalId::shutdn__a_chighpressfanswitch, m.a_chighpressfanswitch, now_ms);
    store.set_signal_u8(SignalId::shutdn__refrigerantlowpressswitch, m.refrigerantlowpressswitch, now_ms);
    store.set_signal_u8(SignalId::shutdn__refrigeranthighpressswitch, m.refrigeranthighpressswitch, now_ms);
    store.set_signal_u8(SignalId::shutdn__engwaittostartlamp, m.engwaittostartlamp, now_ms);
    store.set_signal_u8(SignalId::shutdn__engprtectionsystemhasshutdowneng, m.engprtectionsystemhasshutdowneng, now_ms);
    store.set_signal_u8(SignalId::shutdn__engprtctnsystmapprachingshutdown, m.engprtctnsystmapprachingshutdown, now_ms);
    store.set_signal_u8(SignalId::shutdn__engprotectionsystemtimeroverride, m.engprotectionsystemtimeroverride, now_ms);
    store.set_signal_u8(SignalId::shutdn__engprotectionsystemtimerstate, m.engprotectionsystemtimerstate, now_ms);
    store.set_signal_u8(SignalId::shutdn__engprotectionsystemconfig, m.engprotectionsystemconfig, now_ms);
    store.set_signal_u8(SignalId::shutdn__engalarmacknowledge, m.engalarmacknowledge, now_ms);
    store.set_signal_u8(SignalId::shutdn__engalarmoutputcmdstatus, m.engalarmoutputcmdstatus, now_ms);
    store.set_signal_u8(SignalId::shutdn__engairshutoffcmdstatus, m.engairshutoffcmdstatus, now_ms);
    store.set_signal_u8(SignalId::shutdn__engoverspeedtest, m.engoverspeedtest, now_ms);
    store.set_signal_u8(SignalId::shutdn__engairshutoffstatus, m.engairshutoffstatus, now_ms);
    store.set_signal_u8(SignalId::shutdn__ptoshutdownhasshutdowneng, m.ptoshutdownhasshutdowneng, now_ms);
    store.set_signal_u8(SignalId::shutdn__clntlvlengprtctionshutdownstatus, m.clntlvlengprtctionshutdownstatus, now_ms);
    store.set_signal_u8(SignalId::shutdn__engoilpresssw, m.engoilpresssw, now_ms);
}

} // namespace duramax