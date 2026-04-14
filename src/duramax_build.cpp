#include "duramax_build.hpp"

#include <expected>

namespace duramax {
namespace detail {

template <typename T>
struct always_false : std::false_type {};

template <SignalType>
struct store_getter_name;

template <>
struct store_getter_name<SignalType::u8> {
    static constexpr const char* value = "u8";
};

template <>
struct store_getter_name<SignalType::u16> {
    static constexpr const char* value = "u16";
};

template <>
struct store_getter_name<SignalType::i16> {
    static constexpr const char* value = "i16";
};

template <>
struct store_getter_name<SignalType::u32> {
    static constexpr const char* value = "u32";
};

template <>
struct store_getter_name<SignalType::f64> {
    static constexpr const char* value = "f64";
};

template <>
struct store_getter_name<SignalType::boolean> {
    static constexpr const char* value = "bool";
};

} // namespace detail

auto build_eec5_electronic_engine_control_5_from_store(const ValueStore& store)
    -> std::expected<Eec5ElectronicEngineControl5, BuildError>
{
    Eec5ElectronicEngineControl5 msg{};

    {
        auto v = store.try_get_f64(SignalId::eec5_electronic_engine_control_5__engine_turbocharger_1_calculated);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_turbocharger_1_calculated = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::eec5_electronic_engine_control_5__commanded_vgt_position);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.commanded_vgt_position = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec5_electronic_engine_control_5__engine_variable_geometry_turboch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_variable_geometry_turboch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec5_electronic_engine_control_5__engine_fuel_control_control_mode);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_fuel_control_control_mode = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec5_electronic_engine_control_5__engine_vgt_control_mode);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_vgt_control_mode = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::eec5_electronic_engine_control_5__actual_vgt_position);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.actual_vgt_position = *v;
    }

    return msg;
}

auto build_eec9_electronic_engine_control_9_from_store(const ValueStore& store)
    -> std::expected<Eec9ElectronicEngineControl9, BuildError>
{
    Eec9ElectronicEngineControl9 msg{};

    {
        auto v = store.try_get_f64(SignalId::eec9_electronic_engine_control_9__engine_exhaust_gas_recirculation);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_exhaust_gas_recirculation = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::eec9_electronic_engine_control_9__commanded_fuel_rail_pressure);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.commanded_fuel_rail_pressure = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::eec9_electronic_engine_control_9__commanded_engine_fuel_injection);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.commanded_engine_fuel_injection = *v;
    }

    return msg;
}

auto build_ebcc_engine_exhaust_brake_cont_from_store(const ValueStore& store)
    -> std::expected<EbccEngineExhaustBrakeCont, BuildError>
{
    EbccEngineExhaustBrakeCont msg{};

    {
        auto v = store.try_get_u8(SignalId::ebcc_engine_exhaust_brake_cont__actual_boost_pressure);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.actual_boost_pressure = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebcc_engine_exhaust_brake_cont__desired_boost_pressure);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.desired_boost_pressure = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::ebcc_engine_exhaust_brake_cont__engine_exhaust_brake_actuator_co);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_exhaust_brake_actuator_co = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebcc_engine_exhaust_brake_cont__engine_turbocharger_2_turbine_ou);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_turbocharger_2_turbine_ou = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebcc_engine_exhaust_brake_cont__desired_engine_turbocharger_2_tu);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.desired_engine_turbocharger_2_tu = *v;
    }

    return msg;
}

auto build_et3_engine_temperature_3_from_store(const ValueStore& store)
    -> std::expected<Et3EngineTemperature3, BuildError>
{
    Et3EngineTemperature3 msg{};

    {
        auto v = store.try_get_f64(SignalId::et3_engine_temperature_3__engine_intake_manifold_1_air_tem);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_intake_manifold_1_air_tem = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::et3_engine_temperature_3__engine_coolant_temperature_high);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_coolant_temperature_high = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::et3_engine_temperature_3__engine_intake_valve_actuation_sy);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_intake_valve_actuation_sy = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::et3_engine_temperature_3__engine_cac_outlet_temperature);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_cac_outlet_temperature = *v;
    }

    return msg;
}

auto build_dm21_diagnostic_readiness_2_from_store(const ValueStore& store)
    -> std::expected<Dm21DiagnosticReadiness2, BuildError>
{
    Dm21DiagnosticReadiness2 msg{};

    {
        auto v = store.try_get_u16(SignalId::dm21_diagnostic_readiness_2__engine_run_time_with_mil_on);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_run_time_with_mil_on = *v;
    }

    return msg;
}

auto build_dm26_diagnostic_readiness_3_from_store(const ValueStore& store)
    -> std::expected<Dm26DiagnosticReadiness3, BuildError>
{
    Dm26DiagnosticReadiness3 msg{};

    {
        auto v = store.try_get_u16(SignalId::dm26_diagnostic_readiness_3__time_since_engine_start);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.time_since_engine_start = *v;
    }

    return msg;
}

