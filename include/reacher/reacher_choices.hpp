#pragma once

#include "reacher_concepts.hpp"
#include "reacher_store.hpp"

#include <array>
#include <cstdint>
#include <expected>
#include <optional>
#include <string_view>

namespace reacher {

enum class ChoiceError : std::uint8_t {
    unknown_raw_value
};

struct ChoiceMeta {
    std::int64_t raw_value;
    std::string_view dbc_name;
    std::string_view cpp_name;
};

enum class ReacherCtrlEngOnState : std::uint8_t {
    off = 0,
    on = 255
};

inline constexpr std::array<ChoiceMeta, 2> kReacherCtrlEngOnStateChoices{ {
    ChoiceMeta{ 0, "off", "off" },
    ChoiceMeta{ 255, "on", "on" }
} };

constexpr auto to_reacher_ctrl__eng_on(std::uint8_t raw)
    -> std::expected<ReacherCtrlEngOnState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ReacherCtrlEngOnState::off;
        case static_cast<std::uint8_t>(255):
            return ReacherCtrlEngOnState::on;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ReacherCtrlEngOnState value) -> std::string_view {
    switch (value) {
        case ReacherCtrlEngOnState::off:
            return "off";
        case ReacherCtrlEngOnState::on:
            return "on";
    }
    return "<unknown>";
}

constexpr auto to_raw(ReacherCtrlEngOnState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_reacher_ctrl__eng_on(const ValueStore& store) -> std::optional<ReacherCtrlEngOnState> {
    auto raw = store.template get<SignalId::reacher_ctrl__eng_on>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_reacher_ctrl__eng_on(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ReacherCtrlStartState : std::uint8_t {
    off = 0,
    on = 255
};

inline constexpr std::array<ChoiceMeta, 2> kReacherCtrlStartStateChoices{ {
    ChoiceMeta{ 0, "off", "off" },
    ChoiceMeta{ 255, "on", "on" }
} };

constexpr auto to_reacher_ctrl__start(std::uint8_t raw)
    -> std::expected<ReacherCtrlStartState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ReacherCtrlStartState::off;
        case static_cast<std::uint8_t>(255):
            return ReacherCtrlStartState::on;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ReacherCtrlStartState value) -> std::string_view {
    switch (value) {
        case ReacherCtrlStartState::off:
            return "off";
        case ReacherCtrlStartState::on:
            return "on";
    }
    return "<unknown>";
}

constexpr auto to_raw(ReacherCtrlStartState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_reacher_ctrl__start(const ValueStore& store) -> std::optional<ReacherCtrlStartState> {
    auto raw = store.template get<SignalId::reacher_ctrl__start>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_reacher_ctrl__start(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ReacherCtrlArmState : std::uint8_t {
    off = 0,
    on = 255
};

inline constexpr std::array<ChoiceMeta, 2> kReacherCtrlArmStateChoices{ {
    ChoiceMeta{ 0, "off", "off" },
    ChoiceMeta{ 255, "on", "on" }
} };

constexpr auto to_reacher_ctrl__arm(std::uint8_t raw)
    -> std::expected<ReacherCtrlArmState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ReacherCtrlArmState::off;
        case static_cast<std::uint8_t>(255):
            return ReacherCtrlArmState::on;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ReacherCtrlArmState value) -> std::string_view {
    switch (value) {
        case ReacherCtrlArmState::off:
            return "off";
        case ReacherCtrlArmState::on:
            return "on";
    }
    return "<unknown>";
}

constexpr auto to_raw(ReacherCtrlArmState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_reacher_ctrl__arm(const ValueStore& store) -> std::optional<ReacherCtrlArmState> {
    auto raw = store.template get<SignalId::reacher_ctrl__arm>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_reacher_ctrl__arm(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ReacherCtrlTestState : std::uint8_t {
    off = 0,
    on = 255
};

inline constexpr std::array<ChoiceMeta, 2> kReacherCtrlTestStateChoices{ {
    ChoiceMeta{ 0, "off", "off" },
    ChoiceMeta{ 255, "on", "on" }
} };

constexpr auto to_reacher_ctrl__test(std::uint8_t raw)
    -> std::expected<ReacherCtrlTestState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ReacherCtrlTestState::off;
        case static_cast<std::uint8_t>(255):
            return ReacherCtrlTestState::on;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ReacherCtrlTestState value) -> std::string_view {
    switch (value) {
        case ReacherCtrlTestState::off:
            return "off";
        case ReacherCtrlTestState::on:
            return "on";
    }
    return "<unknown>";
}

constexpr auto to_raw(ReacherCtrlTestState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_reacher_ctrl__test(const ValueStore& store) -> std::optional<ReacherCtrlTestState> {
    auto raw = store.template get<SignalId::reacher_ctrl__test>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_reacher_ctrl__test(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

} // namespace reacher