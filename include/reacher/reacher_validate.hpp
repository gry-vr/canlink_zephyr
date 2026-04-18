#pragma once

#include "reacher_ids.hpp"
#include "reacher_types.hpp"
#include "reacher_concepts.hpp"

#include <cstdint>
#include <expected>
#include <string_view>

namespace reacher {

enum class ValidationError : std::uint8_t {
    value_out_of_range,
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
        case ValidationError::unsupported_message:
            return "unsupported_message";
    }
    return "<unknown>";
}

template <GeneratedMessage Msg>
auto validate_message(const Msg& msg) -> std::expected<void, ValidationIssue>;

auto validate_message(const MessageVariant& msg)
    -> std::expected<void, ValidationIssue>;

} // namespace reacher