auto build_ic1_intake_exhaust_cond_1_from_store(const ValueStore& store)
    -> std::expected<Ic1IntakeExhaustCond1, BuildError>
{
    Ic1IntakeExhaustCond1 msg{};

    {
        auto v = store.try_get_f64(SignalId::ic1_intake_exhaust_cond_1__aft1dpfinpress);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.aft1dpfinpress = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1press);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engintakemanifold1press = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1temp);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engintakemanifold1temp = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ic1_intake_exhaust_cond_1__engairintakepress);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engairintakepress = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::ic1_intake_exhaust_cond_1__engairfilter1diffpress);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engairfilter1diffpress = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::ic1_intake_exhaust_cond_1__engexhaustgastemp);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engexhaustgastemp = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::ic1_intake_exhaust_cond_1__engcoolantfilterdiffpress);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engcoolantfilterdiffpress = *v;
    }

    return msg;
}

auto build_amb_ambient_conditions_from_store(const ValueStore& store)
    -> std::expected<AmbAmbientConditions, BuildError>
{
    AmbAmbientConditions msg{};

    {
        auto v = store.try_get_f64(SignalId::amb_ambient_conditions__barometric_pressurebarometric_pr);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.barometric_pressurebarometric_pr = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::amb_ambient_conditions__cabinteriortemp);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.cabinteriortemp = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::amb_ambient_conditions__ambient_air_temperature);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.ambient_air_temperature = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::amb_ambient_conditions__engine_air_intake_temperature);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_air_intake_temperature = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::amb_ambient_conditions__roadsurfacetemp);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.roadsurfacetemp = *v;
    }

    return msg;
}

auto build_eec1_electronic_engine_control_1_from_store(const ValueStore& store)
    -> std::expected<Eec1ElectronicEngineControl1, BuildError>
{
    Eec1ElectronicEngineControl1 msg{};

    {
        auto v = store.try_get_u8(SignalId::eec1_electronic_engine_control_1__engine_torque_mode);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_torque_mode = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec1_electronic_engine_control_1__actlengprcnttorquehighresolution);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.actlengprcnttorquehighresolution = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::eec1_electronic_engine_control_1__drivers_demand_engine_prcnt_torq);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.drivers_demand_engine_prcnt_torq = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::eec1_electronic_engine_control_1__actual_engine_percent_torque);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.actual_engine_percent_torque = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::eec1_electronic_engine_control_1__engine_speed);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_speed = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec1_electronic_engine_control_1__srcaddrssofcntrllngdvcforengctrl);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.srcaddrssofcntrllngdvcforengctrl = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec1_electronic_engine_control_1__engstartermode);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engstartermode = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::eec1_electronic_engine_control_1__engine_demand_percent_torque);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_demand_percent_torque = *v;
    }

    return msg;
}

auto build_eec2_electronic_engine_control_2_from_store(const ValueStore& store)
    -> std::expected<Eec2ElectronicEngineControl2, BuildError>
{
    Eec2ElectronicEngineControl2 msg{};

    {
        auto v = store.try_get_u8(SignalId::eec2_electronic_engine_control_2__accelpedal1lowidleswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.accelpedal1lowidleswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec2_electronic_engine_control_2__accelpedalkickdownswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.accelpedalkickdownswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec2_electronic_engine_control_2__roadspeedlimitstatus);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.roadspeedlimitstatus = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec2_electronic_engine_control_2__accelpedal2lowidleswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.accelpedal2lowidleswitch = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::eec2_electronic_engine_control_2__accelpedalpos1);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.accelpedalpos1 = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec2_electronic_engine_control_2__engpercentloadatcurrentspeed);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engpercentloadatcurrentspeed = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::eec2_electronic_engine_control_2__remoteaccelpedalpos);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.remoteaccelpedalpos = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::eec2_electronic_engine_control_2__accelpedalpos2);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.accelpedalpos2 = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.vhcleaccelerationratelimitstatus = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.mmntaryengmaxpowerenablefeedback = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec2_electronic_engine_control_2__dpfthermalmanagementactive);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.dpfthermalmanagementactive = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec2_electronic_engine_control_2__scrthermalmanagementactive);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.scrthermalmanagementactive = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::eec2_electronic_engine_control_2__actlmaxavailableengpercenttorque);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.actlmaxavailableengpercenttorque = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::eec2_electronic_engine_control_2__estpumpingpercenttorque);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.estpumpingpercenttorque = *v;
    }

    return msg;
}

auto build_eec3_electronic_engine_control_3_from_store(const ValueStore& store)
    -> std::expected<Eec3ElectronicEngineControl3, BuildError>
{
    Eec3ElectronicEngineControl3 msg{};

    {
        auto v = store.try_get_f64(SignalId::eec3_electronic_engine_control_3__nominalfrictionpercenttorque);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.nominalfrictionpercenttorque = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::eec3_electronic_engine_control_3__enginesdesiredoperatingspeed);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.enginesdesiredoperatingspeed = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec3_electronic_engine_control_3__engnsdsrdoprtngspdasymmtryadjstm);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engnsdsrdoprtngspdasymmtryadjstm = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::eec3_electronic_engine_control_3__estengprsiticlossespercenttorque);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.estengprsiticlossespercenttorque = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::eec3_electronic_engine_control_3__aft1exhgasmfr);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.aft1exhgasmfr = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec3_electronic_engine_control_3__aft1indewpoint);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.aft1indewpoint = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec3_electronic_engine_control_3__aft1exhdewpoint);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.aft1exhdewpoint = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec3_electronic_engine_control_3__aft2indewpoint);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.aft2indewpoint = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::eec3_electronic_engine_control_3__aft2exhdewpoint);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.aft2exhdewpoint = *v;
    }

    return msg;
}

