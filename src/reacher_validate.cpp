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
auto validate_message<ReacherCtrl>(const ReacherCtrl& msg)
    -> std::expected<void, ValidationIssue>
{
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.eng_on),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__eng_on,
            .error = ValidationError::value_out_of_range
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
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.arm),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__arm,
            .error = ValidationError::value_out_of_range
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
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.aux_1),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__aux_1,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.throttle_rpm),
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_ctrl__throttle_rpm,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.aux_2),
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
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.ecu_on),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_engine_feedback__ecu_on,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.f_pump_on),
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::reacher_engine_feedback__f_pump_on,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.st_solenoid_on),
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
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.eng_speed),
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_0__eng_speed,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.actual_throttle,
            0.00392156862745,
            0.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_0__actual_throttle,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.manifold_press),
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
    if (!detail::fits_signed(
            static_cast<std::int64_t>(msg.fuel_rail_pressure),
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
    if (!detail::validate_unsigned_physical(
            msg.battery_bus_voltage,
            0.0175953079179,
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
    if (!detail::validate_unsigned_physical(
            msg.coolant_temp,
            1.12941176471,
            14.0,
            8U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_b__coolant_temp,
            .error = ValidationError::value_out_of_range
        });
    }
    if (!detail::validate_unsigned_physical(
            msg.oil_temp,
            1.8,
            32.0,
            16U))
    {
        return std::unexpected(ValidationIssue{
            .signal_id = SignalId::export_b__oil_temp,
            .error = ValidationError::value_out_of_range
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
    if (!detail::validate_unsigned_physical(
            msg.exhaust_gas_temp,
            1.8,
            32.0,
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
    if (!detail::fits_unsigned(
            static_cast<std::uint64_t>(msg.servo_bus_voltage),
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