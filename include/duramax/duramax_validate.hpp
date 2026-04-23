#pragma once

#include "duramax_ids.hpp"
#include "duramax_types.hpp"
#include "duramax_concepts.hpp"
#include "duramax_metadata.hpp"

#include <cmath>
#include <cstdint>
#include <expected>
#include <limits>
#include <string_view>
#include <type_traits>

namespace duramax {

enum class ValidationError : std::uint8_t {
    value_out_of_range,
    value_outside_dbc_range,
    unsupported_message,
};

struct ValidationIssue {
    SignalId signal_id;
    ValidationError error;
};

constexpr auto validation_error_name(ValidationError e) -> std::string_view {
    switch (e) {
        case ValidationError::value_out_of_range:
            return "value_out_of_range";
        case ValidationError::value_outside_dbc_range:
            return "value_outside_dbc_range";
        case ValidationError::unsupported_message:
            return "unsupported_message";
    }
    return "<unknown>";
}


namespace detail {

constexpr auto validate_mask64(unsigned width) -> std::uint64_t {
    return (width >= 64U) ? ~0ULL : ((1ULL << width) - 1ULL);
}

constexpr auto validate_fits_unsigned(std::uint64_t value, unsigned bit_length) -> bool {
    if (bit_length >= 64U) {
        return true;
    }
    return value <= validate_mask64(bit_length);
}

constexpr auto validate_fits_signed(std::int64_t value, unsigned bit_length) -> bool {
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

    return validate_fits_unsigned(static_cast<std::uint64_t>(rounded), bit_length);
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

    return validate_fits_signed(static_cast<std::int64_t>(rounded), bit_length);
}

} // namespace detail

template <SignalId Id>
auto validate_signal_encodable(signal_value_t<Id> value) -> std::expected<void, ValidationIssue> {
    using Traits = signal_traits<Id>;
    using Value = signal_value_t<Id>;

    if constexpr (std::same_as<Value, bool>) {
        (void)value;
        return {};
    } else if constexpr (std::same_as<Value, double>) {
        const bool ok = Traits::is_signed
            ? detail::validate_signed_physical(value, Traits::scale, Traits::offset, signal_meta(Id).bit_length)
            : detail::validate_unsigned_physical(value, Traits::scale, Traits::offset, signal_meta(Id).bit_length);

        if (!ok) {
            return std::unexpected(ValidationIssue{
                .signal_id = Id,
                .error = ValidationError::value_out_of_range
            });
        }
        return {};
    } else if constexpr (std::signed_integral<Value>) {
        if (!detail::validate_fits_signed(static_cast<std::int64_t>(value), signal_meta(Id).bit_length)) {
            return std::unexpected(ValidationIssue{
                .signal_id = Id,
                .error = ValidationError::value_out_of_range
            });
        }
        return {};
    } else {
        if (!detail::validate_fits_unsigned(static_cast<std::uint64_t>(value), signal_meta(Id).bit_length)) {
            return std::unexpected(ValidationIssue{
                .signal_id = Id,
                .error = ValidationError::value_out_of_range
            });
        }
        return {};
    }
}

template <SignalId Id>
auto validate_signal_within_dbc_range(signal_value_t<Id> value) -> std::expected<void, ValidationIssue> {
    using Traits = signal_traits<Id>;

    if constexpr (std::same_as<signal_value_t<Id>, bool>) {
        const double dv = value ? 1.0 : 0.0;
        if (Traits::has_minimum && dv < Traits::minimum) {
            return std::unexpected(ValidationIssue{.signal_id = Id, .error = ValidationError::value_outside_dbc_range});
        }
        if (Traits::has_maximum && dv > Traits::maximum) {
            return std::unexpected(ValidationIssue{.signal_id = Id, .error = ValidationError::value_outside_dbc_range});
        }
        return {};
    } else {
        const double dv = static_cast<double>(value);
        if (Traits::has_minimum && dv < Traits::minimum) {
            return std::unexpected(ValidationIssue{.signal_id = Id, .error = ValidationError::value_outside_dbc_range});
        }
        if (Traits::has_maximum && dv > Traits::maximum) {
            return std::unexpected(ValidationIssue{.signal_id = Id, .error = ValidationError::value_outside_dbc_range});
        }
        return {};
    }
}

template <SignalId Id>
auto validate_signal_value(signal_value_t<Id> value) -> std::expected<void, ValidationIssue> {
    if (auto r = validate_signal_within_dbc_range<Id>(value); !r) {
        return r;
    }
    return validate_signal_encodable<Id>(value);
}

template <GeneratedMessage Msg>
auto validate_message(const Msg& msg) -> std::expected<void, ValidationIssue>;

auto validate_message(const MessageVariant& msg)
    -> std::expected<void, ValidationIssue>;

} // namespace duramax