auto build_efl_p1_eng_fluid_level_press_1_from_store(const ValueStore& store)
    -> std::expected<EflP1EngFluidLevelPress1, BuildError>
{
    EflP1EngFluidLevelPress1 msg{};

    {
        auto v = store.try_get_u8(SignalId::efl_p1_eng_fluid_level_press_1__engfueldeliverypress);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engfueldeliverypress = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::efl_p1_eng_fluid_level_press_1__engexcrankcaseblowbypress);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engexcrankcaseblowbypress = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::efl_p1_eng_fluid_level_press_1__engoillevel);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engoillevel = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::efl_p1_eng_fluid_level_press_1__engoilpress);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engoilpress = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::efl_p1_eng_fluid_level_press_1__engcrankcasepress);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engcrankcasepress = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::efl_p1_eng_fluid_level_press_1__engcoolantpress);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engcoolantpress = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::efl_p1_eng_fluid_level_press_1__engcoolantlevel);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engcoolantlevel = *v;
    }

    return msg;
}

auto build_efl_p2_eng_fluid_level_press_2_from_store(const ValueStore& store)
    -> std::expected<EflP2EngFluidLevelPress2, BuildError>
{
    EflP2EngFluidLevelPress2 msg{};

    {
        auto v = store.try_get_f64(SignalId::efl_p2_eng_fluid_level_press_2__enginjectionctrlpress);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.enginjectionctrlpress = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail1press);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.enginjectormeteringrail1press = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::efl_p2_eng_fluid_level_press_2__enginjectortimingrail1press);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.enginjectortimingrail1press = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail2press);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.enginjectormeteringrail2press = *v;
    }

    return msg;
}

auto build_et1_engine_temperature_1_from_store(const ValueStore& store)
    -> std::expected<Et1EngineTemperature1, BuildError>
{
    Et1EngineTemperature1 msg{};

    {
        auto v = store.try_get_f64(SignalId::et1_engine_temperature_1__engcoolanttemp);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engcoolanttemp = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::et1_engine_temperature_1__engfueltemp1);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engfueltemp1 = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::et1_engine_temperature_1__engoiltemp1);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engoiltemp1 = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::et1_engine_temperature_1__engturbooiltemp);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engturbooiltemp = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::et1_engine_temperature_1__engintercoolertemp);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engintercoolertemp = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::et1_engine_temperature_1__engintercoolerthermostatopening);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engintercoolerthermostatopening = *v;
    }

    return msg;
}

auto build_lfe1_fuel_economy_liquid_1_from_store(const ValueStore& store)
    -> std::expected<Lfe1FuelEconomyLiquid1, BuildError>
{
    Lfe1FuelEconomyLiquid1 msg{};

    {
        auto v = store.try_get_f64(SignalId::lfe1_fuel_economy_liquid_1__engfuelrate);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engfuelrate = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::lfe1_fuel_economy_liquid_1__enginstantaneousfueleconomy);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.enginstantaneousfueleconomy = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::lfe1_fuel_economy_liquid_1__engaveragefueleconomy);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engaveragefueleconomy = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve1pos);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engthrottlevalve1pos = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve2pos);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engthrottlevalve2pos = *v;
    }

    return msg;
}

auto build_transportprotocol_header_from_store(const ValueStore& store)
    -> std::expected<TransportprotocolHeader, BuildError>
{
    TransportprotocolHeader msg{};

    {
        auto v = store.try_get_u8(SignalId::transportprotocol_header__controlbyte);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.controlbyte = *v;
    }
    {
        auto v = store.try_get_u16(SignalId::transportprotocol_header__totalmessagesizeeoma);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.totalmessagesizeeoma = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::transportprotocol_header__connectionabortreason);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.connectionabortreason = *v;
    }
    {
        auto v = store.try_get_u16(SignalId::transportprotocol_header__totalmessagesize);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.totalmessagesize = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::transportprotocol_header__numberofpacketsthatcanbesent);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.numberofpacketsthatcanbesent = *v;
    }
    {
        auto v = store.try_get_u16(SignalId::transportprotocol_header__totalmessagesizebam);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.totalmessagesizebam = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::transportprotocol_header__nextpacketnumbertobesent);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.nextpacketnumbertobesent = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::transportprotocol_header__totalnumberofpackets);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.totalnumberofpackets = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::transportprotocol_header__totalnumberofpacketseoma);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.totalnumberofpacketseoma = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::transportprotocol_header__totalnumberofpacketsbam);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.totalnumberofpacketsbam = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::transportprotocol_header__maximumnumberofpackets);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.maximumnumberofpackets = *v;
    }
    {
        auto v = store.try_get_u32(SignalId::transportprotocol_header__pgnumber);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.pgnumber = *v;
    }

    return msg;
}

auto build_transportprotocol_data_from_store(const ValueStore& store)
    -> std::expected<TransportprotocolData, BuildError>
{
    TransportprotocolData msg{};

    {
        auto v = store.try_get_u8(SignalId::transportprotocol_data__sequencenumber);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.sequencenumber = *v;
    }

    return msg;
}

