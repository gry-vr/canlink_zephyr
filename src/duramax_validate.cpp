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

inline auto within_dbc_range(double physical,
                             bool has_minimum,
                             double minimum,
                             bool has_maximum,
                             double maximum) -> bool
{
    if (has_minimum && physical < minimum) {
        return false;
    }
    if (has_maximum && physical > maximum) {
        return false;
    }
    return true;
}

} // namespace detail

template <>
auto validate_message<Eec5ElectronicEngineControl5>(const Eec5ElectronicEngineControl5& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::within_dbc_range(
            msg.engine_turbocharger_1_calculated,
            signal_traits<SignalId::eec5_electronic_engine_control_5__engine_turbocharger_1_calculated>::has_minimum,
            signal_traits<SignalId::eec5_electronic_engine_control_5__engine_turbocharger_1_calculated>::minimum,
            signal_traits<SignalId::eec5_electronic_engine_control_5__engine_turbocharger_1_calculated>::has_maximum,
            signal_traits<SignalId::eec5_electronic_engine_control_5__engine_turbocharger_1_calculated>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec5_electronic_engine_control_5__engine_turbocharger_1_calculated,
            .error = ValidationError::value_outside_dbc_range
        });
    }
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
    if (!detail::within_dbc_range(
            msg.commanded_vgt_position,
            signal_traits<SignalId::eec5_electronic_engine_control_5__commanded_vgt_position>::has_minimum,
            signal_traits<SignalId::eec5_electronic_engine_control_5__commanded_vgt_position>::minimum,
            signal_traits<SignalId::eec5_electronic_engine_control_5__commanded_vgt_position>::has_maximum,
            signal_traits<SignalId::eec5_electronic_engine_control_5__commanded_vgt_position>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec5_electronic_engine_control_5__commanded_vgt_position,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec5_electronic_engine_control_5__engine_variable_geometry_turboch>::has_minimum &&
        static_cast<double>(msg.engine_variable_geometry_turboch) < signal_traits<SignalId::eec5_electronic_engine_control_5__engine_variable_geometry_turboch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec5_electronic_engine_control_5__engine_variable_geometry_turboch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec5_electronic_engine_control_5__engine_variable_geometry_turboch>::has_maximum &&
        static_cast<double>(msg.engine_variable_geometry_turboch) > signal_traits<SignalId::eec5_electronic_engine_control_5__engine_variable_geometry_turboch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec5_electronic_engine_control_5__engine_variable_geometry_turboch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engine_variable_geometry_turboch),
            1.0,
            0.0,
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec5_electronic_engine_control_5__engine_variable_geometry_turboch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::eec5_electronic_engine_control_5__engine_fuel_control_control_mode>::has_minimum &&
        static_cast<double>(msg.engine_fuel_control_control_mode) < signal_traits<SignalId::eec5_electronic_engine_control_5__engine_fuel_control_control_mode>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec5_electronic_engine_control_5__engine_fuel_control_control_mode,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec5_electronic_engine_control_5__engine_fuel_control_control_mode>::has_maximum &&
        static_cast<double>(msg.engine_fuel_control_control_mode) > signal_traits<SignalId::eec5_electronic_engine_control_5__engine_fuel_control_control_mode>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec5_electronic_engine_control_5__engine_fuel_control_control_mode,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec5_electronic_engine_control_5__engine_vgt_control_mode>::has_minimum &&
        static_cast<double>(msg.engine_vgt_control_mode) < signal_traits<SignalId::eec5_electronic_engine_control_5__engine_vgt_control_mode>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec5_electronic_engine_control_5__engine_vgt_control_mode,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec5_electronic_engine_control_5__engine_vgt_control_mode>::has_maximum &&
        static_cast<double>(msg.engine_vgt_control_mode) > signal_traits<SignalId::eec5_electronic_engine_control_5__engine_vgt_control_mode>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec5_electronic_engine_control_5__engine_vgt_control_mode,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.actual_vgt_position,
            signal_traits<SignalId::eec5_electronic_engine_control_5__actual_vgt_position>::has_minimum,
            signal_traits<SignalId::eec5_electronic_engine_control_5__actual_vgt_position>::minimum,
            signal_traits<SignalId::eec5_electronic_engine_control_5__actual_vgt_position>::has_maximum,
            signal_traits<SignalId::eec5_electronic_engine_control_5__actual_vgt_position>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec5_electronic_engine_control_5__actual_vgt_position,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engine_exhaust_gas_recirculation,
            signal_traits<SignalId::eec9_electronic_engine_control_9__engine_exhaust_gas_recirculation>::has_minimum,
            signal_traits<SignalId::eec9_electronic_engine_control_9__engine_exhaust_gas_recirculation>::minimum,
            signal_traits<SignalId::eec9_electronic_engine_control_9__engine_exhaust_gas_recirculation>::has_maximum,
            signal_traits<SignalId::eec9_electronic_engine_control_9__engine_exhaust_gas_recirculation>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec9_electronic_engine_control_9__engine_exhaust_gas_recirculation,
            .error = ValidationError::value_outside_dbc_range
        });
    }
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
    if (!detail::within_dbc_range(
            msg.commanded_fuel_rail_pressure,
            signal_traits<SignalId::eec9_electronic_engine_control_9__commanded_fuel_rail_pressure>::has_minimum,
            signal_traits<SignalId::eec9_electronic_engine_control_9__commanded_fuel_rail_pressure>::minimum,
            signal_traits<SignalId::eec9_electronic_engine_control_9__commanded_fuel_rail_pressure>::has_maximum,
            signal_traits<SignalId::eec9_electronic_engine_control_9__commanded_fuel_rail_pressure>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec9_electronic_engine_control_9__commanded_fuel_rail_pressure,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.commanded_engine_fuel_injection,
            signal_traits<SignalId::eec9_electronic_engine_control_9__commanded_engine_fuel_injection>::has_minimum,
            signal_traits<SignalId::eec9_electronic_engine_control_9__commanded_engine_fuel_injection>::minimum,
            signal_traits<SignalId::eec9_electronic_engine_control_9__commanded_engine_fuel_injection>::has_maximum,
            signal_traits<SignalId::eec9_electronic_engine_control_9__commanded_engine_fuel_injection>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec9_electronic_engine_control_9__commanded_engine_fuel_injection,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__actual_boost_pressure>::has_minimum &&
        static_cast<double>(msg.actual_boost_pressure) < signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__actual_boost_pressure>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__actual_boost_pressure,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__actual_boost_pressure>::has_maximum &&
        static_cast<double>(msg.actual_boost_pressure) > signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__actual_boost_pressure>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__actual_boost_pressure,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.actual_boost_pressure),
            2.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__actual_boost_pressure,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__desired_boost_pressure>::has_minimum &&
        static_cast<double>(msg.desired_boost_pressure) < signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__desired_boost_pressure>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__desired_boost_pressure,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__desired_boost_pressure>::has_maximum &&
        static_cast<double>(msg.desired_boost_pressure) > signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__desired_boost_pressure>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__desired_boost_pressure,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.desired_boost_pressure),
            2.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__desired_boost_pressure,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.engine_exhaust_brake_actuator_co,
            signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__engine_exhaust_brake_actuator_co>::has_minimum,
            signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__engine_exhaust_brake_actuator_co>::minimum,
            signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__engine_exhaust_brake_actuator_co>::has_maximum,
            signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__engine_exhaust_brake_actuator_co>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__engine_exhaust_brake_actuator_co,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__engine_turbocharger_2_turbine_ou>::has_minimum &&
        static_cast<double>(msg.engine_turbocharger_2_turbine_ou) < signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__engine_turbocharger_2_turbine_ou>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__engine_turbocharger_2_turbine_ou,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__engine_turbocharger_2_turbine_ou>::has_maximum &&
        static_cast<double>(msg.engine_turbocharger_2_turbine_ou) > signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__engine_turbocharger_2_turbine_ou>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__engine_turbocharger_2_turbine_ou,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engine_turbocharger_2_turbine_ou),
            2.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__engine_turbocharger_2_turbine_ou,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__desired_engine_turbocharger_2_tu>::has_minimum &&
        static_cast<double>(msg.desired_engine_turbocharger_2_tu) < signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__desired_engine_turbocharger_2_tu>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__desired_engine_turbocharger_2_tu,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__desired_engine_turbocharger_2_tu>::has_maximum &&
        static_cast<double>(msg.desired_engine_turbocharger_2_tu) > signal_traits<SignalId::ebcc_engine_exhaust_brake_cont__desired_engine_turbocharger_2_tu>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebcc_engine_exhaust_brake_cont__desired_engine_turbocharger_2_tu,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.desired_engine_turbocharger_2_tu),
            2.0,
            0.0,
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
    if (!detail::within_dbc_range(
            msg.engine_intake_manifold_1_air_tem,
            signal_traits<SignalId::et3_engine_temperature_3__engine_intake_manifold_1_air_tem>::has_minimum,
            signal_traits<SignalId::et3_engine_temperature_3__engine_intake_manifold_1_air_tem>::minimum,
            signal_traits<SignalId::et3_engine_temperature_3__engine_intake_manifold_1_air_tem>::has_maximum,
            signal_traits<SignalId::et3_engine_temperature_3__engine_intake_manifold_1_air_tem>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et3_engine_temperature_3__engine_intake_manifold_1_air_tem,
            .error = ValidationError::value_outside_dbc_range
        });
    }
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
    if (!detail::within_dbc_range(
            msg.engine_coolant_temperature_high,
            signal_traits<SignalId::et3_engine_temperature_3__engine_coolant_temperature_high>::has_minimum,
            signal_traits<SignalId::et3_engine_temperature_3__engine_coolant_temperature_high>::minimum,
            signal_traits<SignalId::et3_engine_temperature_3__engine_coolant_temperature_high>::has_maximum,
            signal_traits<SignalId::et3_engine_temperature_3__engine_coolant_temperature_high>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et3_engine_temperature_3__engine_coolant_temperature_high,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engine_intake_valve_actuation_sy,
            signal_traits<SignalId::et3_engine_temperature_3__engine_intake_valve_actuation_sy>::has_minimum,
            signal_traits<SignalId::et3_engine_temperature_3__engine_intake_valve_actuation_sy>::minimum,
            signal_traits<SignalId::et3_engine_temperature_3__engine_intake_valve_actuation_sy>::has_maximum,
            signal_traits<SignalId::et3_engine_temperature_3__engine_intake_valve_actuation_sy>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et3_engine_temperature_3__engine_intake_valve_actuation_sy,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engine_cac_outlet_temperature,
            signal_traits<SignalId::et3_engine_temperature_3__engine_cac_outlet_temperature>::has_minimum,
            signal_traits<SignalId::et3_engine_temperature_3__engine_cac_outlet_temperature>::minimum,
            signal_traits<SignalId::et3_engine_temperature_3__engine_cac_outlet_temperature>::has_maximum,
            signal_traits<SignalId::et3_engine_temperature_3__engine_cac_outlet_temperature>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et3_engine_temperature_3__engine_cac_outlet_temperature,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::dm21_diagnostic_readiness_2__engine_run_time_with_mil_on>::has_minimum &&
        static_cast<double>(msg.engine_run_time_with_mil_on) < signal_traits<SignalId::dm21_diagnostic_readiness_2__engine_run_time_with_mil_on>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm21_diagnostic_readiness_2__engine_run_time_with_mil_on,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm21_diagnostic_readiness_2__engine_run_time_with_mil_on>::has_maximum &&
        static_cast<double>(msg.engine_run_time_with_mil_on) > signal_traits<SignalId::dm21_diagnostic_readiness_2__engine_run_time_with_mil_on>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm21_diagnostic_readiness_2__engine_run_time_with_mil_on,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engine_run_time_with_mil_on),
            1.0,
            0.0,
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
    if (signal_traits<SignalId::dm26_diagnostic_readiness_3__time_since_engine_start>::has_minimum &&
        static_cast<double>(msg.time_since_engine_start) < signal_traits<SignalId::dm26_diagnostic_readiness_3__time_since_engine_start>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm26_diagnostic_readiness_3__time_since_engine_start,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm26_diagnostic_readiness_3__time_since_engine_start>::has_maximum &&
        static_cast<double>(msg.time_since_engine_start) > signal_traits<SignalId::dm26_diagnostic_readiness_3__time_since_engine_start>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm26_diagnostic_readiness_3__time_since_engine_start,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.time_since_engine_start),
            1.0,
            0.0,
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
    if (!detail::within_dbc_range(
            msg.aft1dpfinpress,
            signal_traits<SignalId::ic1_intake_exhaust_cond_1__aft1dpfinpress>::has_minimum,
            signal_traits<SignalId::ic1_intake_exhaust_cond_1__aft1dpfinpress>::minimum,
            signal_traits<SignalId::ic1_intake_exhaust_cond_1__aft1dpfinpress>::has_maximum,
            signal_traits<SignalId::ic1_intake_exhaust_cond_1__aft1dpfinpress>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__aft1dpfinpress,
            .error = ValidationError::value_outside_dbc_range
        });
    }
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
    if (signal_traits<SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1press>::has_minimum &&
        static_cast<double>(msg.engintakemanifold1press) < signal_traits<SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1press>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1press,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1press>::has_maximum &&
        static_cast<double>(msg.engintakemanifold1press) > signal_traits<SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1press>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1press,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engintakemanifold1press),
            2.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1press,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1temp>::has_minimum &&
        static_cast<double>(msg.engintakemanifold1temp) < signal_traits<SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1temp>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1temp,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1temp>::has_maximum &&
        static_cast<double>(msg.engintakemanifold1temp) > signal_traits<SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1temp>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1temp,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engintakemanifold1temp),
            1.0,
            -40.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engintakemanifold1temp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::ic1_intake_exhaust_cond_1__engairintakepress>::has_minimum &&
        static_cast<double>(msg.engairintakepress) < signal_traits<SignalId::ic1_intake_exhaust_cond_1__engairintakepress>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engairintakepress,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ic1_intake_exhaust_cond_1__engairintakepress>::has_maximum &&
        static_cast<double>(msg.engairintakepress) > signal_traits<SignalId::ic1_intake_exhaust_cond_1__engairintakepress>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engairintakepress,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engairintakepress),
            2.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engairintakepress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.engairfilter1diffpress,
            signal_traits<SignalId::ic1_intake_exhaust_cond_1__engairfilter1diffpress>::has_minimum,
            signal_traits<SignalId::ic1_intake_exhaust_cond_1__engairfilter1diffpress>::minimum,
            signal_traits<SignalId::ic1_intake_exhaust_cond_1__engairfilter1diffpress>::has_maximum,
            signal_traits<SignalId::ic1_intake_exhaust_cond_1__engairfilter1diffpress>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engairfilter1diffpress,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engexhaustgastemp,
            signal_traits<SignalId::ic1_intake_exhaust_cond_1__engexhaustgastemp>::has_minimum,
            signal_traits<SignalId::ic1_intake_exhaust_cond_1__engexhaustgastemp>::minimum,
            signal_traits<SignalId::ic1_intake_exhaust_cond_1__engexhaustgastemp>::has_maximum,
            signal_traits<SignalId::ic1_intake_exhaust_cond_1__engexhaustgastemp>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engexhaustgastemp,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engcoolantfilterdiffpress,
            signal_traits<SignalId::ic1_intake_exhaust_cond_1__engcoolantfilterdiffpress>::has_minimum,
            signal_traits<SignalId::ic1_intake_exhaust_cond_1__engcoolantfilterdiffpress>::minimum,
            signal_traits<SignalId::ic1_intake_exhaust_cond_1__engcoolantfilterdiffpress>::has_maximum,
            signal_traits<SignalId::ic1_intake_exhaust_cond_1__engcoolantfilterdiffpress>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ic1_intake_exhaust_cond_1__engcoolantfilterdiffpress,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.barometric_pressurebarometric_pr,
            signal_traits<SignalId::amb_ambient_conditions__barometric_pressurebarometric_pr>::has_minimum,
            signal_traits<SignalId::amb_ambient_conditions__barometric_pressurebarometric_pr>::minimum,
            signal_traits<SignalId::amb_ambient_conditions__barometric_pressurebarometric_pr>::has_maximum,
            signal_traits<SignalId::amb_ambient_conditions__barometric_pressurebarometric_pr>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::amb_ambient_conditions__barometric_pressurebarometric_pr,
            .error = ValidationError::value_outside_dbc_range
        });
    }
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
    if (!detail::within_dbc_range(
            msg.cabinteriortemp,
            signal_traits<SignalId::amb_ambient_conditions__cabinteriortemp>::has_minimum,
            signal_traits<SignalId::amb_ambient_conditions__cabinteriortemp>::minimum,
            signal_traits<SignalId::amb_ambient_conditions__cabinteriortemp>::has_maximum,
            signal_traits<SignalId::amb_ambient_conditions__cabinteriortemp>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::amb_ambient_conditions__cabinteriortemp,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.ambient_air_temperature,
            signal_traits<SignalId::amb_ambient_conditions__ambient_air_temperature>::has_minimum,
            signal_traits<SignalId::amb_ambient_conditions__ambient_air_temperature>::minimum,
            signal_traits<SignalId::amb_ambient_conditions__ambient_air_temperature>::has_maximum,
            signal_traits<SignalId::amb_ambient_conditions__ambient_air_temperature>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::amb_ambient_conditions__ambient_air_temperature,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::amb_ambient_conditions__engine_air_intake_temperature>::has_minimum &&
        static_cast<double>(msg.engine_air_intake_temperature) < signal_traits<SignalId::amb_ambient_conditions__engine_air_intake_temperature>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::amb_ambient_conditions__engine_air_intake_temperature,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::amb_ambient_conditions__engine_air_intake_temperature>::has_maximum &&
        static_cast<double>(msg.engine_air_intake_temperature) > signal_traits<SignalId::amb_ambient_conditions__engine_air_intake_temperature>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::amb_ambient_conditions__engine_air_intake_temperature,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engine_air_intake_temperature),
            1.0,
            -40.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::amb_ambient_conditions__engine_air_intake_temperature,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.roadsurfacetemp,
            signal_traits<SignalId::amb_ambient_conditions__roadsurfacetemp>::has_minimum,
            signal_traits<SignalId::amb_ambient_conditions__roadsurfacetemp>::minimum,
            signal_traits<SignalId::amb_ambient_conditions__roadsurfacetemp>::has_maximum,
            signal_traits<SignalId::amb_ambient_conditions__roadsurfacetemp>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::amb_ambient_conditions__roadsurfacetemp,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec1_electronic_engine_control_1__engine_torque_mode>::has_minimum &&
        static_cast<double>(msg.engine_torque_mode) < signal_traits<SignalId::eec1_electronic_engine_control_1__engine_torque_mode>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__engine_torque_mode,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec1_electronic_engine_control_1__engine_torque_mode>::has_maximum &&
        static_cast<double>(msg.engine_torque_mode) > signal_traits<SignalId::eec1_electronic_engine_control_1__engine_torque_mode>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__engine_torque_mode,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engine_torque_mode),
            1.0,
            0.0,
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__engine_torque_mode,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::eec1_electronic_engine_control_1__actlengprcnttorquehighresolution>::has_minimum &&
        static_cast<double>(msg.actlengprcnttorquehighresolution) < signal_traits<SignalId::eec1_electronic_engine_control_1__actlengprcnttorquehighresolution>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__actlengprcnttorquehighresolution,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec1_electronic_engine_control_1__actlengprcnttorquehighresolution>::has_maximum &&
        static_cast<double>(msg.actlengprcnttorquehighresolution) > signal_traits<SignalId::eec1_electronic_engine_control_1__actlengprcnttorquehighresolution>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__actlengprcnttorquehighresolution,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec1_electronic_engine_control_1__drivers_demand_engine_prcnt_torq>::has_minimum &&
        static_cast<double>(msg.drivers_demand_engine_prcnt_torq) < signal_traits<SignalId::eec1_electronic_engine_control_1__drivers_demand_engine_prcnt_torq>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__drivers_demand_engine_prcnt_torq,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec1_electronic_engine_control_1__drivers_demand_engine_prcnt_torq>::has_maximum &&
        static_cast<double>(msg.drivers_demand_engine_prcnt_torq) > signal_traits<SignalId::eec1_electronic_engine_control_1__drivers_demand_engine_prcnt_torq>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__drivers_demand_engine_prcnt_torq,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.drivers_demand_engine_prcnt_torq),
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__drivers_demand_engine_prcnt_torq,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::eec1_electronic_engine_control_1__actual_engine_percent_torque>::has_minimum &&
        static_cast<double>(msg.actual_engine_percent_torque) < signal_traits<SignalId::eec1_electronic_engine_control_1__actual_engine_percent_torque>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__actual_engine_percent_torque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec1_electronic_engine_control_1__actual_engine_percent_torque>::has_maximum &&
        static_cast<double>(msg.actual_engine_percent_torque) > signal_traits<SignalId::eec1_electronic_engine_control_1__actual_engine_percent_torque>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__actual_engine_percent_torque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.actual_engine_percent_torque),
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__actual_engine_percent_torque,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.engine_speed,
            signal_traits<SignalId::eec1_electronic_engine_control_1__engine_speed>::has_minimum,
            signal_traits<SignalId::eec1_electronic_engine_control_1__engine_speed>::minimum,
            signal_traits<SignalId::eec1_electronic_engine_control_1__engine_speed>::has_maximum,
            signal_traits<SignalId::eec1_electronic_engine_control_1__engine_speed>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__engine_speed,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec1_electronic_engine_control_1__srcaddrssofcntrllngdvcforengctrl>::has_minimum &&
        static_cast<double>(msg.srcaddrssofcntrllngdvcforengctrl) < signal_traits<SignalId::eec1_electronic_engine_control_1__srcaddrssofcntrllngdvcforengctrl>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__srcaddrssofcntrllngdvcforengctrl,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec1_electronic_engine_control_1__srcaddrssofcntrllngdvcforengctrl>::has_maximum &&
        static_cast<double>(msg.srcaddrssofcntrllngdvcforengctrl) > signal_traits<SignalId::eec1_electronic_engine_control_1__srcaddrssofcntrllngdvcforengctrl>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__srcaddrssofcntrllngdvcforengctrl,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.srcaddrssofcntrllngdvcforengctrl),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__srcaddrssofcntrllngdvcforengctrl,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::eec1_electronic_engine_control_1__engstartermode>::has_minimum &&
        static_cast<double>(msg.engstartermode) < signal_traits<SignalId::eec1_electronic_engine_control_1__engstartermode>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__engstartermode,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec1_electronic_engine_control_1__engstartermode>::has_maximum &&
        static_cast<double>(msg.engstartermode) > signal_traits<SignalId::eec1_electronic_engine_control_1__engstartermode>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__engstartermode,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec1_electronic_engine_control_1__engine_demand_percent_torque>::has_minimum &&
        static_cast<double>(msg.engine_demand_percent_torque) < signal_traits<SignalId::eec1_electronic_engine_control_1__engine_demand_percent_torque>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__engine_demand_percent_torque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec1_electronic_engine_control_1__engine_demand_percent_torque>::has_maximum &&
        static_cast<double>(msg.engine_demand_percent_torque) > signal_traits<SignalId::eec1_electronic_engine_control_1__engine_demand_percent_torque>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec1_electronic_engine_control_1__engine_demand_percent_torque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engine_demand_percent_torque),
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
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedal1lowidleswitch>::has_minimum &&
        static_cast<double>(msg.accelpedal1lowidleswitch) < signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedal1lowidleswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__accelpedal1lowidleswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedal1lowidleswitch>::has_maximum &&
        static_cast<double>(msg.accelpedal1lowidleswitch) > signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedal1lowidleswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__accelpedal1lowidleswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.accelpedal1lowidleswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__accelpedal1lowidleswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedalkickdownswitch>::has_minimum &&
        static_cast<double>(msg.accelpedalkickdownswitch) < signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedalkickdownswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__accelpedalkickdownswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedalkickdownswitch>::has_maximum &&
        static_cast<double>(msg.accelpedalkickdownswitch) > signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedalkickdownswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__accelpedalkickdownswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__roadspeedlimitstatus>::has_minimum &&
        static_cast<double>(msg.roadspeedlimitstatus) < signal_traits<SignalId::eec2_electronic_engine_control_2__roadspeedlimitstatus>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__roadspeedlimitstatus,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__roadspeedlimitstatus>::has_maximum &&
        static_cast<double>(msg.roadspeedlimitstatus) > signal_traits<SignalId::eec2_electronic_engine_control_2__roadspeedlimitstatus>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__roadspeedlimitstatus,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedal2lowidleswitch>::has_minimum &&
        static_cast<double>(msg.accelpedal2lowidleswitch) < signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedal2lowidleswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__accelpedal2lowidleswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedal2lowidleswitch>::has_maximum &&
        static_cast<double>(msg.accelpedal2lowidleswitch) > signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedal2lowidleswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__accelpedal2lowidleswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.accelpedalpos1,
            signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedalpos1>::has_minimum,
            signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedalpos1>::minimum,
            signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedalpos1>::has_maximum,
            signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedalpos1>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__accelpedalpos1,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__engpercentloadatcurrentspeed>::has_minimum &&
        static_cast<double>(msg.engpercentloadatcurrentspeed) < signal_traits<SignalId::eec2_electronic_engine_control_2__engpercentloadatcurrentspeed>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__engpercentloadatcurrentspeed,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__engpercentloadatcurrentspeed>::has_maximum &&
        static_cast<double>(msg.engpercentloadatcurrentspeed) > signal_traits<SignalId::eec2_electronic_engine_control_2__engpercentloadatcurrentspeed>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__engpercentloadatcurrentspeed,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engpercentloadatcurrentspeed),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__engpercentloadatcurrentspeed,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.remoteaccelpedalpos,
            signal_traits<SignalId::eec2_electronic_engine_control_2__remoteaccelpedalpos>::has_minimum,
            signal_traits<SignalId::eec2_electronic_engine_control_2__remoteaccelpedalpos>::minimum,
            signal_traits<SignalId::eec2_electronic_engine_control_2__remoteaccelpedalpos>::has_maximum,
            signal_traits<SignalId::eec2_electronic_engine_control_2__remoteaccelpedalpos>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__remoteaccelpedalpos,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.accelpedalpos2,
            signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedalpos2>::has_minimum,
            signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedalpos2>::minimum,
            signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedalpos2>::has_maximum,
            signal_traits<SignalId::eec2_electronic_engine_control_2__accelpedalpos2>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__accelpedalpos2,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus>::has_minimum &&
        static_cast<double>(msg.vhcleaccelerationratelimitstatus) < signal_traits<SignalId::eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus>::has_maximum &&
        static_cast<double>(msg.vhcleaccelerationratelimitstatus) > signal_traits<SignalId::eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback>::has_minimum &&
        static_cast<double>(msg.mmntaryengmaxpowerenablefeedback) < signal_traits<SignalId::eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback>::has_maximum &&
        static_cast<double>(msg.mmntaryengmaxpowerenablefeedback) > signal_traits<SignalId::eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__dpfthermalmanagementactive>::has_minimum &&
        static_cast<double>(msg.dpfthermalmanagementactive) < signal_traits<SignalId::eec2_electronic_engine_control_2__dpfthermalmanagementactive>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__dpfthermalmanagementactive,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__dpfthermalmanagementactive>::has_maximum &&
        static_cast<double>(msg.dpfthermalmanagementactive) > signal_traits<SignalId::eec2_electronic_engine_control_2__dpfthermalmanagementactive>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__dpfthermalmanagementactive,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__scrthermalmanagementactive>::has_minimum &&
        static_cast<double>(msg.scrthermalmanagementactive) < signal_traits<SignalId::eec2_electronic_engine_control_2__scrthermalmanagementactive>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__scrthermalmanagementactive,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__scrthermalmanagementactive>::has_maximum &&
        static_cast<double>(msg.scrthermalmanagementactive) > signal_traits<SignalId::eec2_electronic_engine_control_2__scrthermalmanagementactive>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__scrthermalmanagementactive,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.actlmaxavailableengpercenttorque,
            signal_traits<SignalId::eec2_electronic_engine_control_2__actlmaxavailableengpercenttorque>::has_minimum,
            signal_traits<SignalId::eec2_electronic_engine_control_2__actlmaxavailableengpercenttorque>::minimum,
            signal_traits<SignalId::eec2_electronic_engine_control_2__actlmaxavailableengpercenttorque>::has_maximum,
            signal_traits<SignalId::eec2_electronic_engine_control_2__actlmaxavailableengpercenttorque>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__actlmaxavailableengpercenttorque,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__estpumpingpercenttorque>::has_minimum &&
        static_cast<double>(msg.estpumpingpercenttorque) < signal_traits<SignalId::eec2_electronic_engine_control_2__estpumpingpercenttorque>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__estpumpingpercenttorque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec2_electronic_engine_control_2__estpumpingpercenttorque>::has_maximum &&
        static_cast<double>(msg.estpumpingpercenttorque) > signal_traits<SignalId::eec2_electronic_engine_control_2__estpumpingpercenttorque>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec2_electronic_engine_control_2__estpumpingpercenttorque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.estpumpingpercenttorque),
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
    if (signal_traits<SignalId::eec3_electronic_engine_control_3__nominalfrictionpercenttorque>::has_minimum &&
        static_cast<double>(msg.nominalfrictionpercenttorque) < signal_traits<SignalId::eec3_electronic_engine_control_3__nominalfrictionpercenttorque>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__nominalfrictionpercenttorque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec3_electronic_engine_control_3__nominalfrictionpercenttorque>::has_maximum &&
        static_cast<double>(msg.nominalfrictionpercenttorque) > signal_traits<SignalId::eec3_electronic_engine_control_3__nominalfrictionpercenttorque>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__nominalfrictionpercenttorque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.nominalfrictionpercenttorque),
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__nominalfrictionpercenttorque,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.enginesdesiredoperatingspeed,
            signal_traits<SignalId::eec3_electronic_engine_control_3__enginesdesiredoperatingspeed>::has_minimum,
            signal_traits<SignalId::eec3_electronic_engine_control_3__enginesdesiredoperatingspeed>::minimum,
            signal_traits<SignalId::eec3_electronic_engine_control_3__enginesdesiredoperatingspeed>::has_maximum,
            signal_traits<SignalId::eec3_electronic_engine_control_3__enginesdesiredoperatingspeed>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__enginesdesiredoperatingspeed,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec3_electronic_engine_control_3__engnsdsrdoprtngspdasymmtryadjstm>::has_minimum &&
        static_cast<double>(msg.engnsdsrdoprtngspdasymmtryadjstm) < signal_traits<SignalId::eec3_electronic_engine_control_3__engnsdsrdoprtngspdasymmtryadjstm>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__engnsdsrdoprtngspdasymmtryadjstm,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec3_electronic_engine_control_3__engnsdsrdoprtngspdasymmtryadjstm>::has_maximum &&
        static_cast<double>(msg.engnsdsrdoprtngspdasymmtryadjstm) > signal_traits<SignalId::eec3_electronic_engine_control_3__engnsdsrdoprtngspdasymmtryadjstm>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__engnsdsrdoprtngspdasymmtryadjstm,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engnsdsrdoprtngspdasymmtryadjstm),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__engnsdsrdoprtngspdasymmtryadjstm,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::eec3_electronic_engine_control_3__estengprsiticlossespercenttorque>::has_minimum &&
        static_cast<double>(msg.estengprsiticlossespercenttorque) < signal_traits<SignalId::eec3_electronic_engine_control_3__estengprsiticlossespercenttorque>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__estengprsiticlossespercenttorque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec3_electronic_engine_control_3__estengprsiticlossespercenttorque>::has_maximum &&
        static_cast<double>(msg.estengprsiticlossespercenttorque) > signal_traits<SignalId::eec3_electronic_engine_control_3__estengprsiticlossespercenttorque>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__estengprsiticlossespercenttorque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.estengprsiticlossespercenttorque),
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__estengprsiticlossespercenttorque,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.aft1exhgasmfr,
            signal_traits<SignalId::eec3_electronic_engine_control_3__aft1exhgasmfr>::has_minimum,
            signal_traits<SignalId::eec3_electronic_engine_control_3__aft1exhgasmfr>::minimum,
            signal_traits<SignalId::eec3_electronic_engine_control_3__aft1exhgasmfr>::has_maximum,
            signal_traits<SignalId::eec3_electronic_engine_control_3__aft1exhgasmfr>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__aft1exhgasmfr,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec3_electronic_engine_control_3__aft1indewpoint>::has_minimum &&
        static_cast<double>(msg.aft1indewpoint) < signal_traits<SignalId::eec3_electronic_engine_control_3__aft1indewpoint>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__aft1indewpoint,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec3_electronic_engine_control_3__aft1indewpoint>::has_maximum &&
        static_cast<double>(msg.aft1indewpoint) > signal_traits<SignalId::eec3_electronic_engine_control_3__aft1indewpoint>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__aft1indewpoint,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec3_electronic_engine_control_3__aft1exhdewpoint>::has_minimum &&
        static_cast<double>(msg.aft1exhdewpoint) < signal_traits<SignalId::eec3_electronic_engine_control_3__aft1exhdewpoint>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__aft1exhdewpoint,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec3_electronic_engine_control_3__aft1exhdewpoint>::has_maximum &&
        static_cast<double>(msg.aft1exhdewpoint) > signal_traits<SignalId::eec3_electronic_engine_control_3__aft1exhdewpoint>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__aft1exhdewpoint,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec3_electronic_engine_control_3__aft2indewpoint>::has_minimum &&
        static_cast<double>(msg.aft2indewpoint) < signal_traits<SignalId::eec3_electronic_engine_control_3__aft2indewpoint>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__aft2indewpoint,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec3_electronic_engine_control_3__aft2indewpoint>::has_maximum &&
        static_cast<double>(msg.aft2indewpoint) > signal_traits<SignalId::eec3_electronic_engine_control_3__aft2indewpoint>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__aft2indewpoint,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::eec3_electronic_engine_control_3__aft2exhdewpoint>::has_minimum &&
        static_cast<double>(msg.aft2exhdewpoint) < signal_traits<SignalId::eec3_electronic_engine_control_3__aft2exhdewpoint>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__aft2exhdewpoint,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::eec3_electronic_engine_control_3__aft2exhdewpoint>::has_maximum &&
        static_cast<double>(msg.aft2exhdewpoint) > signal_traits<SignalId::eec3_electronic_engine_control_3__aft2exhdewpoint>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec3_electronic_engine_control_3__aft2exhdewpoint,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engfueldeliverypress>::has_minimum &&
        static_cast<double>(msg.engfueldeliverypress) < signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engfueldeliverypress>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engfueldeliverypress,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engfueldeliverypress>::has_maximum &&
        static_cast<double>(msg.engfueldeliverypress) > signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engfueldeliverypress>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engfueldeliverypress,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engfueldeliverypress),
            4.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engfueldeliverypress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.engexcrankcaseblowbypress,
            signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engexcrankcaseblowbypress>::has_minimum,
            signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engexcrankcaseblowbypress>::minimum,
            signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engexcrankcaseblowbypress>::has_maximum,
            signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engexcrankcaseblowbypress>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engexcrankcaseblowbypress,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engoillevel,
            signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engoillevel>::has_minimum,
            signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engoillevel>::minimum,
            signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engoillevel>::has_maximum,
            signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engoillevel>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engoillevel,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engoilpress>::has_minimum &&
        static_cast<double>(msg.engoilpress) < signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engoilpress>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engoilpress,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engoilpress>::has_maximum &&
        static_cast<double>(msg.engoilpress) > signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engoilpress>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engoilpress,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engoilpress),
            4.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engoilpress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.engcrankcasepress,
            signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engcrankcasepress>::has_minimum,
            signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engcrankcasepress>::minimum,
            signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engcrankcasepress>::has_maximum,
            signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engcrankcasepress>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engcrankcasepress,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engcoolantpress>::has_minimum &&
        static_cast<double>(msg.engcoolantpress) < signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engcoolantpress>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engcoolantpress,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engcoolantpress>::has_maximum &&
        static_cast<double>(msg.engcoolantpress) > signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engcoolantpress>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engcoolantpress,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engcoolantpress),
            2.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engcoolantpress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.engcoolantlevel,
            signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engcoolantlevel>::has_minimum,
            signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engcoolantlevel>::minimum,
            signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engcoolantlevel>::has_maximum,
            signal_traits<SignalId::efl_p1_eng_fluid_level_press_1__engcoolantlevel>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p1_eng_fluid_level_press_1__engcoolantlevel,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.enginjectionctrlpress,
            signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectionctrlpress>::has_minimum,
            signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectionctrlpress>::minimum,
            signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectionctrlpress>::has_maximum,
            signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectionctrlpress>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p2_eng_fluid_level_press_2__enginjectionctrlpress,
            .error = ValidationError::value_outside_dbc_range
        });
    }
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
    if (!detail::within_dbc_range(
            msg.enginjectormeteringrail1press,
            signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail1press>::has_minimum,
            signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail1press>::minimum,
            signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail1press>::has_maximum,
            signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail1press>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail1press,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.enginjectortimingrail1press,
            signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectortimingrail1press>::has_minimum,
            signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectortimingrail1press>::minimum,
            signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectortimingrail1press>::has_maximum,
            signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectortimingrail1press>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p2_eng_fluid_level_press_2__enginjectortimingrail1press,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.enginjectormeteringrail2press,
            signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail2press>::has_minimum,
            signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail2press>::minimum,
            signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail2press>::has_maximum,
            signal_traits<SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail2press>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::efl_p2_eng_fluid_level_press_2__enginjectormeteringrail2press,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::et1_engine_temperature_1__engcoolanttemp>::has_minimum &&
        static_cast<double>(msg.engcoolanttemp) < signal_traits<SignalId::et1_engine_temperature_1__engcoolanttemp>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engcoolanttemp,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::et1_engine_temperature_1__engcoolanttemp>::has_maximum &&
        static_cast<double>(msg.engcoolanttemp) > signal_traits<SignalId::et1_engine_temperature_1__engcoolanttemp>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engcoolanttemp,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engcoolanttemp),
            1.0,
            -40.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engcoolanttemp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::et1_engine_temperature_1__engfueltemp1>::has_minimum &&
        static_cast<double>(msg.engfueltemp1) < signal_traits<SignalId::et1_engine_temperature_1__engfueltemp1>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engfueltemp1,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::et1_engine_temperature_1__engfueltemp1>::has_maximum &&
        static_cast<double>(msg.engfueltemp1) > signal_traits<SignalId::et1_engine_temperature_1__engfueltemp1>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engfueltemp1,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engfueltemp1),
            1.0,
            -40.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engfueltemp1,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.engoiltemp1,
            signal_traits<SignalId::et1_engine_temperature_1__engoiltemp1>::has_minimum,
            signal_traits<SignalId::et1_engine_temperature_1__engoiltemp1>::minimum,
            signal_traits<SignalId::et1_engine_temperature_1__engoiltemp1>::has_maximum,
            signal_traits<SignalId::et1_engine_temperature_1__engoiltemp1>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engoiltemp1,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engturbooiltemp,
            signal_traits<SignalId::et1_engine_temperature_1__engturbooiltemp>::has_minimum,
            signal_traits<SignalId::et1_engine_temperature_1__engturbooiltemp>::minimum,
            signal_traits<SignalId::et1_engine_temperature_1__engturbooiltemp>::has_maximum,
            signal_traits<SignalId::et1_engine_temperature_1__engturbooiltemp>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engturbooiltemp,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::et1_engine_temperature_1__engintercoolertemp>::has_minimum &&
        static_cast<double>(msg.engintercoolertemp) < signal_traits<SignalId::et1_engine_temperature_1__engintercoolertemp>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engintercoolertemp,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::et1_engine_temperature_1__engintercoolertemp>::has_maximum &&
        static_cast<double>(msg.engintercoolertemp) > signal_traits<SignalId::et1_engine_temperature_1__engintercoolertemp>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engintercoolertemp,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engintercoolertemp),
            1.0,
            -40.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engintercoolertemp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.engintercoolerthermostatopening,
            signal_traits<SignalId::et1_engine_temperature_1__engintercoolerthermostatopening>::has_minimum,
            signal_traits<SignalId::et1_engine_temperature_1__engintercoolerthermostatopening>::minimum,
            signal_traits<SignalId::et1_engine_temperature_1__engintercoolerthermostatopening>::has_maximum,
            signal_traits<SignalId::et1_engine_temperature_1__engintercoolerthermostatopening>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::et1_engine_temperature_1__engintercoolerthermostatopening,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engfuelrate,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engfuelrate>::has_minimum,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engfuelrate>::minimum,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engfuelrate>::has_maximum,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engfuelrate>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::lfe1_fuel_economy_liquid_1__engfuelrate,
            .error = ValidationError::value_outside_dbc_range
        });
    }
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
    if (!detail::within_dbc_range(
            msg.enginstantaneousfueleconomy,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__enginstantaneousfueleconomy>::has_minimum,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__enginstantaneousfueleconomy>::minimum,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__enginstantaneousfueleconomy>::has_maximum,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__enginstantaneousfueleconomy>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::lfe1_fuel_economy_liquid_1__enginstantaneousfueleconomy,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engaveragefueleconomy,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engaveragefueleconomy>::has_minimum,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engaveragefueleconomy>::minimum,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engaveragefueleconomy>::has_maximum,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engaveragefueleconomy>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::lfe1_fuel_economy_liquid_1__engaveragefueleconomy,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engthrottlevalve1pos,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve1pos>::has_minimum,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve1pos>::minimum,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve1pos>::has_maximum,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve1pos>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve1pos,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engthrottlevalve2pos,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve2pos>::has_minimum,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve2pos>::minimum,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve2pos>::has_maximum,
            signal_traits<SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve2pos>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::lfe1_fuel_economy_liquid_1__engthrottlevalve2pos,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::transportprotocol_header__controlbyte>::has_minimum &&
        static_cast<double>(msg.controlbyte) < signal_traits<SignalId::transportprotocol_header__controlbyte>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__controlbyte,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__controlbyte>::has_maximum &&
        static_cast<double>(msg.controlbyte) > signal_traits<SignalId::transportprotocol_header__controlbyte>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__controlbyte,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.controlbyte),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__controlbyte,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__totalmessagesizeeoma>::has_minimum &&
        static_cast<double>(msg.totalmessagesizeeoma) < signal_traits<SignalId::transportprotocol_header__totalmessagesizeeoma>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalmessagesizeeoma,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__totalmessagesizeeoma>::has_maximum &&
        static_cast<double>(msg.totalmessagesizeeoma) > signal_traits<SignalId::transportprotocol_header__totalmessagesizeeoma>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalmessagesizeeoma,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.totalmessagesizeeoma),
            1.0,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalmessagesizeeoma,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__connectionabortreason>::has_minimum &&
        static_cast<double>(msg.connectionabortreason) < signal_traits<SignalId::transportprotocol_header__connectionabortreason>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__connectionabortreason,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__connectionabortreason>::has_maximum &&
        static_cast<double>(msg.connectionabortreason) > signal_traits<SignalId::transportprotocol_header__connectionabortreason>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__connectionabortreason,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::transportprotocol_header__totalmessagesize>::has_minimum &&
        static_cast<double>(msg.totalmessagesize) < signal_traits<SignalId::transportprotocol_header__totalmessagesize>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalmessagesize,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__totalmessagesize>::has_maximum &&
        static_cast<double>(msg.totalmessagesize) > signal_traits<SignalId::transportprotocol_header__totalmessagesize>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalmessagesize,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.totalmessagesize),
            1.0,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalmessagesize,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__numberofpacketsthatcanbesent>::has_minimum &&
        static_cast<double>(msg.numberofpacketsthatcanbesent) < signal_traits<SignalId::transportprotocol_header__numberofpacketsthatcanbesent>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__numberofpacketsthatcanbesent,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__numberofpacketsthatcanbesent>::has_maximum &&
        static_cast<double>(msg.numberofpacketsthatcanbesent) > signal_traits<SignalId::transportprotocol_header__numberofpacketsthatcanbesent>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__numberofpacketsthatcanbesent,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.numberofpacketsthatcanbesent),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__numberofpacketsthatcanbesent,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__totalmessagesizebam>::has_minimum &&
        static_cast<double>(msg.totalmessagesizebam) < signal_traits<SignalId::transportprotocol_header__totalmessagesizebam>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalmessagesizebam,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__totalmessagesizebam>::has_maximum &&
        static_cast<double>(msg.totalmessagesizebam) > signal_traits<SignalId::transportprotocol_header__totalmessagesizebam>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalmessagesizebam,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.totalmessagesizebam),
            1.0,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalmessagesizebam,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__nextpacketnumbertobesent>::has_minimum &&
        static_cast<double>(msg.nextpacketnumbertobesent) < signal_traits<SignalId::transportprotocol_header__nextpacketnumbertobesent>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__nextpacketnumbertobesent,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__nextpacketnumbertobesent>::has_maximum &&
        static_cast<double>(msg.nextpacketnumbertobesent) > signal_traits<SignalId::transportprotocol_header__nextpacketnumbertobesent>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__nextpacketnumbertobesent,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.nextpacketnumbertobesent),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__nextpacketnumbertobesent,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__totalnumberofpackets>::has_minimum &&
        static_cast<double>(msg.totalnumberofpackets) < signal_traits<SignalId::transportprotocol_header__totalnumberofpackets>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalnumberofpackets,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__totalnumberofpackets>::has_maximum &&
        static_cast<double>(msg.totalnumberofpackets) > signal_traits<SignalId::transportprotocol_header__totalnumberofpackets>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalnumberofpackets,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.totalnumberofpackets),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalnumberofpackets,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__totalnumberofpacketseoma>::has_minimum &&
        static_cast<double>(msg.totalnumberofpacketseoma) < signal_traits<SignalId::transportprotocol_header__totalnumberofpacketseoma>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalnumberofpacketseoma,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__totalnumberofpacketseoma>::has_maximum &&
        static_cast<double>(msg.totalnumberofpacketseoma) > signal_traits<SignalId::transportprotocol_header__totalnumberofpacketseoma>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalnumberofpacketseoma,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.totalnumberofpacketseoma),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalnumberofpacketseoma,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__totalnumberofpacketsbam>::has_minimum &&
        static_cast<double>(msg.totalnumberofpacketsbam) < signal_traits<SignalId::transportprotocol_header__totalnumberofpacketsbam>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalnumberofpacketsbam,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__totalnumberofpacketsbam>::has_maximum &&
        static_cast<double>(msg.totalnumberofpacketsbam) > signal_traits<SignalId::transportprotocol_header__totalnumberofpacketsbam>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalnumberofpacketsbam,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.totalnumberofpacketsbam),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__totalnumberofpacketsbam,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__maximumnumberofpackets>::has_minimum &&
        static_cast<double>(msg.maximumnumberofpackets) < signal_traits<SignalId::transportprotocol_header__maximumnumberofpackets>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__maximumnumberofpackets,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__maximumnumberofpackets>::has_maximum &&
        static_cast<double>(msg.maximumnumberofpackets) > signal_traits<SignalId::transportprotocol_header__maximumnumberofpackets>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__maximumnumberofpackets,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.maximumnumberofpackets),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__maximumnumberofpackets,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__pgnumber>::has_minimum &&
        static_cast<double>(msg.pgnumber) < signal_traits<SignalId::transportprotocol_header__pgnumber>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__pgnumber,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_header__pgnumber>::has_maximum &&
        static_cast<double>(msg.pgnumber) > signal_traits<SignalId::transportprotocol_header__pgnumber>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_header__pgnumber,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::transportprotocol_data__sequencenumber>::has_minimum &&
        static_cast<double>(msg.sequencenumber) < signal_traits<SignalId::transportprotocol_data__sequencenumber>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_data__sequencenumber,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::transportprotocol_data__sequencenumber>::has_maximum &&
        static_cast<double>(msg.sequencenumber) > signal_traits<SignalId::transportprotocol_data__sequencenumber>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::transportprotocol_data__sequencenumber,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.sequencenumber),
            1.0,
            0.0,
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
    if (signal_traits<SignalId::dm01_active_diagnostics__protectlampstatus>::has_minimum &&
        static_cast<double>(msg.protectlampstatus) < signal_traits<SignalId::dm01_active_diagnostics__protectlampstatus>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__protectlampstatus,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm01_active_diagnostics__protectlampstatus>::has_maximum &&
        static_cast<double>(msg.protectlampstatus) > signal_traits<SignalId::dm01_active_diagnostics__protectlampstatus>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__protectlampstatus,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.protectlampstatus),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__protectlampstatus,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::dm01_active_diagnostics__amberwarninglampstatus>::has_minimum &&
        static_cast<double>(msg.amberwarninglampstatus) < signal_traits<SignalId::dm01_active_diagnostics__amberwarninglampstatus>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__amberwarninglampstatus,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm01_active_diagnostics__amberwarninglampstatus>::has_maximum &&
        static_cast<double>(msg.amberwarninglampstatus) > signal_traits<SignalId::dm01_active_diagnostics__amberwarninglampstatus>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__amberwarninglampstatus,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::dm01_active_diagnostics__redstoplampstate>::has_minimum &&
        static_cast<double>(msg.redstoplampstate) < signal_traits<SignalId::dm01_active_diagnostics__redstoplampstate>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__redstoplampstate,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm01_active_diagnostics__redstoplampstate>::has_maximum &&
        static_cast<double>(msg.redstoplampstate) > signal_traits<SignalId::dm01_active_diagnostics__redstoplampstate>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__redstoplampstate,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::dm01_active_diagnostics__malfunctionindicatorlampstatus>::has_minimum &&
        static_cast<double>(msg.malfunctionindicatorlampstatus) < signal_traits<SignalId::dm01_active_diagnostics__malfunctionindicatorlampstatus>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__malfunctionindicatorlampstatus,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm01_active_diagnostics__malfunctionindicatorlampstatus>::has_maximum &&
        static_cast<double>(msg.malfunctionindicatorlampstatus) > signal_traits<SignalId::dm01_active_diagnostics__malfunctionindicatorlampstatus>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__malfunctionindicatorlampstatus,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::dm01_active_diagnostics__flashprotectlamp>::has_minimum &&
        static_cast<double>(msg.flashprotectlamp) < signal_traits<SignalId::dm01_active_diagnostics__flashprotectlamp>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__flashprotectlamp,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm01_active_diagnostics__flashprotectlamp>::has_maximum &&
        static_cast<double>(msg.flashprotectlamp) > signal_traits<SignalId::dm01_active_diagnostics__flashprotectlamp>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__flashprotectlamp,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::dm01_active_diagnostics__flashamberwarninglamp>::has_minimum &&
        static_cast<double>(msg.flashamberwarninglamp) < signal_traits<SignalId::dm01_active_diagnostics__flashamberwarninglamp>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__flashamberwarninglamp,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm01_active_diagnostics__flashamberwarninglamp>::has_maximum &&
        static_cast<double>(msg.flashamberwarninglamp) > signal_traits<SignalId::dm01_active_diagnostics__flashamberwarninglamp>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__flashamberwarninglamp,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::dm01_active_diagnostics__flashredstoplamp>::has_minimum &&
        static_cast<double>(msg.flashredstoplamp) < signal_traits<SignalId::dm01_active_diagnostics__flashredstoplamp>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__flashredstoplamp,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm01_active_diagnostics__flashredstoplamp>::has_maximum &&
        static_cast<double>(msg.flashredstoplamp) > signal_traits<SignalId::dm01_active_diagnostics__flashredstoplamp>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__flashredstoplamp,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::dm01_active_diagnostics__flashmalfuncindicatorlamp>::has_minimum &&
        static_cast<double>(msg.flashmalfuncindicatorlamp) < signal_traits<SignalId::dm01_active_diagnostics__flashmalfuncindicatorlamp>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__flashmalfuncindicatorlamp,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm01_active_diagnostics__flashmalfuncindicatorlamp>::has_maximum &&
        static_cast<double>(msg.flashmalfuncindicatorlamp) > signal_traits<SignalId::dm01_active_diagnostics__flashmalfuncindicatorlamp>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__flashmalfuncindicatorlamp,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::dm01_active_diagnostics__dtc1>::has_minimum &&
        static_cast<double>(msg.dtc1) < signal_traits<SignalId::dm01_active_diagnostics__dtc1>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__dtc1,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm01_active_diagnostics__dtc1>::has_maximum &&
        static_cast<double>(msg.dtc1) > signal_traits<SignalId::dm01_active_diagnostics__dtc1>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm01_active_diagnostics__dtc1,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.dtc1),
            1.0,
            0.0,
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
    if (signal_traits<SignalId::tsc1_31__engoverridectrlmode>::has_minimum &&
        static_cast<double>(msg.engoverridectrlmode) < signal_traits<SignalId::tsc1_31__engoverridectrlmode>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__engoverridectrlmode,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_31__engoverridectrlmode>::has_maximum &&
        static_cast<double>(msg.engoverridectrlmode) > signal_traits<SignalId::tsc1_31__engoverridectrlmode>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__engoverridectrlmode,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engoverridectrlmode),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__engoverridectrlmode,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::tsc1_31__engrequestedspeedctrlconditions>::has_minimum &&
        static_cast<double>(msg.engrequestedspeedctrlconditions) < signal_traits<SignalId::tsc1_31__engrequestedspeedctrlconditions>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__engrequestedspeedctrlconditions,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_31__engrequestedspeedctrlconditions>::has_maximum &&
        static_cast<double>(msg.engrequestedspeedctrlconditions) > signal_traits<SignalId::tsc1_31__engrequestedspeedctrlconditions>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__engrequestedspeedctrlconditions,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::tsc1_31__overridectrlmodepriority>::has_minimum &&
        static_cast<double>(msg.overridectrlmodepriority) < signal_traits<SignalId::tsc1_31__overridectrlmodepriority>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__overridectrlmodepriority,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_31__overridectrlmodepriority>::has_maximum &&
        static_cast<double>(msg.overridectrlmodepriority) > signal_traits<SignalId::tsc1_31__overridectrlmodepriority>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__overridectrlmodepriority,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engrequestedspeed_speedlimit,
            signal_traits<SignalId::tsc1_31__engrequestedspeed_speedlimit>::has_minimum,
            signal_traits<SignalId::tsc1_31__engrequestedspeed_speedlimit>::minimum,
            signal_traits<SignalId::tsc1_31__engrequestedspeed_speedlimit>::has_maximum,
            signal_traits<SignalId::tsc1_31__engrequestedspeed_speedlimit>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__engrequestedspeed_speedlimit,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::tsc1_31__engrequestedtorque_torquelimit>::has_minimum &&
        static_cast<double>(msg.engrequestedtorque_torquelimit) < signal_traits<SignalId::tsc1_31__engrequestedtorque_torquelimit>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__engrequestedtorque_torquelimit,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_31__engrequestedtorque_torquelimit>::has_maximum &&
        static_cast<double>(msg.engrequestedtorque_torquelimit) > signal_traits<SignalId::tsc1_31__engrequestedtorque_torquelimit>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__engrequestedtorque_torquelimit,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engrequestedtorque_torquelimit),
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__engrequestedtorque_torquelimit,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::tsc1_31__tsc1transrate>::has_minimum &&
        static_cast<double>(msg.tsc1transrate) < signal_traits<SignalId::tsc1_31__tsc1transrate>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__tsc1transrate,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_31__tsc1transrate>::has_maximum &&
        static_cast<double>(msg.tsc1transrate) > signal_traits<SignalId::tsc1_31__tsc1transrate>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__tsc1transrate,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::tsc1_31__tsc1ctrlpurpose>::has_minimum &&
        static_cast<double>(msg.tsc1ctrlpurpose) < signal_traits<SignalId::tsc1_31__tsc1ctrlpurpose>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__tsc1ctrlpurpose,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_31__tsc1ctrlpurpose>::has_maximum &&
        static_cast<double>(msg.tsc1ctrlpurpose) > signal_traits<SignalId::tsc1_31__tsc1ctrlpurpose>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__tsc1ctrlpurpose,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::tsc1_31__engrequestedtorquehighresolution>::has_minimum &&
        static_cast<double>(msg.engrequestedtorquehighresolution) < signal_traits<SignalId::tsc1_31__engrequestedtorquehighresolution>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__engrequestedtorquehighresolution,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_31__engrequestedtorquehighresolution>::has_maximum &&
        static_cast<double>(msg.engrequestedtorquehighresolution) > signal_traits<SignalId::tsc1_31__engrequestedtorquehighresolution>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__engrequestedtorquehighresolution,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::tsc1_31__messagecounter>::has_minimum &&
        static_cast<double>(msg.messagecounter) < signal_traits<SignalId::tsc1_31__messagecounter>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__messagecounter,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_31__messagecounter>::has_maximum &&
        static_cast<double>(msg.messagecounter) > signal_traits<SignalId::tsc1_31__messagecounter>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__messagecounter,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.messagecounter),
            1.0,
            0.0,
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__messagecounter,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::tsc1_31__messagechecksum>::has_minimum &&
        static_cast<double>(msg.messagechecksum) < signal_traits<SignalId::tsc1_31__messagechecksum>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__messagechecksum,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_31__messagechecksum>::has_maximum &&
        static_cast<double>(msg.messagechecksum) > signal_traits<SignalId::tsc1_31__messagechecksum>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_31__messagechecksum,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.messagechecksum),
            1.0,
            0.0,
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
    if (!detail::within_dbc_range(
            msg.engine_charge_air_cooler_1_intak,
            signal_traits<SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_intak>::has_minimum,
            signal_traits<SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_intak>::minimum,
            signal_traits<SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_intak>::has_maximum,
            signal_traits<SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_intak>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_intak,
            .error = ValidationError::value_outside_dbc_range
        });
    }
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
    if (!detail::within_dbc_range(
            msg.engine_charge_air_cooler_1_ambie,
            signal_traits<SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_ambie>::has_minimum,
            signal_traits<SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_ambie>::minimum,
            signal_traits<SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_ambie>::has_maximum,
            signal_traits<SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_ambie>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_ambie,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engine_charge_air_cooler_1_effic,
            signal_traits<SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_effic>::has_minimum,
            signal_traits<SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_effic>::minimum,
            signal_traits<SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_effic>::has_maximum,
            signal_traits<SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_effic>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_effic,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engine_total_hours_of_operation,
            signal_traits<SignalId::hours_engine_hours_revolutions__engine_total_hours_of_operation>::has_minimum,
            signal_traits<SignalId::hours_engine_hours_revolutions__engine_total_hours_of_operation>::minimum,
            signal_traits<SignalId::hours_engine_hours_revolutions__engine_total_hours_of_operation>::has_maximum,
            signal_traits<SignalId::hours_engine_hours_revolutions__engine_total_hours_of_operation>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::hours_engine_hours_revolutions__engine_total_hours_of_operation,
            .error = ValidationError::value_outside_dbc_range
        });
    }
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
    if (!detail::within_dbc_range(
            msg.engine_total_revolutions_249,
            signal_traits<SignalId::hours_engine_hours_revolutions__engine_total_revolutions_249>::has_minimum,
            signal_traits<SignalId::hours_engine_hours_revolutions__engine_total_revolutions_249>::minimum,
            signal_traits<SignalId::hours_engine_hours_revolutions__engine_total_revolutions_249>::has_maximum,
            signal_traits<SignalId::hours_engine_hours_revolutions__engine_total_revolutions_249>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::hours_engine_hours_revolutions__engine_total_revolutions_249,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.engine_total_revolutions_249,
            1000.0,
            0.0,
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
    if (!detail::within_dbc_range(
            msg.engine_turbocharger_1_turbine_ou,
            signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_1_turbine_ou>::has_minimum,
            signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_1_turbine_ou>::minimum,
            signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_1_turbine_ou>::has_maximum,
            signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_1_turbine_ou>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci5_turbocharger_information_5__engine_turbocharger_1_turbine_ou,
            .error = ValidationError::value_outside_dbc_range
        });
    }
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
    if (!detail::within_dbc_range(
            msg.engine_turbocharger_2_turbine_ou,
            signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_2_turbine_ou>::has_minimum,
            signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_2_turbine_ou>::minimum,
            signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_2_turbine_ou>::has_maximum,
            signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_2_turbine_ou>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci5_turbocharger_information_5__engine_turbocharger_2_turbine_ou,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engine_turbocharger_3_turbine_ou,
            signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_3_turbine_ou>::has_minimum,
            signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_3_turbine_ou>::minimum,
            signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_3_turbine_ou>::has_maximum,
            signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_3_turbine_ou>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci5_turbocharger_information_5__engine_turbocharger_3_turbine_ou,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engine_turbocharger_4_turbine_ou,
            signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_4_turbine_ou>::has_minimum,
            signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_4_turbine_ou>::minimum,
            signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_4_turbine_ou>::has_maximum,
            signal_traits<SignalId::tci5_turbocharger_information_5__engine_turbocharger_4_turbine_ou>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci5_turbocharger_information_5__engine_turbocharger_4_turbine_ou,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::vep1_vehicle_electrical_power_1__net_battery_current_114>::has_minimum &&
        static_cast<double>(msg.net_battery_current_114) < signal_traits<SignalId::vep1_vehicle_electrical_power_1__net_battery_current_114>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::vep1_vehicle_electrical_power_1__net_battery_current_114,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::vep1_vehicle_electrical_power_1__net_battery_current_114>::has_maximum &&
        static_cast<double>(msg.net_battery_current_114) > signal_traits<SignalId::vep1_vehicle_electrical_power_1__net_battery_current_114>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::vep1_vehicle_electrical_power_1__net_battery_current_114,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.net_battery_current_114),
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::vep1_vehicle_electrical_power_1__net_battery_current_114,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::vep1_vehicle_electrical_power_1__alternator_current_115>::has_minimum &&
        static_cast<double>(msg.alternator_current_115) < signal_traits<SignalId::vep1_vehicle_electrical_power_1__alternator_current_115>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::vep1_vehicle_electrical_power_1__alternator_current_115,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::vep1_vehicle_electrical_power_1__alternator_current_115>::has_maximum &&
        static_cast<double>(msg.alternator_current_115) > signal_traits<SignalId::vep1_vehicle_electrical_power_1__alternator_current_115>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::vep1_vehicle_electrical_power_1__alternator_current_115,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.alternator_current_115),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::vep1_vehicle_electrical_power_1__alternator_current_115,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.charging_system_potential_volta,
            signal_traits<SignalId::vep1_vehicle_electrical_power_1__charging_system_potential_volta>::has_minimum,
            signal_traits<SignalId::vep1_vehicle_electrical_power_1__charging_system_potential_volta>::minimum,
            signal_traits<SignalId::vep1_vehicle_electrical_power_1__charging_system_potential_volta>::has_maximum,
            signal_traits<SignalId::vep1_vehicle_electrical_power_1__charging_system_potential_volta>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::vep1_vehicle_electrical_power_1__charging_system_potential_volta,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.battery_potential_power_input_1,
            signal_traits<SignalId::vep1_vehicle_electrical_power_1__battery_potential_power_input_1>::has_minimum,
            signal_traits<SignalId::vep1_vehicle_electrical_power_1__battery_potential_power_input_1>::minimum,
            signal_traits<SignalId::vep1_vehicle_electrical_power_1__battery_potential_power_input_1>::has_maximum,
            signal_traits<SignalId::vep1_vehicle_electrical_power_1__battery_potential_power_input_1>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::vep1_vehicle_electrical_power_1__battery_potential_power_input_1,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.keyswitch_battery_potential_158,
            signal_traits<SignalId::vep1_vehicle_electrical_power_1__keyswitch_battery_potential_158>::has_minimum,
            signal_traits<SignalId::vep1_vehicle_electrical_power_1__keyswitch_battery_potential_158>::minimum,
            signal_traits<SignalId::vep1_vehicle_electrical_power_1__keyswitch_battery_potential_158>::has_maximum,
            signal_traits<SignalId::vep1_vehicle_electrical_power_1__keyswitch_battery_potential_158>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::vep1_vehicle_electrical_power_1__keyswitch_battery_potential_158,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.absolute_engine_load,
            signal_traits<SignalId::eec20_electronic_engine_control__absolute_engine_load>::has_minimum,
            signal_traits<SignalId::eec20_electronic_engine_control__absolute_engine_load>::minimum,
            signal_traits<SignalId::eec20_electronic_engine_control__absolute_engine_load>::has_maximum,
            signal_traits<SignalId::eec20_electronic_engine_control__absolute_engine_load>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::eec20_electronic_engine_control__absolute_engine_load,
            .error = ValidationError::value_outside_dbc_range
        });
    }
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
    if (!detail::within_dbc_range(
            msg.engine_intake_maf,
            signal_traits<SignalId::easi_engine_air_system_info__engine_intake_maf>::has_minimum,
            signal_traits<SignalId::easi_engine_air_system_info__engine_intake_maf>::minimum,
            signal_traits<SignalId::easi_engine_air_system_info__engine_intake_maf>::has_maximum,
            signal_traits<SignalId::easi_engine_air_system_info__engine_intake_maf>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::easi_engine_air_system_info__engine_intake_maf,
            .error = ValidationError::value_outside_dbc_range
        });
    }
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
    if (signal_traits<SignalId::tsc1_03__engoverridectrlmode>::has_minimum &&
        static_cast<double>(msg.engoverridectrlmode) < signal_traits<SignalId::tsc1_03__engoverridectrlmode>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__engoverridectrlmode,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_03__engoverridectrlmode>::has_maximum &&
        static_cast<double>(msg.engoverridectrlmode) > signal_traits<SignalId::tsc1_03__engoverridectrlmode>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__engoverridectrlmode,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engoverridectrlmode),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__engoverridectrlmode,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::tsc1_03__engrequestedspeedctrlconditions>::has_minimum &&
        static_cast<double>(msg.engrequestedspeedctrlconditions) < signal_traits<SignalId::tsc1_03__engrequestedspeedctrlconditions>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__engrequestedspeedctrlconditions,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_03__engrequestedspeedctrlconditions>::has_maximum &&
        static_cast<double>(msg.engrequestedspeedctrlconditions) > signal_traits<SignalId::tsc1_03__engrequestedspeedctrlconditions>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__engrequestedspeedctrlconditions,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::tsc1_03__overridectrlmodepriority>::has_minimum &&
        static_cast<double>(msg.overridectrlmodepriority) < signal_traits<SignalId::tsc1_03__overridectrlmodepriority>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__overridectrlmodepriority,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_03__overridectrlmodepriority>::has_maximum &&
        static_cast<double>(msg.overridectrlmodepriority) > signal_traits<SignalId::tsc1_03__overridectrlmodepriority>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__overridectrlmodepriority,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engrequestedspeed_speedlimit,
            signal_traits<SignalId::tsc1_03__engrequestedspeed_speedlimit>::has_minimum,
            signal_traits<SignalId::tsc1_03__engrequestedspeed_speedlimit>::minimum,
            signal_traits<SignalId::tsc1_03__engrequestedspeed_speedlimit>::has_maximum,
            signal_traits<SignalId::tsc1_03__engrequestedspeed_speedlimit>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__engrequestedspeed_speedlimit,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::tsc1_03__engrequestedtorque_torquelimit>::has_minimum &&
        static_cast<double>(msg.engrequestedtorque_torquelimit) < signal_traits<SignalId::tsc1_03__engrequestedtorque_torquelimit>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__engrequestedtorque_torquelimit,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_03__engrequestedtorque_torquelimit>::has_maximum &&
        static_cast<double>(msg.engrequestedtorque_torquelimit) > signal_traits<SignalId::tsc1_03__engrequestedtorque_torquelimit>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__engrequestedtorque_torquelimit,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engrequestedtorque_torquelimit),
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__engrequestedtorque_torquelimit,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::tsc1_03__tsc1transrate>::has_minimum &&
        static_cast<double>(msg.tsc1transrate) < signal_traits<SignalId::tsc1_03__tsc1transrate>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__tsc1transrate,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_03__tsc1transrate>::has_maximum &&
        static_cast<double>(msg.tsc1transrate) > signal_traits<SignalId::tsc1_03__tsc1transrate>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__tsc1transrate,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::tsc1_03__tsc1ctrlpurpose>::has_minimum &&
        static_cast<double>(msg.tsc1ctrlpurpose) < signal_traits<SignalId::tsc1_03__tsc1ctrlpurpose>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__tsc1ctrlpurpose,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_03__tsc1ctrlpurpose>::has_maximum &&
        static_cast<double>(msg.tsc1ctrlpurpose) > signal_traits<SignalId::tsc1_03__tsc1ctrlpurpose>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__tsc1ctrlpurpose,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::tsc1_03__engrequestedtorquehighresolution>::has_minimum &&
        static_cast<double>(msg.engrequestedtorquehighresolution) < signal_traits<SignalId::tsc1_03__engrequestedtorquehighresolution>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__engrequestedtorquehighresolution,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_03__engrequestedtorquehighresolution>::has_maximum &&
        static_cast<double>(msg.engrequestedtorquehighresolution) > signal_traits<SignalId::tsc1_03__engrequestedtorquehighresolution>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__engrequestedtorquehighresolution,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::tsc1_03__messagecounter>::has_minimum &&
        static_cast<double>(msg.messagecounter) < signal_traits<SignalId::tsc1_03__messagecounter>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__messagecounter,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_03__messagecounter>::has_maximum &&
        static_cast<double>(msg.messagecounter) > signal_traits<SignalId::tsc1_03__messagecounter>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__messagecounter,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.messagecounter),
            1.0,
            0.0,
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__messagecounter,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::tsc1_03__messagechecksum>::has_minimum &&
        static_cast<double>(msg.messagechecksum) < signal_traits<SignalId::tsc1_03__messagechecksum>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__messagechecksum,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_03__messagechecksum>::has_maximum &&
        static_cast<double>(msg.messagechecksum) > signal_traits<SignalId::tsc1_03__messagechecksum>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_03__messagechecksum,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.messagechecksum),
            1.0,
            0.0,
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
    if (signal_traits<SignalId::tsc1_0b__engoverridectrlmode>::has_minimum &&
        static_cast<double>(msg.engoverridectrlmode) < signal_traits<SignalId::tsc1_0b__engoverridectrlmode>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__engoverridectrlmode,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_0b__engoverridectrlmode>::has_maximum &&
        static_cast<double>(msg.engoverridectrlmode) > signal_traits<SignalId::tsc1_0b__engoverridectrlmode>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__engoverridectrlmode,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engoverridectrlmode),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__engoverridectrlmode,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::tsc1_0b__engrequestedspeedctrlconditions>::has_minimum &&
        static_cast<double>(msg.engrequestedspeedctrlconditions) < signal_traits<SignalId::tsc1_0b__engrequestedspeedctrlconditions>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__engrequestedspeedctrlconditions,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_0b__engrequestedspeedctrlconditions>::has_maximum &&
        static_cast<double>(msg.engrequestedspeedctrlconditions) > signal_traits<SignalId::tsc1_0b__engrequestedspeedctrlconditions>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__engrequestedspeedctrlconditions,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::tsc1_0b__overridectrlmodepriority>::has_minimum &&
        static_cast<double>(msg.overridectrlmodepriority) < signal_traits<SignalId::tsc1_0b__overridectrlmodepriority>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__overridectrlmodepriority,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_0b__overridectrlmodepriority>::has_maximum &&
        static_cast<double>(msg.overridectrlmodepriority) > signal_traits<SignalId::tsc1_0b__overridectrlmodepriority>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__overridectrlmodepriority,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engrequestedspeed_speedlimit,
            signal_traits<SignalId::tsc1_0b__engrequestedspeed_speedlimit>::has_minimum,
            signal_traits<SignalId::tsc1_0b__engrequestedspeed_speedlimit>::minimum,
            signal_traits<SignalId::tsc1_0b__engrequestedspeed_speedlimit>::has_maximum,
            signal_traits<SignalId::tsc1_0b__engrequestedspeed_speedlimit>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__engrequestedspeed_speedlimit,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::tsc1_0b__engrequestedtorque_torquelimit>::has_minimum &&
        static_cast<double>(msg.engrequestedtorque_torquelimit) < signal_traits<SignalId::tsc1_0b__engrequestedtorque_torquelimit>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__engrequestedtorque_torquelimit,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_0b__engrequestedtorque_torquelimit>::has_maximum &&
        static_cast<double>(msg.engrequestedtorque_torquelimit) > signal_traits<SignalId::tsc1_0b__engrequestedtorque_torquelimit>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__engrequestedtorque_torquelimit,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.engrequestedtorque_torquelimit),
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__engrequestedtorque_torquelimit,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::tsc1_0b__tsc1transrate>::has_minimum &&
        static_cast<double>(msg.tsc1transrate) < signal_traits<SignalId::tsc1_0b__tsc1transrate>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__tsc1transrate,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_0b__tsc1transrate>::has_maximum &&
        static_cast<double>(msg.tsc1transrate) > signal_traits<SignalId::tsc1_0b__tsc1transrate>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__tsc1transrate,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::tsc1_0b__tsc1ctrlpurpose>::has_minimum &&
        static_cast<double>(msg.tsc1ctrlpurpose) < signal_traits<SignalId::tsc1_0b__tsc1ctrlpurpose>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__tsc1ctrlpurpose,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_0b__tsc1ctrlpurpose>::has_maximum &&
        static_cast<double>(msg.tsc1ctrlpurpose) > signal_traits<SignalId::tsc1_0b__tsc1ctrlpurpose>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__tsc1ctrlpurpose,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::tsc1_0b__engrequestedtorquehighresolution>::has_minimum &&
        static_cast<double>(msg.engrequestedtorquehighresolution) < signal_traits<SignalId::tsc1_0b__engrequestedtorquehighresolution>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__engrequestedtorquehighresolution,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_0b__engrequestedtorquehighresolution>::has_maximum &&
        static_cast<double>(msg.engrequestedtorquehighresolution) > signal_traits<SignalId::tsc1_0b__engrequestedtorquehighresolution>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__engrequestedtorquehighresolution,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::tsc1_0b__messagecounter>::has_minimum &&
        static_cast<double>(msg.messagecounter) < signal_traits<SignalId::tsc1_0b__messagecounter>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__messagecounter,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_0b__messagecounter>::has_maximum &&
        static_cast<double>(msg.messagecounter) > signal_traits<SignalId::tsc1_0b__messagecounter>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__messagecounter,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.messagecounter),
            1.0,
            0.0,
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__messagecounter,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::tsc1_0b__messagechecksum>::has_minimum &&
        static_cast<double>(msg.messagechecksum) < signal_traits<SignalId::tsc1_0b__messagechecksum>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__messagechecksum,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tsc1_0b__messagechecksum>::has_maximum &&
        static_cast<double>(msg.messagechecksum) > signal_traits<SignalId::tsc1_0b__messagechecksum>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tsc1_0b__messagechecksum,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.messagechecksum),
            1.0,
            0.0,
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
    if (signal_traits<SignalId::dm07__testidentifier>::has_minimum &&
        static_cast<double>(msg.testidentifier) < signal_traits<SignalId::dm07__testidentifier>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm07__testidentifier,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm07__testidentifier>::has_maximum &&
        static_cast<double>(msg.testidentifier) > signal_traits<SignalId::dm07__testidentifier>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm07__testidentifier,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.testidentifier),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm07__testidentifier,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::dm07__spn1>::has_minimum &&
        static_cast<double>(msg.spn1) < signal_traits<SignalId::dm07__spn1>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm07__spn1,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm07__spn1>::has_maximum &&
        static_cast<double>(msg.spn1) > signal_traits<SignalId::dm07__spn1>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm07__spn1,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.spn1),
            1.0,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm07__spn1,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::dm07__failuremodeidentifier1>::has_minimum &&
        static_cast<double>(msg.failuremodeidentifier1) < signal_traits<SignalId::dm07__failuremodeidentifier1>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm07__failuremodeidentifier1,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm07__failuremodeidentifier1>::has_maximum &&
        static_cast<double>(msg.failuremodeidentifier1) > signal_traits<SignalId::dm07__failuremodeidentifier1>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm07__failuremodeidentifier1,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::dm07__spn1high>::has_minimum &&
        static_cast<double>(msg.spn1high) < signal_traits<SignalId::dm07__spn1high>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm07__spn1high,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm07__spn1high>::has_maximum &&
        static_cast<double>(msg.spn1high) > signal_traits<SignalId::dm07__spn1high>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm07__spn1high,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.spn1high),
            1.0,
            0.0,
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
    if (signal_traits<SignalId::dm08__testidentifier>::has_minimum &&
        static_cast<double>(msg.testidentifier) < signal_traits<SignalId::dm08__testidentifier>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testidentifier,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm08__testidentifier>::has_maximum &&
        static_cast<double>(msg.testidentifier) > signal_traits<SignalId::dm08__testidentifier>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testidentifier,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.testidentifier),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testidentifier,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::dm08__testtype>::has_minimum &&
        static_cast<double>(msg.testtype) < signal_traits<SignalId::dm08__testtype>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testtype,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm08__testtype>::has_maximum &&
        static_cast<double>(msg.testtype) > signal_traits<SignalId::dm08__testtype>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testtype,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.testtype),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testtype,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::dm08__testvalue>::has_minimum &&
        static_cast<double>(msg.testvalue) < signal_traits<SignalId::dm08__testvalue>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testvalue,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm08__testvalue>::has_maximum &&
        static_cast<double>(msg.testvalue) > signal_traits<SignalId::dm08__testvalue>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testvalue,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.testvalue),
            1.0,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testvalue,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::dm08__testlimitmaximum>::has_minimum &&
        static_cast<double>(msg.testlimitmaximum) < signal_traits<SignalId::dm08__testlimitmaximum>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testlimitmaximum,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm08__testlimitmaximum>::has_maximum &&
        static_cast<double>(msg.testlimitmaximum) > signal_traits<SignalId::dm08__testlimitmaximum>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testlimitmaximum,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.testlimitmaximum),
            1.0,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testlimitmaximum,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::dm08__testlimitminimum>::has_minimum &&
        static_cast<double>(msg.testlimitminimum) < signal_traits<SignalId::dm08__testlimitminimum>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testlimitminimum,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::dm08__testlimitminimum>::has_maximum &&
        static_cast<double>(msg.testlimitminimum) > signal_traits<SignalId::dm08__testlimitminimum>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::dm08__testlimitminimum,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.testlimitminimum),
            1.0,
            0.0,
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
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__retardertorquemode>::has_minimum &&
        static_cast<double>(msg.retardertorquemode) < signal_traits<SignalId::erc1_electronic_retarder_cntrl__retardertorquemode>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retardertorquemode,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__retardertorquemode>::has_maximum &&
        static_cast<double>(msg.retardertorquemode) > signal_traits<SignalId::erc1_electronic_retarder_cntrl__retardertorquemode>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retardertorquemode,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.retardertorquemode),
            1.0,
            0.0,
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retardertorquemode,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch>::has_minimum &&
        static_cast<double>(msg.retarderenablebrakeassistswitch) < signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch>::has_maximum &&
        static_cast<double>(msg.retarderenablebrakeassistswitch) > signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch>::has_minimum &&
        static_cast<double>(msg.retarderenableshiftassistswitch) < signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch>::has_maximum &&
        static_cast<double>(msg.retarderenableshiftassistswitch) > signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__actualretarderpercenttorque>::has_minimum &&
        static_cast<double>(msg.actualretarderpercenttorque) < signal_traits<SignalId::erc1_electronic_retarder_cntrl__actualretarderpercenttorque>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__actualretarderpercenttorque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__actualretarderpercenttorque>::has_maximum &&
        static_cast<double>(msg.actualretarderpercenttorque) > signal_traits<SignalId::erc1_electronic_retarder_cntrl__actualretarderpercenttorque>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__actualretarderpercenttorque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.actualretarderpercenttorque),
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__actualretarderpercenttorque,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__intendedretarderpercenttorque>::has_minimum &&
        static_cast<double>(msg.intendedretarderpercenttorque) < signal_traits<SignalId::erc1_electronic_retarder_cntrl__intendedretarderpercenttorque>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__intendedretarderpercenttorque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__intendedretarderpercenttorque>::has_maximum &&
        static_cast<double>(msg.intendedretarderpercenttorque) > signal_traits<SignalId::erc1_electronic_retarder_cntrl__intendedretarderpercenttorque>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__intendedretarderpercenttorque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.intendedretarderpercenttorque),
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__intendedretarderpercenttorque,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__engcoolantloadincrease>::has_minimum &&
        static_cast<double>(msg.engcoolantloadincrease) < signal_traits<SignalId::erc1_electronic_retarder_cntrl__engcoolantloadincrease>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__engcoolantloadincrease,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__engcoolantloadincrease>::has_maximum &&
        static_cast<double>(msg.engcoolantloadincrease) > signal_traits<SignalId::erc1_electronic_retarder_cntrl__engcoolantloadincrease>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__engcoolantloadincrease,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderrequestingbrakelight>::has_minimum &&
        static_cast<double>(msg.retarderrequestingbrakelight) < signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderrequestingbrakelight>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderrequestingbrakelight,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderrequestingbrakelight>::has_maximum &&
        static_cast<double>(msg.retarderrequestingbrakelight) > signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderrequestingbrakelight>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderrequestingbrakelight,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch>::has_minimum &&
        static_cast<double>(msg.retarderroadspeedlimitswitch) < signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch>::has_maximum &&
        static_cast<double>(msg.retarderroadspeedlimitswitch) > signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus>::has_minimum &&
        static_cast<double>(msg.retarderroadspeedexceededstatus) < signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus>::has_maximum &&
        static_cast<double>(msg.retarderroadspeedexceededstatus) > signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__srcaddrssofcntrllngdvcfrrtrdrctr>::has_minimum &&
        static_cast<double>(msg.srcaddrssofcntrllngdvcfrrtrdrctr) < signal_traits<SignalId::erc1_electronic_retarder_cntrl__srcaddrssofcntrllngdvcfrrtrdrctr>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__srcaddrssofcntrllngdvcfrrtrdrctr,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__srcaddrssofcntrllngdvcfrrtrdrctr>::has_maximum &&
        static_cast<double>(msg.srcaddrssofcntrllngdvcfrrtrdrctr) > signal_traits<SignalId::erc1_electronic_retarder_cntrl__srcaddrssofcntrllngdvcfrrtrdrctr>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__srcaddrssofcntrllngdvcfrrtrdrctr,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.srcaddrssofcntrllngdvcfrrtrdrctr),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__srcaddrssofcntrllngdvcfrrtrdrctr,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__drvrsdemandretarderpercenttorque>::has_minimum &&
        static_cast<double>(msg.drvrsdemandretarderpercenttorque) < signal_traits<SignalId::erc1_electronic_retarder_cntrl__drvrsdemandretarderpercenttorque>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__drvrsdemandretarderpercenttorque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__drvrsdemandretarderpercenttorque>::has_maximum &&
        static_cast<double>(msg.drvrsdemandretarderpercenttorque) > signal_traits<SignalId::erc1_electronic_retarder_cntrl__drvrsdemandretarderpercenttorque>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__drvrsdemandretarderpercenttorque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.drvrsdemandretarderpercenttorque),
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__drvrsdemandretarderpercenttorque,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.retarderselectionnonengine,
            signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderselectionnonengine>::has_minimum,
            signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderselectionnonengine>::minimum,
            signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderselectionnonengine>::has_maximum,
            signal_traits<SignalId::erc1_electronic_retarder_cntrl__retarderselectionnonengine>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__retarderselectionnonengine,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__actlmxavlblretarderpercenttorque>::has_minimum &&
        static_cast<double>(msg.actlmxavlblretarderpercenttorque) < signal_traits<SignalId::erc1_electronic_retarder_cntrl__actlmxavlblretarderpercenttorque>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__actlmxavlblretarderpercenttorque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::erc1_electronic_retarder_cntrl__actlmxavlblretarderpercenttorque>::has_maximum &&
        static_cast<double>(msg.actlmxavlblretarderpercenttorque) > signal_traits<SignalId::erc1_electronic_retarder_cntrl__actlmxavlblretarderpercenttorque>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::erc1_electronic_retarder_cntrl__actlmxavlblretarderpercenttorque,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.actlmxavlblretarderpercenttorque),
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
    if (signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transdrivelineengaged>::has_minimum &&
        static_cast<double>(msg.transdrivelineengaged) < signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transdrivelineengaged>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__transdrivelineengaged,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transdrivelineengaged>::has_maximum &&
        static_cast<double>(msg.transdrivelineengaged) > signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transdrivelineengaged>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__transdrivelineengaged,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.transdrivelineengaged),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__transdrivelineengaged,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged>::has_minimum &&
        static_cast<double>(msg.trnstorqueconverterlockupengaged) < signal_traits<SignalId::etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged>::has_maximum &&
        static_cast<double>(msg.trnstorqueconverterlockupengaged) > signal_traits<SignalId::etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transshiftinprocess>::has_minimum &&
        static_cast<double>(msg.transshiftinprocess) < signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transshiftinprocess>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__transshiftinprocess,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transshiftinprocess>::has_maximum &&
        static_cast<double>(msg.transshiftinprocess) > signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transshiftinprocess>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__transshiftinprocess,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess>::has_minimum &&
        static_cast<double>(msg.trnstrqcnvrtrlckptrnstninprocess) < signal_traits<SignalId::etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess>::has_maximum &&
        static_cast<double>(msg.trnstrqcnvrtrlckptrnstninprocess) > signal_traits<SignalId::etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.transoutputshaftspeed,
            signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transoutputshaftspeed>::has_minimum,
            signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transoutputshaftspeed>::minimum,
            signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transoutputshaftspeed>::has_maximum,
            signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transoutputshaftspeed>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__transoutputshaftspeed,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.percentclutchslip,
            signal_traits<SignalId::etc1_electronic_trans_cntrl_1__percentclutchslip>::has_minimum,
            signal_traits<SignalId::etc1_electronic_trans_cntrl_1__percentclutchslip>::minimum,
            signal_traits<SignalId::etc1_electronic_trans_cntrl_1__percentclutchslip>::has_maximum,
            signal_traits<SignalId::etc1_electronic_trans_cntrl_1__percentclutchslip>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__percentclutchslip,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable>::has_minimum &&
        static_cast<double>(msg.engmomentaryoverspeedenable) < signal_traits<SignalId::etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable>::has_maximum &&
        static_cast<double>(msg.engmomentaryoverspeedenable) > signal_traits<SignalId::etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::etc1_electronic_trans_cntrl_1__progressiveshiftdisable>::has_minimum &&
        static_cast<double>(msg.progressiveshiftdisable) < signal_traits<SignalId::etc1_electronic_trans_cntrl_1__progressiveshiftdisable>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__progressiveshiftdisable,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::etc1_electronic_trans_cntrl_1__progressiveshiftdisable>::has_maximum &&
        static_cast<double>(msg.progressiveshiftdisable) > signal_traits<SignalId::etc1_electronic_trans_cntrl_1__progressiveshiftdisable>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__progressiveshiftdisable,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable>::has_minimum &&
        static_cast<double>(msg.momentaryengmaxpowerenable) < signal_traits<SignalId::etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable>::has_maximum &&
        static_cast<double>(msg.momentaryengmaxpowerenable) > signal_traits<SignalId::etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.transinputshaftspeed,
            signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transinputshaftspeed>::has_minimum,
            signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transinputshaftspeed>::minimum,
            signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transinputshaftspeed>::has_maximum,
            signal_traits<SignalId::etc1_electronic_trans_cntrl_1__transinputshaftspeed>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__transinputshaftspeed,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::etc1_electronic_trans_cntrl_1__srcaddrssofcntrllngdvcfrtrnsctrl>::has_minimum &&
        static_cast<double>(msg.srcaddrssofcntrllngdvcfrtrnsctrl) < signal_traits<SignalId::etc1_electronic_trans_cntrl_1__srcaddrssofcntrllngdvcfrtrnsctrl>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__srcaddrssofcntrllngdvcfrtrnsctrl,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::etc1_electronic_trans_cntrl_1__srcaddrssofcntrllngdvcfrtrnsctrl>::has_maximum &&
        static_cast<double>(msg.srcaddrssofcntrllngdvcfrtrnsctrl) > signal_traits<SignalId::etc1_electronic_trans_cntrl_1__srcaddrssofcntrllngdvcfrtrnsctrl>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc1_electronic_trans_cntrl_1__srcaddrssofcntrllngdvcfrtrnsctrl,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.srcaddrssofcntrllngdvcfrtrnsctrl),
            1.0,
            0.0,
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
    if (signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transselectedgear>::has_minimum &&
        static_cast<double>(msg.transselectedgear) < signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transselectedgear>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transselectedgear,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transselectedgear>::has_maximum &&
        static_cast<double>(msg.transselectedgear) > signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transselectedgear>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transselectedgear,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.transselectedgear),
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transselectedgear,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.transactualgearratio,
            signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transactualgearratio>::has_minimum,
            signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transactualgearratio>::minimum,
            signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transactualgearratio>::has_maximum,
            signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transactualgearratio>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transactualgearratio,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transcurrentgear>::has_minimum &&
        static_cast<double>(msg.transcurrentgear) < signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transcurrentgear>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transcurrentgear,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transcurrentgear>::has_maximum &&
        static_cast<double>(msg.transcurrentgear) > signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transcurrentgear>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transcurrentgear,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.transcurrentgear),
            1.0,
            -125.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transcurrentgear,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transrequestedrange>::has_minimum &&
        static_cast<double>(msg.transrequestedrange) < signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transrequestedrange>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transrequestedrange,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transrequestedrange>::has_maximum &&
        static_cast<double>(msg.transrequestedrange) > signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transrequestedrange>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transrequestedrange,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.transrequestedrange),
            1.0,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transrequestedrange,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transcurrentrange>::has_minimum &&
        static_cast<double>(msg.transcurrentrange) < signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transcurrentrange>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transcurrentrange,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transcurrentrange>::has_maximum &&
        static_cast<double>(msg.transcurrentrange) > signal_traits<SignalId::etc2_electronic_trans_cntrl_2__transcurrentrange>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::etc2_electronic_trans_cntrl_2__transcurrentrange,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.transcurrentrange),
            1.0,
            0.0,
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
    if (signal_traits<SignalId::rqst_00_5e__parametergroupnumber>::has_minimum &&
        static_cast<double>(msg.parametergroupnumber) < signal_traits<SignalId::rqst_00_5e__parametergroupnumber>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::rqst_00_5e__parametergroupnumber,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::rqst_00_5e__parametergroupnumber>::has_maximum &&
        static_cast<double>(msg.parametergroupnumber) > signal_traits<SignalId::rqst_00_5e__parametergroupnumber>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::rqst_00_5e__parametergroupnumber,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.parametergroupnumber),
            1.0,
            0.0,
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
    if (signal_traits<SignalId::rqst_00_21__parametergroupnumber>::has_minimum &&
        static_cast<double>(msg.parametergroupnumber) < signal_traits<SignalId::rqst_00_21__parametergroupnumber>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::rqst_00_21__parametergroupnumber,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::rqst_00_21__parametergroupnumber>::has_maximum &&
        static_cast<double>(msg.parametergroupnumber) > signal_traits<SignalId::rqst_00_21__parametergroupnumber>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::rqst_00_21__parametergroupnumber,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.parametergroupnumber),
            1.0,
            0.0,
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
    if (signal_traits<SignalId::rqst_global_5e__parametergroupnumber>::has_minimum &&
        static_cast<double>(msg.parametergroupnumber) < signal_traits<SignalId::rqst_global_5e__parametergroupnumber>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::rqst_global_5e__parametergroupnumber,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::rqst_global_5e__parametergroupnumber>::has_maximum &&
        static_cast<double>(msg.parametergroupnumber) > signal_traits<SignalId::rqst_global_5e__parametergroupnumber>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::rqst_global_5e__parametergroupnumber,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.parametergroupnumber),
            1.0,
            0.0,
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
    if (signal_traits<SignalId::rqst_global_03__parametergroupnumber>::has_minimum &&
        static_cast<double>(msg.parametergroupnumber) < signal_traits<SignalId::rqst_global_03__parametergroupnumber>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::rqst_global_03__parametergroupnumber,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::rqst_global_03__parametergroupnumber>::has_maximum &&
        static_cast<double>(msg.parametergroupnumber) > signal_traits<SignalId::rqst_global_03__parametergroupnumber>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::rqst_global_03__parametergroupnumber,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.parametergroupnumber),
            1.0,
            0.0,
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
    if (signal_traits<SignalId::tci_transfer_case_information__transfercasestatus>::has_minimum &&
        static_cast<double>(msg.transfercasestatus) < signal_traits<SignalId::tci_transfer_case_information__transfercasestatus>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci_transfer_case_information__transfercasestatus,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tci_transfer_case_information__transfercasestatus>::has_maximum &&
        static_cast<double>(msg.transfercasestatus) > signal_traits<SignalId::tci_transfer_case_information__transfercasestatus>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci_transfer_case_information__transfercasestatus,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.transfercasestatus),
            3U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci_transfer_case_information__transfercasestatus,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::tci_transfer_case_information__dirstatus>::has_minimum &&
        static_cast<double>(msg.dirstatus) < signal_traits<SignalId::tci_transfer_case_information__dirstatus>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci_transfer_case_information__dirstatus,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tci_transfer_case_information__dirstatus>::has_maximum &&
        static_cast<double>(msg.dirstatus) > signal_traits<SignalId::tci_transfer_case_information__dirstatus>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci_transfer_case_information__dirstatus,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.actualgearratio,
            signal_traits<SignalId::tci_transfer_case_information__actualgearratio>::has_minimum,
            signal_traits<SignalId::tci_transfer_case_information__actualgearratio>::minimum,
            signal_traits<SignalId::tci_transfer_case_information__actualgearratio>::has_maximum,
            signal_traits<SignalId::tci_transfer_case_information__actualgearratio>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci_transfer_case_information__actualgearratio,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::tci_transfer_case_information__messagecounter>::has_minimum &&
        static_cast<double>(msg.messagecounter) < signal_traits<SignalId::tci_transfer_case_information__messagecounter>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci_transfer_case_information__messagecounter,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tci_transfer_case_information__messagecounter>::has_maximum &&
        static_cast<double>(msg.messagecounter) > signal_traits<SignalId::tci_transfer_case_information__messagecounter>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci_transfer_case_information__messagecounter,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.messagecounter),
            1.0,
            0.0,
            4U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci_transfer_case_information__messagecounter,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::tci_transfer_case_information__messagechecksum>::has_minimum &&
        static_cast<double>(msg.messagechecksum) < signal_traits<SignalId::tci_transfer_case_information__messagechecksum>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci_transfer_case_information__messagechecksum,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::tci_transfer_case_information__messagechecksum>::has_maximum &&
        static_cast<double>(msg.messagechecksum) > signal_traits<SignalId::tci_transfer_case_information__messagechecksum>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::tci_transfer_case_information__messagechecksum,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.messagechecksum),
            1.0,
            0.0,
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
    if (signal_traits<SignalId::trf1_transmission_fluids_1__clutchpress>::has_minimum &&
        static_cast<double>(msg.clutchpress) < signal_traits<SignalId::trf1_transmission_fluids_1__clutchpress>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__clutchpress,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::trf1_transmission_fluids_1__clutchpress>::has_maximum &&
        static_cast<double>(msg.clutchpress) > signal_traits<SignalId::trf1_transmission_fluids_1__clutchpress>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__clutchpress,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.clutchpress),
            16.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__clutchpress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.transoillevel1,
            signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1>::has_minimum,
            signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1>::minimum,
            signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1>::has_maximum,
            signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transoillevel1,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::trf1_transmission_fluids_1__transfilterdiffpress>::has_minimum &&
        static_cast<double>(msg.transfilterdiffpress) < signal_traits<SignalId::trf1_transmission_fluids_1__transfilterdiffpress>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transfilterdiffpress,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::trf1_transmission_fluids_1__transfilterdiffpress>::has_maximum &&
        static_cast<double>(msg.transfilterdiffpress) > signal_traits<SignalId::trf1_transmission_fluids_1__transfilterdiffpress>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transfilterdiffpress,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.transfilterdiffpress),
            2.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transfilterdiffpress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::trf1_transmission_fluids_1__transoilpress>::has_minimum &&
        static_cast<double>(msg.transoilpress) < signal_traits<SignalId::trf1_transmission_fluids_1__transoilpress>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transoilpress,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::trf1_transmission_fluids_1__transoilpress>::has_maximum &&
        static_cast<double>(msg.transoilpress) > signal_traits<SignalId::trf1_transmission_fluids_1__transoilpress>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transoilpress,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.transoilpress),
            16.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transoilpress,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.transoiltemp1,
            signal_traits<SignalId::trf1_transmission_fluids_1__transoiltemp1>::has_minimum,
            signal_traits<SignalId::trf1_transmission_fluids_1__transoiltemp1>::minimum,
            signal_traits<SignalId::trf1_transmission_fluids_1__transoiltemp1>::has_maximum,
            signal_traits<SignalId::trf1_transmission_fluids_1__transoiltemp1>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transoiltemp1,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.transoillevel1high_low,
            signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1high_low>::has_minimum,
            signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1high_low>::minimum,
            signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1high_low>::has_maximum,
            signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1high_low>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transoillevel1high_low,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1countdowntimer>::has_minimum &&
        static_cast<double>(msg.transoillevel1countdowntimer) < signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1countdowntimer>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transoillevel1countdowntimer,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1countdowntimer>::has_maximum &&
        static_cast<double>(msg.transoillevel1countdowntimer) > signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1countdowntimer>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transoillevel1countdowntimer,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1measurementstatus>::has_minimum &&
        static_cast<double>(msg.transoillevel1measurementstatus) < signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1measurementstatus>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transoillevel1measurementstatus,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1measurementstatus>::has_maximum &&
        static_cast<double>(msg.transoillevel1measurementstatus) > signal_traits<SignalId::trf1_transmission_fluids_1__transoillevel1measurementstatus>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::trf1_transmission_fluids_1__transoillevel1measurementstatus,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit>::has_minimum &&
        static_cast<double>(msg.maxvehiclespeedlimit) < signal_traits<SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit>::has_maximum &&
        static_cast<double>(msg.maxvehiclespeedlimit) > signal_traits<SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.maxvehiclespeedlimit),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__cruisectrlhighsetlimitspeed>::has_minimum &&
        static_cast<double>(msg.cruisectrlhighsetlimitspeed) < signal_traits<SignalId::ccss_cruise_control_vehicle_spd__cruisectrlhighsetlimitspeed>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__cruisectrlhighsetlimitspeed,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__cruisectrlhighsetlimitspeed>::has_maximum &&
        static_cast<double>(msg.cruisectrlhighsetlimitspeed) > signal_traits<SignalId::ccss_cruise_control_vehicle_spd__cruisectrlhighsetlimitspeed>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__cruisectrlhighsetlimitspeed,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.cruisectrlhighsetlimitspeed),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__cruisectrlhighsetlimitspeed,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__cruisectrllowsetlimitspeed>::has_minimum &&
        static_cast<double>(msg.cruisectrllowsetlimitspeed) < signal_traits<SignalId::ccss_cruise_control_vehicle_spd__cruisectrllowsetlimitspeed>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__cruisectrllowsetlimitspeed,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__cruisectrllowsetlimitspeed>::has_maximum &&
        static_cast<double>(msg.cruisectrllowsetlimitspeed) > signal_traits<SignalId::ccss_cruise_control_vehicle_spd__cruisectrllowsetlimitspeed>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__cruisectrllowsetlimitspeed,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.cruisectrllowsetlimitspeed),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__cruisectrllowsetlimitspeed,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.maxvehiclespeedlimit6808,
            signal_traits<SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit6808>::has_minimum,
            signal_traits<SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit6808>::minimum,
            signal_traits<SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit6808>::has_maximum,
            signal_traits<SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit6808>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__maxvehiclespeedlimit6808,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlsyslowsetlmtspd>::has_minimum &&
        static_cast<double>(msg.ctrlsyslowsetlmtspd) < signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlsyslowsetlmtspd>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__ctrlsyslowsetlmtspd,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlsyslowsetlmtspd>::has_maximum &&
        static_cast<double>(msg.ctrlsyslowsetlmtspd) > signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlsyslowsetlmtspd>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__ctrlsyslowsetlmtspd,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.ctrlsyslowsetlmtspd),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__ctrlsyslowsetlmtspd,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrldiscmdsupport>::has_minimum &&
        static_cast<double>(msg.ctrldiscmdsupport) < signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrldiscmdsupport>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__ctrldiscmdsupport,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrldiscmdsupport>::has_maximum &&
        static_cast<double>(msg.ctrldiscmdsupport) > signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrldiscmdsupport>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__ctrldiscmdsupport,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport>::has_minimum &&
        static_cast<double>(msg.ctrlresumecmdsupport) < signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport>::has_maximum &&
        static_cast<double>(msg.ctrlresumecmdsupport) > signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport>::has_minimum &&
        static_cast<double>(msg.ctrlpausecmdsupport) < signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport>::has_maximum &&
        static_cast<double>(msg.ctrlpausecmdsupport) > signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport>::has_minimum &&
        static_cast<double>(msg.ctrlsetcmdsupport) < signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport>::has_maximum &&
        static_cast<double>(msg.ctrlsetcmdsupport) > signal_traits<SignalId::ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__powertrainadaptivecctype>::has_minimum &&
        static_cast<double>(msg.powertrainadaptivecctype) < signal_traits<SignalId::ccss_cruise_control_vehicle_spd__powertrainadaptivecctype>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__powertrainadaptivecctype,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccss_cruise_control_vehicle_spd__powertrainadaptivecctype>::has_maximum &&
        static_cast<double>(msg.powertrainadaptivecctype) > signal_traits<SignalId::ccss_cruise_control_vehicle_spd__powertrainadaptivecctype>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccss_cruise_control_vehicle_spd__powertrainadaptivecctype,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__twospeedaxleswitch>::has_minimum &&
        static_cast<double>(msg.twospeedaxleswitch) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__twospeedaxleswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__twospeedaxleswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__twospeedaxleswitch>::has_maximum &&
        static_cast<double>(msg.twospeedaxleswitch) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__twospeedaxleswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__twospeedaxleswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.twospeedaxleswitch),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__twospeedaxleswitch,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__parkingbrakeswitch>::has_minimum &&
        static_cast<double>(msg.parkingbrakeswitch) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__parkingbrakeswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__parkingbrakeswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__parkingbrakeswitch>::has_maximum &&
        static_cast<double>(msg.parkingbrakeswitch) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__parkingbrakeswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__parkingbrakeswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlpauseswitch>::has_minimum &&
        static_cast<double>(msg.cruisectrlpauseswitch) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlpauseswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlpauseswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlpauseswitch>::has_maximum &&
        static_cast<double>(msg.cruisectrlpauseswitch) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlpauseswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlpauseswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq>::has_minimum &&
        static_cast<double>(msg.parkbrakereleaseinhibitrq) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq>::has_maximum &&
        static_cast<double>(msg.parkbrakereleaseinhibitrq) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.wheelbasedvehiclespeed,
            signal_traits<SignalId::ccvs1_cruise_control_vehspd__wheelbasedvehiclespeed>::has_minimum,
            signal_traits<SignalId::ccvs1_cruise_control_vehspd__wheelbasedvehiclespeed>::minimum,
            signal_traits<SignalId::ccvs1_cruise_control_vehspd__wheelbasedvehiclespeed>::has_maximum,
            signal_traits<SignalId::ccvs1_cruise_control_vehspd__wheelbasedvehiclespeed>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__wheelbasedvehiclespeed,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlactive>::has_minimum &&
        static_cast<double>(msg.cruisectrlactive) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlactive>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlactive,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlactive>::has_maximum &&
        static_cast<double>(msg.cruisectrlactive) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlactive>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlactive,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlenableswitch>::has_minimum &&
        static_cast<double>(msg.cruisectrlenableswitch) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlenableswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlenableswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlenableswitch>::has_maximum &&
        static_cast<double>(msg.cruisectrlenableswitch) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlenableswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlenableswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__brakeswitch>::has_minimum &&
        static_cast<double>(msg.brakeswitch) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__brakeswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__brakeswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__brakeswitch>::has_maximum &&
        static_cast<double>(msg.brakeswitch) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__brakeswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__brakeswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__clutchswitch>::has_minimum &&
        static_cast<double>(msg.clutchswitch) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__clutchswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__clutchswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__clutchswitch>::has_maximum &&
        static_cast<double>(msg.clutchswitch) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__clutchswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__clutchswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetswitch>::has_minimum &&
        static_cast<double>(msg.cruisectrlsetswitch) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetswitch>::has_maximum &&
        static_cast<double>(msg.cruisectrlsetswitch) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlcoastswitch>::has_minimum &&
        static_cast<double>(msg.cruisectrlcoastswitch) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlcoastswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlcoastswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlcoastswitch>::has_maximum &&
        static_cast<double>(msg.cruisectrlcoastswitch) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlcoastswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlcoastswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlresumeswitch>::has_minimum &&
        static_cast<double>(msg.cruisectrlresumeswitch) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlresumeswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlresumeswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlresumeswitch>::has_maximum &&
        static_cast<double>(msg.cruisectrlresumeswitch) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlresumeswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlresumeswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch>::has_minimum &&
        static_cast<double>(msg.cruisectrlaccelerateswitch) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch>::has_maximum &&
        static_cast<double>(msg.cruisectrlaccelerateswitch) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetspeed>::has_minimum &&
        static_cast<double>(msg.cruisectrlsetspeed) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetspeed>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetspeed,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetspeed>::has_maximum &&
        static_cast<double>(msg.cruisectrlsetspeed) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetspeed>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetspeed,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.cruisectrlsetspeed),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetspeed,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__ptogovernorstate>::has_minimum &&
        static_cast<double>(msg.ptogovernorstate) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__ptogovernorstate>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__ptogovernorstate,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__ptogovernorstate>::has_maximum &&
        static_cast<double>(msg.ptogovernorstate) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__ptogovernorstate>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__ptogovernorstate,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlstates>::has_minimum &&
        static_cast<double>(msg.cruisectrlstates) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlstates>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlstates,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlstates>::has_maximum &&
        static_cast<double>(msg.cruisectrlstates) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__cruisectrlstates>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__cruisectrlstates,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__engidleincrementswitch>::has_minimum &&
        static_cast<double>(msg.engidleincrementswitch) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__engidleincrementswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__engidleincrementswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__engidleincrementswitch>::has_maximum &&
        static_cast<double>(msg.engidleincrementswitch) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__engidleincrementswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__engidleincrementswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__engidledecrementswitch>::has_minimum &&
        static_cast<double>(msg.engidledecrementswitch) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__engidledecrementswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__engidledecrementswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__engidledecrementswitch>::has_maximum &&
        static_cast<double>(msg.engidledecrementswitch) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__engidledecrementswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__engidledecrementswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__engtestmodeswitch>::has_minimum &&
        static_cast<double>(msg.engtestmodeswitch) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__engtestmodeswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__engtestmodeswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__engtestmodeswitch>::has_maximum &&
        static_cast<double>(msg.engtestmodeswitch) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__engtestmodeswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__engtestmodeswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__engshutdownoverrideswitch>::has_minimum &&
        static_cast<double>(msg.engshutdownoverrideswitch) < signal_traits<SignalId::ccvs1_cruise_control_vehspd__engshutdownoverrideswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__engshutdownoverrideswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ccvs1_cruise_control_vehspd__engshutdownoverrideswitch>::has_maximum &&
        static_cast<double>(msg.engshutdownoverrideswitch) > signal_traits<SignalId::ccvs1_cruise_control_vehspd__engshutdownoverrideswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ccvs1_cruise_control_vehspd__engshutdownoverrideswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__asrengctrlactive>::has_minimum &&
        static_cast<double>(msg.asrengctrlactive) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__asrengctrlactive>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__asrengctrlactive,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__asrengctrlactive>::has_maximum &&
        static_cast<double>(msg.asrengctrlactive) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__asrengctrlactive>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__asrengctrlactive,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.asrengctrlactive),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__asrengctrlactive,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__asrbrakectrlactive>::has_minimum &&
        static_cast<double>(msg.asrbrakectrlactive) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__asrbrakectrlactive>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__asrbrakectrlactive,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__asrbrakectrlactive>::has_maximum &&
        static_cast<double>(msg.asrbrakectrlactive) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__asrbrakectrlactive>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__asrbrakectrlactive,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__antilockbrakingactive>::has_minimum &&
        static_cast<double>(msg.antilockbrakingactive) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__antilockbrakingactive>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__antilockbrakingactive,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__antilockbrakingactive>::has_maximum &&
        static_cast<double>(msg.antilockbrakingactive) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__antilockbrakingactive>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__antilockbrakingactive,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__ebsbrakeswitch>::has_minimum &&
        static_cast<double>(msg.ebsbrakeswitch) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__ebsbrakeswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__ebsbrakeswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__ebsbrakeswitch>::has_maximum &&
        static_cast<double>(msg.ebsbrakeswitch) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__ebsbrakeswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__ebsbrakeswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.brakepedalpos,
            signal_traits<SignalId::ebc1_electronic_brake_cntrl__brakepedalpos>::has_minimum,
            signal_traits<SignalId::ebc1_electronic_brake_cntrl__brakepedalpos>::minimum,
            signal_traits<SignalId::ebc1_electronic_brake_cntrl__brakepedalpos>::has_maximum,
            signal_traits<SignalId::ebc1_electronic_brake_cntrl__brakepedalpos>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__brakepedalpos,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__absoffroadswitch>::has_minimum &&
        static_cast<double>(msg.absoffroadswitch) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__absoffroadswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__absoffroadswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__absoffroadswitch>::has_maximum &&
        static_cast<double>(msg.absoffroadswitch) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__absoffroadswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__absoffroadswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__asroffroadswitch>::has_minimum &&
        static_cast<double>(msg.asroffroadswitch) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__asroffroadswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__asroffroadswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__asroffroadswitch>::has_maximum &&
        static_cast<double>(msg.asroffroadswitch) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__asroffroadswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__asroffroadswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__asrhillholderswitch>::has_minimum &&
        static_cast<double>(msg.asrhillholderswitch) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__asrhillholderswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__asrhillholderswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__asrhillholderswitch>::has_maximum &&
        static_cast<double>(msg.asrhillholderswitch) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__asrhillholderswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__asrhillholderswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__tractionctrloverrideswitch>::has_minimum &&
        static_cast<double>(msg.tractionctrloverrideswitch) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__tractionctrloverrideswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__tractionctrloverrideswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__tractionctrloverrideswitch>::has_maximum &&
        static_cast<double>(msg.tractionctrloverrideswitch) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__tractionctrloverrideswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__tractionctrloverrideswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__accelinterlockswitch>::has_minimum &&
        static_cast<double>(msg.accelinterlockswitch) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__accelinterlockswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__accelinterlockswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__accelinterlockswitch>::has_maximum &&
        static_cast<double>(msg.accelinterlockswitch) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__accelinterlockswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__accelinterlockswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__engderateswitch>::has_minimum &&
        static_cast<double>(msg.engderateswitch) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__engderateswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__engderateswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__engderateswitch>::has_maximum &&
        static_cast<double>(msg.engderateswitch) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__engderateswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__engderateswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__engauxshutdownswitch>::has_minimum &&
        static_cast<double>(msg.engauxshutdownswitch) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__engauxshutdownswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__engauxshutdownswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__engauxshutdownswitch>::has_maximum &&
        static_cast<double>(msg.engauxshutdownswitch) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__engauxshutdownswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__engauxshutdownswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__remoteaccelenableswitch>::has_minimum &&
        static_cast<double>(msg.remoteaccelenableswitch) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__remoteaccelenableswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__remoteaccelenableswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__remoteaccelenableswitch>::has_maximum &&
        static_cast<double>(msg.remoteaccelenableswitch) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__remoteaccelenableswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__remoteaccelenableswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (!detail::within_dbc_range(
            msg.engretarderselection,
            signal_traits<SignalId::ebc1_electronic_brake_cntrl__engretarderselection>::has_minimum,
            signal_traits<SignalId::ebc1_electronic_brake_cntrl__engretarderselection>::minimum,
            signal_traits<SignalId::ebc1_electronic_brake_cntrl__engretarderselection>::has_maximum,
            signal_traits<SignalId::ebc1_electronic_brake_cntrl__engretarderselection>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__engretarderselection,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__absfullyoperational>::has_minimum &&
        static_cast<double>(msg.absfullyoperational) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__absfullyoperational>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__absfullyoperational,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__absfullyoperational>::has_maximum &&
        static_cast<double>(msg.absfullyoperational) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__absfullyoperational>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__absfullyoperational,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__ebsredwarningsignal>::has_minimum &&
        static_cast<double>(msg.ebsredwarningsignal) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__ebsredwarningsignal>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__ebsredwarningsignal,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__ebsredwarningsignal>::has_maximum &&
        static_cast<double>(msg.ebsredwarningsignal) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__ebsredwarningsignal>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__ebsredwarningsignal,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal>::has_minimum &&
        static_cast<double>(msg.abs_ebsamberwarningsignal) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal>::has_maximum &&
        static_cast<double>(msg.abs_ebsamberwarningsignal) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__atc_asrinformationsignal>::has_minimum &&
        static_cast<double>(msg.atc_asrinformationsignal) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__atc_asrinformationsignal>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__atc_asrinformationsignal,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__atc_asrinformationsignal>::has_maximum &&
        static_cast<double>(msg.atc_asrinformationsignal) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__atc_asrinformationsignal>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__atc_asrinformationsignal,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__srcaddrssofcntrllngdvcfrbrkectrl>::has_minimum &&
        static_cast<double>(msg.srcaddrssofcntrllngdvcfrbrkectrl) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__srcaddrssofcntrllngdvcfrbrkectrl>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__srcaddrssofcntrllngdvcfrbrkectrl,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__srcaddrssofcntrllngdvcfrbrkectrl>::has_maximum &&
        static_cast<double>(msg.srcaddrssofcntrllngdvcfrbrkectrl) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__srcaddrssofcntrllngdvcfrbrkectrl>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__srcaddrssofcntrllngdvcfrbrkectrl,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.srcaddrssofcntrllngdvcfrbrkectrl),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__srcaddrssofcntrllngdvcfrbrkectrl,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__railroadmodesw>::has_minimum &&
        static_cast<double>(msg.railroadmodesw) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__railroadmodesw>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__railroadmodesw,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__railroadmodesw>::has_maximum &&
        static_cast<double>(msg.railroadmodesw) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__railroadmodesw>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__railroadmodesw,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__haltbrakeswitch>::has_minimum &&
        static_cast<double>(msg.haltbrakeswitch) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__haltbrakeswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__haltbrakeswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__haltbrakeswitch>::has_maximum &&
        static_cast<double>(msg.haltbrakeswitch) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__haltbrakeswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__haltbrakeswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__trailerabsstatus>::has_minimum &&
        static_cast<double>(msg.trailerabsstatus) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__trailerabsstatus>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__trailerabsstatus,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__trailerabsstatus>::has_maximum &&
        static_cast<double>(msg.trailerabsstatus) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__trailerabsstatus>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__trailerabsstatus,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal>::has_minimum &&
        static_cast<double>(msg.trctrmntdtrailerabswarningsignal) < signal_traits<SignalId::ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal>::has_maximum &&
        static_cast<double>(msg.trctrmntdtrailerabswarningsignal) > signal_traits<SignalId::ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__engidleshutdownhasshutdowneng>::has_minimum &&
        static_cast<double>(msg.engidleshutdownhasshutdowneng) < signal_traits<SignalId::shutdn__engidleshutdownhasshutdowneng>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engidleshutdownhasshutdowneng,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engidleshutdownhasshutdowneng>::has_maximum &&
        static_cast<double>(msg.engidleshutdownhasshutdowneng) > signal_traits<SignalId::shutdn__engidleshutdownhasshutdowneng>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engidleshutdownhasshutdowneng,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.engidleshutdownhasshutdowneng),
            2U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engidleshutdownhasshutdowneng,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::shutdn__engidleshutdowndriveralertmode>::has_minimum &&
        static_cast<double>(msg.engidleshutdowndriveralertmode) < signal_traits<SignalId::shutdn__engidleshutdowndriveralertmode>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engidleshutdowndriveralertmode,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engidleshutdowndriveralertmode>::has_maximum &&
        static_cast<double>(msg.engidleshutdowndriveralertmode) > signal_traits<SignalId::shutdn__engidleshutdowndriveralertmode>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engidleshutdowndriveralertmode,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__engidleshutdowntimeroverride>::has_minimum &&
        static_cast<double>(msg.engidleshutdowntimeroverride) < signal_traits<SignalId::shutdn__engidleshutdowntimeroverride>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engidleshutdowntimeroverride,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engidleshutdowntimeroverride>::has_maximum &&
        static_cast<double>(msg.engidleshutdowntimeroverride) > signal_traits<SignalId::shutdn__engidleshutdowntimeroverride>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engidleshutdowntimeroverride,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__engidleshutdowntimerstate>::has_minimum &&
        static_cast<double>(msg.engidleshutdowntimerstate) < signal_traits<SignalId::shutdn__engidleshutdowntimerstate>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engidleshutdowntimerstate,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engidleshutdowntimerstate>::has_maximum &&
        static_cast<double>(msg.engidleshutdowntimerstate) > signal_traits<SignalId::shutdn__engidleshutdowntimerstate>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engidleshutdowntimerstate,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__engidleshutdowntimerfunction>::has_minimum &&
        static_cast<double>(msg.engidleshutdowntimerfunction) < signal_traits<SignalId::shutdn__engidleshutdowntimerfunction>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engidleshutdowntimerfunction,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engidleshutdowntimerfunction>::has_maximum &&
        static_cast<double>(msg.engidleshutdowntimerfunction) > signal_traits<SignalId::shutdn__engidleshutdowntimerfunction>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engidleshutdowntimerfunction,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__a_chighpressfanswitch>::has_minimum &&
        static_cast<double>(msg.a_chighpressfanswitch) < signal_traits<SignalId::shutdn__a_chighpressfanswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__a_chighpressfanswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__a_chighpressfanswitch>::has_maximum &&
        static_cast<double>(msg.a_chighpressfanswitch) > signal_traits<SignalId::shutdn__a_chighpressfanswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__a_chighpressfanswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__refrigerantlowpressswitch>::has_minimum &&
        static_cast<double>(msg.refrigerantlowpressswitch) < signal_traits<SignalId::shutdn__refrigerantlowpressswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__refrigerantlowpressswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__refrigerantlowpressswitch>::has_maximum &&
        static_cast<double>(msg.refrigerantlowpressswitch) > signal_traits<SignalId::shutdn__refrigerantlowpressswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__refrigerantlowpressswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__refrigeranthighpressswitch>::has_minimum &&
        static_cast<double>(msg.refrigeranthighpressswitch) < signal_traits<SignalId::shutdn__refrigeranthighpressswitch>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__refrigeranthighpressswitch,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__refrigeranthighpressswitch>::has_maximum &&
        static_cast<double>(msg.refrigeranthighpressswitch) > signal_traits<SignalId::shutdn__refrigeranthighpressswitch>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__refrigeranthighpressswitch,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__engwaittostartlamp>::has_minimum &&
        static_cast<double>(msg.engwaittostartlamp) < signal_traits<SignalId::shutdn__engwaittostartlamp>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engwaittostartlamp,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engwaittostartlamp>::has_maximum &&
        static_cast<double>(msg.engwaittostartlamp) > signal_traits<SignalId::shutdn__engwaittostartlamp>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engwaittostartlamp,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__engprtectionsystemhasshutdowneng>::has_minimum &&
        static_cast<double>(msg.engprtectionsystemhasshutdowneng) < signal_traits<SignalId::shutdn__engprtectionsystemhasshutdowneng>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engprtectionsystemhasshutdowneng,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engprtectionsystemhasshutdowneng>::has_maximum &&
        static_cast<double>(msg.engprtectionsystemhasshutdowneng) > signal_traits<SignalId::shutdn__engprtectionsystemhasshutdowneng>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engprtectionsystemhasshutdowneng,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__engprtctnsystmapprachingshutdown>::has_minimum &&
        static_cast<double>(msg.engprtctnsystmapprachingshutdown) < signal_traits<SignalId::shutdn__engprtctnsystmapprachingshutdown>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engprtctnsystmapprachingshutdown,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engprtctnsystmapprachingshutdown>::has_maximum &&
        static_cast<double>(msg.engprtctnsystmapprachingshutdown) > signal_traits<SignalId::shutdn__engprtctnsystmapprachingshutdown>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engprtctnsystmapprachingshutdown,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__engprotectionsystemtimeroverride>::has_minimum &&
        static_cast<double>(msg.engprotectionsystemtimeroverride) < signal_traits<SignalId::shutdn__engprotectionsystemtimeroverride>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engprotectionsystemtimeroverride,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engprotectionsystemtimeroverride>::has_maximum &&
        static_cast<double>(msg.engprotectionsystemtimeroverride) > signal_traits<SignalId::shutdn__engprotectionsystemtimeroverride>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engprotectionsystemtimeroverride,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__engprotectionsystemtimerstate>::has_minimum &&
        static_cast<double>(msg.engprotectionsystemtimerstate) < signal_traits<SignalId::shutdn__engprotectionsystemtimerstate>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engprotectionsystemtimerstate,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engprotectionsystemtimerstate>::has_maximum &&
        static_cast<double>(msg.engprotectionsystemtimerstate) > signal_traits<SignalId::shutdn__engprotectionsystemtimerstate>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engprotectionsystemtimerstate,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__engprotectionsystemconfig>::has_minimum &&
        static_cast<double>(msg.engprotectionsystemconfig) < signal_traits<SignalId::shutdn__engprotectionsystemconfig>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engprotectionsystemconfig,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engprotectionsystemconfig>::has_maximum &&
        static_cast<double>(msg.engprotectionsystemconfig) > signal_traits<SignalId::shutdn__engprotectionsystemconfig>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engprotectionsystemconfig,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__engalarmacknowledge>::has_minimum &&
        static_cast<double>(msg.engalarmacknowledge) < signal_traits<SignalId::shutdn__engalarmacknowledge>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engalarmacknowledge,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engalarmacknowledge>::has_maximum &&
        static_cast<double>(msg.engalarmacknowledge) > signal_traits<SignalId::shutdn__engalarmacknowledge>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engalarmacknowledge,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__engalarmoutputcmdstatus>::has_minimum &&
        static_cast<double>(msg.engalarmoutputcmdstatus) < signal_traits<SignalId::shutdn__engalarmoutputcmdstatus>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engalarmoutputcmdstatus,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engalarmoutputcmdstatus>::has_maximum &&
        static_cast<double>(msg.engalarmoutputcmdstatus) > signal_traits<SignalId::shutdn__engalarmoutputcmdstatus>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engalarmoutputcmdstatus,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__engairshutoffcmdstatus>::has_minimum &&
        static_cast<double>(msg.engairshutoffcmdstatus) < signal_traits<SignalId::shutdn__engairshutoffcmdstatus>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engairshutoffcmdstatus,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engairshutoffcmdstatus>::has_maximum &&
        static_cast<double>(msg.engairshutoffcmdstatus) > signal_traits<SignalId::shutdn__engairshutoffcmdstatus>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engairshutoffcmdstatus,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__engoverspeedtest>::has_minimum &&
        static_cast<double>(msg.engoverspeedtest) < signal_traits<SignalId::shutdn__engoverspeedtest>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engoverspeedtest,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engoverspeedtest>::has_maximum &&
        static_cast<double>(msg.engoverspeedtest) > signal_traits<SignalId::shutdn__engoverspeedtest>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engoverspeedtest,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__engairshutoffstatus>::has_minimum &&
        static_cast<double>(msg.engairshutoffstatus) < signal_traits<SignalId::shutdn__engairshutoffstatus>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engairshutoffstatus,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engairshutoffstatus>::has_maximum &&
        static_cast<double>(msg.engairshutoffstatus) > signal_traits<SignalId::shutdn__engairshutoffstatus>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engairshutoffstatus,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__ptoshutdownhasshutdowneng>::has_minimum &&
        static_cast<double>(msg.ptoshutdownhasshutdowneng) < signal_traits<SignalId::shutdn__ptoshutdownhasshutdowneng>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__ptoshutdownhasshutdowneng,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__ptoshutdownhasshutdowneng>::has_maximum &&
        static_cast<double>(msg.ptoshutdownhasshutdowneng) > signal_traits<SignalId::shutdn__ptoshutdownhasshutdowneng>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__ptoshutdownhasshutdowneng,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__clntlvlengprtctionshutdownstatus>::has_minimum &&
        static_cast<double>(msg.clntlvlengprtctionshutdownstatus) < signal_traits<SignalId::shutdn__clntlvlengprtctionshutdownstatus>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__clntlvlengprtctionshutdownstatus,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__clntlvlengprtctionshutdownstatus>::has_maximum &&
        static_cast<double>(msg.clntlvlengprtctionshutdownstatus) > signal_traits<SignalId::shutdn__clntlvlengprtctionshutdownstatus>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__clntlvlengprtctionshutdownstatus,
            .error = ValidationError::value_outside_dbc_range
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
    if (signal_traits<SignalId::shutdn__engoilpresssw>::has_minimum &&
        static_cast<double>(msg.engoilpresssw) < signal_traits<SignalId::shutdn__engoilpresssw>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engoilpresssw,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::shutdn__engoilpresssw>::has_maximum &&
        static_cast<double>(msg.engoilpresssw) > signal_traits<SignalId::shutdn__engoilpresssw>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::shutdn__engoilpresssw,
            .error = ValidationError::value_outside_dbc_range
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