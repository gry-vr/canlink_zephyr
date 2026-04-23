#include "reacher/reacher_validate.hpp"
#include "reacher/reacher_metadata.hpp"

#include <cmath>
#include <cstdint>
#include <expected>
#include <limits>
#include <type_traits>
#include <variant>

namespace reacher {
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
auto validate_message<ReacherCtrl>(const ReacherCtrl& msg)
    -> std::expected<void, ValidationIssue>
{
    if (signal_traits<SignalId::reacher_ctrl__eng_on>::has_minimum &&
        static_cast<double>(msg.eng_on) < signal_traits<SignalId::reacher_ctrl__eng_on>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__eng_on,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::reacher_ctrl__eng_on>::has_maximum &&
        static_cast<double>(msg.eng_on) > signal_traits<SignalId::reacher_ctrl__eng_on>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__eng_on,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.eng_on),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__eng_on,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::reacher_ctrl__start>::has_minimum &&
        static_cast<double>(msg.start) < signal_traits<SignalId::reacher_ctrl__start>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__start,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::reacher_ctrl__start>::has_maximum &&
        static_cast<double>(msg.start) > signal_traits<SignalId::reacher_ctrl__start>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__start,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.start),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__start,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::reacher_ctrl__arm>::has_minimum &&
        static_cast<double>(msg.arm) < signal_traits<SignalId::reacher_ctrl__arm>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__arm,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::reacher_ctrl__arm>::has_maximum &&
        static_cast<double>(msg.arm) > signal_traits<SignalId::reacher_ctrl__arm>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__arm,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.arm),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__arm,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::reacher_ctrl__test>::has_minimum &&
        static_cast<double>(msg.test) < signal_traits<SignalId::reacher_ctrl__test>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__test,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::reacher_ctrl__test>::has_maximum &&
        static_cast<double>(msg.test) > signal_traits<SignalId::reacher_ctrl__test>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__test,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.test),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__test,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::reacher_ctrl__aux_1>::has_minimum &&
        static_cast<double>(msg.aux_1) < signal_traits<SignalId::reacher_ctrl__aux_1>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__aux_1,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::reacher_ctrl__aux_1>::has_maximum &&
        static_cast<double>(msg.aux_1) > signal_traits<SignalId::reacher_ctrl__aux_1>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__aux_1,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.aux_1),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__aux_1,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.throttle_rpm,
            signal_traits<SignalId::reacher_ctrl__throttle_rpm>::has_minimum,
            signal_traits<SignalId::reacher_ctrl__throttle_rpm>::minimum,
            signal_traits<SignalId::reacher_ctrl__throttle_rpm>::has_maximum,
            signal_traits<SignalId::reacher_ctrl__throttle_rpm>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__throttle_rpm,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.throttle_rpm,
            0.125,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__throttle_rpm,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::reacher_ctrl__aux_2>::has_minimum &&
        static_cast<double>(msg.aux_2) < signal_traits<SignalId::reacher_ctrl__aux_2>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__aux_2,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::reacher_ctrl__aux_2>::has_maximum &&
        static_cast<double>(msg.aux_2) > signal_traits<SignalId::reacher_ctrl__aux_2>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__aux_2,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.aux_2),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__aux_2,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<ReacherEngineFeedback>(const ReacherEngineFeedback& msg)
    -> std::expected<void, ValidationIssue>
{
    if (signal_traits<SignalId::reacher_engine_feedback__ecu_on>::has_minimum &&
        static_cast<double>(msg.ecu_on) < signal_traits<SignalId::reacher_engine_feedback__ecu_on>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_engine_feedback__ecu_on,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::reacher_engine_feedback__ecu_on>::has_maximum &&
        static_cast<double>(msg.ecu_on) > signal_traits<SignalId::reacher_engine_feedback__ecu_on>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_engine_feedback__ecu_on,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.ecu_on),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_engine_feedback__ecu_on,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::reacher_engine_feedback__f_pump_on>::has_minimum &&
        static_cast<double>(msg.f_pump_on) < signal_traits<SignalId::reacher_engine_feedback__f_pump_on>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_engine_feedback__f_pump_on,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::reacher_engine_feedback__f_pump_on>::has_maximum &&
        static_cast<double>(msg.f_pump_on) > signal_traits<SignalId::reacher_engine_feedback__f_pump_on>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_engine_feedback__f_pump_on,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.f_pump_on),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_engine_feedback__f_pump_on,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::reacher_engine_feedback__st_solenoid_on>::has_minimum &&
        static_cast<double>(msg.st_solenoid_on) < signal_traits<SignalId::reacher_engine_feedback__st_solenoid_on>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_engine_feedback__st_solenoid_on,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::reacher_engine_feedback__st_solenoid_on>::has_maximum &&
        static_cast<double>(msg.st_solenoid_on) > signal_traits<SignalId::reacher_engine_feedback__st_solenoid_on>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_engine_feedback__st_solenoid_on,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.st_solenoid_on),
            1.0,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_engine_feedback__st_solenoid_on,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Export0>(const Export0& msg)
    -> std::expected<void, ValidationIssue>
{
    if (signal_traits<SignalId::export_0__eng_speed>::has_minimum &&
        static_cast<double>(msg.eng_speed) < signal_traits<SignalId::export_0__eng_speed>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_0__eng_speed,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::export_0__eng_speed>::has_maximum &&
        static_cast<double>(msg.eng_speed) > signal_traits<SignalId::export_0__eng_speed>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_0__eng_speed,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.eng_speed),
            1.0,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_0__eng_speed,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.actual_throttle,
            signal_traits<SignalId::export_0__actual_throttle>::has_minimum,
            signal_traits<SignalId::export_0__actual_throttle>::minimum,
            signal_traits<SignalId::export_0__actual_throttle>::has_maximum,
            signal_traits<SignalId::export_0__actual_throttle>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_0__actual_throttle,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.actual_throttle,
            0.4,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_0__actual_throttle,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::export_0__manifold_press>::has_minimum &&
        static_cast<double>(msg.manifold_press) < signal_traits<SignalId::export_0__manifold_press>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_0__manifold_press,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::export_0__manifold_press>::has_maximum &&
        static_cast<double>(msg.manifold_press) > signal_traits<SignalId::export_0__manifold_press>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_0__manifold_press,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.manifold_press),
            1.0,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_0__manifold_press,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Export3>(const Export3& msg)
    -> std::expected<void, ValidationIssue>
{
    if (signal_traits<SignalId::export_3__fuel_rail_pressure>::has_minimum &&
        static_cast<double>(msg.fuel_rail_pressure) < signal_traits<SignalId::export_3__fuel_rail_pressure>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_3__fuel_rail_pressure,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::export_3__fuel_rail_pressure>::has_maximum &&
        static_cast<double>(msg.fuel_rail_pressure) > signal_traits<SignalId::export_3__fuel_rail_pressure>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_3__fuel_rail_pressure,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_signed_physical(
            static_cast<double>(msg.fuel_rail_pressure),
            1.0,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_3__fuel_rail_pressure,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<Export8>(const Export8& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::within_dbc_range(
            msg.battery_bus_voltage,
            signal_traits<SignalId::export_8__battery_bus_voltage>::has_minimum,
            signal_traits<SignalId::export_8__battery_bus_voltage>::minimum,
            signal_traits<SignalId::export_8__battery_bus_voltage>::has_maximum,
            signal_traits<SignalId::export_8__battery_bus_voltage>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_8__battery_bus_voltage,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.battery_bus_voltage,
            0.05,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_8__battery_bus_voltage,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<ExportB>(const ExportB& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::within_dbc_range(
            msg.coolant_temp,
            signal_traits<SignalId::export_b__coolant_temp>::has_minimum,
            signal_traits<SignalId::export_b__coolant_temp>::minimum,
            signal_traits<SignalId::export_b__coolant_temp>::has_maximum,
            signal_traits<SignalId::export_b__coolant_temp>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_b__coolant_temp,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.coolant_temp,
            1.8,
            -40.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_b__coolant_temp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (signal_traits<SignalId::export_b__oil_temp>::has_minimum &&
        static_cast<double>(msg.oil_temp) < signal_traits<SignalId::export_b__oil_temp>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_b__oil_temp,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::export_b__oil_temp>::has_maximum &&
        static_cast<double>(msg.oil_temp) > signal_traits<SignalId::export_b__oil_temp>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_b__oil_temp,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.oil_temp),
            1.0,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_b__oil_temp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.oil_pressure,
            signal_traits<SignalId::export_b__oil_pressure>::has_minimum,
            signal_traits<SignalId::export_b__oil_pressure>::minimum,
            signal_traits<SignalId::export_b__oil_pressure>::has_maximum,
            signal_traits<SignalId::export_b__oil_pressure>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_b__oil_pressure,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.oil_pressure,
            0.580152,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_b__oil_pressure,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::within_dbc_range(
            msg.exhaust_gas_temp,
            signal_traits<SignalId::export_b__exhaust_gas_temp>::has_minimum,
            signal_traits<SignalId::export_b__exhaust_gas_temp>::minimum,
            signal_traits<SignalId::export_b__exhaust_gas_temp>::has_maximum,
            signal_traits<SignalId::export_b__exhaust_gas_temp>::maximum))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_b__exhaust_gas_temp,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.exhaust_gas_temp,
            0.05625,
            -459.4,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_b__exhaust_gas_temp,
            .error = ValidationError::value_out_of_range
        });
    }

    return {};
}
template <>
auto validate_message<ServoBatt>(const ServoBatt& msg)
    -> std::expected<void, ValidationIssue>
{
    if (signal_traits<SignalId::servo_batt__servo_bus_voltage>::has_minimum &&
        static_cast<double>(msg.servo_bus_voltage) < signal_traits<SignalId::servo_batt__servo_bus_voltage>::minimum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::servo_batt__servo_bus_voltage,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (signal_traits<SignalId::servo_batt__servo_bus_voltage>::has_maximum &&
        static_cast<double>(msg.servo_bus_voltage) > signal_traits<SignalId::servo_batt__servo_bus_voltage>::maximum) {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::servo_batt__servo_bus_voltage,
            .error = ValidationError::value_outside_dbc_range
        });
    }
    if (!detail::validate_unsigned_physical(
            static_cast<double>(msg.servo_bus_voltage),
            100.0,
            0.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::servo_batt__servo_bus_voltage,
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

} // namespace reacher