auto build_dm01_active_diagnostics_from_store(const ValueStore& store)
    -> std::expected<Dm01ActiveDiagnostics, BuildError>
{
    Dm01ActiveDiagnostics msg{};

    {
        auto v = store.try_get_u8(SignalId::dm01_active_diagnostics__protectlampstatus);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.protectlampstatus = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::dm01_active_diagnostics__amberwarninglampstatus);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.amberwarninglampstatus = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::dm01_active_diagnostics__redstoplampstate);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.redstoplampstate = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::dm01_active_diagnostics__malfunctionindicatorlampstatus);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.malfunctionindicatorlampstatus = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::dm01_active_diagnostics__flashprotectlamp);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.flashprotectlamp = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::dm01_active_diagnostics__flashamberwarninglamp);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.flashamberwarninglamp = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::dm01_active_diagnostics__flashredstoplamp);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.flashredstoplamp = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::dm01_active_diagnostics__flashmalfuncindicatorlamp);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.flashmalfuncindicatorlamp = *v;
    }
    {
        auto v = store.try_get_u32(SignalId::dm01_active_diagnostics__dtc1);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.dtc1 = *v;
    }

    return msg;
}

auto build_tsc1_31_from_store(const ValueStore& store)
    -> std::expected<Tsc131, BuildError>
{
    Tsc131 msg{};

    {
        auto v = store.try_get_u8(SignalId::tsc1_31__engoverridectrlmode);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engoverridectrlmode = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_31__engrequestedspeedctrlconditions);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engrequestedspeedctrlconditions = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_31__overridectrlmodepriority);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.overridectrlmodepriority = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::tsc1_31__engrequestedspeed_speedlimit);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engrequestedspeed_speedlimit = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::tsc1_31__engrequestedtorque_torquelimit);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engrequestedtorque_torquelimit = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_31__tsc1transrate);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.tsc1transrate = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_31__tsc1ctrlpurpose);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.tsc1ctrlpurpose = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_31__engrequestedtorquehighresolution);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engrequestedtorquehighresolution = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_31__messagecounter);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.messagecounter = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_31__messagechecksum);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.messagechecksum = *v;
    }

    return msg;
}

auto build_cac1_charge_air_cooler_1_from_store(const ValueStore& store)
    -> std::expected<Cac1ChargeAirCooler1, BuildError>
{
    Cac1ChargeAirCooler1 msg{};

    {
        auto v = store.try_get_f64(SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_intak);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_charge_air_cooler_1_intak = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_ambie);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_charge_air_cooler_1_ambie = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_effic);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_charge_air_cooler_1_effic = *v;
    }

    return msg;
}

auto build_hours_engine_hours_revolutions_from_store(const ValueStore& store)
    -> std::expected<HoursEngineHoursRevolutions, BuildError>
{
    HoursEngineHoursRevolutions msg{};

    {
        auto v = store.try_get_f64(SignalId::hours_engine_hours_revolutions__engine_total_hours_of_operation);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_total_hours_of_operation = *v;
    }
    {
        auto v = store.try_get_u32(SignalId::hours_engine_hours_revolutions__engine_total_revolutions_249);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_total_revolutions_249 = *v;
    }

    return msg;
}

auto build_tci5_turbocharger_information_5_from_store(const ValueStore& store)
    -> std::expected<Tci5TurbochargerInformation5, BuildError>
{
    Tci5TurbochargerInformation5 msg{};

    {
        auto v = store.try_get_f64(SignalId::tci5_turbocharger_information_5__engine_turbocharger_1_turbine_ou);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_turbocharger_1_turbine_ou = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::tci5_turbocharger_information_5__engine_turbocharger_2_turbine_ou);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_turbocharger_2_turbine_ou = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::tci5_turbocharger_information_5__engine_turbocharger_3_turbine_ou);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_turbocharger_3_turbine_ou = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::tci5_turbocharger_information_5__engine_turbocharger_4_turbine_ou);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_turbocharger_4_turbine_ou = *v;
    }

    return msg;
}

auto build_vep1_vehicle_electrical_power_1_from_store(const ValueStore& store)
    -> std::expected<Vep1VehicleElectricalPower1, BuildError>
{
    Vep1VehicleElectricalPower1 msg{};

    {
        auto v = store.try_get_f64(SignalId::vep1_vehicle_electrical_power_1__net_battery_current_114);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.net_battery_current_114 = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::vep1_vehicle_electrical_power_1__alternator_current_115);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.alternator_current_115 = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::vep1_vehicle_electrical_power_1__charging_system_potential_volta);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.charging_system_potential_volta = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::vep1_vehicle_electrical_power_1__battery_potential_power_input_1);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.battery_potential_power_input_1 = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::vep1_vehicle_electrical_power_1__keyswitch_battery_potential_158);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.keyswitch_battery_potential_158 = *v;
    }

    return msg;
}

auto build_eec20_electronic_engine_control_from_store(const ValueStore& store)
    -> std::expected<Eec20ElectronicEngineControl, BuildError>
{
    Eec20ElectronicEngineControl msg{};

    {
        auto v = store.try_get_f64(SignalId::eec20_electronic_engine_control__absolute_engine_load);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.absolute_engine_load = *v;
    }

    return msg;
}

