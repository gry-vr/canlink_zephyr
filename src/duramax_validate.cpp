#include "duramax/duramax_validate.hpp"
#include "duramax/duramax_metadata.hpp"

#include <cmath>
#include <cstdint>
#include <expected>
#include <limits>
#include <type_traits>
#include <variant>

namespace duramax {
namespace detail {

constexpr auto mask64(unsigned width) -> std::uint64_t {
    return (width >= 64U) ? ~0ULL : ((1ULL << width) - 1ULL);
}

inline auto fits_unsigned(std::uint64_t value, unsigned bit_length) -> bool {
    if (bit_length >= 64U) {
        return true;
    }
    return value <= mask64(bit_length);
}

inline auto fits_signed(std::int64_t value, unsigned bit_length) -> bool {
    if (bit_length == 0U || bit_length >= 64U) {
        return true;
    }

    const std::int64_t minv =
        -(static_cast<std::int64_t>(1ULL << (bit_length - 1U)));
    const std::int64_t maxv =
         static_cast<std::int64_t>((1ULL << (bit_length - 1U)) - 1ULL);

    return value >= minv && value <= maxv;
}

inline auto validate_unsigned_physical(double physical,
                                       double scale,
                                       double offset,
                                       unsigned bit_length) -> bool
{
    if (scale == 0.0) {
        return false;
    }

    const double raw_f = (physical - offset) / scale;
    if (!std::isfinite(raw_f)) {
        return false;
    }

    const double rounded = std::round(raw_f);
    if (rounded < 0.0) {
        return false;
    }

    if (rounded > static_cast<double>(std::numeric_limits<std::uint64_t>::max())) {
        return false;
    }

    return fits_unsigned(static_cast<std::uint64_t>(rounded), bit_length);
}

inline auto validate_signed_physical(double physical,
                                     double scale,
                                     double offset,
                                     unsigned bit_length) -> bool
{
    if (scale == 0.0) {
        return false;
    }

    const double raw_f = (physical - offset) / scale;
    if (!std::isfinite(raw_f)) {
        return false;
    }

    const double rounded = std::round(raw_f);
    if (rounded < static_cast<double>(std::numeric_limits<std::int64_t>::min()) ||
        rounded > static_cast<double>(std::numeric_limits<std::int64_t>::max())) {
        return false;
    }

    return fits_signed(static_cast<std::int64_t>(rounded), bit_length);
}

} // namespace detail

template <>
auto validate_message<Eec5ElectronicEngineControl5>(const Eec5ElectronicEngineControl5& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::validate_unsigned_physical(
            msg.engine_turbocharger_1_calculated,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec5_electronic_engine_control_5__engine_turbocharger_1_calculated,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.commanded_vgt_position,
            0.0025,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec5_electronic_engine_control_5__commanded_vgt_position,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engine_variable_geometry_turboch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec5_electronic_engine_control_5__engine_variable_geometry_turboch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engine_fuel_control_control_mode),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec5_electronic_engine_control_5__engine_fuel_control_control_mode,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engine_vgt_control_mode),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec5_electronic_engine_control_5__engine_vgt_control_mode,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.actual_vgt_position,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec5_electronic_engine_control_5__actual_vgt_position,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Eec9ElectronicEngineControl9>(const Eec9ElectronicEngineControl9& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::validate_unsigned_physical(
            msg.engine_exhaust_gas_recirculation,
            0.0025,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec9_electronic_engine_control_9__engine_exhaust_gas_recirculation,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.commanded_fuel_rail_pressure,
            0.00390625,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec9_electronic_engine_control_9__commanded_fuel_rail_pressure,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.commanded_engine_fuel_injection,
            0.00390625,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec9_electronic_engine_control_9__commanded_engine_fuel_injection,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<EbccEngineExhaustBrakeCont>(const EbccEngineExhaustBrakeCont& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.actual_boost_pressure),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__actual_boost_pressure,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.desired_boost_pressure),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__desired_boost_pressure,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engine_exhaust_brake_actuator_co,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__engine_exhaust_brake_actuator_co,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engine_turbocharger_2_turbine_ou),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__engine_turbocharger_2_turbine_ou,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.desired_engine_turbocharger_2_tu),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__desired_engine_turbocharger_2_tu,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Et3EngineTemperature3>(const Et3EngineTemperature3& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::validate_unsigned_physical(
            msg.engine_intake_manifold_1_air_tem,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et3_engine_temperature_3__engine_intake_manifold_1_air_tem,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engine_coolant_temperature_high,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et3_engine_temperature_3__engine_coolant_temperature_high,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engine_intake_valve_actuation_sy,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et3_engine_temperature_3__engine_intake_valve_actuation_sy,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engine_cac_outlet_temperature,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et3_engine_temperature_3__engine_cac_outlet_temperature,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Dm21DiagnosticReadiness2>(const Dm21DiagnosticReadiness2& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engine_run_time_with_mil_on),
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm21_diagnostic_readiness_2__engine_run_time_with_mil_on,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Dm26DiagnosticReadiness3>(const Dm26DiagnosticReadiness3& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.time_since_engine_start),
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm26_diagnostic_readiness_3__time_since_engine_start,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Ic1IntakeExhaustCond1>(const Ic1IntakeExhaustCond1& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::validate_unsigned_physical(
            msg.aft1dpfinpress,
            0.5,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__aft1dpfinpress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engintakemanifold1press),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1press,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engintakemanifold1temp,
            1.0,
            -40.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1temp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engairintakepress),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engairintakepress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engairfilter1diffpress,
            0.05,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engairfilter1diffpress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engexhaustgastemp,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engexhaustgastemp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engcoolantfilterdiffpress,
            0.5,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engcoolantfilterdiffpress,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<AmbAmbientConditions>(const AmbAmbientConditions& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::validate_unsigned_physical(
            msg.barometric_pressurebarometric_pr,
            0.5,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::amb_ambient_conditions__barometric_pressurebarometric_pr,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.cabinteriortemp,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::amb_ambient_conditions__cabinteriortemp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.ambient_air_temperature,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::amb_ambient_conditions__ambient_air_temperature,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engine_air_intake_temperature,
            1.0,
            -40.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::amb_ambient_conditions__engine_air_intake_temperature,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.roadsurfacetemp,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::amb_ambient_conditions__roadsurfacetemp,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Eec1ElectronicEngineControl1>(const Eec1ElectronicEngineControl1& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engine_torque_mode),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__engine_torque_mode,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.actlengprcnttorquehighresolution),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__actlengprcnttorquehighresolution,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.drivers_demand_engine_prcnt_torq,
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__drivers_demand_engine_prcnt_torq,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.actual_engine_percent_torque,
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__actual_engine_percent_torque,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engine_speed,
            0.125,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__engine_speed,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.srcaddrssofcntrllngdvcforengctrl),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__srcaddrssofcntrllngdvcforengctrl,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engstartermode),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__engstartermode,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engine_demand_percent_torque,
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__engine_demand_percent_torque,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Eec2ElectronicEngineControl2>(const Eec2ElectronicEngineControl2& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.accelpedal1lowidleswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__accelpedal1lowidleswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.accelpedalkickdownswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__accelpedalkickdownswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.roadspeedlimitstatus),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__roadspeedlimitstatus,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.accelpedal2lowidleswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__accelpedal2lowidleswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.accelpedalpos1,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__accelpedalpos1,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engpercentloadatcurrentspeed),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__engpercentloadatcurrentspeed,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.remoteaccelpedalpos,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__remoteaccelpedalpos,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.accelpedalpos2,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__accelpedalpos2,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.vhcleaccelerationratelimitstatus),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.mmntaryengmaxpowerenablefeedback),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.dpfthermalmanagementactive),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__dpfthermalmanagementactive,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.scrthermalmanagementactive),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__scrthermalmanagementactive,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.actlmaxavailableengpercenttorque,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__actlmaxavailableengpercenttorque,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.estpumpingpercenttorque,
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__estpumpingpercenttorque,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Eec3ElectronicEngineControl3>(const Eec3ElectronicEngineControl3& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::validate_unsigned_physical(
            msg.nominalfrictionpercenttorque,
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__nominalfrictionpercenttorque,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.enginesdesiredoperatingspeed,
            0.125,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__enginesdesiredoperatingspeed,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engnsdsrdoprtngspdasymmtryadjstm),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__engnsdsrdoprtngspdasymmtryadjstm,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.estengprsiticlossespercenttorque,
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__estengprsiticlossespercenttorque,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.aft1exhgasmfr,
            0.2,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__aft1exhgasmfr,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.aft1indewpoint),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__aft1indewpoint,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.aft1exhdewpoint),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__aft1exhdewpoint,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.aft2indewpoint),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__aft2indewpoint,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.aft2exhdewpoint),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__aft2exhdewpoint,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<EflP1EngFluidLevelPress1>(const EflP1EngFluidLevelPress1& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engfueldeliverypress),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engfueldeliverypress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engexcrankcaseblowbypress,
            0.05,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engexcrankcaseblowbypress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engoillevel,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engoillevel,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engoilpress),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engoilpress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engcrankcasepress,
            0.0078125,
            -250.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engcrankcasepress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engcoolantpress),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engcoolantpress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engcoolantlevel,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engcoolantlevel,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<EflP2EngFluidLevelPress2>(const EflP2EngFluidLevelPress2& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::validate_unsigned_physical(
            msg.enginjectionctrlpress,
            0.00390625,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p2_eng_fluid_level_press_2__enginjectionctrlpress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.enginjectormeteringrail1press,
            0.00390625,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail1press,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.enginjectortimingrail1press,
            0.00390625,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p2_eng_fluid_level_press_2__enginjectortimingrail1press,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.enginjectormeteringrail2press,
            0.00390625,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail2press,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Et1EngineTemperature1>(const Et1EngineTemperature1& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::validate_unsigned_physical(
            msg.engcoolanttemp,
            1.0,
            -40.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engcoolanttemp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engfueltemp1,
            1.0,
            -40.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engfueltemp1,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engoiltemp1,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engoiltemp1,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engturbooiltemp,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engturbooiltemp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engintercoolertemp,
            1.0,
            -40.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engintercoolertemp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engintercoolerthermostatopening,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engintercoolerthermostatopening,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Lfe1FuelEconomyLiquid1>(const Lfe1FuelEconomyLiquid1& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::validate_unsigned_physical(
            msg.engfuelrate,
            0.05,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::lfe1_fuel_economy_liquid_1__engfuelrate,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.enginstantaneousfueleconomy,
            0.00195312,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::lfe1_fuel_economy_liquid_1__enginstantaneousfueleconomy,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engaveragefueleconomy,
            0.00195312,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::lfe1_fuel_economy_liquid_1__engaveragefueleconomy,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engthrottlevalve1pos,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve1pos,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engthrottlevalve2pos,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve2pos,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<TransportprotocolHeader>(const TransportprotocolHeader& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.controlbyte),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__controlbyte,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.totalmessagesizeeoma),
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalmessagesizeeoma,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.connectionabortreason),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__connectionabortreason,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.totalmessagesize),
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalmessagesize,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.numberofpacketsthatcanbesent),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__numberofpacketsthatcanbesent,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.totalmessagesizebam),
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalmessagesizebam,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.nextpacketnumbertobesent),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__nextpacketnumbertobesent,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.totalnumberofpackets),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalnumberofpackets,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.totalnumberofpacketseoma),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalnumberofpacketseoma,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.totalnumberofpacketsbam),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalnumberofpacketsbam,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.maximumnumberofpackets),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__maximumnumberofpackets,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.pgnumber),
            24U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__pgnumber,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<TransportprotocolData>(const TransportprotocolData& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.sequencenumber),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_data__sequencenumber,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Dm01ActiveDiagnostics>(const Dm01ActiveDiagnostics& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.protectlampstatus),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__protectlampstatus,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.amberwarninglampstatus),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__amberwarninglampstatus,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.redstoplampstate),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__redstoplampstate,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.malfunctionindicatorlampstatus),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__malfunctionindicatorlampstatus,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.flashprotectlamp),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__flashprotectlamp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.flashamberwarninglamp),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__flashamberwarninglamp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.flashredstoplamp),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__flashredstoplamp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.flashmalfuncindicatorlamp),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__flashmalfuncindicatorlamp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.dtc1),
            32U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__dtc1,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Tsc131>(const Tsc131& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engoverridectrlmode),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__engoverridectrlmode,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engrequestedspeedctrlconditions),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__engrequestedspeedctrlconditions,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.overridectrlmodepriority),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__overridectrlmodepriority,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engrequestedspeed_speedlimit,
            0.125,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__engrequestedspeed_speedlimit,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engrequestedtorque_torquelimit,
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__engrequestedtorque_torquelimit,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.tsc1transrate),
            3U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__tsc1transrate,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.tsc1ctrlpurpose),
            5U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__tsc1ctrlpurpose,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engrequestedtorquehighresolution),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__engrequestedtorquehighresolution,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.messagecounter),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__messagecounter,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.messagechecksum),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__messagechecksum,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Cac1ChargeAirCooler1>(const Cac1ChargeAirCooler1& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::validate_unsigned_physical(
            msg.engine_charge_air_cooler_1_intak,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_intak,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engine_charge_air_cooler_1_ambie,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_ambie,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engine_charge_air_cooler_1_effic,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_effic,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<HoursEngineHoursRevolutions>(const HoursEngineHoursRevolutions& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::validate_unsigned_physical(
            msg.engine_total_hours_of_operation,
            0.05,
            0.0,
            32U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::hours_engine_hours_revolutions__engine_total_hours_of_operation,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engine_total_revolutions_249),
            32U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::hours_engine_hours_revolutions__engine_total_revolutions_249,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Tci5TurbochargerInformation5>(const Tci5TurbochargerInformation5& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::validate_unsigned_physical(
            msg.engine_turbocharger_1_turbine_ou,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci5_turbocharger_information_5__engine_turbocharger_1_turbine_ou,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engine_turbocharger_2_turbine_ou,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci5_turbocharger_information_5__engine_turbocharger_2_turbine_ou,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engine_turbocharger_3_turbine_ou,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci5_turbocharger_information_5__engine_turbocharger_3_turbine_ou,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engine_turbocharger_4_turbine_ou,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci5_turbocharger_information_5__engine_turbocharger_4_turbine_ou,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Vep1VehicleElectricalPower1>(const Vep1VehicleElectricalPower1& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::validate_unsigned_physical(
            msg.net_battery_current_114,
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::vep1_vehicle_electrical_power_1__net_battery_current_114,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.alternator_current_115),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::vep1_vehicle_electrical_power_1__alternator_current_115,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.charging_system_potential_volta,
            0.05,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::vep1_vehicle_electrical_power_1__charging_system_potential_volta,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.battery_potential_power_input_1,
            0.05,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::vep1_vehicle_electrical_power_1__battery_potential_power_input_1,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.keyswitch_battery_potential_158,
            0.05,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::vep1_vehicle_electrical_power_1__keyswitch_battery_potential_158,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Eec20ElectronicEngineControl>(const Eec20ElectronicEngineControl& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::validate_unsigned_physical(
            msg.absolute_engine_load,
            0.025,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec20_electronic_engine_control__absolute_engine_load,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<EasiEngineAirSystemInfo>(const EasiEngineAirSystemInfo& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::validate_unsigned_physical(
            msg.engine_intake_maf,
            0.000976562,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::easi_engine_air_system_info__engine_intake_maf,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Tsc103>(const Tsc103& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engoverridectrlmode),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__engoverridectrlmode,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engrequestedspeedctrlconditions),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__engrequestedspeedctrlconditions,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.overridectrlmodepriority),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__overridectrlmodepriority,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engrequestedspeed_speedlimit,
            0.125,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__engrequestedspeed_speedlimit,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engrequestedtorque_torquelimit,
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__engrequestedtorque_torquelimit,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.tsc1transrate),
            3U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__tsc1transrate,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.tsc1ctrlpurpose),
            5U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__tsc1ctrlpurpose,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engrequestedtorquehighresolution),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__engrequestedtorquehighresolution,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.messagecounter),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__messagecounter,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.messagechecksum),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__messagechecksum,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Tsc10b>(const Tsc10b& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engoverridectrlmode),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__engoverridectrlmode,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engrequestedspeedctrlconditions),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__engrequestedspeedctrlconditions,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.overridectrlmodepriority),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__overridectrlmodepriority,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engrequestedspeed_speedlimit,
            0.125,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__engrequestedspeed_speedlimit,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engrequestedtorque_torquelimit,
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__engrequestedtorque_torquelimit,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.tsc1transrate),
            3U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__tsc1transrate,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.tsc1ctrlpurpose),
            5U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__tsc1ctrlpurpose,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engrequestedtorquehighresolution),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__engrequestedtorquehighresolution,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.messagecounter),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__messagecounter,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.messagechecksum),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__messagechecksum,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Dm07>(const Dm07& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.testidentifier),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm07__testidentifier,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.spn1),
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm07__spn1,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.failuremodeidentifier1),
            5U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm07__failuremodeidentifier1,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.spn1high),
            3U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm07__spn1high,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Dm08>(const Dm08& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.testidentifier),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testidentifier,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.testtype),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testtype,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.testvalue),
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testvalue,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.testlimitmaximum),
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testlimitmaximum,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.testlimitminimum),
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testlimitminimum,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Erc1ElectronicRetarderCntrl>(const Erc1ElectronicRetarderCntrl& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.retardertorquemode),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retardertorquemode,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.retarderenablebrakeassistswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.retarderenableshiftassistswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.actualretarderpercenttorque,
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__actualretarderpercenttorque,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.intendedretarderpercenttorque,
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__intendedretarderpercenttorque,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engcoolantloadincrease),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__engcoolantloadincrease,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.retarderrequestingbrakelight),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderrequestingbrakelight,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.retarderroadspeedlimitswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.retarderroadspeedexceededstatus),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.srcaddrssofcntrllngdvcfrrtrdrctr),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__srcaddrssofcntrllngdvcfrrtrdrctr,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.drvrsdemandretarderpercenttorque,
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__drvrsdemandretarderpercenttorque,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.retarderselectionnonengine,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderselectionnonengine,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.actlmxavlblretarderpercenttorque,
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__actlmxavlblretarderpercenttorque,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Etc1ElectronicTransCntrl1>(const Etc1ElectronicTransCntrl1& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.transdrivelineengaged),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__transdrivelineengaged,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.trnstorqueconverterlockupengaged),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.transshiftinprocess),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__transshiftinprocess,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.trnstrqcnvrtrlckptrnstninprocess),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.transoutputshaftspeed,
            0.125,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__transoutputshaftspeed,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.percentclutchslip,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__percentclutchslip,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engmomentaryoverspeedenable),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.progressiveshiftdisable),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__progressiveshiftdisable,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.momentaryengmaxpowerenable),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.transinputshaftspeed,
            0.125,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__transinputshaftspeed,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.srcaddrssofcntrllngdvcfrtrnsctrl),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__srcaddrssofcntrllngdvcfrtrnsctrl,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Etc2ElectronicTransCntrl2>(const Etc2ElectronicTransCntrl2& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::validate_unsigned_physical(
            msg.transselectedgear,
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transselectedgear,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.transactualgearratio,
            0.001,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transactualgearratio,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.transcurrentgear,
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transcurrentgear,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.transrequestedrange),
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transrequestedrange,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.transcurrentrange),
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transcurrentrange,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Rqst005e>(const Rqst005e& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.parametergroupnumber),
            24U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::rqst_00_5e__parametergroupnumber,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Rqst0021>(const Rqst0021& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.parametergroupnumber),
            24U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::rqst_00_21__parametergroupnumber,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<RqstGlobal5e>(const RqstGlobal5e& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.parametergroupnumber),
            24U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::rqst_global_5e__parametergroupnumber,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<RqstGlobal03>(const RqstGlobal03& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.parametergroupnumber),
            24U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::rqst_global_03__parametergroupnumber,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<TciTransferCaseInformation>(const TciTransferCaseInformation& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.transfercasestatus),
            3U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci_transfer_case_information__transfercasestatus,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.dirstatus),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci_transfer_case_information__dirstatus,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.actualgearratio,
            0.01,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci_transfer_case_information__actualgearratio,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.messagecounter),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci_transfer_case_information__messagecounter,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.messagechecksum),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci_transfer_case_information__messagechecksum,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Trf1TransmissionFluids1>(const Trf1TransmissionFluids1& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.clutchpress),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__clutchpress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.transoillevel1,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transoillevel1,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.transfilterdiffpress),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transfilterdiffpress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.transoilpress),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transoilpress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.transoiltemp1,
            0.03125,
            -273.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transoiltemp1,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.transoillevel1high_low,
            0.5,
            -62.5,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transoillevel1high_low,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.transoillevel1countdowntimer),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transoillevel1countdowntimer,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.transoillevel1measurementstatus),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transoillevel1measurementstatus,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<CcssCruiseControlVehicleSpd>(const CcssCruiseControlVehicleSpd& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.maxvehiclespeedlimit),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.cruisectrlhighsetlimitspeed),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__cruisectrlhighsetlimitspeed,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.cruisectrllowsetlimitspeed),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__cruisectrllowsetlimitspeed,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.maxvehiclespeedlimit6808,
            0.00390625,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit6808,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.ctrlsyslowsetlmtspd),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__ctrlsyslowsetlmtspd,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.ctrldiscmdsupport),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__ctrldiscmdsupport,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.ctrlresumecmdsupport),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.ctrlpausecmdsupport),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.ctrlsetcmdsupport),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.powertrainadaptivecctype),
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__powertrainadaptivecctype,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Ccvs1CruiseControlVehspd>(const Ccvs1CruiseControlVehspd& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.twospeedaxleswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__twospeedaxleswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.parkingbrakeswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__parkingbrakeswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.cruisectrlpauseswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlpauseswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.parkbrakereleaseinhibitrq),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.wheelbasedvehiclespeed,
            0.00390625,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__wheelbasedvehiclespeed,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.cruisectrlactive),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlactive,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.cruisectrlenableswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlenableswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.brakeswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__brakeswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.clutchswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__clutchswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.cruisectrlsetswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.cruisectrlcoastswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlcoastswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.cruisectrlresumeswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlresumeswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.cruisectrlaccelerateswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.cruisectrlsetspeed),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetspeed,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.ptogovernorstate),
            5U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__ptogovernorstate,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.cruisectrlstates),
            3U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlstates,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engidleincrementswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__engidleincrementswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engidledecrementswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__engidledecrementswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engtestmodeswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__engtestmodeswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engshutdownoverrideswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__engshutdownoverrideswitch,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Ebc1ElectronicBrakeCntrl>(const Ebc1ElectronicBrakeCntrl& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.asrengctrlactive),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__asrengctrlactive,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.asrbrakectrlactive),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__asrbrakectrlactive,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.antilockbrakingactive),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__antilockbrakingactive,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.ebsbrakeswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__ebsbrakeswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.brakepedalpos,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__brakepedalpos,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.absoffroadswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__absoffroadswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.asroffroadswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__asroffroadswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.asrhillholderswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__asrhillholderswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.tractionctrloverrideswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__tractionctrloverrideswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.accelinterlockswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__accelinterlockswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engderateswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__engderateswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engauxshutdownswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__engauxshutdownswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.remoteaccelenableswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__remoteaccelenableswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engretarderselection,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__engretarderselection,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.absfullyoperational),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__absfullyoperational,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.ebsredwarningsignal),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__ebsredwarningsignal,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.abs_ebsamberwarningsignal),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.atc_asrinformationsignal),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__atc_asrinformationsignal,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.srcaddrssofcntrllngdvcfrbrkectrl),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__srcaddrssofcntrllngdvcfrbrkectrl,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.railroadmodesw),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__railroadmodesw,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.haltbrakeswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__haltbrakeswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.trailerabsstatus),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__trailerabsstatus,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.trctrmntdtrailerabswarningsignal),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Shutdn>(const Shutdn& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engidleshutdownhasshutdowneng),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engidleshutdownhasshutdowneng,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engidleshutdowndriveralertmode),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engidleshutdowndriveralertmode,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engidleshutdowntimeroverride),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engidleshutdowntimeroverride,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engidleshutdowntimerstate),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engidleshutdowntimerstate,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engidleshutdowntimerfunction),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engidleshutdowntimerfunction,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.a_chighpressfanswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__a_chighpressfanswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.refrigerantlowpressswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__refrigerantlowpressswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.refrigeranthighpressswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__refrigeranthighpressswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engwaittostartlamp),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engwaittostartlamp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engprtectionsystemhasshutdowneng),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engprtectionsystemhasshutdowneng,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engprtctnsystmapprachingshutdown),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engprtctnsystmapprachingshutdown,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engprotectionsystemtimeroverride),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engprotectionsystemtimeroverride,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engprotectionsystemtimerstate),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engprotectionsystemtimerstate,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engprotectionsystemconfig),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engprotectionsystemconfig,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engalarmacknowledge),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engalarmacknowledge,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engalarmoutputcmdstatus),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engalarmoutputcmdstatus,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engairshutoffcmdstatus),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engairshutoffcmdstatus,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engoverspeedtest),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engoverspeedtest,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engairshutoffstatus),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engairshutoffstatus,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.ptoshutdownhasshutdowneng),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__ptoshutdownhasshutdowneng,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.clntlvlengprtctionshutdownstatus),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__clntlvlengprtctionshutdownstatus,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engoilpresssw),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engoilpresssw,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}

auto validate_message(const MessageVariant& msg)
    -> std::expected<void, ValidationIssue>
{
    return std::visit(
        [](const auto& m) -> std::expected<void, ValidationIssue> {
            return validate_message(m);
        },
        msg
    );
}

} // namespace duramax