auto build_easi_engine_air_system_info_from_store(const ValueStore& store)
    -> std::expected<EasiEngineAirSystemInfo, BuildError>
{
    EasiEngineAirSystemInfo msg{};

    {
        auto v = store.try_get_f64(SignalId::easi_engine_air_system_info__engine_intake_maf);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engine_intake_maf = *v;
    }

    return msg;
}

auto build_tsc1_03_from_store(const ValueStore& store)
    -> std::expected<Tsc103, BuildError>
{
    Tsc103 msg{};

    {
        auto v = store.try_get_u8(SignalId::tsc1_03__engoverridectrlmode);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engoverridectrlmode = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_03__engrequestedspeedctrlconditions);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engrequestedspeedctrlconditions = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_03__overridectrlmodepriority);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.overridectrlmodepriority = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::tsc1_03__engrequestedspeed_speedlimit);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engrequestedspeed_speedlimit = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::tsc1_03__engrequestedtorque_torquelimit);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engrequestedtorque_torquelimit = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_03__tsc1transrate);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.tsc1transrate = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_03__tsc1ctrlpurpose);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.tsc1ctrlpurpose = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_03__engrequestedtorquehighresolution);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engrequestedtorquehighresolution = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_03__messagecounter);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.messagecounter = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_03__messagechecksum);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.messagechecksum = *v;
    }

    return msg;
}

auto build_tsc1_0b_from_store(const ValueStore& store)
    -> std::expected<Tsc10b, BuildError>
{
    Tsc10b msg{};

    {
        auto v = store.try_get_u8(SignalId::tsc1_0b__engoverridectrlmode);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engoverridectrlmode = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_0b__engrequestedspeedctrlconditions);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engrequestedspeedctrlconditions = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_0b__overridectrlmodepriority);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.overridectrlmodepriority = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::tsc1_0b__engrequestedspeed_speedlimit);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engrequestedspeed_speedlimit = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::tsc1_0b__engrequestedtorque_torquelimit);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engrequestedtorque_torquelimit = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_0b__tsc1transrate);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.tsc1transrate = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_0b__tsc1ctrlpurpose);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.tsc1ctrlpurpose = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_0b__engrequestedtorquehighresolution);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engrequestedtorquehighresolution = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_0b__messagecounter);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.messagecounter = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tsc1_0b__messagechecksum);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.messagechecksum = *v;
    }

    return msg;
}

auto build_dm07_from_store(const ValueStore& store)
    -> std::expected<Dm07, BuildError>
{
    Dm07 msg{};

    {
        auto v = store.try_get_u8(SignalId::dm07__testidentifier);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.testidentifier = *v;
    }
    {
        auto v = store.try_get_u16(SignalId::dm07__spn1);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.spn1 = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::dm07__failuremodeidentifier1);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.failuremodeidentifier1 = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::dm07__spn1high);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.spn1high = *v;
    }

    return msg;
}

auto build_dm08_from_store(const ValueStore& store)
    -> std::expected<Dm08, BuildError>
{
    Dm08 msg{};

    {
        auto v = store.try_get_u8(SignalId::dm08__testidentifier);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.testidentifier = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::dm08__testtype);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.testtype = *v;
    }
    {
        auto v = store.try_get_u16(SignalId::dm08__testvalue);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.testvalue = *v;
    }
    {
        auto v = store.try_get_u16(SignalId::dm08__testlimitmaximum);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.testlimitmaximum = *v;
    }
    {
        auto v = store.try_get_u16(SignalId::dm08__testlimitminimum);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.testlimitminimum = *v;
    }

    return msg;
}

auto build_erc1_electronic_retarder_cntrl_from_store(const ValueStore& store)
    -> std::expected<Erc1ElectronicRetarderCntrl, BuildError>
{
    Erc1ElectronicRetarderCntrl msg{};

    {
        auto v = store.try_get_u8(SignalId::erc1_electronic_retarder_cntrl__retardertorquemode);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.retardertorquemode = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.retarderenablebrakeassistswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.retarderenableshiftassistswitch = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::erc1_electronic_retarder_cntrl__actualretarderpercenttorque);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.actualretarderpercenttorque = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::erc1_electronic_retarder_cntrl__intendedretarderpercenttorque);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.intendedretarderpercenttorque = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::erc1_electronic_retarder_cntrl__engcoolantloadincrease);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engcoolantloadincrease = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::erc1_electronic_retarder_cntrl__retarderrequestingbrakelight);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.retarderrequestingbrakelight = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.retarderroadspeedlimitswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.retarderroadspeedexceededstatus = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::erc1_electronic_retarder_cntrl__srcaddrssofcntrllngdvcfrrtrdrctr);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.srcaddrssofcntrllngdvcfrrtrdrctr = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::erc1_electronic_retarder_cntrl__drvrsdemandretarderpercenttorque);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.drvrsdemandretarderpercenttorque = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::erc1_electronic_retarder_cntrl__retarderselectionnonengine);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.retarderselectionnonengine = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::erc1_electronic_retarder_cntrl__actlmxavlblretarderpercenttorque);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.actlmxavlblretarderpercenttorque = *v;
    }

    return msg;
}

auto build_etc1_electronic_trans_cntrl_1_from_store(const ValueStore& store)
    -> std::expected<Etc1ElectronicTransCntrl1, BuildError>
{
    Etc1ElectronicTransCntrl1 msg{};

    {
        auto v = store.try_get_u8(SignalId::etc1_electronic_trans_cntrl_1__transdrivelineengaged);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transdrivelineengaged = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.trnstorqueconverterlockupengaged = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::etc1_electronic_trans_cntrl_1__transshiftinprocess);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transshiftinprocess = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.trnstrqcnvrtrlckptrnstninprocess = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::etc1_electronic_trans_cntrl_1__transoutputshaftspeed);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transoutputshaftspeed = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::etc1_electronic_trans_cntrl_1__percentclutchslip);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.percentclutchslip = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engmomentaryoverspeedenable = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::etc1_electronic_trans_cntrl_1__progressiveshiftdisable);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.progressiveshiftdisable = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.momentaryengmaxpowerenable = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::etc1_electronic_trans_cntrl_1__transinputshaftspeed);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transinputshaftspeed = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::etc1_electronic_trans_cntrl_1__srcaddrssofcntrllngdvcfrtrnsctrl);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.srcaddrssofcntrllngdvcfrtrnsctrl = *v;
    }

    return msg;
}

auto build_etc2_electronic_trans_cntrl_2_from_store(const ValueStore& store)
    -> std::expected<Etc2ElectronicTransCntrl2, BuildError>
{
    Etc2ElectronicTransCntrl2 msg{};

    {
        auto v = store.try_get_f64(SignalId::etc2_electronic_trans_cntrl_2__transselectedgear);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transselectedgear = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::etc2_electronic_trans_cntrl_2__transactualgearratio);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transactualgearratio = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::etc2_electronic_trans_cntrl_2__transcurrentgear);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transcurrentgear = *v;
    }
    {
        auto v = store.try_get_u16(SignalId::etc2_electronic_trans_cntrl_2__transrequestedrange);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transrequestedrange = *v;
    }
    {
        auto v = store.try_get_u16(SignalId::etc2_electronic_trans_cntrl_2__transcurrentrange);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transcurrentrange = *v;
    }

    return msg;
}

auto build_rqst_00_5e_from_store(const ValueStore& store)
    -> std::expected<Rqst005e, BuildError>
{
    Rqst005e msg{};

    {
        auto v = store.try_get_u32(SignalId::rqst_00_5e__parametergroupnumber);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.parametergroupnumber = *v;
    }

    return msg;
}

auto build_rqst_00_21_from_store(const ValueStore& store)
    -> std::expected<Rqst0021, BuildError>
{
    Rqst0021 msg{};

    {
        auto v = store.try_get_u32(SignalId::rqst_00_21__parametergroupnumber);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.parametergroupnumber = *v;
    }

    return msg;
}

auto build_rqst_global_5e_from_store(const ValueStore& store)
    -> std::expected<RqstGlobal5e, BuildError>
{
    RqstGlobal5e msg{};

    {
        auto v = store.try_get_u32(SignalId::rqst_global_5e__parametergroupnumber);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.parametergroupnumber = *v;
    }

    return msg;
}

auto build_rqst_global_03_from_store(const ValueStore& store)
    -> std::expected<RqstGlobal03, BuildError>
{
    RqstGlobal03 msg{};

    {
        auto v = store.try_get_u32(SignalId::rqst_global_03__parametergroupnumber);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.parametergroupnumber = *v;
    }

    return msg;
}

auto build_tci_transfer_case_information_from_store(const ValueStore& store)
    -> std::expected<TciTransferCaseInformation, BuildError>
{
    TciTransferCaseInformation msg{};

    {
        auto v = store.try_get_u8(SignalId::tci_transfer_case_information__transfercasestatus);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transfercasestatus = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tci_transfer_case_information__dirstatus);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.dirstatus = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::tci_transfer_case_information__actualgearratio);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.actualgearratio = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tci_transfer_case_information__messagecounter);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.messagecounter = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::tci_transfer_case_information__messagechecksum);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.messagechecksum = *v;
    }

    return msg;
}

auto build_trf1_transmission_fluids_1_from_store(const ValueStore& store)
    -> std::expected<Trf1TransmissionFluids1, BuildError>
{
    Trf1TransmissionFluids1 msg{};

    {
        auto v = store.try_get_u8(SignalId::trf1_transmission_fluids_1__clutchpress);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.clutchpress = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::trf1_transmission_fluids_1__transoillevel1);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transoillevel1 = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::trf1_transmission_fluids_1__transfilterdiffpress);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transfilterdiffpress = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::trf1_transmission_fluids_1__transoilpress);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transoilpress = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::trf1_transmission_fluids_1__transoiltemp1);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transoiltemp1 = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::trf1_transmission_fluids_1__transoillevel1high_low);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transoillevel1high_low = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::trf1_transmission_fluids_1__transoillevel1countdowntimer);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transoillevel1countdowntimer = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::trf1_transmission_fluids_1__transoillevel1measurementstatus);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.transoillevel1measurementstatus = *v;
    }

    return msg;
}

auto build_ccss_cruise_control_vehicle_spd_from_store(const ValueStore& store)
    -> std::expected<CcssCruiseControlVehicleSpd, BuildError>
{
    CcssCruiseControlVehicleSpd msg{};

    {
        auto v = store.try_get_u8(SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.maxvehiclespeedlimit = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccss_cruise_control_vehicle_spd__cruisectrlhighsetlimitspeed);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.cruisectrlhighsetlimitspeed = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccss_cruise_control_vehicle_spd__cruisectrllowsetlimitspeed);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.cruisectrllowsetlimitspeed = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit6808);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.maxvehiclespeedlimit6808 = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccss_cruise_control_vehicle_spd__ctrlsyslowsetlmtspd);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.ctrlsyslowsetlmtspd = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccss_cruise_control_vehicle_spd__ctrldiscmdsupport);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.ctrldiscmdsupport = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.ctrlresumecmdsupport = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.ctrlpausecmdsupport = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.ctrlsetcmdsupport = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccss_cruise_control_vehicle_spd__powertrainadaptivecctype);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.powertrainadaptivecctype = *v;
    }

    return msg;
}

auto build_ccvs1_cruise_control_vehspd_from_store(const ValueStore& store)
    -> std::expected<Ccvs1CruiseControlVehspd, BuildError>
{
    Ccvs1CruiseControlVehspd msg{};

    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__twospeedaxleswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.twospeedaxleswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__parkingbrakeswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.parkingbrakeswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlpauseswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.cruisectrlpauseswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.parkbrakereleaseinhibitrq = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::ccvs1_cruise_control_vehspd__wheelbasedvehiclespeed);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.wheelbasedvehiclespeed = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlactive);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.cruisectrlactive = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlenableswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.cruisectrlenableswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__brakeswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.brakeswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__clutchswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.clutchswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.cruisectrlsetswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlcoastswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.cruisectrlcoastswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlresumeswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.cruisectrlresumeswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.cruisectrlaccelerateswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetspeed);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.cruisectrlsetspeed = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__ptogovernorstate);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.ptogovernorstate = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__cruisectrlstates);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.cruisectrlstates = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__engidleincrementswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engidleincrementswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__engidledecrementswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engidledecrementswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__engtestmodeswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engtestmodeswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ccvs1_cruise_control_vehspd__engshutdownoverrideswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engshutdownoverrideswitch = *v;
    }

    return msg;
}

auto build_ebc1_electronic_brake_cntrl_from_store(const ValueStore& store)
    -> std::expected<Ebc1ElectronicBrakeCntrl, BuildError>
{
    Ebc1ElectronicBrakeCntrl msg{};

    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__asrengctrlactive);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.asrengctrlactive = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__asrbrakectrlactive);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.asrbrakectrlactive = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__antilockbrakingactive);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.antilockbrakingactive = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__ebsbrakeswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.ebsbrakeswitch = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::ebc1_electronic_brake_cntrl__brakepedalpos);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.brakepedalpos = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__absoffroadswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.absoffroadswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__asroffroadswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.asroffroadswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__asrhillholderswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.asrhillholderswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__tractionctrloverrideswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.tractionctrloverrideswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__accelinterlockswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.accelinterlockswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__engderateswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engderateswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__engauxshutdownswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engauxshutdownswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__remoteaccelenableswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.remoteaccelenableswitch = *v;
    }
    {
        auto v = store.try_get_f64(SignalId::ebc1_electronic_brake_cntrl__engretarderselection);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engretarderselection = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__absfullyoperational);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.absfullyoperational = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__ebsredwarningsignal);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.ebsredwarningsignal = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.abs_ebsamberwarningsignal = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__atc_asrinformationsignal);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.atc_asrinformationsignal = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__srcaddrssofcntrllngdvcfrbrkectrl);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.srcaddrssofcntrllngdvcfrbrkectrl = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__railroadmodesw);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.railroadmodesw = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__haltbrakeswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.haltbrakeswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__trailerabsstatus);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.trailerabsstatus = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.trctrmntdtrailerabswarningsignal = *v;
    }

    return msg;
}

auto build_shutdn_from_store(const ValueStore& store)
    -> std::expected<Shutdn, BuildError>
{
    Shutdn msg{};

    {
        auto v = store.try_get_u8(SignalId::shutdn__engidleshutdownhasshutdowneng);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engidleshutdownhasshutdowneng = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__engidleshutdowndriveralertmode);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engidleshutdowndriveralertmode = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__engidleshutdowntimeroverride);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engidleshutdowntimeroverride = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__engidleshutdowntimerstate);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engidleshutdowntimerstate = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__engidleshutdowntimerfunction);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engidleshutdowntimerfunction = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__a_chighpressfanswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.a_chighpressfanswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__refrigerantlowpressswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.refrigerantlowpressswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__refrigeranthighpressswitch);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.refrigeranthighpressswitch = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__engwaittostartlamp);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engwaittostartlamp = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__engprtectionsystemhasshutdowneng);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engprtectionsystemhasshutdowneng = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__engprtctnsystmapprachingshutdown);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engprtctnsystmapprachingshutdown = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__engprotectionsystemtimeroverride);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engprotectionsystemtimeroverride = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__engprotectionsystemtimerstate);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engprotectionsystemtimerstate = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__engprotectionsystemconfig);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engprotectionsystemconfig = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__engalarmacknowledge);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engalarmacknowledge = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__engalarmoutputcmdstatus);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engalarmoutputcmdstatus = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__engairshutoffcmdstatus);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engairshutoffcmdstatus = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__engoverspeedtest);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engoverspeedtest = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__engairshutoffstatus);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engairshutoffstatus = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__ptoshutdownhasshutdowneng);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.ptoshutdownhasshutdowneng = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__clntlvlengprtctionshutdownstatus);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.clntlvlengprtctionshutdownstatus = *v;
    }
    {
        auto v = store.try_get_u8(SignalId::shutdn__engoilpresssw);
        if (!v) {
            return std::unexpected(BuildError::missing_signal);
        }
        msg.engoilpresssw = *v;
    }

    return msg;
}

auto build_message_from_store(MessageId id, const ValueStore& store)
    -> std::expected<MessageVariant, BuildError>
{
    switch (id) {
    case MessageId::eec5_electronic_engine_control_5: {
        auto built = build_eec5_electronic_engine_control_5_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::eec9_electronic_engine_control_9: {
        auto built = build_eec9_electronic_engine_control_9_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::ebcc_engine_exhaust_brake_cont: {
        auto built = build_ebcc_engine_exhaust_brake_cont_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::et3_engine_temperature_3: {
        auto built = build_et3_engine_temperature_3_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::dm21_diagnostic_readiness_2: {
        auto built = build_dm21_diagnostic_readiness_2_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::dm26_diagnostic_readiness_3: {
        auto built = build_dm26_diagnostic_readiness_3_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::ic1_intake_exhaust_cond_1: {
        auto built = build_ic1_intake_exhaust_cond_1_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::amb_ambient_conditions: {
        auto built = build_amb_ambient_conditions_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::eec1_electronic_engine_control_1: {
        auto built = build_eec1_electronic_engine_control_1_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::eec2_electronic_engine_control_2: {
        auto built = build_eec2_electronic_engine_control_2_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::eec3_electronic_engine_control_3: {
        auto built = build_eec3_electronic_engine_control_3_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::efl_p1_eng_fluid_level_press_1: {
        auto built = build_efl_p1_eng_fluid_level_press_1_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::efl_p2_eng_fluid_level_press_2: {
        auto built = build_efl_p2_eng_fluid_level_press_2_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::et1_engine_temperature_1: {
        auto built = build_et1_engine_temperature_1_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::lfe1_fuel_economy_liquid_1: {
        auto built = build_lfe1_fuel_economy_liquid_1_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::transportprotocol_header: {
        auto built = build_transportprotocol_header_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::transportprotocol_data: {
        auto built = build_transportprotocol_data_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::dm01_active_diagnostics: {
        auto built = build_dm01_active_diagnostics_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::tsc1_31: {
        auto built = build_tsc1_31_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::cac1_charge_air_cooler_1: {
        auto built = build_cac1_charge_air_cooler_1_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::hours_engine_hours_revolutions: {
        auto built = build_hours_engine_hours_revolutions_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::tci5_turbocharger_information_5: {
        auto built = build_tci5_turbocharger_information_5_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::vep1_vehicle_electrical_power_1: {
        auto built = build_vep1_vehicle_electrical_power_1_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::eec20_electronic_engine_control: {
        auto built = build_eec20_electronic_engine_control_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::easi_engine_air_system_info: {
        auto built = build_easi_engine_air_system_info_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::tsc1_03: {
        auto built = build_tsc1_03_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::tsc1_0b: {
        auto built = build_tsc1_0b_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::dm07: {
        auto built = build_dm07_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::dm08: {
        auto built = build_dm08_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::erc1_electronic_retarder_cntrl: {
        auto built = build_erc1_electronic_retarder_cntrl_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::etc1_electronic_trans_cntrl_1: {
        auto built = build_etc1_electronic_trans_cntrl_1_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::etc2_electronic_trans_cntrl_2: {
        auto built = build_etc2_electronic_trans_cntrl_2_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::rqst_00_5e: {
        auto built = build_rqst_00_5e_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::rqst_00_21: {
        auto built = build_rqst_00_21_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::rqst_global_5e: {
        auto built = build_rqst_global_5e_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::rqst_global_03: {
        auto built = build_rqst_global_03_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::tci_transfer_case_information: {
        auto built = build_tci_transfer_case_information_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::trf1_transmission_fluids_1: {
        auto built = build_trf1_transmission_fluids_1_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::ccss_cruise_control_vehicle_spd: {
        auto built = build_ccss_cruise_control_vehicle_spd_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::ccvs1_cruise_control_vehspd: {
        auto built = build_ccvs1_cruise_control_vehspd_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::ebc1_electronic_brake_cntrl: {
        auto built = build_ebc1_electronic_brake_cntrl_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    case MessageId::shutdn: {
        auto built = build_shutdn_from_store(store);
        if (!built) {
            return std::unexpected(built.error());
        }
        return MessageVariant{*built};
    }
    default:
        return std::unexpected(BuildError::unsupported_message);
    }
}

} // namespace duramax