#pragma once

#include "duramax_concepts.hpp"
#include "duramax_store.hpp"

#include <array>
#include <cstdint>
#include <expected>
#include <optional>
#include <string_view>

namespace duramax {

enum class ChoiceError : std::uint8_t {
    unknown_raw_value
};

struct ChoiceMeta {
    std::int64_t raw_value;
    std::string_view dbc_name;
    std::string_view cpp_name;
};

enum class Eec5ElectronicEngineControl5EngineFuelControlControlModeState : std::uint8_t {
    open_loop = 0,
    closed_loop = 1,
    sae_reserved = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEec5ElectronicEngineControl5EngineFuelControlControlModeStateChoices{ {
    ChoiceMeta{ 0, "Open Loop", "open_loop" },
    ChoiceMeta{ 1, "Closed Loop", "closed_loop" },
    ChoiceMeta{ 2, "SAE Reserved", "sae_reserved" },
    ChoiceMeta{ 3, "Not Available", "not_available" }
} };

constexpr auto to_eec5_electronic_engine_control_5__engine_fuel_control_control_mode(std::uint8_t raw)
    -> std::expected<Eec5ElectronicEngineControl5EngineFuelControlControlModeState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Eec5ElectronicEngineControl5EngineFuelControlControlModeState::open_loop;
        case static_cast<std::uint8_t>(1):
            return Eec5ElectronicEngineControl5EngineFuelControlControlModeState::closed_loop;
        case static_cast<std::uint8_t>(2):
            return Eec5ElectronicEngineControl5EngineFuelControlControlModeState::sae_reserved;
        case static_cast<std::uint8_t>(3):
            return Eec5ElectronicEngineControl5EngineFuelControlControlModeState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Eec5ElectronicEngineControl5EngineFuelControlControlModeState value) -> std::string_view {
    switch (value) {
        case Eec5ElectronicEngineControl5EngineFuelControlControlModeState::open_loop:
            return "Open Loop";
        case Eec5ElectronicEngineControl5EngineFuelControlControlModeState::closed_loop:
            return "Closed Loop";
        case Eec5ElectronicEngineControl5EngineFuelControlControlModeState::sae_reserved:
            return "SAE Reserved";
        case Eec5ElectronicEngineControl5EngineFuelControlControlModeState::not_available:
            return "Not Available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Eec5ElectronicEngineControl5EngineFuelControlControlModeState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_eec5_electronic_engine_control_5__engine_fuel_control_control_mode(const ValueStore& store) -> std::optional<Eec5ElectronicEngineControl5EngineFuelControlControlModeState> {
    auto raw = store.template get<SignalId::eec5_electronic_engine_control_5__engine_fuel_control_control_mode>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_eec5_electronic_engine_control_5__engine_fuel_control_control_mode(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Eec5ElectronicEngineControl5EngineVgtControlModeState : std::uint8_t {
    open_loop = 0,
    closed_loop = 1,
    sae_reserved = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEec5ElectronicEngineControl5EngineVgtControlModeStateChoices{ {
    ChoiceMeta{ 0, "Open Loop", "open_loop" },
    ChoiceMeta{ 1, "Closed Loop", "closed_loop" },
    ChoiceMeta{ 2, "SAE Reserved", "sae_reserved" },
    ChoiceMeta{ 3, "Not Available", "not_available" }
} };

constexpr auto to_eec5_electronic_engine_control_5__engine_vgt_control_mode(std::uint8_t raw)
    -> std::expected<Eec5ElectronicEngineControl5EngineVgtControlModeState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Eec5ElectronicEngineControl5EngineVgtControlModeState::open_loop;
        case static_cast<std::uint8_t>(1):
            return Eec5ElectronicEngineControl5EngineVgtControlModeState::closed_loop;
        case static_cast<std::uint8_t>(2):
            return Eec5ElectronicEngineControl5EngineVgtControlModeState::sae_reserved;
        case static_cast<std::uint8_t>(3):
            return Eec5ElectronicEngineControl5EngineVgtControlModeState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Eec5ElectronicEngineControl5EngineVgtControlModeState value) -> std::string_view {
    switch (value) {
        case Eec5ElectronicEngineControl5EngineVgtControlModeState::open_loop:
            return "Open Loop";
        case Eec5ElectronicEngineControl5EngineVgtControlModeState::closed_loop:
            return "Closed Loop";
        case Eec5ElectronicEngineControl5EngineVgtControlModeState::sae_reserved:
            return "SAE Reserved";
        case Eec5ElectronicEngineControl5EngineVgtControlModeState::not_available:
            return "Not Available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Eec5ElectronicEngineControl5EngineVgtControlModeState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_eec5_electronic_engine_control_5__engine_vgt_control_mode(const ValueStore& store) -> std::optional<Eec5ElectronicEngineControl5EngineVgtControlModeState> {
    auto raw = store.template get<SignalId::eec5_electronic_engine_control_5__engine_vgt_control_mode>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_eec5_electronic_engine_control_5__engine_vgt_control_mode(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Eec1ElectronicEngineControl1ActlengprcnttorquehighresolutionState : std::uint8_t {
    _0_000 = 0,
    _0_125 = 1,
    _0_875 = 7
};

inline constexpr std::array<ChoiceMeta, 3> kEec1ElectronicEngineControl1ActlengprcnttorquehighresolutionStateChoices{ {
    ChoiceMeta{ 0, "+0.000%", "_0_000" },
    ChoiceMeta{ 1, "+0.125%", "_0_125" },
    ChoiceMeta{ 7, "+0.875%", "_0_875" }
} };

constexpr auto to_eec1_electronic_engine_control_1__actlengprcnttorquehighresolution(std::uint8_t raw)
    -> std::expected<Eec1ElectronicEngineControl1ActlengprcnttorquehighresolutionState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Eec1ElectronicEngineControl1ActlengprcnttorquehighresolutionState::_0_000;
        case static_cast<std::uint8_t>(1):
            return Eec1ElectronicEngineControl1ActlengprcnttorquehighresolutionState::_0_125;
        case static_cast<std::uint8_t>(7):
            return Eec1ElectronicEngineControl1ActlengprcnttorquehighresolutionState::_0_875;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Eec1ElectronicEngineControl1ActlengprcnttorquehighresolutionState value) -> std::string_view {
    switch (value) {
        case Eec1ElectronicEngineControl1ActlengprcnttorquehighresolutionState::_0_000:
            return "+0.000%";
        case Eec1ElectronicEngineControl1ActlengprcnttorquehighresolutionState::_0_125:
            return "+0.125%";
        case Eec1ElectronicEngineControl1ActlengprcnttorquehighresolutionState::_0_875:
            return "+0.875%";
    }
    return "<unknown>";
}

constexpr auto to_raw(Eec1ElectronicEngineControl1ActlengprcnttorquehighresolutionState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_eec1_electronic_engine_control_1__actlengprcnttorquehighresolution(const ValueStore& store) -> std::optional<Eec1ElectronicEngineControl1ActlengprcnttorquehighresolutionState> {
    auto raw = store.template get<SignalId::eec1_electronic_engine_control_1__actlengprcnttorquehighresolution>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_eec1_electronic_engine_control_1__actlengprcnttorquehighresolution(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Eec1ElectronicEngineControl1EngstartermodeState : std::uint8_t {
    start_not_requested = 0,
    starter_active_but_not_engaged = 1,
    starter_active_and_engaged = 2,
    start_finished = 3,
    starter_inhibited_due_to_engine_already_running = 4,
    starter_inhibited_due_to_engine_not_ready_for_start = 5,
    starter_inhibited_due_to_driveline_engaged_or_other_transmission_inhibit = 6,
    starter_inhibited_due_to_active_immobilizer = 7,
    starter_inhibited_due_to_starter_over_temp = 8,
    starter_inhibited_due_to_intake_air_shutoff_valve_being_active = 9,
    starter_inhibited_due_to_active_emissions_control_system_condition = 10,
    starter_inhibited_due_to_ignition_key_cycle_required = 11,
    starter_inhibited = 12,
    error_legacy_implementation_only = 13,
    error = 14,
    not_available = 15
};

inline constexpr std::array<ChoiceMeta, 16> kEec1ElectronicEngineControl1EngstartermodeStateChoices{ {
    ChoiceMeta{ 0, "start not requested", "start_not_requested" },
    ChoiceMeta{ 1, "starter active but not engaged", "starter_active_but_not_engaged" },
    ChoiceMeta{ 2, "starter active and engaged", "starter_active_and_engaged" },
    ChoiceMeta{ 3, "start finished", "start_finished" },
    ChoiceMeta{ 4, "starter inhibited due to engine already running", "starter_inhibited_due_to_engine_already_running" },
    ChoiceMeta{ 5, "starter inhibited due to engine not ready for start", "starter_inhibited_due_to_engine_not_ready_for_start" },
    ChoiceMeta{ 6, "starter inhibited due to driveline engaged or other transmission inhibit", "starter_inhibited_due_to_driveline_engaged_or_other_transmission_inhibit" },
    ChoiceMeta{ 7, "starter inhibited due to active immobilizer", "starter_inhibited_due_to_active_immobilizer" },
    ChoiceMeta{ 8, "starter inhibited due to starter over-temp", "starter_inhibited_due_to_starter_over_temp" },
    ChoiceMeta{ 9, "starter inhibited due to intake air shutoff valve being active", "starter_inhibited_due_to_intake_air_shutoff_valve_being_active" },
    ChoiceMeta{ 10, "starter inhibited due to active emissions control system condition", "starter_inhibited_due_to_active_emissions_control_system_condition" },
    ChoiceMeta{ 11, "starter inhibited due to ignition key cycle required", "starter_inhibited_due_to_ignition_key_cycle_required" },
    ChoiceMeta{ 12, "starter inhibited", "starter_inhibited" },
    ChoiceMeta{ 13, "error, legacy implementation only", "error_legacy_implementation_only" },
    ChoiceMeta{ 14, "error", "error" },
    ChoiceMeta{ 15, "not available", "not_available" }
} };

constexpr auto to_eec1_electronic_engine_control_1__engstartermode(std::uint8_t raw)
    -> std::expected<Eec1ElectronicEngineControl1EngstartermodeState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Eec1ElectronicEngineControl1EngstartermodeState::start_not_requested;
        case static_cast<std::uint8_t>(1):
            return Eec1ElectronicEngineControl1EngstartermodeState::starter_active_but_not_engaged;
        case static_cast<std::uint8_t>(2):
            return Eec1ElectronicEngineControl1EngstartermodeState::starter_active_and_engaged;
        case static_cast<std::uint8_t>(3):
            return Eec1ElectronicEngineControl1EngstartermodeState::start_finished;
        case static_cast<std::uint8_t>(4):
            return Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited_due_to_engine_already_running;
        case static_cast<std::uint8_t>(5):
            return Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited_due_to_engine_not_ready_for_start;
        case static_cast<std::uint8_t>(6):
            return Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited_due_to_driveline_engaged_or_other_transmission_inhibit;
        case static_cast<std::uint8_t>(7):
            return Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited_due_to_active_immobilizer;
        case static_cast<std::uint8_t>(8):
            return Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited_due_to_starter_over_temp;
        case static_cast<std::uint8_t>(9):
            return Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited_due_to_intake_air_shutoff_valve_being_active;
        case static_cast<std::uint8_t>(10):
            return Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited_due_to_active_emissions_control_system_condition;
        case static_cast<std::uint8_t>(11):
            return Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited_due_to_ignition_key_cycle_required;
        case static_cast<std::uint8_t>(12):
            return Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited;
        case static_cast<std::uint8_t>(13):
            return Eec1ElectronicEngineControl1EngstartermodeState::error_legacy_implementation_only;
        case static_cast<std::uint8_t>(14):
            return Eec1ElectronicEngineControl1EngstartermodeState::error;
        case static_cast<std::uint8_t>(15):
            return Eec1ElectronicEngineControl1EngstartermodeState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Eec1ElectronicEngineControl1EngstartermodeState value) -> std::string_view {
    switch (value) {
        case Eec1ElectronicEngineControl1EngstartermodeState::start_not_requested:
            return "start not requested";
        case Eec1ElectronicEngineControl1EngstartermodeState::starter_active_but_not_engaged:
            return "starter active but not engaged";
        case Eec1ElectronicEngineControl1EngstartermodeState::starter_active_and_engaged:
            return "starter active and engaged";
        case Eec1ElectronicEngineControl1EngstartermodeState::start_finished:
            return "start finished";
        case Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited_due_to_engine_already_running:
            return "starter inhibited due to engine already running";
        case Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited_due_to_engine_not_ready_for_start:
            return "starter inhibited due to engine not ready for start";
        case Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited_due_to_driveline_engaged_or_other_transmission_inhibit:
            return "starter inhibited due to driveline engaged or other transmission inhibit";
        case Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited_due_to_active_immobilizer:
            return "starter inhibited due to active immobilizer";
        case Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited_due_to_starter_over_temp:
            return "starter inhibited due to starter over-temp";
        case Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited_due_to_intake_air_shutoff_valve_being_active:
            return "starter inhibited due to intake air shutoff valve being active";
        case Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited_due_to_active_emissions_control_system_condition:
            return "starter inhibited due to active emissions control system condition";
        case Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited_due_to_ignition_key_cycle_required:
            return "starter inhibited due to ignition key cycle required";
        case Eec1ElectronicEngineControl1EngstartermodeState::starter_inhibited:
            return "starter inhibited";
        case Eec1ElectronicEngineControl1EngstartermodeState::error_legacy_implementation_only:
            return "error, legacy implementation only";
        case Eec1ElectronicEngineControl1EngstartermodeState::error:
            return "error";
        case Eec1ElectronicEngineControl1EngstartermodeState::not_available:
            return "not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Eec1ElectronicEngineControl1EngstartermodeState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_eec1_electronic_engine_control_1__engstartermode(const ValueStore& store) -> std::optional<Eec1ElectronicEngineControl1EngstartermodeState> {
    auto raw = store.template get<SignalId::eec1_electronic_engine_control_1__engstartermode>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_eec1_electronic_engine_control_1__engstartermode(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Eec2ElectronicEngineControl2Accelpedal1lowidleswitchState : std::uint8_t {
    accelerator_pedal_1_not_in_low_idle_condition = 0,
    accelerator_pedal_1_in_low_idle_condition = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEec2ElectronicEngineControl2Accelpedal1lowidleswitchStateChoices{ {
    ChoiceMeta{ 0, "Accelerator pedal 1 not in low idle condition", "accelerator_pedal_1_not_in_low_idle_condition" },
    ChoiceMeta{ 1, "Accelerator pedal 1 in low idle condition", "accelerator_pedal_1_in_low_idle_condition" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_eec2_electronic_engine_control_2__accelpedal1lowidleswitch(std::uint8_t raw)
    -> std::expected<Eec2ElectronicEngineControl2Accelpedal1lowidleswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Eec2ElectronicEngineControl2Accelpedal1lowidleswitchState::accelerator_pedal_1_not_in_low_idle_condition;
        case static_cast<std::uint8_t>(1):
            return Eec2ElectronicEngineControl2Accelpedal1lowidleswitchState::accelerator_pedal_1_in_low_idle_condition;
        case static_cast<std::uint8_t>(2):
            return Eec2ElectronicEngineControl2Accelpedal1lowidleswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Eec2ElectronicEngineControl2Accelpedal1lowidleswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Eec2ElectronicEngineControl2Accelpedal1lowidleswitchState value) -> std::string_view {
    switch (value) {
        case Eec2ElectronicEngineControl2Accelpedal1lowidleswitchState::accelerator_pedal_1_not_in_low_idle_condition:
            return "Accelerator pedal 1 not in low idle condition";
        case Eec2ElectronicEngineControl2Accelpedal1lowidleswitchState::accelerator_pedal_1_in_low_idle_condition:
            return "Accelerator pedal 1 in low idle condition";
        case Eec2ElectronicEngineControl2Accelpedal1lowidleswitchState::error:
            return "Error";
        case Eec2ElectronicEngineControl2Accelpedal1lowidleswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Eec2ElectronicEngineControl2Accelpedal1lowidleswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_eec2_electronic_engine_control_2__accelpedal1lowidleswitch(const ValueStore& store) -> std::optional<Eec2ElectronicEngineControl2Accelpedal1lowidleswitchState> {
    auto raw = store.template get<SignalId::eec2_electronic_engine_control_2__accelpedal1lowidleswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_eec2_electronic_engine_control_2__accelpedal1lowidleswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Eec2ElectronicEngineControl2AccelpedalkickdownswitchState : std::uint8_t {
    kickdown_passive = 0,
    kickdown_active = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEec2ElectronicEngineControl2AccelpedalkickdownswitchStateChoices{ {
    ChoiceMeta{ 0, "Kickdown passive", "kickdown_passive" },
    ChoiceMeta{ 1, "Kickdown active", "kickdown_active" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_eec2_electronic_engine_control_2__accelpedalkickdownswitch(std::uint8_t raw)
    -> std::expected<Eec2ElectronicEngineControl2AccelpedalkickdownswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Eec2ElectronicEngineControl2AccelpedalkickdownswitchState::kickdown_passive;
        case static_cast<std::uint8_t>(1):
            return Eec2ElectronicEngineControl2AccelpedalkickdownswitchState::kickdown_active;
        case static_cast<std::uint8_t>(2):
            return Eec2ElectronicEngineControl2AccelpedalkickdownswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Eec2ElectronicEngineControl2AccelpedalkickdownswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Eec2ElectronicEngineControl2AccelpedalkickdownswitchState value) -> std::string_view {
    switch (value) {
        case Eec2ElectronicEngineControl2AccelpedalkickdownswitchState::kickdown_passive:
            return "Kickdown passive";
        case Eec2ElectronicEngineControl2AccelpedalkickdownswitchState::kickdown_active:
            return "Kickdown active";
        case Eec2ElectronicEngineControl2AccelpedalkickdownswitchState::error:
            return "Error";
        case Eec2ElectronicEngineControl2AccelpedalkickdownswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Eec2ElectronicEngineControl2AccelpedalkickdownswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_eec2_electronic_engine_control_2__accelpedalkickdownswitch(const ValueStore& store) -> std::optional<Eec2ElectronicEngineControl2AccelpedalkickdownswitchState> {
    auto raw = store.template get<SignalId::eec2_electronic_engine_control_2__accelpedalkickdownswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_eec2_electronic_engine_control_2__accelpedalkickdownswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Eec2ElectronicEngineControl2RoadspeedlimitstatusState : std::uint8_t {
    active = 0,
    not_active = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEec2ElectronicEngineControl2RoadspeedlimitstatusStateChoices{ {
    ChoiceMeta{ 0, "Active", "active" },
    ChoiceMeta{ 1, "Not Active", "not_active" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_eec2_electronic_engine_control_2__roadspeedlimitstatus(std::uint8_t raw)
    -> std::expected<Eec2ElectronicEngineControl2RoadspeedlimitstatusState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Eec2ElectronicEngineControl2RoadspeedlimitstatusState::active;
        case static_cast<std::uint8_t>(1):
            return Eec2ElectronicEngineControl2RoadspeedlimitstatusState::not_active;
        case static_cast<std::uint8_t>(2):
            return Eec2ElectronicEngineControl2RoadspeedlimitstatusState::error;
        case static_cast<std::uint8_t>(3):
            return Eec2ElectronicEngineControl2RoadspeedlimitstatusState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Eec2ElectronicEngineControl2RoadspeedlimitstatusState value) -> std::string_view {
    switch (value) {
        case Eec2ElectronicEngineControl2RoadspeedlimitstatusState::active:
            return "Active";
        case Eec2ElectronicEngineControl2RoadspeedlimitstatusState::not_active:
            return "Not Active";
        case Eec2ElectronicEngineControl2RoadspeedlimitstatusState::error:
            return "Error";
        case Eec2ElectronicEngineControl2RoadspeedlimitstatusState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Eec2ElectronicEngineControl2RoadspeedlimitstatusState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_eec2_electronic_engine_control_2__roadspeedlimitstatus(const ValueStore& store) -> std::optional<Eec2ElectronicEngineControl2RoadspeedlimitstatusState> {
    auto raw = store.template get<SignalId::eec2_electronic_engine_control_2__roadspeedlimitstatus>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_eec2_electronic_engine_control_2__roadspeedlimitstatus(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Eec2ElectronicEngineControl2Accelpedal2lowidleswitchState : std::uint8_t {
    accelerator_pedal_2_not_in_low_idle_condition = 0,
    accelerator_pedal_2_in_low_idle_condition = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEec2ElectronicEngineControl2Accelpedal2lowidleswitchStateChoices{ {
    ChoiceMeta{ 0, "Accelerator pedal 2 not in low idle condition", "accelerator_pedal_2_not_in_low_idle_condition" },
    ChoiceMeta{ 1, "Accelerator pedal 2 in low idle condition", "accelerator_pedal_2_in_low_idle_condition" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_eec2_electronic_engine_control_2__accelpedal2lowidleswitch(std::uint8_t raw)
    -> std::expected<Eec2ElectronicEngineControl2Accelpedal2lowidleswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Eec2ElectronicEngineControl2Accelpedal2lowidleswitchState::accelerator_pedal_2_not_in_low_idle_condition;
        case static_cast<std::uint8_t>(1):
            return Eec2ElectronicEngineControl2Accelpedal2lowidleswitchState::accelerator_pedal_2_in_low_idle_condition;
        case static_cast<std::uint8_t>(2):
            return Eec2ElectronicEngineControl2Accelpedal2lowidleswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Eec2ElectronicEngineControl2Accelpedal2lowidleswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Eec2ElectronicEngineControl2Accelpedal2lowidleswitchState value) -> std::string_view {
    switch (value) {
        case Eec2ElectronicEngineControl2Accelpedal2lowidleswitchState::accelerator_pedal_2_not_in_low_idle_condition:
            return "Accelerator pedal 2 not in low idle condition";
        case Eec2ElectronicEngineControl2Accelpedal2lowidleswitchState::accelerator_pedal_2_in_low_idle_condition:
            return "Accelerator pedal 2 in low idle condition";
        case Eec2ElectronicEngineControl2Accelpedal2lowidleswitchState::error:
            return "Error";
        case Eec2ElectronicEngineControl2Accelpedal2lowidleswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Eec2ElectronicEngineControl2Accelpedal2lowidleswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_eec2_electronic_engine_control_2__accelpedal2lowidleswitch(const ValueStore& store) -> std::optional<Eec2ElectronicEngineControl2Accelpedal2lowidleswitchState> {
    auto raw = store.template get<SignalId::eec2_electronic_engine_control_2__accelpedal2lowidleswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_eec2_electronic_engine_control_2__accelpedal2lowidleswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Eec2ElectronicEngineControl2VhcleaccelerationratelimitstatusState : std::uint8_t {
    limit_not_active = 0,
    limit_active = 1,
    reserved = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEec2ElectronicEngineControl2VhcleaccelerationratelimitstatusStateChoices{ {
    ChoiceMeta{ 0, "Limit not active", "limit_not_active" },
    ChoiceMeta{ 1, "Limit active", "limit_active" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus(std::uint8_t raw)
    -> std::expected<Eec2ElectronicEngineControl2VhcleaccelerationratelimitstatusState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Eec2ElectronicEngineControl2VhcleaccelerationratelimitstatusState::limit_not_active;
        case static_cast<std::uint8_t>(1):
            return Eec2ElectronicEngineControl2VhcleaccelerationratelimitstatusState::limit_active;
        case static_cast<std::uint8_t>(2):
            return Eec2ElectronicEngineControl2VhcleaccelerationratelimitstatusState::reserved;
        case static_cast<std::uint8_t>(3):
            return Eec2ElectronicEngineControl2VhcleaccelerationratelimitstatusState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Eec2ElectronicEngineControl2VhcleaccelerationratelimitstatusState value) -> std::string_view {
    switch (value) {
        case Eec2ElectronicEngineControl2VhcleaccelerationratelimitstatusState::limit_not_active:
            return "Limit not active";
        case Eec2ElectronicEngineControl2VhcleaccelerationratelimitstatusState::limit_active:
            return "Limit active";
        case Eec2ElectronicEngineControl2VhcleaccelerationratelimitstatusState::reserved:
            return "Reserved";
        case Eec2ElectronicEngineControl2VhcleaccelerationratelimitstatusState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Eec2ElectronicEngineControl2VhcleaccelerationratelimitstatusState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus(const ValueStore& store) -> std::optional<Eec2ElectronicEngineControl2VhcleaccelerationratelimitstatusState> {
    auto raw = store.template get<SignalId::eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_eec2_electronic_engine_control_2__vhcleaccelerationratelimitstatus(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Eec2ElectronicEngineControl2MmntaryengmaxpowerenablefeedbackState : std::uint8_t {
    disabled = 0,
    supported = 1,
    reserved = 2,
    don_t_care = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEec2ElectronicEngineControl2MmntaryengmaxpowerenablefeedbackStateChoices{ {
    ChoiceMeta{ 0, "disabled", "disabled" },
    ChoiceMeta{ 1, "supported", "supported" },
    ChoiceMeta{ 2, "reserved", "reserved" },
    ChoiceMeta{ 3, "don't care", "don_t_care" }
} };

constexpr auto to_eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback(std::uint8_t raw)
    -> std::expected<Eec2ElectronicEngineControl2MmntaryengmaxpowerenablefeedbackState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Eec2ElectronicEngineControl2MmntaryengmaxpowerenablefeedbackState::disabled;
        case static_cast<std::uint8_t>(1):
            return Eec2ElectronicEngineControl2MmntaryengmaxpowerenablefeedbackState::supported;
        case static_cast<std::uint8_t>(2):
            return Eec2ElectronicEngineControl2MmntaryengmaxpowerenablefeedbackState::reserved;
        case static_cast<std::uint8_t>(3):
            return Eec2ElectronicEngineControl2MmntaryengmaxpowerenablefeedbackState::don_t_care;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Eec2ElectronicEngineControl2MmntaryengmaxpowerenablefeedbackState value) -> std::string_view {
    switch (value) {
        case Eec2ElectronicEngineControl2MmntaryengmaxpowerenablefeedbackState::disabled:
            return "disabled";
        case Eec2ElectronicEngineControl2MmntaryengmaxpowerenablefeedbackState::supported:
            return "supported";
        case Eec2ElectronicEngineControl2MmntaryengmaxpowerenablefeedbackState::reserved:
            return "reserved";
        case Eec2ElectronicEngineControl2MmntaryengmaxpowerenablefeedbackState::don_t_care:
            return "don't care";
    }
    return "<unknown>";
}

constexpr auto to_raw(Eec2ElectronicEngineControl2MmntaryengmaxpowerenablefeedbackState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback(const ValueStore& store) -> std::optional<Eec2ElectronicEngineControl2MmntaryengmaxpowerenablefeedbackState> {
    auto raw = store.template get<SignalId::eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_eec2_electronic_engine_control_2__mmntaryengmaxpowerenablefeedback(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Eec2ElectronicEngineControl2DpfthermalmanagementactiveState : std::uint8_t {
    dpf_thermal_management_is_not_active = 0,
    dpf_thermal_management_is_active = 1,
    reserved = 2,
    don_t_care = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEec2ElectronicEngineControl2DpfthermalmanagementactiveStateChoices{ {
    ChoiceMeta{ 0, "DPF Thermal Management is not active", "dpf_thermal_management_is_not_active" },
    ChoiceMeta{ 1, "DPF Thermal Management is active", "dpf_thermal_management_is_active" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Don't care", "don_t_care" }
} };

constexpr auto to_eec2_electronic_engine_control_2__dpfthermalmanagementactive(std::uint8_t raw)
    -> std::expected<Eec2ElectronicEngineControl2DpfthermalmanagementactiveState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Eec2ElectronicEngineControl2DpfthermalmanagementactiveState::dpf_thermal_management_is_not_active;
        case static_cast<std::uint8_t>(1):
            return Eec2ElectronicEngineControl2DpfthermalmanagementactiveState::dpf_thermal_management_is_active;
        case static_cast<std::uint8_t>(2):
            return Eec2ElectronicEngineControl2DpfthermalmanagementactiveState::reserved;
        case static_cast<std::uint8_t>(3):
            return Eec2ElectronicEngineControl2DpfthermalmanagementactiveState::don_t_care;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Eec2ElectronicEngineControl2DpfthermalmanagementactiveState value) -> std::string_view {
    switch (value) {
        case Eec2ElectronicEngineControl2DpfthermalmanagementactiveState::dpf_thermal_management_is_not_active:
            return "DPF Thermal Management is not active";
        case Eec2ElectronicEngineControl2DpfthermalmanagementactiveState::dpf_thermal_management_is_active:
            return "DPF Thermal Management is active";
        case Eec2ElectronicEngineControl2DpfthermalmanagementactiveState::reserved:
            return "Reserved";
        case Eec2ElectronicEngineControl2DpfthermalmanagementactiveState::don_t_care:
            return "Don't care";
    }
    return "<unknown>";
}

constexpr auto to_raw(Eec2ElectronicEngineControl2DpfthermalmanagementactiveState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_eec2_electronic_engine_control_2__dpfthermalmanagementactive(const ValueStore& store) -> std::optional<Eec2ElectronicEngineControl2DpfthermalmanagementactiveState> {
    auto raw = store.template get<SignalId::eec2_electronic_engine_control_2__dpfthermalmanagementactive>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_eec2_electronic_engine_control_2__dpfthermalmanagementactive(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Eec2ElectronicEngineControl2ScrthermalmanagementactiveState : std::uint8_t {
    scr_thermal_management_is_not_active = 0,
    scr_thermal_management_is_active = 1,
    reserved = 2,
    don_t_care = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEec2ElectronicEngineControl2ScrthermalmanagementactiveStateChoices{ {
    ChoiceMeta{ 0, "SCR Thermal Management is not active", "scr_thermal_management_is_not_active" },
    ChoiceMeta{ 1, "SCR Thermal Management is active", "scr_thermal_management_is_active" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Don't care", "don_t_care" }
} };

constexpr auto to_eec2_electronic_engine_control_2__scrthermalmanagementactive(std::uint8_t raw)
    -> std::expected<Eec2ElectronicEngineControl2ScrthermalmanagementactiveState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Eec2ElectronicEngineControl2ScrthermalmanagementactiveState::scr_thermal_management_is_not_active;
        case static_cast<std::uint8_t>(1):
            return Eec2ElectronicEngineControl2ScrthermalmanagementactiveState::scr_thermal_management_is_active;
        case static_cast<std::uint8_t>(2):
            return Eec2ElectronicEngineControl2ScrthermalmanagementactiveState::reserved;
        case static_cast<std::uint8_t>(3):
            return Eec2ElectronicEngineControl2ScrthermalmanagementactiveState::don_t_care;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Eec2ElectronicEngineControl2ScrthermalmanagementactiveState value) -> std::string_view {
    switch (value) {
        case Eec2ElectronicEngineControl2ScrthermalmanagementactiveState::scr_thermal_management_is_not_active:
            return "SCR Thermal Management is not active";
        case Eec2ElectronicEngineControl2ScrthermalmanagementactiveState::scr_thermal_management_is_active:
            return "SCR Thermal Management is active";
        case Eec2ElectronicEngineControl2ScrthermalmanagementactiveState::reserved:
            return "Reserved";
        case Eec2ElectronicEngineControl2ScrthermalmanagementactiveState::don_t_care:
            return "Don't care";
    }
    return "<unknown>";
}

constexpr auto to_raw(Eec2ElectronicEngineControl2ScrthermalmanagementactiveState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_eec2_electronic_engine_control_2__scrthermalmanagementactive(const ValueStore& store) -> std::optional<Eec2ElectronicEngineControl2ScrthermalmanagementactiveState> {
    auto raw = store.template get<SignalId::eec2_electronic_engine_control_2__scrthermalmanagementactive>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_eec2_electronic_engine_control_2__scrthermalmanagementactive(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Eec3ElectronicEngineControl3Aft1indewpointState : std::uint8_t {
    not_exceeded_the_dew_point = 0,
    exceeded_the_dew_point = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEec3ElectronicEngineControl3Aft1indewpointStateChoices{ {
    ChoiceMeta{ 0, "Not exceeded the dew point", "not_exceeded_the_dew_point" },
    ChoiceMeta{ 1, "Exceeded the dew point", "exceeded_the_dew_point" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_eec3_electronic_engine_control_3__aft1indewpoint(std::uint8_t raw)
    -> std::expected<Eec3ElectronicEngineControl3Aft1indewpointState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Eec3ElectronicEngineControl3Aft1indewpointState::not_exceeded_the_dew_point;
        case static_cast<std::uint8_t>(1):
            return Eec3ElectronicEngineControl3Aft1indewpointState::exceeded_the_dew_point;
        case static_cast<std::uint8_t>(2):
            return Eec3ElectronicEngineControl3Aft1indewpointState::error;
        case static_cast<std::uint8_t>(3):
            return Eec3ElectronicEngineControl3Aft1indewpointState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Eec3ElectronicEngineControl3Aft1indewpointState value) -> std::string_view {
    switch (value) {
        case Eec3ElectronicEngineControl3Aft1indewpointState::not_exceeded_the_dew_point:
            return "Not exceeded the dew point";
        case Eec3ElectronicEngineControl3Aft1indewpointState::exceeded_the_dew_point:
            return "Exceeded the dew point";
        case Eec3ElectronicEngineControl3Aft1indewpointState::error:
            return "Error";
        case Eec3ElectronicEngineControl3Aft1indewpointState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Eec3ElectronicEngineControl3Aft1indewpointState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_eec3_electronic_engine_control_3__aft1indewpoint(const ValueStore& store) -> std::optional<Eec3ElectronicEngineControl3Aft1indewpointState> {
    auto raw = store.template get<SignalId::eec3_electronic_engine_control_3__aft1indewpoint>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_eec3_electronic_engine_control_3__aft1indewpoint(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Eec3ElectronicEngineControl3Aft1exhdewpointState : std::uint8_t {
    not_exceeded_the_dew_point = 0,
    exceeded_the_dew_point = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEec3ElectronicEngineControl3Aft1exhdewpointStateChoices{ {
    ChoiceMeta{ 0, "Not exceeded the dew point", "not_exceeded_the_dew_point" },
    ChoiceMeta{ 1, "Exceeded the dew point", "exceeded_the_dew_point" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_eec3_electronic_engine_control_3__aft1exhdewpoint(std::uint8_t raw)
    -> std::expected<Eec3ElectronicEngineControl3Aft1exhdewpointState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Eec3ElectronicEngineControl3Aft1exhdewpointState::not_exceeded_the_dew_point;
        case static_cast<std::uint8_t>(1):
            return Eec3ElectronicEngineControl3Aft1exhdewpointState::exceeded_the_dew_point;
        case static_cast<std::uint8_t>(2):
            return Eec3ElectronicEngineControl3Aft1exhdewpointState::error;
        case static_cast<std::uint8_t>(3):
            return Eec3ElectronicEngineControl3Aft1exhdewpointState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Eec3ElectronicEngineControl3Aft1exhdewpointState value) -> std::string_view {
    switch (value) {
        case Eec3ElectronicEngineControl3Aft1exhdewpointState::not_exceeded_the_dew_point:
            return "Not exceeded the dew point";
        case Eec3ElectronicEngineControl3Aft1exhdewpointState::exceeded_the_dew_point:
            return "Exceeded the dew point";
        case Eec3ElectronicEngineControl3Aft1exhdewpointState::error:
            return "Error";
        case Eec3ElectronicEngineControl3Aft1exhdewpointState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Eec3ElectronicEngineControl3Aft1exhdewpointState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_eec3_electronic_engine_control_3__aft1exhdewpoint(const ValueStore& store) -> std::optional<Eec3ElectronicEngineControl3Aft1exhdewpointState> {
    auto raw = store.template get<SignalId::eec3_electronic_engine_control_3__aft1exhdewpoint>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_eec3_electronic_engine_control_3__aft1exhdewpoint(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Eec3ElectronicEngineControl3Aft2indewpointState : std::uint8_t {
    not_exceeded_the_dew_point = 0,
    exceeded_the_dew_point = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEec3ElectronicEngineControl3Aft2indewpointStateChoices{ {
    ChoiceMeta{ 0, "Not exceeded the dew point", "not_exceeded_the_dew_point" },
    ChoiceMeta{ 1, "Exceeded the dew point", "exceeded_the_dew_point" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_eec3_electronic_engine_control_3__aft2indewpoint(std::uint8_t raw)
    -> std::expected<Eec3ElectronicEngineControl3Aft2indewpointState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Eec3ElectronicEngineControl3Aft2indewpointState::not_exceeded_the_dew_point;
        case static_cast<std::uint8_t>(1):
            return Eec3ElectronicEngineControl3Aft2indewpointState::exceeded_the_dew_point;
        case static_cast<std::uint8_t>(2):
            return Eec3ElectronicEngineControl3Aft2indewpointState::error;
        case static_cast<std::uint8_t>(3):
            return Eec3ElectronicEngineControl3Aft2indewpointState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Eec3ElectronicEngineControl3Aft2indewpointState value) -> std::string_view {
    switch (value) {
        case Eec3ElectronicEngineControl3Aft2indewpointState::not_exceeded_the_dew_point:
            return "Not exceeded the dew point";
        case Eec3ElectronicEngineControl3Aft2indewpointState::exceeded_the_dew_point:
            return "Exceeded the dew point";
        case Eec3ElectronicEngineControl3Aft2indewpointState::error:
            return "Error";
        case Eec3ElectronicEngineControl3Aft2indewpointState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Eec3ElectronicEngineControl3Aft2indewpointState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_eec3_electronic_engine_control_3__aft2indewpoint(const ValueStore& store) -> std::optional<Eec3ElectronicEngineControl3Aft2indewpointState> {
    auto raw = store.template get<SignalId::eec3_electronic_engine_control_3__aft2indewpoint>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_eec3_electronic_engine_control_3__aft2indewpoint(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Eec3ElectronicEngineControl3Aft2exhdewpointState : std::uint8_t {
    not_exceeded_the_dew_point = 0,
    exceeded_the_dew_point = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEec3ElectronicEngineControl3Aft2exhdewpointStateChoices{ {
    ChoiceMeta{ 0, "Not exceeded the dew point", "not_exceeded_the_dew_point" },
    ChoiceMeta{ 1, "Exceeded the dew point", "exceeded_the_dew_point" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_eec3_electronic_engine_control_3__aft2exhdewpoint(std::uint8_t raw)
    -> std::expected<Eec3ElectronicEngineControl3Aft2exhdewpointState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Eec3ElectronicEngineControl3Aft2exhdewpointState::not_exceeded_the_dew_point;
        case static_cast<std::uint8_t>(1):
            return Eec3ElectronicEngineControl3Aft2exhdewpointState::exceeded_the_dew_point;
        case static_cast<std::uint8_t>(2):
            return Eec3ElectronicEngineControl3Aft2exhdewpointState::error;
        case static_cast<std::uint8_t>(3):
            return Eec3ElectronicEngineControl3Aft2exhdewpointState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Eec3ElectronicEngineControl3Aft2exhdewpointState value) -> std::string_view {
    switch (value) {
        case Eec3ElectronicEngineControl3Aft2exhdewpointState::not_exceeded_the_dew_point:
            return "Not exceeded the dew point";
        case Eec3ElectronicEngineControl3Aft2exhdewpointState::exceeded_the_dew_point:
            return "Exceeded the dew point";
        case Eec3ElectronicEngineControl3Aft2exhdewpointState::error:
            return "Error";
        case Eec3ElectronicEngineControl3Aft2exhdewpointState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Eec3ElectronicEngineControl3Aft2exhdewpointState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_eec3_electronic_engine_control_3__aft2exhdewpoint(const ValueStore& store) -> std::optional<Eec3ElectronicEngineControl3Aft2exhdewpointState> {
    auto raw = store.template get<SignalId::eec3_electronic_engine_control_3__aft2exhdewpoint>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_eec3_electronic_engine_control_3__aft2exhdewpoint(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class TransportprotocolHeaderControlbyteState : std::uint8_t {
    rts = 16,
    cts = 17,
    eoma = 19,
    bam = 32,
    abort = 255
};

inline constexpr std::array<ChoiceMeta, 5> kTransportprotocolHeaderControlbyteStateChoices{ {
    ChoiceMeta{ 16, "RTS", "rts" },
    ChoiceMeta{ 17, "CTS", "cts" },
    ChoiceMeta{ 19, "EoMA", "eoma" },
    ChoiceMeta{ 32, "BAM", "bam" },
    ChoiceMeta{ 255, "Abort", "abort" }
} };

constexpr auto to_transportprotocol_header__controlbyte(std::uint8_t raw)
    -> std::expected<TransportprotocolHeaderControlbyteState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(16):
            return TransportprotocolHeaderControlbyteState::rts;
        case static_cast<std::uint8_t>(17):
            return TransportprotocolHeaderControlbyteState::cts;
        case static_cast<std::uint8_t>(19):
            return TransportprotocolHeaderControlbyteState::eoma;
        case static_cast<std::uint8_t>(32):
            return TransportprotocolHeaderControlbyteState::bam;
        case static_cast<std::uint8_t>(255):
            return TransportprotocolHeaderControlbyteState::abort;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(TransportprotocolHeaderControlbyteState value) -> std::string_view {
    switch (value) {
        case TransportprotocolHeaderControlbyteState::rts:
            return "RTS";
        case TransportprotocolHeaderControlbyteState::cts:
            return "CTS";
        case TransportprotocolHeaderControlbyteState::eoma:
            return "EoMA";
        case TransportprotocolHeaderControlbyteState::bam:
            return "BAM";
        case TransportprotocolHeaderControlbyteState::abort:
            return "Abort";
    }
    return "<unknown>";
}

constexpr auto to_raw(TransportprotocolHeaderControlbyteState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_transportprotocol_header__controlbyte(const ValueStore& store) -> std::optional<TransportprotocolHeaderControlbyteState> {
    auto raw = store.template get<SignalId::transportprotocol_header__controlbyte>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_transportprotocol_header__controlbyte(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class TransportprotocolHeaderConnectionabortreasonState : std::uint8_t {
    already_in_one_or_more_connection_managed_sessions_and_cannot_support_another = 1,
    system_resources_were_needed_for_another_task_so_this_connection_managed_session_was_terminated = 2,
    a_timeout_occurred_and_this_is_the_connection_abort_to_close_the_session = 3,
    cts_messages_received_when_data_transfer_is_in_progress = 4,
    maximum_retransmit_request_limit_reached = 5,
    unexpected_data_transfer_packet = 6,
    bad_sequence_number_software_cannot_recover = 7,
    duplicate_sequence_number_software_cannot_recover = 8,
    total_message_size_is_greater_than_1785_bytes = 9,
    connection_abort_reason_is_not_listed = 250,
    error_indicator = 254,
    not_available = 255
};

inline constexpr std::array<ChoiceMeta, 12> kTransportprotocolHeaderConnectionabortreasonStateChoices{ {
    ChoiceMeta{ 1, "Already in one or more connection managed sessions and cannot support another.", "already_in_one_or_more_connection_managed_sessions_and_cannot_support_another" },
    ChoiceMeta{ 2, "System resources were needed for another task so this connection managed session was terminated.", "system_resources_were_needed_for_another_task_so_this_connection_managed_session_was_terminated" },
    ChoiceMeta{ 3, "A timeout occurred and this is the connection abort to close the session.", "a_timeout_occurred_and_this_is_the_connection_abort_to_close_the_session" },
    ChoiceMeta{ 4, "CTS messages received when data transfer is in progress.", "cts_messages_received_when_data_transfer_is_in_progress" },
    ChoiceMeta{ 5, "Maximum retransmit request limit reached", "maximum_retransmit_request_limit_reached" },
    ChoiceMeta{ 6, "Unexpected data transfer packet", "unexpected_data_transfer_packet" },
    ChoiceMeta{ 7, "Bad sequence number (software cannot recover)", "bad_sequence_number_software_cannot_recover" },
    ChoiceMeta{ 8, "Duplicate sequence number (software cannot recover)", "duplicate_sequence_number_software_cannot_recover" },
    ChoiceMeta{ 9, "Total Message Size is greater than 1785 bytes", "total_message_size_is_greater_than_1785_bytes" },
    ChoiceMeta{ 250, "Connection Abort reason is not listed", "connection_abort_reason_is_not_listed" },
    ChoiceMeta{ 254, "Error indicator", "error_indicator" },
    ChoiceMeta{ 255, "Not available", "not_available" }
} };

constexpr auto to_transportprotocol_header__connectionabortreason(std::uint8_t raw)
    -> std::expected<TransportprotocolHeaderConnectionabortreasonState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(1):
            return TransportprotocolHeaderConnectionabortreasonState::already_in_one_or_more_connection_managed_sessions_and_cannot_support_another;
        case static_cast<std::uint8_t>(2):
            return TransportprotocolHeaderConnectionabortreasonState::system_resources_were_needed_for_another_task_so_this_connection_managed_session_was_terminated;
        case static_cast<std::uint8_t>(3):
            return TransportprotocolHeaderConnectionabortreasonState::a_timeout_occurred_and_this_is_the_connection_abort_to_close_the_session;
        case static_cast<std::uint8_t>(4):
            return TransportprotocolHeaderConnectionabortreasonState::cts_messages_received_when_data_transfer_is_in_progress;
        case static_cast<std::uint8_t>(5):
            return TransportprotocolHeaderConnectionabortreasonState::maximum_retransmit_request_limit_reached;
        case static_cast<std::uint8_t>(6):
            return TransportprotocolHeaderConnectionabortreasonState::unexpected_data_transfer_packet;
        case static_cast<std::uint8_t>(7):
            return TransportprotocolHeaderConnectionabortreasonState::bad_sequence_number_software_cannot_recover;
        case static_cast<std::uint8_t>(8):
            return TransportprotocolHeaderConnectionabortreasonState::duplicate_sequence_number_software_cannot_recover;
        case static_cast<std::uint8_t>(9):
            return TransportprotocolHeaderConnectionabortreasonState::total_message_size_is_greater_than_1785_bytes;
        case static_cast<std::uint8_t>(250):
            return TransportprotocolHeaderConnectionabortreasonState::connection_abort_reason_is_not_listed;
        case static_cast<std::uint8_t>(254):
            return TransportprotocolHeaderConnectionabortreasonState::error_indicator;
        case static_cast<std::uint8_t>(255):
            return TransportprotocolHeaderConnectionabortreasonState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(TransportprotocolHeaderConnectionabortreasonState value) -> std::string_view {
    switch (value) {
        case TransportprotocolHeaderConnectionabortreasonState::already_in_one_or_more_connection_managed_sessions_and_cannot_support_another:
            return "Already in one or more connection managed sessions and cannot support another.";
        case TransportprotocolHeaderConnectionabortreasonState::system_resources_were_needed_for_another_task_so_this_connection_managed_session_was_terminated:
            return "System resources were needed for another task so this connection managed session was terminated.";
        case TransportprotocolHeaderConnectionabortreasonState::a_timeout_occurred_and_this_is_the_connection_abort_to_close_the_session:
            return "A timeout occurred and this is the connection abort to close the session.";
        case TransportprotocolHeaderConnectionabortreasonState::cts_messages_received_when_data_transfer_is_in_progress:
            return "CTS messages received when data transfer is in progress.";
        case TransportprotocolHeaderConnectionabortreasonState::maximum_retransmit_request_limit_reached:
            return "Maximum retransmit request limit reached";
        case TransportprotocolHeaderConnectionabortreasonState::unexpected_data_transfer_packet:
            return "Unexpected data transfer packet";
        case TransportprotocolHeaderConnectionabortreasonState::bad_sequence_number_software_cannot_recover:
            return "Bad sequence number (software cannot recover)";
        case TransportprotocolHeaderConnectionabortreasonState::duplicate_sequence_number_software_cannot_recover:
            return "Duplicate sequence number (software cannot recover)";
        case TransportprotocolHeaderConnectionabortreasonState::total_message_size_is_greater_than_1785_bytes:
            return "Total Message Size is greater than 1785 bytes";
        case TransportprotocolHeaderConnectionabortreasonState::connection_abort_reason_is_not_listed:
            return "Connection Abort reason is not listed";
        case TransportprotocolHeaderConnectionabortreasonState::error_indicator:
            return "Error indicator";
        case TransportprotocolHeaderConnectionabortreasonState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(TransportprotocolHeaderConnectionabortreasonState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_transportprotocol_header__connectionabortreason(const ValueStore& store) -> std::optional<TransportprotocolHeaderConnectionabortreasonState> {
    auto raw = store.template get<SignalId::transportprotocol_header__connectionabortreason>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_transportprotocol_header__connectionabortreason(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class TransportprotocolHeaderPgnumberState : std::uint32_t {
    notavailable = 255
};

inline constexpr std::array<ChoiceMeta, 1> kTransportprotocolHeaderPgnumberStateChoices{ {
    ChoiceMeta{ 255, "NotAvailable", "notavailable" }
} };

constexpr auto to_transportprotocol_header__pgnumber(std::uint32_t raw)
    -> std::expected<TransportprotocolHeaderPgnumberState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint32_t>(255):
            return TransportprotocolHeaderPgnumberState::notavailable;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(TransportprotocolHeaderPgnumberState value) -> std::string_view {
    switch (value) {
        case TransportprotocolHeaderPgnumberState::notavailable:
            return "NotAvailable";
    }
    return "<unknown>";
}

constexpr auto to_raw(TransportprotocolHeaderPgnumberState value) -> std::uint32_t {
    return static_cast<std::uint32_t>(value);
}

constexpr auto try_get_transportprotocol_header__pgnumber(const ValueStore& store) -> std::optional<TransportprotocolHeaderPgnumberState> {
    auto raw = store.template get<SignalId::transportprotocol_header__pgnumber>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_transportprotocol_header__pgnumber(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Dm01ActiveDiagnosticsProtectlampstatusState : std::uint8_t {
    lamp_off = 0,
    lamp_on = 1,
    reserved = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kDm01ActiveDiagnosticsProtectlampstatusStateChoices{ {
    ChoiceMeta{ 0, "Lamp Off", "lamp_off" },
    ChoiceMeta{ 1, "Lamp On", "lamp_on" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_dm01_active_diagnostics__protectlampstatus(std::uint8_t raw)
    -> std::expected<Dm01ActiveDiagnosticsProtectlampstatusState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Dm01ActiveDiagnosticsProtectlampstatusState::lamp_off;
        case static_cast<std::uint8_t>(1):
            return Dm01ActiveDiagnosticsProtectlampstatusState::lamp_on;
        case static_cast<std::uint8_t>(2):
            return Dm01ActiveDiagnosticsProtectlampstatusState::reserved;
        case static_cast<std::uint8_t>(3):
            return Dm01ActiveDiagnosticsProtectlampstatusState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Dm01ActiveDiagnosticsProtectlampstatusState value) -> std::string_view {
    switch (value) {
        case Dm01ActiveDiagnosticsProtectlampstatusState::lamp_off:
            return "Lamp Off";
        case Dm01ActiveDiagnosticsProtectlampstatusState::lamp_on:
            return "Lamp On";
        case Dm01ActiveDiagnosticsProtectlampstatusState::reserved:
            return "Reserved";
        case Dm01ActiveDiagnosticsProtectlampstatusState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Dm01ActiveDiagnosticsProtectlampstatusState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_dm01_active_diagnostics__protectlampstatus(const ValueStore& store) -> std::optional<Dm01ActiveDiagnosticsProtectlampstatusState> {
    auto raw = store.template get<SignalId::dm01_active_diagnostics__protectlampstatus>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_dm01_active_diagnostics__protectlampstatus(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Dm01ActiveDiagnosticsAmberwarninglampstatusState : std::uint8_t {
    lamp_off = 0,
    lamp_on = 1,
    reserved = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kDm01ActiveDiagnosticsAmberwarninglampstatusStateChoices{ {
    ChoiceMeta{ 0, "Lamp Off", "lamp_off" },
    ChoiceMeta{ 1, "Lamp On", "lamp_on" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_dm01_active_diagnostics__amberwarninglampstatus(std::uint8_t raw)
    -> std::expected<Dm01ActiveDiagnosticsAmberwarninglampstatusState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Dm01ActiveDiagnosticsAmberwarninglampstatusState::lamp_off;
        case static_cast<std::uint8_t>(1):
            return Dm01ActiveDiagnosticsAmberwarninglampstatusState::lamp_on;
        case static_cast<std::uint8_t>(2):
            return Dm01ActiveDiagnosticsAmberwarninglampstatusState::reserved;
        case static_cast<std::uint8_t>(3):
            return Dm01ActiveDiagnosticsAmberwarninglampstatusState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Dm01ActiveDiagnosticsAmberwarninglampstatusState value) -> std::string_view {
    switch (value) {
        case Dm01ActiveDiagnosticsAmberwarninglampstatusState::lamp_off:
            return "Lamp Off";
        case Dm01ActiveDiagnosticsAmberwarninglampstatusState::lamp_on:
            return "Lamp On";
        case Dm01ActiveDiagnosticsAmberwarninglampstatusState::reserved:
            return "Reserved";
        case Dm01ActiveDiagnosticsAmberwarninglampstatusState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Dm01ActiveDiagnosticsAmberwarninglampstatusState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_dm01_active_diagnostics__amberwarninglampstatus(const ValueStore& store) -> std::optional<Dm01ActiveDiagnosticsAmberwarninglampstatusState> {
    auto raw = store.template get<SignalId::dm01_active_diagnostics__amberwarninglampstatus>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_dm01_active_diagnostics__amberwarninglampstatus(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Dm01ActiveDiagnosticsRedstoplampstateState : std::uint8_t {
    lamp_off = 0,
    lamp_on = 1,
    reserved = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kDm01ActiveDiagnosticsRedstoplampstateStateChoices{ {
    ChoiceMeta{ 0, "Lamp Off", "lamp_off" },
    ChoiceMeta{ 1, "Lamp On", "lamp_on" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_dm01_active_diagnostics__redstoplampstate(std::uint8_t raw)
    -> std::expected<Dm01ActiveDiagnosticsRedstoplampstateState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Dm01ActiveDiagnosticsRedstoplampstateState::lamp_off;
        case static_cast<std::uint8_t>(1):
            return Dm01ActiveDiagnosticsRedstoplampstateState::lamp_on;
        case static_cast<std::uint8_t>(2):
            return Dm01ActiveDiagnosticsRedstoplampstateState::reserved;
        case static_cast<std::uint8_t>(3):
            return Dm01ActiveDiagnosticsRedstoplampstateState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Dm01ActiveDiagnosticsRedstoplampstateState value) -> std::string_view {
    switch (value) {
        case Dm01ActiveDiagnosticsRedstoplampstateState::lamp_off:
            return "Lamp Off";
        case Dm01ActiveDiagnosticsRedstoplampstateState::lamp_on:
            return "Lamp On";
        case Dm01ActiveDiagnosticsRedstoplampstateState::reserved:
            return "Reserved";
        case Dm01ActiveDiagnosticsRedstoplampstateState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Dm01ActiveDiagnosticsRedstoplampstateState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_dm01_active_diagnostics__redstoplampstate(const ValueStore& store) -> std::optional<Dm01ActiveDiagnosticsRedstoplampstateState> {
    auto raw = store.template get<SignalId::dm01_active_diagnostics__redstoplampstate>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_dm01_active_diagnostics__redstoplampstate(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Dm01ActiveDiagnosticsMalfunctionindicatorlampstatusState : std::uint8_t {
    lamp_off = 0,
    lamp_on = 1,
    short_mil_for_wwh_obd = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kDm01ActiveDiagnosticsMalfunctionindicatorlampstatusStateChoices{ {
    ChoiceMeta{ 0, "Lamp Off", "lamp_off" },
    ChoiceMeta{ 1, "Lamp On", "lamp_on" },
    ChoiceMeta{ 2, "Short MIL for WWH OBD", "short_mil_for_wwh_obd" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_dm01_active_diagnostics__malfunctionindicatorlampstatus(std::uint8_t raw)
    -> std::expected<Dm01ActiveDiagnosticsMalfunctionindicatorlampstatusState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Dm01ActiveDiagnosticsMalfunctionindicatorlampstatusState::lamp_off;
        case static_cast<std::uint8_t>(1):
            return Dm01ActiveDiagnosticsMalfunctionindicatorlampstatusState::lamp_on;
        case static_cast<std::uint8_t>(2):
            return Dm01ActiveDiagnosticsMalfunctionindicatorlampstatusState::short_mil_for_wwh_obd;
        case static_cast<std::uint8_t>(3):
            return Dm01ActiveDiagnosticsMalfunctionindicatorlampstatusState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Dm01ActiveDiagnosticsMalfunctionindicatorlampstatusState value) -> std::string_view {
    switch (value) {
        case Dm01ActiveDiagnosticsMalfunctionindicatorlampstatusState::lamp_off:
            return "Lamp Off";
        case Dm01ActiveDiagnosticsMalfunctionindicatorlampstatusState::lamp_on:
            return "Lamp On";
        case Dm01ActiveDiagnosticsMalfunctionindicatorlampstatusState::short_mil_for_wwh_obd:
            return "Short MIL for WWH OBD";
        case Dm01ActiveDiagnosticsMalfunctionindicatorlampstatusState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Dm01ActiveDiagnosticsMalfunctionindicatorlampstatusState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_dm01_active_diagnostics__malfunctionindicatorlampstatus(const ValueStore& store) -> std::optional<Dm01ActiveDiagnosticsMalfunctionindicatorlampstatusState> {
    auto raw = store.template get<SignalId::dm01_active_diagnostics__malfunctionindicatorlampstatus>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_dm01_active_diagnostics__malfunctionindicatorlampstatus(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Dm01ActiveDiagnosticsFlashprotectlampState : std::uint8_t {
    slow_flash = 0,
    fast_flash = 1,
    reserved = 2,
    unavailable_do_not_flash = 3
};

inline constexpr std::array<ChoiceMeta, 4> kDm01ActiveDiagnosticsFlashprotectlampStateChoices{ {
    ChoiceMeta{ 0, "Slow Flash", "slow_flash" },
    ChoiceMeta{ 1, "Fast Flash", "fast_flash" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Unavailable / Do Not Flash", "unavailable_do_not_flash" }
} };

constexpr auto to_dm01_active_diagnostics__flashprotectlamp(std::uint8_t raw)
    -> std::expected<Dm01ActiveDiagnosticsFlashprotectlampState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Dm01ActiveDiagnosticsFlashprotectlampState::slow_flash;
        case static_cast<std::uint8_t>(1):
            return Dm01ActiveDiagnosticsFlashprotectlampState::fast_flash;
        case static_cast<std::uint8_t>(2):
            return Dm01ActiveDiagnosticsFlashprotectlampState::reserved;
        case static_cast<std::uint8_t>(3):
            return Dm01ActiveDiagnosticsFlashprotectlampState::unavailable_do_not_flash;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Dm01ActiveDiagnosticsFlashprotectlampState value) -> std::string_view {
    switch (value) {
        case Dm01ActiveDiagnosticsFlashprotectlampState::slow_flash:
            return "Slow Flash";
        case Dm01ActiveDiagnosticsFlashprotectlampState::fast_flash:
            return "Fast Flash";
        case Dm01ActiveDiagnosticsFlashprotectlampState::reserved:
            return "Reserved";
        case Dm01ActiveDiagnosticsFlashprotectlampState::unavailable_do_not_flash:
            return "Unavailable / Do Not Flash";
    }
    return "<unknown>";
}

constexpr auto to_raw(Dm01ActiveDiagnosticsFlashprotectlampState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_dm01_active_diagnostics__flashprotectlamp(const ValueStore& store) -> std::optional<Dm01ActiveDiagnosticsFlashprotectlampState> {
    auto raw = store.template get<SignalId::dm01_active_diagnostics__flashprotectlamp>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_dm01_active_diagnostics__flashprotectlamp(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Dm01ActiveDiagnosticsFlashamberwarninglampState : std::uint8_t {
    slow_flash = 0,
    fast_flash = 1,
    reserved = 2,
    unavailable_do_not_flash = 3
};

inline constexpr std::array<ChoiceMeta, 4> kDm01ActiveDiagnosticsFlashamberwarninglampStateChoices{ {
    ChoiceMeta{ 0, "Slow Flash", "slow_flash" },
    ChoiceMeta{ 1, "Fast Flash", "fast_flash" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Unavailable / Do Not Flash", "unavailable_do_not_flash" }
} };

constexpr auto to_dm01_active_diagnostics__flashamberwarninglamp(std::uint8_t raw)
    -> std::expected<Dm01ActiveDiagnosticsFlashamberwarninglampState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Dm01ActiveDiagnosticsFlashamberwarninglampState::slow_flash;
        case static_cast<std::uint8_t>(1):
            return Dm01ActiveDiagnosticsFlashamberwarninglampState::fast_flash;
        case static_cast<std::uint8_t>(2):
            return Dm01ActiveDiagnosticsFlashamberwarninglampState::reserved;
        case static_cast<std::uint8_t>(3):
            return Dm01ActiveDiagnosticsFlashamberwarninglampState::unavailable_do_not_flash;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Dm01ActiveDiagnosticsFlashamberwarninglampState value) -> std::string_view {
    switch (value) {
        case Dm01ActiveDiagnosticsFlashamberwarninglampState::slow_flash:
            return "Slow Flash";
        case Dm01ActiveDiagnosticsFlashamberwarninglampState::fast_flash:
            return "Fast Flash";
        case Dm01ActiveDiagnosticsFlashamberwarninglampState::reserved:
            return "Reserved";
        case Dm01ActiveDiagnosticsFlashamberwarninglampState::unavailable_do_not_flash:
            return "Unavailable / Do Not Flash";
    }
    return "<unknown>";
}

constexpr auto to_raw(Dm01ActiveDiagnosticsFlashamberwarninglampState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_dm01_active_diagnostics__flashamberwarninglamp(const ValueStore& store) -> std::optional<Dm01ActiveDiagnosticsFlashamberwarninglampState> {
    auto raw = store.template get<SignalId::dm01_active_diagnostics__flashamberwarninglamp>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_dm01_active_diagnostics__flashamberwarninglamp(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Dm01ActiveDiagnosticsFlashredstoplampState : std::uint8_t {
    slow_flash = 0,
    fast_flash = 1,
    reserved = 2,
    unavailable_do_not_flash = 3
};

inline constexpr std::array<ChoiceMeta, 4> kDm01ActiveDiagnosticsFlashredstoplampStateChoices{ {
    ChoiceMeta{ 0, "Slow Flash", "slow_flash" },
    ChoiceMeta{ 1, "Fast Flash", "fast_flash" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Unavailable / Do Not Flash", "unavailable_do_not_flash" }
} };

constexpr auto to_dm01_active_diagnostics__flashredstoplamp(std::uint8_t raw)
    -> std::expected<Dm01ActiveDiagnosticsFlashredstoplampState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Dm01ActiveDiagnosticsFlashredstoplampState::slow_flash;
        case static_cast<std::uint8_t>(1):
            return Dm01ActiveDiagnosticsFlashredstoplampState::fast_flash;
        case static_cast<std::uint8_t>(2):
            return Dm01ActiveDiagnosticsFlashredstoplampState::reserved;
        case static_cast<std::uint8_t>(3):
            return Dm01ActiveDiagnosticsFlashredstoplampState::unavailable_do_not_flash;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Dm01ActiveDiagnosticsFlashredstoplampState value) -> std::string_view {
    switch (value) {
        case Dm01ActiveDiagnosticsFlashredstoplampState::slow_flash:
            return "Slow Flash";
        case Dm01ActiveDiagnosticsFlashredstoplampState::fast_flash:
            return "Fast Flash";
        case Dm01ActiveDiagnosticsFlashredstoplampState::reserved:
            return "Reserved";
        case Dm01ActiveDiagnosticsFlashredstoplampState::unavailable_do_not_flash:
            return "Unavailable / Do Not Flash";
    }
    return "<unknown>";
}

constexpr auto to_raw(Dm01ActiveDiagnosticsFlashredstoplampState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_dm01_active_diagnostics__flashredstoplamp(const ValueStore& store) -> std::optional<Dm01ActiveDiagnosticsFlashredstoplampState> {
    auto raw = store.template get<SignalId::dm01_active_diagnostics__flashredstoplamp>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_dm01_active_diagnostics__flashredstoplamp(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Dm01ActiveDiagnosticsFlashmalfuncindicatorlampState : std::uint8_t {
    slow_flash = 0,
    fast_flash = 1,
    class_c_dtc = 2,
    unavailable_do_not_flash = 3
};

inline constexpr std::array<ChoiceMeta, 4> kDm01ActiveDiagnosticsFlashmalfuncindicatorlampStateChoices{ {
    ChoiceMeta{ 0, "Slow Flash", "slow_flash" },
    ChoiceMeta{ 1, "Fast Flash", "fast_flash" },
    ChoiceMeta{ 2, "Class C DTC  ", "class_c_dtc" },
    ChoiceMeta{ 3, "Unavailable / Do Not Flash", "unavailable_do_not_flash" }
} };

constexpr auto to_dm01_active_diagnostics__flashmalfuncindicatorlamp(std::uint8_t raw)
    -> std::expected<Dm01ActiveDiagnosticsFlashmalfuncindicatorlampState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Dm01ActiveDiagnosticsFlashmalfuncindicatorlampState::slow_flash;
        case static_cast<std::uint8_t>(1):
            return Dm01ActiveDiagnosticsFlashmalfuncindicatorlampState::fast_flash;
        case static_cast<std::uint8_t>(2):
            return Dm01ActiveDiagnosticsFlashmalfuncindicatorlampState::class_c_dtc;
        case static_cast<std::uint8_t>(3):
            return Dm01ActiveDiagnosticsFlashmalfuncindicatorlampState::unavailable_do_not_flash;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Dm01ActiveDiagnosticsFlashmalfuncindicatorlampState value) -> std::string_view {
    switch (value) {
        case Dm01ActiveDiagnosticsFlashmalfuncindicatorlampState::slow_flash:
            return "Slow Flash";
        case Dm01ActiveDiagnosticsFlashmalfuncindicatorlampState::fast_flash:
            return "Fast Flash";
        case Dm01ActiveDiagnosticsFlashmalfuncindicatorlampState::class_c_dtc:
            return "Class C DTC  ";
        case Dm01ActiveDiagnosticsFlashmalfuncindicatorlampState::unavailable_do_not_flash:
            return "Unavailable / Do Not Flash";
    }
    return "<unknown>";
}

constexpr auto to_raw(Dm01ActiveDiagnosticsFlashmalfuncindicatorlampState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_dm01_active_diagnostics__flashmalfuncindicatorlamp(const ValueStore& store) -> std::optional<Dm01ActiveDiagnosticsFlashmalfuncindicatorlampState> {
    auto raw = store.template get<SignalId::dm01_active_diagnostics__flashmalfuncindicatorlamp>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_dm01_active_diagnostics__flashmalfuncindicatorlamp(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc131EngoverridectrlmodeState : std::uint8_t {
    override_disabled = 0,
    speed_control = 1,
    torque_control = 2,
    speed_torque_limit_control = 3
};

inline constexpr std::array<ChoiceMeta, 4> kTsc131EngoverridectrlmodeStateChoices{ {
    ChoiceMeta{ 0, "Override disabled", "override_disabled" },
    ChoiceMeta{ 1, "Speed control", "speed_control" },
    ChoiceMeta{ 2, "Torque control", "torque_control" },
    ChoiceMeta{ 3, "Speed/torque limit control", "speed_torque_limit_control" }
} };

constexpr auto to_tsc1_31__engoverridectrlmode(std::uint8_t raw)
    -> std::expected<Tsc131EngoverridectrlmodeState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc131EngoverridectrlmodeState::override_disabled;
        case static_cast<std::uint8_t>(1):
            return Tsc131EngoverridectrlmodeState::speed_control;
        case static_cast<std::uint8_t>(2):
            return Tsc131EngoverridectrlmodeState::torque_control;
        case static_cast<std::uint8_t>(3):
            return Tsc131EngoverridectrlmodeState::speed_torque_limit_control;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc131EngoverridectrlmodeState value) -> std::string_view {
    switch (value) {
        case Tsc131EngoverridectrlmodeState::override_disabled:
            return "Override disabled";
        case Tsc131EngoverridectrlmodeState::speed_control:
            return "Speed control";
        case Tsc131EngoverridectrlmodeState::torque_control:
            return "Torque control";
        case Tsc131EngoverridectrlmodeState::speed_torque_limit_control:
            return "Speed/torque limit control";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc131EngoverridectrlmodeState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_31__engoverridectrlmode(const ValueStore& store) -> std::optional<Tsc131EngoverridectrlmodeState> {
    auto raw = store.template get<SignalId::tsc1_31__engoverridectrlmode>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_31__engoverridectrlmode(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc131EngrequestedspeedctrlconditionsState : std::uint8_t {
    transient_optimized_for_driveline_disengaged_and_non_lockup_conditions = 0,
    stability_optimized_for_driveline_disengaged_and_non_lockup_conditions = 1,
    stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_1 = 2,
    stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_2 = 3
};

inline constexpr std::array<ChoiceMeta, 4> kTsc131EngrequestedspeedctrlconditionsStateChoices{ {
    ChoiceMeta{ 0, "Transient Optimized for driveline disengaged and non-lockup conditions", "transient_optimized_for_driveline_disengaged_and_non_lockup_conditions" },
    ChoiceMeta{ 1, "Stability Optimized for driveline disengaged and non-lockup conditions", "stability_optimized_for_driveline_disengaged_and_non_lockup_conditions" },
    ChoiceMeta{ 2, "Stability Optimized for driveline engaged and/or in lockup condition 1", "stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_1" },
    ChoiceMeta{ 3, "Stability Optimized for driveline engaged and/or in lockup condition 2", "stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_2" }
} };

constexpr auto to_tsc1_31__engrequestedspeedctrlconditions(std::uint8_t raw)
    -> std::expected<Tsc131EngrequestedspeedctrlconditionsState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc131EngrequestedspeedctrlconditionsState::transient_optimized_for_driveline_disengaged_and_non_lockup_conditions;
        case static_cast<std::uint8_t>(1):
            return Tsc131EngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_disengaged_and_non_lockup_conditions;
        case static_cast<std::uint8_t>(2):
            return Tsc131EngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_1;
        case static_cast<std::uint8_t>(3):
            return Tsc131EngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_2;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc131EngrequestedspeedctrlconditionsState value) -> std::string_view {
    switch (value) {
        case Tsc131EngrequestedspeedctrlconditionsState::transient_optimized_for_driveline_disengaged_and_non_lockup_conditions:
            return "Transient Optimized for driveline disengaged and non-lockup conditions";
        case Tsc131EngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_disengaged_and_non_lockup_conditions:
            return "Stability Optimized for driveline disengaged and non-lockup conditions";
        case Tsc131EngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_1:
            return "Stability Optimized for driveline engaged and/or in lockup condition 1";
        case Tsc131EngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_2:
            return "Stability Optimized for driveline engaged and/or in lockup condition 2";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc131EngrequestedspeedctrlconditionsState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_31__engrequestedspeedctrlconditions(const ValueStore& store) -> std::optional<Tsc131EngrequestedspeedctrlconditionsState> {
    auto raw = store.template get<SignalId::tsc1_31__engrequestedspeedctrlconditions>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_31__engrequestedspeedctrlconditions(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc131OverridectrlmodepriorityState : std::uint8_t {
    highest_priority = 0,
    high_priority = 1,
    medium_priority = 2,
    low_priority = 3
};

inline constexpr std::array<ChoiceMeta, 4> kTsc131OverridectrlmodepriorityStateChoices{ {
    ChoiceMeta{ 0, "Highest priority", "highest_priority" },
    ChoiceMeta{ 1, "High priority", "high_priority" },
    ChoiceMeta{ 2, "Medium priority", "medium_priority" },
    ChoiceMeta{ 3, "Low priority", "low_priority" }
} };

constexpr auto to_tsc1_31__overridectrlmodepriority(std::uint8_t raw)
    -> std::expected<Tsc131OverridectrlmodepriorityState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc131OverridectrlmodepriorityState::highest_priority;
        case static_cast<std::uint8_t>(1):
            return Tsc131OverridectrlmodepriorityState::high_priority;
        case static_cast<std::uint8_t>(2):
            return Tsc131OverridectrlmodepriorityState::medium_priority;
        case static_cast<std::uint8_t>(3):
            return Tsc131OverridectrlmodepriorityState::low_priority;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc131OverridectrlmodepriorityState value) -> std::string_view {
    switch (value) {
        case Tsc131OverridectrlmodepriorityState::highest_priority:
            return "Highest priority";
        case Tsc131OverridectrlmodepriorityState::high_priority:
            return "High priority";
        case Tsc131OverridectrlmodepriorityState::medium_priority:
            return "Medium priority";
        case Tsc131OverridectrlmodepriorityState::low_priority:
            return "Low priority";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc131OverridectrlmodepriorityState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_31__overridectrlmodepriority(const ValueStore& store) -> std::optional<Tsc131OverridectrlmodepriorityState> {
    auto raw = store.template get<SignalId::tsc1_31__overridectrlmodepriority>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_31__overridectrlmodepriority(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc131Tsc1transrateState : std::uint8_t {
    _1000_ms_transmission_rate = 0,
    _750_ms_transmission_rate = 1,
    _500_ms_transmission_rate = 2,
    _250_ms_transmission_rate = 3,
    _100_ms_transmission_rate = 4,
    _50_ms_transmission_rate = 5,
    _20_ms_transmission_rate = 6,
    use_standard_tsc1_transmission_rates_of_10_ms_to_engine = 7
};

inline constexpr std::array<ChoiceMeta, 8> kTsc131Tsc1transrateStateChoices{ {
    ChoiceMeta{ 0, "1000 ms transmission rate", "_1000_ms_transmission_rate" },
    ChoiceMeta{ 1, "750 ms transmission rate", "_750_ms_transmission_rate" },
    ChoiceMeta{ 2, "500 ms transmission rate", "_500_ms_transmission_rate" },
    ChoiceMeta{ 3, "250 ms transmission rate", "_250_ms_transmission_rate" },
    ChoiceMeta{ 4, "100 ms transmission rate", "_100_ms_transmission_rate" },
    ChoiceMeta{ 5, "50 ms transmission rate", "_50_ms_transmission_rate" },
    ChoiceMeta{ 6, "20 ms transmission rate", "_20_ms_transmission_rate" },
    ChoiceMeta{ 7, "Use standard TSC1 transmission rates of 10 ms to engine", "use_standard_tsc1_transmission_rates_of_10_ms_to_engine" }
} };

constexpr auto to_tsc1_31__tsc1transrate(std::uint8_t raw)
    -> std::expected<Tsc131Tsc1transrateState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc131Tsc1transrateState::_1000_ms_transmission_rate;
        case static_cast<std::uint8_t>(1):
            return Tsc131Tsc1transrateState::_750_ms_transmission_rate;
        case static_cast<std::uint8_t>(2):
            return Tsc131Tsc1transrateState::_500_ms_transmission_rate;
        case static_cast<std::uint8_t>(3):
            return Tsc131Tsc1transrateState::_250_ms_transmission_rate;
        case static_cast<std::uint8_t>(4):
            return Tsc131Tsc1transrateState::_100_ms_transmission_rate;
        case static_cast<std::uint8_t>(5):
            return Tsc131Tsc1transrateState::_50_ms_transmission_rate;
        case static_cast<std::uint8_t>(6):
            return Tsc131Tsc1transrateState::_20_ms_transmission_rate;
        case static_cast<std::uint8_t>(7):
            return Tsc131Tsc1transrateState::use_standard_tsc1_transmission_rates_of_10_ms_to_engine;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc131Tsc1transrateState value) -> std::string_view {
    switch (value) {
        case Tsc131Tsc1transrateState::_1000_ms_transmission_rate:
            return "1000 ms transmission rate";
        case Tsc131Tsc1transrateState::_750_ms_transmission_rate:
            return "750 ms transmission rate";
        case Tsc131Tsc1transrateState::_500_ms_transmission_rate:
            return "500 ms transmission rate";
        case Tsc131Tsc1transrateState::_250_ms_transmission_rate:
            return "250 ms transmission rate";
        case Tsc131Tsc1transrateState::_100_ms_transmission_rate:
            return "100 ms transmission rate";
        case Tsc131Tsc1transrateState::_50_ms_transmission_rate:
            return "50 ms transmission rate";
        case Tsc131Tsc1transrateState::_20_ms_transmission_rate:
            return "20 ms transmission rate";
        case Tsc131Tsc1transrateState::use_standard_tsc1_transmission_rates_of_10_ms_to_engine:
            return "Use standard TSC1 transmission rates of 10 ms to engine";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc131Tsc1transrateState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_31__tsc1transrate(const ValueStore& store) -> std::optional<Tsc131Tsc1transrateState> {
    auto raw = store.template get<SignalId::tsc1_31__tsc1transrate>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_31__tsc1transrate(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc131Tsc1ctrlpurposeState : std::uint8_t {
    p1_accelerator_pedal_operator_selection = 0,
    p2_cruise_control = 1,
    p3_pto_governor = 2,
    p4_road_speed_governor = 3,
    p5_engine_protection = 4,
    p6_transient_optimized_torque_limit = 5,
    p7_automated_driving_system_input = 6,
    p32_temporary_powertrain_control = 31
};

inline constexpr std::array<ChoiceMeta, 8> kTsc131Tsc1ctrlpurposeStateChoices{ {
    ChoiceMeta{ 0, "P1 = Accelerator Pedal/Operator Selection", "p1_accelerator_pedal_operator_selection" },
    ChoiceMeta{ 1, "P2 = Cruise Control", "p2_cruise_control" },
    ChoiceMeta{ 2, "P3 = PTO Governor", "p3_pto_governor" },
    ChoiceMeta{ 3, "P4 = Road Speed Governor", "p4_road_speed_governor" },
    ChoiceMeta{ 4, "P5 = Engine Protection", "p5_engine_protection" },
    ChoiceMeta{ 5, "P6 = Transient-Optimized Torque Limit", "p6_transient_optimized_torque_limit" },
    ChoiceMeta{ 6, "P7 = Automated Driving System Input", "p7_automated_driving_system_input" },
    ChoiceMeta{ 31, "P32 = Temporary Powertrain Control", "p32_temporary_powertrain_control" }
} };

constexpr auto to_tsc1_31__tsc1ctrlpurpose(std::uint8_t raw)
    -> std::expected<Tsc131Tsc1ctrlpurposeState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc131Tsc1ctrlpurposeState::p1_accelerator_pedal_operator_selection;
        case static_cast<std::uint8_t>(1):
            return Tsc131Tsc1ctrlpurposeState::p2_cruise_control;
        case static_cast<std::uint8_t>(2):
            return Tsc131Tsc1ctrlpurposeState::p3_pto_governor;
        case static_cast<std::uint8_t>(3):
            return Tsc131Tsc1ctrlpurposeState::p4_road_speed_governor;
        case static_cast<std::uint8_t>(4):
            return Tsc131Tsc1ctrlpurposeState::p5_engine_protection;
        case static_cast<std::uint8_t>(5):
            return Tsc131Tsc1ctrlpurposeState::p6_transient_optimized_torque_limit;
        case static_cast<std::uint8_t>(6):
            return Tsc131Tsc1ctrlpurposeState::p7_automated_driving_system_input;
        case static_cast<std::uint8_t>(31):
            return Tsc131Tsc1ctrlpurposeState::p32_temporary_powertrain_control;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc131Tsc1ctrlpurposeState value) -> std::string_view {
    switch (value) {
        case Tsc131Tsc1ctrlpurposeState::p1_accelerator_pedal_operator_selection:
            return "P1 = Accelerator Pedal/Operator Selection";
        case Tsc131Tsc1ctrlpurposeState::p2_cruise_control:
            return "P2 = Cruise Control";
        case Tsc131Tsc1ctrlpurposeState::p3_pto_governor:
            return "P3 = PTO Governor";
        case Tsc131Tsc1ctrlpurposeState::p4_road_speed_governor:
            return "P4 = Road Speed Governor";
        case Tsc131Tsc1ctrlpurposeState::p5_engine_protection:
            return "P5 = Engine Protection";
        case Tsc131Tsc1ctrlpurposeState::p6_transient_optimized_torque_limit:
            return "P6 = Transient-Optimized Torque Limit";
        case Tsc131Tsc1ctrlpurposeState::p7_automated_driving_system_input:
            return "P7 = Automated Driving System Input";
        case Tsc131Tsc1ctrlpurposeState::p32_temporary_powertrain_control:
            return "P32 = Temporary Powertrain Control";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc131Tsc1ctrlpurposeState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_31__tsc1ctrlpurpose(const ValueStore& store) -> std::optional<Tsc131Tsc1ctrlpurposeState> {
    auto raw = store.template get<SignalId::tsc1_31__tsc1ctrlpurpose>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_31__tsc1ctrlpurpose(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc131EngrequestedtorquehighresolutionState : std::uint8_t {
    _0_000 = 0,
    _0_125 = 1,
    _0_875 = 7
};

inline constexpr std::array<ChoiceMeta, 3> kTsc131EngrequestedtorquehighresolutionStateChoices{ {
    ChoiceMeta{ 0, "+0.000%", "_0_000" },
    ChoiceMeta{ 1, "+0.125%", "_0_125" },
    ChoiceMeta{ 7, "+0.875%", "_0_875" }
} };

constexpr auto to_tsc1_31__engrequestedtorquehighresolution(std::uint8_t raw)
    -> std::expected<Tsc131EngrequestedtorquehighresolutionState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc131EngrequestedtorquehighresolutionState::_0_000;
        case static_cast<std::uint8_t>(1):
            return Tsc131EngrequestedtorquehighresolutionState::_0_125;
        case static_cast<std::uint8_t>(7):
            return Tsc131EngrequestedtorquehighresolutionState::_0_875;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc131EngrequestedtorquehighresolutionState value) -> std::string_view {
    switch (value) {
        case Tsc131EngrequestedtorquehighresolutionState::_0_000:
            return "+0.000%";
        case Tsc131EngrequestedtorquehighresolutionState::_0_125:
            return "+0.125%";
        case Tsc131EngrequestedtorquehighresolutionState::_0_875:
            return "+0.875%";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc131EngrequestedtorquehighresolutionState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_31__engrequestedtorquehighresolution(const ValueStore& store) -> std::optional<Tsc131EngrequestedtorquehighresolutionState> {
    auto raw = store.template get<SignalId::tsc1_31__engrequestedtorquehighresolution>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_31__engrequestedtorquehighresolution(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc103EngoverridectrlmodeState : std::uint8_t {
    override_disabled = 0,
    speed_control = 1,
    torque_control = 2,
    speed_torque_limit_control = 3
};

inline constexpr std::array<ChoiceMeta, 4> kTsc103EngoverridectrlmodeStateChoices{ {
    ChoiceMeta{ 0, "Override disabled", "override_disabled" },
    ChoiceMeta{ 1, "Speed control", "speed_control" },
    ChoiceMeta{ 2, "Torque control", "torque_control" },
    ChoiceMeta{ 3, "Speed/torque limit control", "speed_torque_limit_control" }
} };

constexpr auto to_tsc1_03__engoverridectrlmode(std::uint8_t raw)
    -> std::expected<Tsc103EngoverridectrlmodeState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc103EngoverridectrlmodeState::override_disabled;
        case static_cast<std::uint8_t>(1):
            return Tsc103EngoverridectrlmodeState::speed_control;
        case static_cast<std::uint8_t>(2):
            return Tsc103EngoverridectrlmodeState::torque_control;
        case static_cast<std::uint8_t>(3):
            return Tsc103EngoverridectrlmodeState::speed_torque_limit_control;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc103EngoverridectrlmodeState value) -> std::string_view {
    switch (value) {
        case Tsc103EngoverridectrlmodeState::override_disabled:
            return "Override disabled";
        case Tsc103EngoverridectrlmodeState::speed_control:
            return "Speed control";
        case Tsc103EngoverridectrlmodeState::torque_control:
            return "Torque control";
        case Tsc103EngoverridectrlmodeState::speed_torque_limit_control:
            return "Speed/torque limit control";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc103EngoverridectrlmodeState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_03__engoverridectrlmode(const ValueStore& store) -> std::optional<Tsc103EngoverridectrlmodeState> {
    auto raw = store.template get<SignalId::tsc1_03__engoverridectrlmode>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_03__engoverridectrlmode(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc103EngrequestedspeedctrlconditionsState : std::uint8_t {
    transient_optimized_for_driveline_disengaged_and_non_lockup_conditions = 0,
    stability_optimized_for_driveline_disengaged_and_non_lockup_conditions = 1,
    stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_1 = 2,
    stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_2 = 3
};

inline constexpr std::array<ChoiceMeta, 4> kTsc103EngrequestedspeedctrlconditionsStateChoices{ {
    ChoiceMeta{ 0, "Transient Optimized for driveline disengaged and non-lockup conditions", "transient_optimized_for_driveline_disengaged_and_non_lockup_conditions" },
    ChoiceMeta{ 1, "Stability Optimized for driveline disengaged and non-lockup conditions", "stability_optimized_for_driveline_disengaged_and_non_lockup_conditions" },
    ChoiceMeta{ 2, "Stability Optimized for driveline engaged and/or in lockup condition 1", "stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_1" },
    ChoiceMeta{ 3, "Stability Optimized for driveline engaged and/or in lockup condition 2", "stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_2" }
} };

constexpr auto to_tsc1_03__engrequestedspeedctrlconditions(std::uint8_t raw)
    -> std::expected<Tsc103EngrequestedspeedctrlconditionsState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc103EngrequestedspeedctrlconditionsState::transient_optimized_for_driveline_disengaged_and_non_lockup_conditions;
        case static_cast<std::uint8_t>(1):
            return Tsc103EngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_disengaged_and_non_lockup_conditions;
        case static_cast<std::uint8_t>(2):
            return Tsc103EngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_1;
        case static_cast<std::uint8_t>(3):
            return Tsc103EngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_2;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc103EngrequestedspeedctrlconditionsState value) -> std::string_view {
    switch (value) {
        case Tsc103EngrequestedspeedctrlconditionsState::transient_optimized_for_driveline_disengaged_and_non_lockup_conditions:
            return "Transient Optimized for driveline disengaged and non-lockup conditions";
        case Tsc103EngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_disengaged_and_non_lockup_conditions:
            return "Stability Optimized for driveline disengaged and non-lockup conditions";
        case Tsc103EngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_1:
            return "Stability Optimized for driveline engaged and/or in lockup condition 1";
        case Tsc103EngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_2:
            return "Stability Optimized for driveline engaged and/or in lockup condition 2";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc103EngrequestedspeedctrlconditionsState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_03__engrequestedspeedctrlconditions(const ValueStore& store) -> std::optional<Tsc103EngrequestedspeedctrlconditionsState> {
    auto raw = store.template get<SignalId::tsc1_03__engrequestedspeedctrlconditions>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_03__engrequestedspeedctrlconditions(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc103OverridectrlmodepriorityState : std::uint8_t {
    highest_priority = 0,
    high_priority = 1,
    medium_priority = 2,
    low_priority = 3
};

inline constexpr std::array<ChoiceMeta, 4> kTsc103OverridectrlmodepriorityStateChoices{ {
    ChoiceMeta{ 0, "Highest priority", "highest_priority" },
    ChoiceMeta{ 1, "High priority", "high_priority" },
    ChoiceMeta{ 2, "Medium priority", "medium_priority" },
    ChoiceMeta{ 3, "Low priority", "low_priority" }
} };

constexpr auto to_tsc1_03__overridectrlmodepriority(std::uint8_t raw)
    -> std::expected<Tsc103OverridectrlmodepriorityState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc103OverridectrlmodepriorityState::highest_priority;
        case static_cast<std::uint8_t>(1):
            return Tsc103OverridectrlmodepriorityState::high_priority;
        case static_cast<std::uint8_t>(2):
            return Tsc103OverridectrlmodepriorityState::medium_priority;
        case static_cast<std::uint8_t>(3):
            return Tsc103OverridectrlmodepriorityState::low_priority;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc103OverridectrlmodepriorityState value) -> std::string_view {
    switch (value) {
        case Tsc103OverridectrlmodepriorityState::highest_priority:
            return "Highest priority";
        case Tsc103OverridectrlmodepriorityState::high_priority:
            return "High priority";
        case Tsc103OverridectrlmodepriorityState::medium_priority:
            return "Medium priority";
        case Tsc103OverridectrlmodepriorityState::low_priority:
            return "Low priority";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc103OverridectrlmodepriorityState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_03__overridectrlmodepriority(const ValueStore& store) -> std::optional<Tsc103OverridectrlmodepriorityState> {
    auto raw = store.template get<SignalId::tsc1_03__overridectrlmodepriority>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_03__overridectrlmodepriority(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc103Tsc1transrateState : std::uint8_t {
    _1000_ms_transmission_rate = 0,
    _750_ms_transmission_rate = 1,
    _500_ms_transmission_rate = 2,
    _250_ms_transmission_rate = 3,
    _100_ms_transmission_rate = 4,
    _50_ms_transmission_rate = 5,
    _20_ms_transmission_rate = 6,
    use_standard_tsc1_transmission_rates_of_10_ms_to_engine = 7
};

inline constexpr std::array<ChoiceMeta, 8> kTsc103Tsc1transrateStateChoices{ {
    ChoiceMeta{ 0, "1000 ms transmission rate", "_1000_ms_transmission_rate" },
    ChoiceMeta{ 1, "750 ms transmission rate", "_750_ms_transmission_rate" },
    ChoiceMeta{ 2, "500 ms transmission rate", "_500_ms_transmission_rate" },
    ChoiceMeta{ 3, "250 ms transmission rate", "_250_ms_transmission_rate" },
    ChoiceMeta{ 4, "100 ms transmission rate", "_100_ms_transmission_rate" },
    ChoiceMeta{ 5, "50 ms transmission rate", "_50_ms_transmission_rate" },
    ChoiceMeta{ 6, "20 ms transmission rate", "_20_ms_transmission_rate" },
    ChoiceMeta{ 7, "Use standard TSC1 transmission rates of 10 ms to engine", "use_standard_tsc1_transmission_rates_of_10_ms_to_engine" }
} };

constexpr auto to_tsc1_03__tsc1transrate(std::uint8_t raw)
    -> std::expected<Tsc103Tsc1transrateState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc103Tsc1transrateState::_1000_ms_transmission_rate;
        case static_cast<std::uint8_t>(1):
            return Tsc103Tsc1transrateState::_750_ms_transmission_rate;
        case static_cast<std::uint8_t>(2):
            return Tsc103Tsc1transrateState::_500_ms_transmission_rate;
        case static_cast<std::uint8_t>(3):
            return Tsc103Tsc1transrateState::_250_ms_transmission_rate;
        case static_cast<std::uint8_t>(4):
            return Tsc103Tsc1transrateState::_100_ms_transmission_rate;
        case static_cast<std::uint8_t>(5):
            return Tsc103Tsc1transrateState::_50_ms_transmission_rate;
        case static_cast<std::uint8_t>(6):
            return Tsc103Tsc1transrateState::_20_ms_transmission_rate;
        case static_cast<std::uint8_t>(7):
            return Tsc103Tsc1transrateState::use_standard_tsc1_transmission_rates_of_10_ms_to_engine;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc103Tsc1transrateState value) -> std::string_view {
    switch (value) {
        case Tsc103Tsc1transrateState::_1000_ms_transmission_rate:
            return "1000 ms transmission rate";
        case Tsc103Tsc1transrateState::_750_ms_transmission_rate:
            return "750 ms transmission rate";
        case Tsc103Tsc1transrateState::_500_ms_transmission_rate:
            return "500 ms transmission rate";
        case Tsc103Tsc1transrateState::_250_ms_transmission_rate:
            return "250 ms transmission rate";
        case Tsc103Tsc1transrateState::_100_ms_transmission_rate:
            return "100 ms transmission rate";
        case Tsc103Tsc1transrateState::_50_ms_transmission_rate:
            return "50 ms transmission rate";
        case Tsc103Tsc1transrateState::_20_ms_transmission_rate:
            return "20 ms transmission rate";
        case Tsc103Tsc1transrateState::use_standard_tsc1_transmission_rates_of_10_ms_to_engine:
            return "Use standard TSC1 transmission rates of 10 ms to engine";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc103Tsc1transrateState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_03__tsc1transrate(const ValueStore& store) -> std::optional<Tsc103Tsc1transrateState> {
    auto raw = store.template get<SignalId::tsc1_03__tsc1transrate>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_03__tsc1transrate(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc103Tsc1ctrlpurposeState : std::uint8_t {
    p1_accelerator_pedal_operator_selection = 0,
    p2_cruise_control = 1,
    p3_pto_governor = 2,
    p4_road_speed_governor = 3,
    p5_engine_protection = 4,
    p6_transient_optimized_torque_limit = 5,
    p7_automated_driving_system_input = 6,
    p32_temporary_powertrain_control = 31
};

inline constexpr std::array<ChoiceMeta, 8> kTsc103Tsc1ctrlpurposeStateChoices{ {
    ChoiceMeta{ 0, "P1 = Accelerator Pedal/Operator Selection", "p1_accelerator_pedal_operator_selection" },
    ChoiceMeta{ 1, "P2 = Cruise Control", "p2_cruise_control" },
    ChoiceMeta{ 2, "P3 = PTO Governor", "p3_pto_governor" },
    ChoiceMeta{ 3, "P4 = Road Speed Governor", "p4_road_speed_governor" },
    ChoiceMeta{ 4, "P5 = Engine Protection", "p5_engine_protection" },
    ChoiceMeta{ 5, "P6 = Transient-Optimized Torque Limit", "p6_transient_optimized_torque_limit" },
    ChoiceMeta{ 6, "P7 = Automated Driving System Input", "p7_automated_driving_system_input" },
    ChoiceMeta{ 31, "P32 = Temporary Powertrain Control", "p32_temporary_powertrain_control" }
} };

constexpr auto to_tsc1_03__tsc1ctrlpurpose(std::uint8_t raw)
    -> std::expected<Tsc103Tsc1ctrlpurposeState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc103Tsc1ctrlpurposeState::p1_accelerator_pedal_operator_selection;
        case static_cast<std::uint8_t>(1):
            return Tsc103Tsc1ctrlpurposeState::p2_cruise_control;
        case static_cast<std::uint8_t>(2):
            return Tsc103Tsc1ctrlpurposeState::p3_pto_governor;
        case static_cast<std::uint8_t>(3):
            return Tsc103Tsc1ctrlpurposeState::p4_road_speed_governor;
        case static_cast<std::uint8_t>(4):
            return Tsc103Tsc1ctrlpurposeState::p5_engine_protection;
        case static_cast<std::uint8_t>(5):
            return Tsc103Tsc1ctrlpurposeState::p6_transient_optimized_torque_limit;
        case static_cast<std::uint8_t>(6):
            return Tsc103Tsc1ctrlpurposeState::p7_automated_driving_system_input;
        case static_cast<std::uint8_t>(31):
            return Tsc103Tsc1ctrlpurposeState::p32_temporary_powertrain_control;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc103Tsc1ctrlpurposeState value) -> std::string_view {
    switch (value) {
        case Tsc103Tsc1ctrlpurposeState::p1_accelerator_pedal_operator_selection:
            return "P1 = Accelerator Pedal/Operator Selection";
        case Tsc103Tsc1ctrlpurposeState::p2_cruise_control:
            return "P2 = Cruise Control";
        case Tsc103Tsc1ctrlpurposeState::p3_pto_governor:
            return "P3 = PTO Governor";
        case Tsc103Tsc1ctrlpurposeState::p4_road_speed_governor:
            return "P4 = Road Speed Governor";
        case Tsc103Tsc1ctrlpurposeState::p5_engine_protection:
            return "P5 = Engine Protection";
        case Tsc103Tsc1ctrlpurposeState::p6_transient_optimized_torque_limit:
            return "P6 = Transient-Optimized Torque Limit";
        case Tsc103Tsc1ctrlpurposeState::p7_automated_driving_system_input:
            return "P7 = Automated Driving System Input";
        case Tsc103Tsc1ctrlpurposeState::p32_temporary_powertrain_control:
            return "P32 = Temporary Powertrain Control";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc103Tsc1ctrlpurposeState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_03__tsc1ctrlpurpose(const ValueStore& store) -> std::optional<Tsc103Tsc1ctrlpurposeState> {
    auto raw = store.template get<SignalId::tsc1_03__tsc1ctrlpurpose>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_03__tsc1ctrlpurpose(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc103EngrequestedtorquehighresolutionState : std::uint8_t {
    _0_000 = 0,
    _0_125 = 1,
    _0_875 = 7
};

inline constexpr std::array<ChoiceMeta, 3> kTsc103EngrequestedtorquehighresolutionStateChoices{ {
    ChoiceMeta{ 0, "+0.000%", "_0_000" },
    ChoiceMeta{ 1, "+0.125%", "_0_125" },
    ChoiceMeta{ 7, "+0.875%", "_0_875" }
} };

constexpr auto to_tsc1_03__engrequestedtorquehighresolution(std::uint8_t raw)
    -> std::expected<Tsc103EngrequestedtorquehighresolutionState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc103EngrequestedtorquehighresolutionState::_0_000;
        case static_cast<std::uint8_t>(1):
            return Tsc103EngrequestedtorquehighresolutionState::_0_125;
        case static_cast<std::uint8_t>(7):
            return Tsc103EngrequestedtorquehighresolutionState::_0_875;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc103EngrequestedtorquehighresolutionState value) -> std::string_view {
    switch (value) {
        case Tsc103EngrequestedtorquehighresolutionState::_0_000:
            return "+0.000%";
        case Tsc103EngrequestedtorquehighresolutionState::_0_125:
            return "+0.125%";
        case Tsc103EngrequestedtorquehighresolutionState::_0_875:
            return "+0.875%";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc103EngrequestedtorquehighresolutionState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_03__engrequestedtorquehighresolution(const ValueStore& store) -> std::optional<Tsc103EngrequestedtorquehighresolutionState> {
    auto raw = store.template get<SignalId::tsc1_03__engrequestedtorquehighresolution>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_03__engrequestedtorquehighresolution(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc10bEngoverridectrlmodeState : std::uint8_t {
    override_disabled = 0,
    speed_control = 1,
    torque_control = 2,
    speed_torque_limit_control = 3
};

inline constexpr std::array<ChoiceMeta, 4> kTsc10bEngoverridectrlmodeStateChoices{ {
    ChoiceMeta{ 0, "Override disabled", "override_disabled" },
    ChoiceMeta{ 1, "Speed control", "speed_control" },
    ChoiceMeta{ 2, "Torque control", "torque_control" },
    ChoiceMeta{ 3, "Speed/torque limit control", "speed_torque_limit_control" }
} };

constexpr auto to_tsc1_0b__engoverridectrlmode(std::uint8_t raw)
    -> std::expected<Tsc10bEngoverridectrlmodeState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc10bEngoverridectrlmodeState::override_disabled;
        case static_cast<std::uint8_t>(1):
            return Tsc10bEngoverridectrlmodeState::speed_control;
        case static_cast<std::uint8_t>(2):
            return Tsc10bEngoverridectrlmodeState::torque_control;
        case static_cast<std::uint8_t>(3):
            return Tsc10bEngoverridectrlmodeState::speed_torque_limit_control;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc10bEngoverridectrlmodeState value) -> std::string_view {
    switch (value) {
        case Tsc10bEngoverridectrlmodeState::override_disabled:
            return "Override disabled";
        case Tsc10bEngoverridectrlmodeState::speed_control:
            return "Speed control";
        case Tsc10bEngoverridectrlmodeState::torque_control:
            return "Torque control";
        case Tsc10bEngoverridectrlmodeState::speed_torque_limit_control:
            return "Speed/torque limit control";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc10bEngoverridectrlmodeState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_0b__engoverridectrlmode(const ValueStore& store) -> std::optional<Tsc10bEngoverridectrlmodeState> {
    auto raw = store.template get<SignalId::tsc1_0b__engoverridectrlmode>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_0b__engoverridectrlmode(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc10bEngrequestedspeedctrlconditionsState : std::uint8_t {
    transient_optimized_for_driveline_disengaged_and_non_lockup_conditions = 0,
    stability_optimized_for_driveline_disengaged_and_non_lockup_conditions = 1,
    stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_1 = 2,
    stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_2 = 3
};

inline constexpr std::array<ChoiceMeta, 4> kTsc10bEngrequestedspeedctrlconditionsStateChoices{ {
    ChoiceMeta{ 0, "Transient Optimized for driveline disengaged and non-lockup conditions", "transient_optimized_for_driveline_disengaged_and_non_lockup_conditions" },
    ChoiceMeta{ 1, "Stability Optimized for driveline disengaged and non-lockup conditions", "stability_optimized_for_driveline_disengaged_and_non_lockup_conditions" },
    ChoiceMeta{ 2, "Stability Optimized for driveline engaged and/or in lockup condition 1", "stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_1" },
    ChoiceMeta{ 3, "Stability Optimized for driveline engaged and/or in lockup condition 2", "stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_2" }
} };

constexpr auto to_tsc1_0b__engrequestedspeedctrlconditions(std::uint8_t raw)
    -> std::expected<Tsc10bEngrequestedspeedctrlconditionsState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc10bEngrequestedspeedctrlconditionsState::transient_optimized_for_driveline_disengaged_and_non_lockup_conditions;
        case static_cast<std::uint8_t>(1):
            return Tsc10bEngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_disengaged_and_non_lockup_conditions;
        case static_cast<std::uint8_t>(2):
            return Tsc10bEngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_1;
        case static_cast<std::uint8_t>(3):
            return Tsc10bEngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_2;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc10bEngrequestedspeedctrlconditionsState value) -> std::string_view {
    switch (value) {
        case Tsc10bEngrequestedspeedctrlconditionsState::transient_optimized_for_driveline_disengaged_and_non_lockup_conditions:
            return "Transient Optimized for driveline disengaged and non-lockup conditions";
        case Tsc10bEngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_disengaged_and_non_lockup_conditions:
            return "Stability Optimized for driveline disengaged and non-lockup conditions";
        case Tsc10bEngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_1:
            return "Stability Optimized for driveline engaged and/or in lockup condition 1";
        case Tsc10bEngrequestedspeedctrlconditionsState::stability_optimized_for_driveline_engaged_and_or_in_lockup_condition_2:
            return "Stability Optimized for driveline engaged and/or in lockup condition 2";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc10bEngrequestedspeedctrlconditionsState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_0b__engrequestedspeedctrlconditions(const ValueStore& store) -> std::optional<Tsc10bEngrequestedspeedctrlconditionsState> {
    auto raw = store.template get<SignalId::tsc1_0b__engrequestedspeedctrlconditions>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_0b__engrequestedspeedctrlconditions(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc10bOverridectrlmodepriorityState : std::uint8_t {
    highest_priority = 0,
    high_priority = 1,
    medium_priority = 2,
    low_priority = 3
};

inline constexpr std::array<ChoiceMeta, 4> kTsc10bOverridectrlmodepriorityStateChoices{ {
    ChoiceMeta{ 0, "Highest priority", "highest_priority" },
    ChoiceMeta{ 1, "High priority", "high_priority" },
    ChoiceMeta{ 2, "Medium priority", "medium_priority" },
    ChoiceMeta{ 3, "Low priority", "low_priority" }
} };

constexpr auto to_tsc1_0b__overridectrlmodepriority(std::uint8_t raw)
    -> std::expected<Tsc10bOverridectrlmodepriorityState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc10bOverridectrlmodepriorityState::highest_priority;
        case static_cast<std::uint8_t>(1):
            return Tsc10bOverridectrlmodepriorityState::high_priority;
        case static_cast<std::uint8_t>(2):
            return Tsc10bOverridectrlmodepriorityState::medium_priority;
        case static_cast<std::uint8_t>(3):
            return Tsc10bOverridectrlmodepriorityState::low_priority;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc10bOverridectrlmodepriorityState value) -> std::string_view {
    switch (value) {
        case Tsc10bOverridectrlmodepriorityState::highest_priority:
            return "Highest priority";
        case Tsc10bOverridectrlmodepriorityState::high_priority:
            return "High priority";
        case Tsc10bOverridectrlmodepriorityState::medium_priority:
            return "Medium priority";
        case Tsc10bOverridectrlmodepriorityState::low_priority:
            return "Low priority";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc10bOverridectrlmodepriorityState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_0b__overridectrlmodepriority(const ValueStore& store) -> std::optional<Tsc10bOverridectrlmodepriorityState> {
    auto raw = store.template get<SignalId::tsc1_0b__overridectrlmodepriority>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_0b__overridectrlmodepriority(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc10bTsc1transrateState : std::uint8_t {
    _1000_ms_transmission_rate = 0,
    _750_ms_transmission_rate = 1,
    _500_ms_transmission_rate = 2,
    _250_ms_transmission_rate = 3,
    _100_ms_transmission_rate = 4,
    _50_ms_transmission_rate = 5,
    _20_ms_transmission_rate = 6,
    use_standard_tsc1_transmission_rates_of_10_ms_to_engine = 7
};

inline constexpr std::array<ChoiceMeta, 8> kTsc10bTsc1transrateStateChoices{ {
    ChoiceMeta{ 0, "1000 ms transmission rate", "_1000_ms_transmission_rate" },
    ChoiceMeta{ 1, "750 ms transmission rate", "_750_ms_transmission_rate" },
    ChoiceMeta{ 2, "500 ms transmission rate", "_500_ms_transmission_rate" },
    ChoiceMeta{ 3, "250 ms transmission rate", "_250_ms_transmission_rate" },
    ChoiceMeta{ 4, "100 ms transmission rate", "_100_ms_transmission_rate" },
    ChoiceMeta{ 5, "50 ms transmission rate", "_50_ms_transmission_rate" },
    ChoiceMeta{ 6, "20 ms transmission rate", "_20_ms_transmission_rate" },
    ChoiceMeta{ 7, "Use standard TSC1 transmission rates of 10 ms to engine", "use_standard_tsc1_transmission_rates_of_10_ms_to_engine" }
} };

constexpr auto to_tsc1_0b__tsc1transrate(std::uint8_t raw)
    -> std::expected<Tsc10bTsc1transrateState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc10bTsc1transrateState::_1000_ms_transmission_rate;
        case static_cast<std::uint8_t>(1):
            return Tsc10bTsc1transrateState::_750_ms_transmission_rate;
        case static_cast<std::uint8_t>(2):
            return Tsc10bTsc1transrateState::_500_ms_transmission_rate;
        case static_cast<std::uint8_t>(3):
            return Tsc10bTsc1transrateState::_250_ms_transmission_rate;
        case static_cast<std::uint8_t>(4):
            return Tsc10bTsc1transrateState::_100_ms_transmission_rate;
        case static_cast<std::uint8_t>(5):
            return Tsc10bTsc1transrateState::_50_ms_transmission_rate;
        case static_cast<std::uint8_t>(6):
            return Tsc10bTsc1transrateState::_20_ms_transmission_rate;
        case static_cast<std::uint8_t>(7):
            return Tsc10bTsc1transrateState::use_standard_tsc1_transmission_rates_of_10_ms_to_engine;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc10bTsc1transrateState value) -> std::string_view {
    switch (value) {
        case Tsc10bTsc1transrateState::_1000_ms_transmission_rate:
            return "1000 ms transmission rate";
        case Tsc10bTsc1transrateState::_750_ms_transmission_rate:
            return "750 ms transmission rate";
        case Tsc10bTsc1transrateState::_500_ms_transmission_rate:
            return "500 ms transmission rate";
        case Tsc10bTsc1transrateState::_250_ms_transmission_rate:
            return "250 ms transmission rate";
        case Tsc10bTsc1transrateState::_100_ms_transmission_rate:
            return "100 ms transmission rate";
        case Tsc10bTsc1transrateState::_50_ms_transmission_rate:
            return "50 ms transmission rate";
        case Tsc10bTsc1transrateState::_20_ms_transmission_rate:
            return "20 ms transmission rate";
        case Tsc10bTsc1transrateState::use_standard_tsc1_transmission_rates_of_10_ms_to_engine:
            return "Use standard TSC1 transmission rates of 10 ms to engine";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc10bTsc1transrateState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_0b__tsc1transrate(const ValueStore& store) -> std::optional<Tsc10bTsc1transrateState> {
    auto raw = store.template get<SignalId::tsc1_0b__tsc1transrate>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_0b__tsc1transrate(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc10bTsc1ctrlpurposeState : std::uint8_t {
    p1_accelerator_pedal_operator_selection = 0,
    p2_cruise_control = 1,
    p3_pto_governor = 2,
    p4_road_speed_governor = 3,
    p5_engine_protection = 4,
    p6_transient_optimized_torque_limit = 5,
    p7_automated_driving_system_input = 6,
    p32_temporary_powertrain_control = 31
};

inline constexpr std::array<ChoiceMeta, 8> kTsc10bTsc1ctrlpurposeStateChoices{ {
    ChoiceMeta{ 0, "P1 = Accelerator Pedal/Operator Selection", "p1_accelerator_pedal_operator_selection" },
    ChoiceMeta{ 1, "P2 = Cruise Control", "p2_cruise_control" },
    ChoiceMeta{ 2, "P3 = PTO Governor", "p3_pto_governor" },
    ChoiceMeta{ 3, "P4 = Road Speed Governor", "p4_road_speed_governor" },
    ChoiceMeta{ 4, "P5 = Engine Protection", "p5_engine_protection" },
    ChoiceMeta{ 5, "P6 = Transient-Optimized Torque Limit", "p6_transient_optimized_torque_limit" },
    ChoiceMeta{ 6, "P7 = Automated Driving System Input", "p7_automated_driving_system_input" },
    ChoiceMeta{ 31, "P32 = Temporary Powertrain Control", "p32_temporary_powertrain_control" }
} };

constexpr auto to_tsc1_0b__tsc1ctrlpurpose(std::uint8_t raw)
    -> std::expected<Tsc10bTsc1ctrlpurposeState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc10bTsc1ctrlpurposeState::p1_accelerator_pedal_operator_selection;
        case static_cast<std::uint8_t>(1):
            return Tsc10bTsc1ctrlpurposeState::p2_cruise_control;
        case static_cast<std::uint8_t>(2):
            return Tsc10bTsc1ctrlpurposeState::p3_pto_governor;
        case static_cast<std::uint8_t>(3):
            return Tsc10bTsc1ctrlpurposeState::p4_road_speed_governor;
        case static_cast<std::uint8_t>(4):
            return Tsc10bTsc1ctrlpurposeState::p5_engine_protection;
        case static_cast<std::uint8_t>(5):
            return Tsc10bTsc1ctrlpurposeState::p6_transient_optimized_torque_limit;
        case static_cast<std::uint8_t>(6):
            return Tsc10bTsc1ctrlpurposeState::p7_automated_driving_system_input;
        case static_cast<std::uint8_t>(31):
            return Tsc10bTsc1ctrlpurposeState::p32_temporary_powertrain_control;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc10bTsc1ctrlpurposeState value) -> std::string_view {
    switch (value) {
        case Tsc10bTsc1ctrlpurposeState::p1_accelerator_pedal_operator_selection:
            return "P1 = Accelerator Pedal/Operator Selection";
        case Tsc10bTsc1ctrlpurposeState::p2_cruise_control:
            return "P2 = Cruise Control";
        case Tsc10bTsc1ctrlpurposeState::p3_pto_governor:
            return "P3 = PTO Governor";
        case Tsc10bTsc1ctrlpurposeState::p4_road_speed_governor:
            return "P4 = Road Speed Governor";
        case Tsc10bTsc1ctrlpurposeState::p5_engine_protection:
            return "P5 = Engine Protection";
        case Tsc10bTsc1ctrlpurposeState::p6_transient_optimized_torque_limit:
            return "P6 = Transient-Optimized Torque Limit";
        case Tsc10bTsc1ctrlpurposeState::p7_automated_driving_system_input:
            return "P7 = Automated Driving System Input";
        case Tsc10bTsc1ctrlpurposeState::p32_temporary_powertrain_control:
            return "P32 = Temporary Powertrain Control";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc10bTsc1ctrlpurposeState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_0b__tsc1ctrlpurpose(const ValueStore& store) -> std::optional<Tsc10bTsc1ctrlpurposeState> {
    auto raw = store.template get<SignalId::tsc1_0b__tsc1ctrlpurpose>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_0b__tsc1ctrlpurpose(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Tsc10bEngrequestedtorquehighresolutionState : std::uint8_t {
    _0_000 = 0,
    _0_125 = 1,
    _0_875 = 7
};

inline constexpr std::array<ChoiceMeta, 3> kTsc10bEngrequestedtorquehighresolutionStateChoices{ {
    ChoiceMeta{ 0, "+0.000%", "_0_000" },
    ChoiceMeta{ 1, "+0.125%", "_0_125" },
    ChoiceMeta{ 7, "+0.875%", "_0_875" }
} };

constexpr auto to_tsc1_0b__engrequestedtorquehighresolution(std::uint8_t raw)
    -> std::expected<Tsc10bEngrequestedtorquehighresolutionState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Tsc10bEngrequestedtorquehighresolutionState::_0_000;
        case static_cast<std::uint8_t>(1):
            return Tsc10bEngrequestedtorquehighresolutionState::_0_125;
        case static_cast<std::uint8_t>(7):
            return Tsc10bEngrequestedtorquehighresolutionState::_0_875;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Tsc10bEngrequestedtorquehighresolutionState value) -> std::string_view {
    switch (value) {
        case Tsc10bEngrequestedtorquehighresolutionState::_0_000:
            return "+0.000%";
        case Tsc10bEngrequestedtorquehighresolutionState::_0_125:
            return "+0.125%";
        case Tsc10bEngrequestedtorquehighresolutionState::_0_875:
            return "+0.875%";
    }
    return "<unknown>";
}

constexpr auto to_raw(Tsc10bEngrequestedtorquehighresolutionState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tsc1_0b__engrequestedtorquehighresolution(const ValueStore& store) -> std::optional<Tsc10bEngrequestedtorquehighresolutionState> {
    auto raw = store.template get<SignalId::tsc1_0b__engrequestedtorquehighresolution>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tsc1_0b__engrequestedtorquehighresolution(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Dm07TestidentifierState : std::uint8_t {
    all_scaled_test_results = 247,
    command_standard_test = 249,
    last_measured_scaled_results = 250
};

inline constexpr std::array<ChoiceMeta, 3> kDm07TestidentifierStateChoices{ {
    ChoiceMeta{ 247, "All scaled test results", "all_scaled_test_results" },
    ChoiceMeta{ 249, "Command Standard Test", "command_standard_test" },
    ChoiceMeta{ 250, "Last Measured Scaled Results", "last_measured_scaled_results" }
} };

constexpr auto to_dm07__testidentifier(std::uint8_t raw)
    -> std::expected<Dm07TestidentifierState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(247):
            return Dm07TestidentifierState::all_scaled_test_results;
        case static_cast<std::uint8_t>(249):
            return Dm07TestidentifierState::command_standard_test;
        case static_cast<std::uint8_t>(250):
            return Dm07TestidentifierState::last_measured_scaled_results;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Dm07TestidentifierState value) -> std::string_view {
    switch (value) {
        case Dm07TestidentifierState::all_scaled_test_results:
            return "All scaled test results";
        case Dm07TestidentifierState::command_standard_test:
            return "Command Standard Test";
        case Dm07TestidentifierState::last_measured_scaled_results:
            return "Last Measured Scaled Results";
    }
    return "<unknown>";
}

constexpr auto to_raw(Dm07TestidentifierState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_dm07__testidentifier(const ValueStore& store) -> std::optional<Dm07TestidentifierState> {
    auto raw = store.template get<SignalId::dm07__testidentifier>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_dm07__testidentifier(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Dm07Failuremodeidentifier1State : std::uint8_t {
    above_normal_most_severe = 0,
    below_normal_most_severe = 1,
    data_erratic = 2,
    voltage_above_normal = 3,
    voltage_below_normal = 4,
    current_below_normal = 5,
    current_above_normal = 6,
    mechanical_system_not_responding = 7,
    abnormal_frequency = 8,
    abnormal_update_rate = 9,
    abnormal_rate_of_change = 10,
    root_cause_not_known = 11,
    bad_intelligent_device = 12,
    out_of_calibration = 13,
    special_intstructions = 14,
    above_normal_least_severe = 15,
    above_normal_moderately_severe = 16,
    below_normal_least_severe = 17,
    below_normal_moderately_severe = 18,
    received_network_data_in_error = 19,
    not_available = 31
};

inline constexpr std::array<ChoiceMeta, 21> kDm07Failuremodeidentifier1StateChoices{ {
    ChoiceMeta{ 0, "Above normal (most severe)", "above_normal_most_severe" },
    ChoiceMeta{ 1, "Below normal (most severe)", "below_normal_most_severe" },
    ChoiceMeta{ 2, "Data erratic", "data_erratic" },
    ChoiceMeta{ 3, "Voltage above normal", "voltage_above_normal" },
    ChoiceMeta{ 4, "Voltage below normal", "voltage_below_normal" },
    ChoiceMeta{ 5, "Current below normal", "current_below_normal" },
    ChoiceMeta{ 6, "Current above normal", "current_above_normal" },
    ChoiceMeta{ 7, "Mechanical system not responding", "mechanical_system_not_responding" },
    ChoiceMeta{ 8, "Abnormal frequency", "abnormal_frequency" },
    ChoiceMeta{ 9, "Abnormal update rate", "abnormal_update_rate" },
    ChoiceMeta{ 10, "Abnormal rate of change", "abnormal_rate_of_change" },
    ChoiceMeta{ 11, "Root cause not known", "root_cause_not_known" },
    ChoiceMeta{ 12, "Bad intelligent device", "bad_intelligent_device" },
    ChoiceMeta{ 13, "Out of calibration", "out_of_calibration" },
    ChoiceMeta{ 14, "Special intstructions", "special_intstructions" },
    ChoiceMeta{ 15, "Above normal (least severe)", "above_normal_least_severe" },
    ChoiceMeta{ 16, "Above normal (moderately severe)", "above_normal_moderately_severe" },
    ChoiceMeta{ 17, "Below normal (least severe)", "below_normal_least_severe" },
    ChoiceMeta{ 18, "Below normal (moderately severe)", "below_normal_moderately_severe" },
    ChoiceMeta{ 19, "Received network data in error", "received_network_data_in_error" },
    ChoiceMeta{ 31, "Not available", "not_available" }
} };

constexpr auto to_dm07__failuremodeidentifier1(std::uint8_t raw)
    -> std::expected<Dm07Failuremodeidentifier1State, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Dm07Failuremodeidentifier1State::above_normal_most_severe;
        case static_cast<std::uint8_t>(1):
            return Dm07Failuremodeidentifier1State::below_normal_most_severe;
        case static_cast<std::uint8_t>(2):
            return Dm07Failuremodeidentifier1State::data_erratic;
        case static_cast<std::uint8_t>(3):
            return Dm07Failuremodeidentifier1State::voltage_above_normal;
        case static_cast<std::uint8_t>(4):
            return Dm07Failuremodeidentifier1State::voltage_below_normal;
        case static_cast<std::uint8_t>(5):
            return Dm07Failuremodeidentifier1State::current_below_normal;
        case static_cast<std::uint8_t>(6):
            return Dm07Failuremodeidentifier1State::current_above_normal;
        case static_cast<std::uint8_t>(7):
            return Dm07Failuremodeidentifier1State::mechanical_system_not_responding;
        case static_cast<std::uint8_t>(8):
            return Dm07Failuremodeidentifier1State::abnormal_frequency;
        case static_cast<std::uint8_t>(9):
            return Dm07Failuremodeidentifier1State::abnormal_update_rate;
        case static_cast<std::uint8_t>(10):
            return Dm07Failuremodeidentifier1State::abnormal_rate_of_change;
        case static_cast<std::uint8_t>(11):
            return Dm07Failuremodeidentifier1State::root_cause_not_known;
        case static_cast<std::uint8_t>(12):
            return Dm07Failuremodeidentifier1State::bad_intelligent_device;
        case static_cast<std::uint8_t>(13):
            return Dm07Failuremodeidentifier1State::out_of_calibration;
        case static_cast<std::uint8_t>(14):
            return Dm07Failuremodeidentifier1State::special_intstructions;
        case static_cast<std::uint8_t>(15):
            return Dm07Failuremodeidentifier1State::above_normal_least_severe;
        case static_cast<std::uint8_t>(16):
            return Dm07Failuremodeidentifier1State::above_normal_moderately_severe;
        case static_cast<std::uint8_t>(17):
            return Dm07Failuremodeidentifier1State::below_normal_least_severe;
        case static_cast<std::uint8_t>(18):
            return Dm07Failuremodeidentifier1State::below_normal_moderately_severe;
        case static_cast<std::uint8_t>(19):
            return Dm07Failuremodeidentifier1State::received_network_data_in_error;
        case static_cast<std::uint8_t>(31):
            return Dm07Failuremodeidentifier1State::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Dm07Failuremodeidentifier1State value) -> std::string_view {
    switch (value) {
        case Dm07Failuremodeidentifier1State::above_normal_most_severe:
            return "Above normal (most severe)";
        case Dm07Failuremodeidentifier1State::below_normal_most_severe:
            return "Below normal (most severe)";
        case Dm07Failuremodeidentifier1State::data_erratic:
            return "Data erratic";
        case Dm07Failuremodeidentifier1State::voltage_above_normal:
            return "Voltage above normal";
        case Dm07Failuremodeidentifier1State::voltage_below_normal:
            return "Voltage below normal";
        case Dm07Failuremodeidentifier1State::current_below_normal:
            return "Current below normal";
        case Dm07Failuremodeidentifier1State::current_above_normal:
            return "Current above normal";
        case Dm07Failuremodeidentifier1State::mechanical_system_not_responding:
            return "Mechanical system not responding";
        case Dm07Failuremodeidentifier1State::abnormal_frequency:
            return "Abnormal frequency";
        case Dm07Failuremodeidentifier1State::abnormal_update_rate:
            return "Abnormal update rate";
        case Dm07Failuremodeidentifier1State::abnormal_rate_of_change:
            return "Abnormal rate of change";
        case Dm07Failuremodeidentifier1State::root_cause_not_known:
            return "Root cause not known";
        case Dm07Failuremodeidentifier1State::bad_intelligent_device:
            return "Bad intelligent device";
        case Dm07Failuremodeidentifier1State::out_of_calibration:
            return "Out of calibration";
        case Dm07Failuremodeidentifier1State::special_intstructions:
            return "Special intstructions";
        case Dm07Failuremodeidentifier1State::above_normal_least_severe:
            return "Above normal (least severe)";
        case Dm07Failuremodeidentifier1State::above_normal_moderately_severe:
            return "Above normal (moderately severe)";
        case Dm07Failuremodeidentifier1State::below_normal_least_severe:
            return "Below normal (least severe)";
        case Dm07Failuremodeidentifier1State::below_normal_moderately_severe:
            return "Below normal (moderately severe)";
        case Dm07Failuremodeidentifier1State::received_network_data_in_error:
            return "Received network data in error";
        case Dm07Failuremodeidentifier1State::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Dm07Failuremodeidentifier1State value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_dm07__failuremodeidentifier1(const ValueStore& store) -> std::optional<Dm07Failuremodeidentifier1State> {
    auto raw = store.template get<SignalId::dm07__failuremodeidentifier1>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_dm07__failuremodeidentifier1(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Dm08TestidentifierState : std::uint8_t {
    all_scaled_test_results = 247,
    command_standard_test = 249,
    last_measured_scaled_results = 250
};

inline constexpr std::array<ChoiceMeta, 3> kDm08TestidentifierStateChoices{ {
    ChoiceMeta{ 247, "All scaled test results", "all_scaled_test_results" },
    ChoiceMeta{ 249, "Command Standard Test", "command_standard_test" },
    ChoiceMeta{ 250, "Last Measured Scaled Results", "last_measured_scaled_results" }
} };

constexpr auto to_dm08__testidentifier(std::uint8_t raw)
    -> std::expected<Dm08TestidentifierState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(247):
            return Dm08TestidentifierState::all_scaled_test_results;
        case static_cast<std::uint8_t>(249):
            return Dm08TestidentifierState::command_standard_test;
        case static_cast<std::uint8_t>(250):
            return Dm08TestidentifierState::last_measured_scaled_results;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Dm08TestidentifierState value) -> std::string_view {
    switch (value) {
        case Dm08TestidentifierState::all_scaled_test_results:
            return "All scaled test results";
        case Dm08TestidentifierState::command_standard_test:
            return "Command Standard Test";
        case Dm08TestidentifierState::last_measured_scaled_results:
            return "Last Measured Scaled Results";
    }
    return "<unknown>";
}

constexpr auto to_raw(Dm08TestidentifierState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_dm08__testidentifier(const ValueStore& store) -> std::optional<Dm08TestidentifierState> {
    auto raw = store.template get<SignalId::dm08__testidentifier>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_dm08__testidentifier(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Erc1ElectronicRetarderCntrlRetarderenablebrakeassistswitchState : std::uint8_t {
    retarder_brake_assist_disabled = 0,
    retarder_brake_assist_enabled = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kErc1ElectronicRetarderCntrlRetarderenablebrakeassistswitchStateChoices{ {
    ChoiceMeta{ 0, "Retarder, brake assist disabled", "retarder_brake_assist_disabled" },
    ChoiceMeta{ 1, "Retarder, brake assist enabled", "retarder_brake_assist_enabled" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch(std::uint8_t raw)
    -> std::expected<Erc1ElectronicRetarderCntrlRetarderenablebrakeassistswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Erc1ElectronicRetarderCntrlRetarderenablebrakeassistswitchState::retarder_brake_assist_disabled;
        case static_cast<std::uint8_t>(1):
            return Erc1ElectronicRetarderCntrlRetarderenablebrakeassistswitchState::retarder_brake_assist_enabled;
        case static_cast<std::uint8_t>(2):
            return Erc1ElectronicRetarderCntrlRetarderenablebrakeassistswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Erc1ElectronicRetarderCntrlRetarderenablebrakeassistswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Erc1ElectronicRetarderCntrlRetarderenablebrakeassistswitchState value) -> std::string_view {
    switch (value) {
        case Erc1ElectronicRetarderCntrlRetarderenablebrakeassistswitchState::retarder_brake_assist_disabled:
            return "Retarder, brake assist disabled";
        case Erc1ElectronicRetarderCntrlRetarderenablebrakeassistswitchState::retarder_brake_assist_enabled:
            return "Retarder, brake assist enabled";
        case Erc1ElectronicRetarderCntrlRetarderenablebrakeassistswitchState::error:
            return "Error";
        case Erc1ElectronicRetarderCntrlRetarderenablebrakeassistswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Erc1ElectronicRetarderCntrlRetarderenablebrakeassistswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch(const ValueStore& store) -> std::optional<Erc1ElectronicRetarderCntrlRetarderenablebrakeassistswitchState> {
    auto raw = store.template get<SignalId::erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_erc1_electronic_retarder_cntrl__retarderenablebrakeassistswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Erc1ElectronicRetarderCntrlRetarderenableshiftassistswitchState : std::uint8_t {
    retarder_shift_assist_disabled = 0,
    retarder_shift_assist_enabled = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kErc1ElectronicRetarderCntrlRetarderenableshiftassistswitchStateChoices{ {
    ChoiceMeta{ 0, "Retarder, shift assist disabled", "retarder_shift_assist_disabled" },
    ChoiceMeta{ 1, "Retarder, shift assist enabled", "retarder_shift_assist_enabled" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch(std::uint8_t raw)
    -> std::expected<Erc1ElectronicRetarderCntrlRetarderenableshiftassistswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Erc1ElectronicRetarderCntrlRetarderenableshiftassistswitchState::retarder_shift_assist_disabled;
        case static_cast<std::uint8_t>(1):
            return Erc1ElectronicRetarderCntrlRetarderenableshiftassistswitchState::retarder_shift_assist_enabled;
        case static_cast<std::uint8_t>(2):
            return Erc1ElectronicRetarderCntrlRetarderenableshiftassistswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Erc1ElectronicRetarderCntrlRetarderenableshiftassistswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Erc1ElectronicRetarderCntrlRetarderenableshiftassistswitchState value) -> std::string_view {
    switch (value) {
        case Erc1ElectronicRetarderCntrlRetarderenableshiftassistswitchState::retarder_shift_assist_disabled:
            return "Retarder, shift assist disabled";
        case Erc1ElectronicRetarderCntrlRetarderenableshiftassistswitchState::retarder_shift_assist_enabled:
            return "Retarder, shift assist enabled";
        case Erc1ElectronicRetarderCntrlRetarderenableshiftassistswitchState::error:
            return "Error";
        case Erc1ElectronicRetarderCntrlRetarderenableshiftassistswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Erc1ElectronicRetarderCntrlRetarderenableshiftassistswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch(const ValueStore& store) -> std::optional<Erc1ElectronicRetarderCntrlRetarderenableshiftassistswitchState> {
    auto raw = store.template get<SignalId::erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_erc1_electronic_retarder_cntrl__retarderenableshiftassistswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Erc1ElectronicRetarderCntrlEngcoolantloadincreaseState : std::uint8_t {
    no_coolant_load_increase = 0,
    coolant_load_increase_possible = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kErc1ElectronicRetarderCntrlEngcoolantloadincreaseStateChoices{ {
    ChoiceMeta{ 0, "No coolant load increase", "no_coolant_load_increase" },
    ChoiceMeta{ 1, "Coolant load increase possible", "coolant_load_increase_possible" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_erc1_electronic_retarder_cntrl__engcoolantloadincrease(std::uint8_t raw)
    -> std::expected<Erc1ElectronicRetarderCntrlEngcoolantloadincreaseState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Erc1ElectronicRetarderCntrlEngcoolantloadincreaseState::no_coolant_load_increase;
        case static_cast<std::uint8_t>(1):
            return Erc1ElectronicRetarderCntrlEngcoolantloadincreaseState::coolant_load_increase_possible;
        case static_cast<std::uint8_t>(2):
            return Erc1ElectronicRetarderCntrlEngcoolantloadincreaseState::error;
        case static_cast<std::uint8_t>(3):
            return Erc1ElectronicRetarderCntrlEngcoolantloadincreaseState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Erc1ElectronicRetarderCntrlEngcoolantloadincreaseState value) -> std::string_view {
    switch (value) {
        case Erc1ElectronicRetarderCntrlEngcoolantloadincreaseState::no_coolant_load_increase:
            return "No coolant load increase";
        case Erc1ElectronicRetarderCntrlEngcoolantloadincreaseState::coolant_load_increase_possible:
            return "Coolant load increase possible";
        case Erc1ElectronicRetarderCntrlEngcoolantloadincreaseState::error:
            return "Error";
        case Erc1ElectronicRetarderCntrlEngcoolantloadincreaseState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Erc1ElectronicRetarderCntrlEngcoolantloadincreaseState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_erc1_electronic_retarder_cntrl__engcoolantloadincrease(const ValueStore& store) -> std::optional<Erc1ElectronicRetarderCntrlEngcoolantloadincreaseState> {
    auto raw = store.template get<SignalId::erc1_electronic_retarder_cntrl__engcoolantloadincrease>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_erc1_electronic_retarder_cntrl__engcoolantloadincrease(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Erc1ElectronicRetarderCntrlRetarderrequestingbrakelightState : std::uint8_t {
    retarder_is_not_requesting_that_the_brake_lights_are_illuminated = 0,
    retarder_is_requesting_that_the_brake_lights_are_illuminated = 1,
    reserved = 2,
    not_available_take_no_action = 3
};

inline constexpr std::array<ChoiceMeta, 4> kErc1ElectronicRetarderCntrlRetarderrequestingbrakelightStateChoices{ {
    ChoiceMeta{ 0, "Retarder is not requesting that the brake lights are illuminated", "retarder_is_not_requesting_that_the_brake_lights_are_illuminated" },
    ChoiceMeta{ 1, "Retarder is requesting that the brake lights are illuminated", "retarder_is_requesting_that_the_brake_lights_are_illuminated" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Not available/Take no action", "not_available_take_no_action" }
} };

constexpr auto to_erc1_electronic_retarder_cntrl__retarderrequestingbrakelight(std::uint8_t raw)
    -> std::expected<Erc1ElectronicRetarderCntrlRetarderrequestingbrakelightState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Erc1ElectronicRetarderCntrlRetarderrequestingbrakelightState::retarder_is_not_requesting_that_the_brake_lights_are_illuminated;
        case static_cast<std::uint8_t>(1):
            return Erc1ElectronicRetarderCntrlRetarderrequestingbrakelightState::retarder_is_requesting_that_the_brake_lights_are_illuminated;
        case static_cast<std::uint8_t>(2):
            return Erc1ElectronicRetarderCntrlRetarderrequestingbrakelightState::reserved;
        case static_cast<std::uint8_t>(3):
            return Erc1ElectronicRetarderCntrlRetarderrequestingbrakelightState::not_available_take_no_action;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Erc1ElectronicRetarderCntrlRetarderrequestingbrakelightState value) -> std::string_view {
    switch (value) {
        case Erc1ElectronicRetarderCntrlRetarderrequestingbrakelightState::retarder_is_not_requesting_that_the_brake_lights_are_illuminated:
            return "Retarder is not requesting that the brake lights are illuminated";
        case Erc1ElectronicRetarderCntrlRetarderrequestingbrakelightState::retarder_is_requesting_that_the_brake_lights_are_illuminated:
            return "Retarder is requesting that the brake lights are illuminated";
        case Erc1ElectronicRetarderCntrlRetarderrequestingbrakelightState::reserved:
            return "Reserved";
        case Erc1ElectronicRetarderCntrlRetarderrequestingbrakelightState::not_available_take_no_action:
            return "Not available/Take no action";
    }
    return "<unknown>";
}

constexpr auto to_raw(Erc1ElectronicRetarderCntrlRetarderrequestingbrakelightState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_erc1_electronic_retarder_cntrl__retarderrequestingbrakelight(const ValueStore& store) -> std::optional<Erc1ElectronicRetarderCntrlRetarderrequestingbrakelightState> {
    auto raw = store.template get<SignalId::erc1_electronic_retarder_cntrl__retarderrequestingbrakelight>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_erc1_electronic_retarder_cntrl__retarderrequestingbrakelight(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Erc1ElectronicRetarderCntrlRetarderroadspeedlimitswitchState : std::uint8_t {
    road_speed_limiting_by_retarder_is_disabled = 0,
    road_speed_limiting_by_retarder_is_enabled = 1,
    error_indicator = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kErc1ElectronicRetarderCntrlRetarderroadspeedlimitswitchStateChoices{ {
    ChoiceMeta{ 0, "Road speed limiting by retarder is disabled", "road_speed_limiting_by_retarder_is_disabled" },
    ChoiceMeta{ 1, "Road speed limiting by retarder is enabled", "road_speed_limiting_by_retarder_is_enabled" },
    ChoiceMeta{ 2, "Error Indicator", "error_indicator" },
    ChoiceMeta{ 3, "Not Available", "not_available" }
} };

constexpr auto to_erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch(std::uint8_t raw)
    -> std::expected<Erc1ElectronicRetarderCntrlRetarderroadspeedlimitswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Erc1ElectronicRetarderCntrlRetarderroadspeedlimitswitchState::road_speed_limiting_by_retarder_is_disabled;
        case static_cast<std::uint8_t>(1):
            return Erc1ElectronicRetarderCntrlRetarderroadspeedlimitswitchState::road_speed_limiting_by_retarder_is_enabled;
        case static_cast<std::uint8_t>(2):
            return Erc1ElectronicRetarderCntrlRetarderroadspeedlimitswitchState::error_indicator;
        case static_cast<std::uint8_t>(3):
            return Erc1ElectronicRetarderCntrlRetarderroadspeedlimitswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Erc1ElectronicRetarderCntrlRetarderroadspeedlimitswitchState value) -> std::string_view {
    switch (value) {
        case Erc1ElectronicRetarderCntrlRetarderroadspeedlimitswitchState::road_speed_limiting_by_retarder_is_disabled:
            return "Road speed limiting by retarder is disabled";
        case Erc1ElectronicRetarderCntrlRetarderroadspeedlimitswitchState::road_speed_limiting_by_retarder_is_enabled:
            return "Road speed limiting by retarder is enabled";
        case Erc1ElectronicRetarderCntrlRetarderroadspeedlimitswitchState::error_indicator:
            return "Error Indicator";
        case Erc1ElectronicRetarderCntrlRetarderroadspeedlimitswitchState::not_available:
            return "Not Available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Erc1ElectronicRetarderCntrlRetarderroadspeedlimitswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch(const ValueStore& store) -> std::optional<Erc1ElectronicRetarderCntrlRetarderroadspeedlimitswitchState> {
    auto raw = store.template get<SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_erc1_electronic_retarder_cntrl__retarderroadspeedlimitswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Erc1ElectronicRetarderCntrlRetarderroadspeedexceededstatusState : std::uint8_t {
    road_speed_is_below_threshold = 0,
    road_speed_is_above_threshold_and_retarder_is_allowed_to_be_activated = 1,
    reserved = 2,
    don_t_care_take_no_action = 3
};

inline constexpr std::array<ChoiceMeta, 4> kErc1ElectronicRetarderCntrlRetarderroadspeedexceededstatusStateChoices{ {
    ChoiceMeta{ 0, "Road speed is below threshold", "road_speed_is_below_threshold" },
    ChoiceMeta{ 1, "Road speed is above threshold and retarder is allowed to be activated", "road_speed_is_above_threshold_and_retarder_is_allowed_to_be_activated" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Don't care/Take no action", "don_t_care_take_no_action" }
} };

constexpr auto to_erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus(std::uint8_t raw)
    -> std::expected<Erc1ElectronicRetarderCntrlRetarderroadspeedexceededstatusState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Erc1ElectronicRetarderCntrlRetarderroadspeedexceededstatusState::road_speed_is_below_threshold;
        case static_cast<std::uint8_t>(1):
            return Erc1ElectronicRetarderCntrlRetarderroadspeedexceededstatusState::road_speed_is_above_threshold_and_retarder_is_allowed_to_be_activated;
        case static_cast<std::uint8_t>(2):
            return Erc1ElectronicRetarderCntrlRetarderroadspeedexceededstatusState::reserved;
        case static_cast<std::uint8_t>(3):
            return Erc1ElectronicRetarderCntrlRetarderroadspeedexceededstatusState::don_t_care_take_no_action;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Erc1ElectronicRetarderCntrlRetarderroadspeedexceededstatusState value) -> std::string_view {
    switch (value) {
        case Erc1ElectronicRetarderCntrlRetarderroadspeedexceededstatusState::road_speed_is_below_threshold:
            return "Road speed is below threshold";
        case Erc1ElectronicRetarderCntrlRetarderroadspeedexceededstatusState::road_speed_is_above_threshold_and_retarder_is_allowed_to_be_activated:
            return "Road speed is above threshold and retarder is allowed to be activated";
        case Erc1ElectronicRetarderCntrlRetarderroadspeedexceededstatusState::reserved:
            return "Reserved";
        case Erc1ElectronicRetarderCntrlRetarderroadspeedexceededstatusState::don_t_care_take_no_action:
            return "Don't care/Take no action";
    }
    return "<unknown>";
}

constexpr auto to_raw(Erc1ElectronicRetarderCntrlRetarderroadspeedexceededstatusState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus(const ValueStore& store) -> std::optional<Erc1ElectronicRetarderCntrlRetarderroadspeedexceededstatusState> {
    auto raw = store.template get<SignalId::erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_erc1_electronic_retarder_cntrl__retarderroadspeedexceededstatus(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Etc1ElectronicTransCntrl1TransdrivelineengagedState : std::uint8_t {
    driveline_disengaged = 0,
    driveline_engaged = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEtc1ElectronicTransCntrl1TransdrivelineengagedStateChoices{ {
    ChoiceMeta{ 0, "Driveline disengaged", "driveline_disengaged" },
    ChoiceMeta{ 1, "Driveline engaged", "driveline_engaged" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_etc1_electronic_trans_cntrl_1__transdrivelineengaged(std::uint8_t raw)
    -> std::expected<Etc1ElectronicTransCntrl1TransdrivelineengagedState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Etc1ElectronicTransCntrl1TransdrivelineengagedState::driveline_disengaged;
        case static_cast<std::uint8_t>(1):
            return Etc1ElectronicTransCntrl1TransdrivelineengagedState::driveline_engaged;
        case static_cast<std::uint8_t>(2):
            return Etc1ElectronicTransCntrl1TransdrivelineengagedState::error;
        case static_cast<std::uint8_t>(3):
            return Etc1ElectronicTransCntrl1TransdrivelineengagedState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Etc1ElectronicTransCntrl1TransdrivelineengagedState value) -> std::string_view {
    switch (value) {
        case Etc1ElectronicTransCntrl1TransdrivelineengagedState::driveline_disengaged:
            return "Driveline disengaged";
        case Etc1ElectronicTransCntrl1TransdrivelineengagedState::driveline_engaged:
            return "Driveline engaged";
        case Etc1ElectronicTransCntrl1TransdrivelineengagedState::error:
            return "Error";
        case Etc1ElectronicTransCntrl1TransdrivelineengagedState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Etc1ElectronicTransCntrl1TransdrivelineengagedState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_etc1_electronic_trans_cntrl_1__transdrivelineengaged(const ValueStore& store) -> std::optional<Etc1ElectronicTransCntrl1TransdrivelineengagedState> {
    auto raw = store.template get<SignalId::etc1_electronic_trans_cntrl_1__transdrivelineengaged>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_etc1_electronic_trans_cntrl_1__transdrivelineengaged(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Etc1ElectronicTransCntrl1TrnstorqueconverterlockupengagedState : std::uint8_t {
    torque_converter_lockup_disengaged = 0,
    torque_converter_lockup_engaged = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEtc1ElectronicTransCntrl1TrnstorqueconverterlockupengagedStateChoices{ {
    ChoiceMeta{ 0, "Torque converter lockup disengaged", "torque_converter_lockup_disengaged" },
    ChoiceMeta{ 1, "Torque converter lockup engaged", "torque_converter_lockup_engaged" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged(std::uint8_t raw)
    -> std::expected<Etc1ElectronicTransCntrl1TrnstorqueconverterlockupengagedState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Etc1ElectronicTransCntrl1TrnstorqueconverterlockupengagedState::torque_converter_lockup_disengaged;
        case static_cast<std::uint8_t>(1):
            return Etc1ElectronicTransCntrl1TrnstorqueconverterlockupengagedState::torque_converter_lockup_engaged;
        case static_cast<std::uint8_t>(2):
            return Etc1ElectronicTransCntrl1TrnstorqueconverterlockupengagedState::error;
        case static_cast<std::uint8_t>(3):
            return Etc1ElectronicTransCntrl1TrnstorqueconverterlockupengagedState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Etc1ElectronicTransCntrl1TrnstorqueconverterlockupengagedState value) -> std::string_view {
    switch (value) {
        case Etc1ElectronicTransCntrl1TrnstorqueconverterlockupengagedState::torque_converter_lockup_disengaged:
            return "Torque converter lockup disengaged";
        case Etc1ElectronicTransCntrl1TrnstorqueconverterlockupengagedState::torque_converter_lockup_engaged:
            return "Torque converter lockup engaged";
        case Etc1ElectronicTransCntrl1TrnstorqueconverterlockupengagedState::error:
            return "Error";
        case Etc1ElectronicTransCntrl1TrnstorqueconverterlockupengagedState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Etc1ElectronicTransCntrl1TrnstorqueconverterlockupengagedState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged(const ValueStore& store) -> std::optional<Etc1ElectronicTransCntrl1TrnstorqueconverterlockupengagedState> {
    auto raw = store.template get<SignalId::etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_etc1_electronic_trans_cntrl_1__trnstorqueconverterlockupengaged(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Etc1ElectronicTransCntrl1TransshiftinprocessState : std::uint8_t {
    shift_is_not_in_process = 0,
    shift_in_process = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEtc1ElectronicTransCntrl1TransshiftinprocessStateChoices{ {
    ChoiceMeta{ 0, "Shift is not in process", "shift_is_not_in_process" },
    ChoiceMeta{ 1, "Shift in process", "shift_in_process" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_etc1_electronic_trans_cntrl_1__transshiftinprocess(std::uint8_t raw)
    -> std::expected<Etc1ElectronicTransCntrl1TransshiftinprocessState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Etc1ElectronicTransCntrl1TransshiftinprocessState::shift_is_not_in_process;
        case static_cast<std::uint8_t>(1):
            return Etc1ElectronicTransCntrl1TransshiftinprocessState::shift_in_process;
        case static_cast<std::uint8_t>(2):
            return Etc1ElectronicTransCntrl1TransshiftinprocessState::error;
        case static_cast<std::uint8_t>(3):
            return Etc1ElectronicTransCntrl1TransshiftinprocessState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Etc1ElectronicTransCntrl1TransshiftinprocessState value) -> std::string_view {
    switch (value) {
        case Etc1ElectronicTransCntrl1TransshiftinprocessState::shift_is_not_in_process:
            return "Shift is not in process";
        case Etc1ElectronicTransCntrl1TransshiftinprocessState::shift_in_process:
            return "Shift in process";
        case Etc1ElectronicTransCntrl1TransshiftinprocessState::error:
            return "Error";
        case Etc1ElectronicTransCntrl1TransshiftinprocessState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Etc1ElectronicTransCntrl1TransshiftinprocessState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_etc1_electronic_trans_cntrl_1__transshiftinprocess(const ValueStore& store) -> std::optional<Etc1ElectronicTransCntrl1TransshiftinprocessState> {
    auto raw = store.template get<SignalId::etc1_electronic_trans_cntrl_1__transshiftinprocess>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_etc1_electronic_trans_cntrl_1__transshiftinprocess(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Etc1ElectronicTransCntrl1TrnstrqcnvrtrlckptrnstninprocessState : std::uint8_t {
    transition_is_not_in_process = 0,
    transition_is_in_process = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEtc1ElectronicTransCntrl1TrnstrqcnvrtrlckptrnstninprocessStateChoices{ {
    ChoiceMeta{ 0, "Transition is not in process", "transition_is_not_in_process" },
    ChoiceMeta{ 1, "Transition is in process", "transition_is_in_process" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess(std::uint8_t raw)
    -> std::expected<Etc1ElectronicTransCntrl1TrnstrqcnvrtrlckptrnstninprocessState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Etc1ElectronicTransCntrl1TrnstrqcnvrtrlckptrnstninprocessState::transition_is_not_in_process;
        case static_cast<std::uint8_t>(1):
            return Etc1ElectronicTransCntrl1TrnstrqcnvrtrlckptrnstninprocessState::transition_is_in_process;
        case static_cast<std::uint8_t>(2):
            return Etc1ElectronicTransCntrl1TrnstrqcnvrtrlckptrnstninprocessState::error;
        case static_cast<std::uint8_t>(3):
            return Etc1ElectronicTransCntrl1TrnstrqcnvrtrlckptrnstninprocessState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Etc1ElectronicTransCntrl1TrnstrqcnvrtrlckptrnstninprocessState value) -> std::string_view {
    switch (value) {
        case Etc1ElectronicTransCntrl1TrnstrqcnvrtrlckptrnstninprocessState::transition_is_not_in_process:
            return "Transition is not in process";
        case Etc1ElectronicTransCntrl1TrnstrqcnvrtrlckptrnstninprocessState::transition_is_in_process:
            return "Transition is in process";
        case Etc1ElectronicTransCntrl1TrnstrqcnvrtrlckptrnstninprocessState::error:
            return "Error";
        case Etc1ElectronicTransCntrl1TrnstrqcnvrtrlckptrnstninprocessState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Etc1ElectronicTransCntrl1TrnstrqcnvrtrlckptrnstninprocessState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess(const ValueStore& store) -> std::optional<Etc1ElectronicTransCntrl1TrnstrqcnvrtrlckptrnstninprocessState> {
    auto raw = store.template get<SignalId::etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_etc1_electronic_trans_cntrl_1__trnstrqcnvrtrlckptrnstninprocess(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Etc1ElectronicTransCntrl1EngmomentaryoverspeedenableState : std::uint8_t {
    momentary_engine_overspeed_is_disabled = 0,
    momentary_engine_overspeed_is_enabled = 1,
    reserved = 2,
    take_no_action = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEtc1ElectronicTransCntrl1EngmomentaryoverspeedenableStateChoices{ {
    ChoiceMeta{ 0, "Momentary engine overspeed is disabled", "momentary_engine_overspeed_is_disabled" },
    ChoiceMeta{ 1, "Momentary engine overspeed is enabled", "momentary_engine_overspeed_is_enabled" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Take no action", "take_no_action" }
} };

constexpr auto to_etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable(std::uint8_t raw)
    -> std::expected<Etc1ElectronicTransCntrl1EngmomentaryoverspeedenableState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Etc1ElectronicTransCntrl1EngmomentaryoverspeedenableState::momentary_engine_overspeed_is_disabled;
        case static_cast<std::uint8_t>(1):
            return Etc1ElectronicTransCntrl1EngmomentaryoverspeedenableState::momentary_engine_overspeed_is_enabled;
        case static_cast<std::uint8_t>(2):
            return Etc1ElectronicTransCntrl1EngmomentaryoverspeedenableState::reserved;
        case static_cast<std::uint8_t>(3):
            return Etc1ElectronicTransCntrl1EngmomentaryoverspeedenableState::take_no_action;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Etc1ElectronicTransCntrl1EngmomentaryoverspeedenableState value) -> std::string_view {
    switch (value) {
        case Etc1ElectronicTransCntrl1EngmomentaryoverspeedenableState::momentary_engine_overspeed_is_disabled:
            return "Momentary engine overspeed is disabled";
        case Etc1ElectronicTransCntrl1EngmomentaryoverspeedenableState::momentary_engine_overspeed_is_enabled:
            return "Momentary engine overspeed is enabled";
        case Etc1ElectronicTransCntrl1EngmomentaryoverspeedenableState::reserved:
            return "Reserved";
        case Etc1ElectronicTransCntrl1EngmomentaryoverspeedenableState::take_no_action:
            return "Take no action";
    }
    return "<unknown>";
}

constexpr auto to_raw(Etc1ElectronicTransCntrl1EngmomentaryoverspeedenableState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable(const ValueStore& store) -> std::optional<Etc1ElectronicTransCntrl1EngmomentaryoverspeedenableState> {
    auto raw = store.template get<SignalId::etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_etc1_electronic_trans_cntrl_1__engmomentaryoverspeedenable(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Etc1ElectronicTransCntrl1ProgressiveshiftdisableState : std::uint8_t {
    progressive_shift_is_not_disabled = 0,
    progressive_shift_is_disabled = 1,
    reserved = 2,
    take_no_action = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEtc1ElectronicTransCntrl1ProgressiveshiftdisableStateChoices{ {
    ChoiceMeta{ 0, "Progressive shift is not disabled", "progressive_shift_is_not_disabled" },
    ChoiceMeta{ 1, "Progressive shift is disabled", "progressive_shift_is_disabled" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Take no action", "take_no_action" }
} };

constexpr auto to_etc1_electronic_trans_cntrl_1__progressiveshiftdisable(std::uint8_t raw)
    -> std::expected<Etc1ElectronicTransCntrl1ProgressiveshiftdisableState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Etc1ElectronicTransCntrl1ProgressiveshiftdisableState::progressive_shift_is_not_disabled;
        case static_cast<std::uint8_t>(1):
            return Etc1ElectronicTransCntrl1ProgressiveshiftdisableState::progressive_shift_is_disabled;
        case static_cast<std::uint8_t>(2):
            return Etc1ElectronicTransCntrl1ProgressiveshiftdisableState::reserved;
        case static_cast<std::uint8_t>(3):
            return Etc1ElectronicTransCntrl1ProgressiveshiftdisableState::take_no_action;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Etc1ElectronicTransCntrl1ProgressiveshiftdisableState value) -> std::string_view {
    switch (value) {
        case Etc1ElectronicTransCntrl1ProgressiveshiftdisableState::progressive_shift_is_not_disabled:
            return "Progressive shift is not disabled";
        case Etc1ElectronicTransCntrl1ProgressiveshiftdisableState::progressive_shift_is_disabled:
            return "Progressive shift is disabled";
        case Etc1ElectronicTransCntrl1ProgressiveshiftdisableState::reserved:
            return "Reserved";
        case Etc1ElectronicTransCntrl1ProgressiveshiftdisableState::take_no_action:
            return "Take no action";
    }
    return "<unknown>";
}

constexpr auto to_raw(Etc1ElectronicTransCntrl1ProgressiveshiftdisableState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_etc1_electronic_trans_cntrl_1__progressiveshiftdisable(const ValueStore& store) -> std::optional<Etc1ElectronicTransCntrl1ProgressiveshiftdisableState> {
    auto raw = store.template get<SignalId::etc1_electronic_trans_cntrl_1__progressiveshiftdisable>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_etc1_electronic_trans_cntrl_1__progressiveshiftdisable(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Etc1ElectronicTransCntrl1MomentaryengmaxpowerenableState : std::uint8_t {
    not_requesting_maximum_power_available = 0,
    momentarily_requesting_maximum_power_available = 1,
    fault = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEtc1ElectronicTransCntrl1MomentaryengmaxpowerenableStateChoices{ {
    ChoiceMeta{ 0, "not requesting maximum power available", "not_requesting_maximum_power_available" },
    ChoiceMeta{ 1, "momentarily requesting maximum power available", "momentarily_requesting_maximum_power_available" },
    ChoiceMeta{ 2, "fault", "fault" },
    ChoiceMeta{ 3, "not available", "not_available" }
} };

constexpr auto to_etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable(std::uint8_t raw)
    -> std::expected<Etc1ElectronicTransCntrl1MomentaryengmaxpowerenableState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Etc1ElectronicTransCntrl1MomentaryengmaxpowerenableState::not_requesting_maximum_power_available;
        case static_cast<std::uint8_t>(1):
            return Etc1ElectronicTransCntrl1MomentaryengmaxpowerenableState::momentarily_requesting_maximum_power_available;
        case static_cast<std::uint8_t>(2):
            return Etc1ElectronicTransCntrl1MomentaryengmaxpowerenableState::fault;
        case static_cast<std::uint8_t>(3):
            return Etc1ElectronicTransCntrl1MomentaryengmaxpowerenableState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Etc1ElectronicTransCntrl1MomentaryengmaxpowerenableState value) -> std::string_view {
    switch (value) {
        case Etc1ElectronicTransCntrl1MomentaryengmaxpowerenableState::not_requesting_maximum_power_available:
            return "not requesting maximum power available";
        case Etc1ElectronicTransCntrl1MomentaryengmaxpowerenableState::momentarily_requesting_maximum_power_available:
            return "momentarily requesting maximum power available";
        case Etc1ElectronicTransCntrl1MomentaryengmaxpowerenableState::fault:
            return "fault";
        case Etc1ElectronicTransCntrl1MomentaryengmaxpowerenableState::not_available:
            return "not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Etc1ElectronicTransCntrl1MomentaryengmaxpowerenableState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable(const ValueStore& store) -> std::optional<Etc1ElectronicTransCntrl1MomentaryengmaxpowerenableState> {
    auto raw = store.template get<SignalId::etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_etc1_electronic_trans_cntrl_1__momentaryengmaxpowerenable(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class TciTransferCaseInformationTransfercasestatusState : std::uint8_t {
    _2_wheel_high = 0,
    _4_wheel_high = 1,
    neutral = 2,
    _2_wheel_low = 3,
    _4_wheel_low = 4,
    transfer_case_shift_in_progress_or_gear_not_confirmed = 5,
    error = 6,
    not_available = 7
};

inline constexpr std::array<ChoiceMeta, 8> kTciTransferCaseInformationTransfercasestatusStateChoices{ {
    ChoiceMeta{ 0, "2 wheel high", "_2_wheel_high" },
    ChoiceMeta{ 1, "4 wheel high", "_4_wheel_high" },
    ChoiceMeta{ 2, "neutral", "neutral" },
    ChoiceMeta{ 3, "2 wheel low", "_2_wheel_low" },
    ChoiceMeta{ 4, "4 wheel low", "_4_wheel_low" },
    ChoiceMeta{ 5, "Transfer Case Shift in Progress or gear not confirmed", "transfer_case_shift_in_progress_or_gear_not_confirmed" },
    ChoiceMeta{ 6, "error", "error" },
    ChoiceMeta{ 7, "not available", "not_available" }
} };

constexpr auto to_tci_transfer_case_information__transfercasestatus(std::uint8_t raw)
    -> std::expected<TciTransferCaseInformationTransfercasestatusState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return TciTransferCaseInformationTransfercasestatusState::_2_wheel_high;
        case static_cast<std::uint8_t>(1):
            return TciTransferCaseInformationTransfercasestatusState::_4_wheel_high;
        case static_cast<std::uint8_t>(2):
            return TciTransferCaseInformationTransfercasestatusState::neutral;
        case static_cast<std::uint8_t>(3):
            return TciTransferCaseInformationTransfercasestatusState::_2_wheel_low;
        case static_cast<std::uint8_t>(4):
            return TciTransferCaseInformationTransfercasestatusState::_4_wheel_low;
        case static_cast<std::uint8_t>(5):
            return TciTransferCaseInformationTransfercasestatusState::transfer_case_shift_in_progress_or_gear_not_confirmed;
        case static_cast<std::uint8_t>(6):
            return TciTransferCaseInformationTransfercasestatusState::error;
        case static_cast<std::uint8_t>(7):
            return TciTransferCaseInformationTransfercasestatusState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(TciTransferCaseInformationTransfercasestatusState value) -> std::string_view {
    switch (value) {
        case TciTransferCaseInformationTransfercasestatusState::_2_wheel_high:
            return "2 wheel high";
        case TciTransferCaseInformationTransfercasestatusState::_4_wheel_high:
            return "4 wheel high";
        case TciTransferCaseInformationTransfercasestatusState::neutral:
            return "neutral";
        case TciTransferCaseInformationTransfercasestatusState::_2_wheel_low:
            return "2 wheel low";
        case TciTransferCaseInformationTransfercasestatusState::_4_wheel_low:
            return "4 wheel low";
        case TciTransferCaseInformationTransfercasestatusState::transfer_case_shift_in_progress_or_gear_not_confirmed:
            return "Transfer Case Shift in Progress or gear not confirmed";
        case TciTransferCaseInformationTransfercasestatusState::error:
            return "error";
        case TciTransferCaseInformationTransfercasestatusState::not_available:
            return "not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(TciTransferCaseInformationTransfercasestatusState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tci_transfer_case_information__transfercasestatus(const ValueStore& store) -> std::optional<TciTransferCaseInformationTransfercasestatusState> {
    auto raw = store.template get<SignalId::tci_transfer_case_information__transfercasestatus>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tci_transfer_case_information__transfercasestatus(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class TciTransferCaseInformationDirstatusState : std::uint8_t {
    forward = 0,
    reverse = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kTciTransferCaseInformationDirstatusStateChoices{ {
    ChoiceMeta{ 0, "Forward", "forward" },
    ChoiceMeta{ 1, "Reverse", "reverse" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not Available", "not_available" }
} };

constexpr auto to_tci_transfer_case_information__dirstatus(std::uint8_t raw)
    -> std::expected<TciTransferCaseInformationDirstatusState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return TciTransferCaseInformationDirstatusState::forward;
        case static_cast<std::uint8_t>(1):
            return TciTransferCaseInformationDirstatusState::reverse;
        case static_cast<std::uint8_t>(2):
            return TciTransferCaseInformationDirstatusState::error;
        case static_cast<std::uint8_t>(3):
            return TciTransferCaseInformationDirstatusState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(TciTransferCaseInformationDirstatusState value) -> std::string_view {
    switch (value) {
        case TciTransferCaseInformationDirstatusState::forward:
            return "Forward";
        case TciTransferCaseInformationDirstatusState::reverse:
            return "Reverse";
        case TciTransferCaseInformationDirstatusState::error:
            return "Error";
        case TciTransferCaseInformationDirstatusState::not_available:
            return "Not Available";
    }
    return "<unknown>";
}

constexpr auto to_raw(TciTransferCaseInformationDirstatusState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_tci_transfer_case_information__dirstatus(const ValueStore& store) -> std::optional<TciTransferCaseInformationDirstatusState> {
    auto raw = store.template get<SignalId::tci_transfer_case_information__dirstatus>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_tci_transfer_case_information__dirstatus(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Trf1TransmissionFluids1Transoillevel1countdowntimerState : std::uint8_t {
    less_than_1_minute = 0,
    one_minute = 1,
    two_minutes = 2,
    three_minutes = 3,
    four_minutes = 4,
    five_minutes = 5,
    six_minutes = 6,
    seven_minutes = 7,
    eight_minutes = 8,
    nine_minutes = 9,
    ten_minutes = 10,
    eleven_minutes = 11,
    twelve_minutes = 12,
    thirteen_minutes = 13,
    error = 14,
    not_available = 15
};

inline constexpr std::array<ChoiceMeta, 16> kTrf1TransmissionFluids1Transoillevel1countdowntimerStateChoices{ {
    ChoiceMeta{ 0, "less than 1 minute", "less_than_1_minute" },
    ChoiceMeta{ 1, "One minute", "one_minute" },
    ChoiceMeta{ 2, "Two minutes", "two_minutes" },
    ChoiceMeta{ 3, "Three minutes", "three_minutes" },
    ChoiceMeta{ 4, "Four minutes", "four_minutes" },
    ChoiceMeta{ 5, "Five minutes", "five_minutes" },
    ChoiceMeta{ 6, "Six minutes", "six_minutes" },
    ChoiceMeta{ 7, "Seven minutes", "seven_minutes" },
    ChoiceMeta{ 8, "Eight minutes", "eight_minutes" },
    ChoiceMeta{ 9, "Nine minutes", "nine_minutes" },
    ChoiceMeta{ 10, "Ten minutes", "ten_minutes" },
    ChoiceMeta{ 11, "Eleven minutes", "eleven_minutes" },
    ChoiceMeta{ 12, "Twelve minutes", "twelve_minutes" },
    ChoiceMeta{ 13, "Thirteen minutes", "thirteen_minutes" },
    ChoiceMeta{ 14, "Error", "error" },
    ChoiceMeta{ 15, "Not Available", "not_available" }
} };

constexpr auto to_trf1_transmission_fluids_1__transoillevel1countdowntimer(std::uint8_t raw)
    -> std::expected<Trf1TransmissionFluids1Transoillevel1countdowntimerState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Trf1TransmissionFluids1Transoillevel1countdowntimerState::less_than_1_minute;
        case static_cast<std::uint8_t>(1):
            return Trf1TransmissionFluids1Transoillevel1countdowntimerState::one_minute;
        case static_cast<std::uint8_t>(2):
            return Trf1TransmissionFluids1Transoillevel1countdowntimerState::two_minutes;
        case static_cast<std::uint8_t>(3):
            return Trf1TransmissionFluids1Transoillevel1countdowntimerState::three_minutes;
        case static_cast<std::uint8_t>(4):
            return Trf1TransmissionFluids1Transoillevel1countdowntimerState::four_minutes;
        case static_cast<std::uint8_t>(5):
            return Trf1TransmissionFluids1Transoillevel1countdowntimerState::five_minutes;
        case static_cast<std::uint8_t>(6):
            return Trf1TransmissionFluids1Transoillevel1countdowntimerState::six_minutes;
        case static_cast<std::uint8_t>(7):
            return Trf1TransmissionFluids1Transoillevel1countdowntimerState::seven_minutes;
        case static_cast<std::uint8_t>(8):
            return Trf1TransmissionFluids1Transoillevel1countdowntimerState::eight_minutes;
        case static_cast<std::uint8_t>(9):
            return Trf1TransmissionFluids1Transoillevel1countdowntimerState::nine_minutes;
        case static_cast<std::uint8_t>(10):
            return Trf1TransmissionFluids1Transoillevel1countdowntimerState::ten_minutes;
        case static_cast<std::uint8_t>(11):
            return Trf1TransmissionFluids1Transoillevel1countdowntimerState::eleven_minutes;
        case static_cast<std::uint8_t>(12):
            return Trf1TransmissionFluids1Transoillevel1countdowntimerState::twelve_minutes;
        case static_cast<std::uint8_t>(13):
            return Trf1TransmissionFluids1Transoillevel1countdowntimerState::thirteen_minutes;
        case static_cast<std::uint8_t>(14):
            return Trf1TransmissionFluids1Transoillevel1countdowntimerState::error;
        case static_cast<std::uint8_t>(15):
            return Trf1TransmissionFluids1Transoillevel1countdowntimerState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Trf1TransmissionFluids1Transoillevel1countdowntimerState value) -> std::string_view {
    switch (value) {
        case Trf1TransmissionFluids1Transoillevel1countdowntimerState::less_than_1_minute:
            return "less than 1 minute";
        case Trf1TransmissionFluids1Transoillevel1countdowntimerState::one_minute:
            return "One minute";
        case Trf1TransmissionFluids1Transoillevel1countdowntimerState::two_minutes:
            return "Two minutes";
        case Trf1TransmissionFluids1Transoillevel1countdowntimerState::three_minutes:
            return "Three minutes";
        case Trf1TransmissionFluids1Transoillevel1countdowntimerState::four_minutes:
            return "Four minutes";
        case Trf1TransmissionFluids1Transoillevel1countdowntimerState::five_minutes:
            return "Five minutes";
        case Trf1TransmissionFluids1Transoillevel1countdowntimerState::six_minutes:
            return "Six minutes";
        case Trf1TransmissionFluids1Transoillevel1countdowntimerState::seven_minutes:
            return "Seven minutes";
        case Trf1TransmissionFluids1Transoillevel1countdowntimerState::eight_minutes:
            return "Eight minutes";
        case Trf1TransmissionFluids1Transoillevel1countdowntimerState::nine_minutes:
            return "Nine minutes";
        case Trf1TransmissionFluids1Transoillevel1countdowntimerState::ten_minutes:
            return "Ten minutes";
        case Trf1TransmissionFluids1Transoillevel1countdowntimerState::eleven_minutes:
            return "Eleven minutes";
        case Trf1TransmissionFluids1Transoillevel1countdowntimerState::twelve_minutes:
            return "Twelve minutes";
        case Trf1TransmissionFluids1Transoillevel1countdowntimerState::thirteen_minutes:
            return "Thirteen minutes";
        case Trf1TransmissionFluids1Transoillevel1countdowntimerState::error:
            return "Error";
        case Trf1TransmissionFluids1Transoillevel1countdowntimerState::not_available:
            return "Not Available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Trf1TransmissionFluids1Transoillevel1countdowntimerState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_trf1_transmission_fluids_1__transoillevel1countdowntimer(const ValueStore& store) -> std::optional<Trf1TransmissionFluids1Transoillevel1countdowntimerState> {
    auto raw = store.template get<SignalId::trf1_transmission_fluids_1__transoillevel1countdowntimer>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_trf1_transmission_fluids_1__transoillevel1countdowntimer(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Trf1TransmissionFluids1Transoillevel1measurementstatusState : std::uint8_t {
    conditions_valid_for_transmission_oil_level_measurement = 0,
    conditions_not_valid_settling_timer_still_counting_down = 1,
    conditions_not_valid_transmission_in_gear = 2,
    conditions_not_valid_transmission_fluid_temperature_too_low = 3,
    conditions_not_valid_transmission_fluid_temperature_too_high = 4,
    conditions_not_valid_vehicle_moving = 5,
    conditions_not_valid_vehicle_not_level = 6,
    conditions_not_valid_engine_speed_too_low = 7,
    conditions_not_valid_engine_speed_too_high = 8,
    conditions_not_valid_no_request_for_reading = 9,
    not_defined_10 = 10,
    not_defined_11 = 11,
    not_defined_12 = 12,
    conditions_not_valid_other = 13,
    error = 14,
    not_available = 15
};

inline constexpr std::array<ChoiceMeta, 16> kTrf1TransmissionFluids1Transoillevel1measurementstatusStateChoices{ {
    ChoiceMeta{ 0, "Conditions valid for transmission oil level measurement", "conditions_valid_for_transmission_oil_level_measurement" },
    ChoiceMeta{ 1, "Conditions not valid, Settling timer still counting down", "conditions_not_valid_settling_timer_still_counting_down" },
    ChoiceMeta{ 2, "Conditions not valid, Transmission in gear", "conditions_not_valid_transmission_in_gear" },
    ChoiceMeta{ 3, "Conditions not valid, Transmission fluid temperature too low", "conditions_not_valid_transmission_fluid_temperature_too_low" },
    ChoiceMeta{ 4, "Conditions not valid, Transmission fluid temperature too high", "conditions_not_valid_transmission_fluid_temperature_too_high" },
    ChoiceMeta{ 5, "Conditions not valid, Vehicle moving", "conditions_not_valid_vehicle_moving" },
    ChoiceMeta{ 6, "Conditions not valid, Vehicle not level", "conditions_not_valid_vehicle_not_level" },
    ChoiceMeta{ 7, "Conditions not valid, Engine speed too low", "conditions_not_valid_engine_speed_too_low" },
    ChoiceMeta{ 8, "Conditions not valid, Engine speed too high", "conditions_not_valid_engine_speed_too_high" },
    ChoiceMeta{ 9, "Conditions not valid, No request for reading", "conditions_not_valid_no_request_for_reading" },
    ChoiceMeta{ 10, "Not defined", "not_defined_10" },
    ChoiceMeta{ 11, "Not defined", "not_defined_11" },
    ChoiceMeta{ 12, "Not defined", "not_defined_12" },
    ChoiceMeta{ 13, "Conditions not valid, Other", "conditions_not_valid_other" },
    ChoiceMeta{ 14, "Error", "error" },
    ChoiceMeta{ 15, "Not available", "not_available" }
} };

constexpr auto to_trf1_transmission_fluids_1__transoillevel1measurementstatus(std::uint8_t raw)
    -> std::expected<Trf1TransmissionFluids1Transoillevel1measurementstatusState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_valid_for_transmission_oil_level_measurement;
        case static_cast<std::uint8_t>(1):
            return Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_settling_timer_still_counting_down;
        case static_cast<std::uint8_t>(2):
            return Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_transmission_in_gear;
        case static_cast<std::uint8_t>(3):
            return Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_transmission_fluid_temperature_too_low;
        case static_cast<std::uint8_t>(4):
            return Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_transmission_fluid_temperature_too_high;
        case static_cast<std::uint8_t>(5):
            return Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_vehicle_moving;
        case static_cast<std::uint8_t>(6):
            return Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_vehicle_not_level;
        case static_cast<std::uint8_t>(7):
            return Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_engine_speed_too_low;
        case static_cast<std::uint8_t>(8):
            return Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_engine_speed_too_high;
        case static_cast<std::uint8_t>(9):
            return Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_no_request_for_reading;
        case static_cast<std::uint8_t>(10):
            return Trf1TransmissionFluids1Transoillevel1measurementstatusState::not_defined_10;
        case static_cast<std::uint8_t>(11):
            return Trf1TransmissionFluids1Transoillevel1measurementstatusState::not_defined_11;
        case static_cast<std::uint8_t>(12):
            return Trf1TransmissionFluids1Transoillevel1measurementstatusState::not_defined_12;
        case static_cast<std::uint8_t>(13):
            return Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_other;
        case static_cast<std::uint8_t>(14):
            return Trf1TransmissionFluids1Transoillevel1measurementstatusState::error;
        case static_cast<std::uint8_t>(15):
            return Trf1TransmissionFluids1Transoillevel1measurementstatusState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Trf1TransmissionFluids1Transoillevel1measurementstatusState value) -> std::string_view {
    switch (value) {
        case Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_valid_for_transmission_oil_level_measurement:
            return "Conditions valid for transmission oil level measurement";
        case Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_settling_timer_still_counting_down:
            return "Conditions not valid, Settling timer still counting down";
        case Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_transmission_in_gear:
            return "Conditions not valid, Transmission in gear";
        case Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_transmission_fluid_temperature_too_low:
            return "Conditions not valid, Transmission fluid temperature too low";
        case Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_transmission_fluid_temperature_too_high:
            return "Conditions not valid, Transmission fluid temperature too high";
        case Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_vehicle_moving:
            return "Conditions not valid, Vehicle moving";
        case Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_vehicle_not_level:
            return "Conditions not valid, Vehicle not level";
        case Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_engine_speed_too_low:
            return "Conditions not valid, Engine speed too low";
        case Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_engine_speed_too_high:
            return "Conditions not valid, Engine speed too high";
        case Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_no_request_for_reading:
            return "Conditions not valid, No request for reading";
        case Trf1TransmissionFluids1Transoillevel1measurementstatusState::not_defined_10:
            return "Not defined";
        case Trf1TransmissionFluids1Transoillevel1measurementstatusState::not_defined_11:
            return "Not defined";
        case Trf1TransmissionFluids1Transoillevel1measurementstatusState::not_defined_12:
            return "Not defined";
        case Trf1TransmissionFluids1Transoillevel1measurementstatusState::conditions_not_valid_other:
            return "Conditions not valid, Other";
        case Trf1TransmissionFluids1Transoillevel1measurementstatusState::error:
            return "Error";
        case Trf1TransmissionFluids1Transoillevel1measurementstatusState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Trf1TransmissionFluids1Transoillevel1measurementstatusState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_trf1_transmission_fluids_1__transoillevel1measurementstatus(const ValueStore& store) -> std::optional<Trf1TransmissionFluids1Transoillevel1measurementstatusState> {
    auto raw = store.template get<SignalId::trf1_transmission_fluids_1__transoillevel1measurementstatus>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_trf1_transmission_fluids_1__transoillevel1measurementstatus(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class CcssCruiseControlVehicleSpdCtrldiscmdsupportState : std::uint8_t {
    system_does_not_support_the_cruise_control_disable_command = 0,
    system_does_support_the_cruise_control_disable_command_feature = 1,
    reserved = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcssCruiseControlVehicleSpdCtrldiscmdsupportStateChoices{ {
    ChoiceMeta{ 0, "System does not support the 'Cruise Control Disable Command'", "system_does_not_support_the_cruise_control_disable_command" },
    ChoiceMeta{ 1, "System does support the 'Cruise Control Disable Command' feature", "system_does_support_the_cruise_control_disable_command_feature" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccss_cruise_control_vehicle_spd__ctrldiscmdsupport(std::uint8_t raw)
    -> std::expected<CcssCruiseControlVehicleSpdCtrldiscmdsupportState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return CcssCruiseControlVehicleSpdCtrldiscmdsupportState::system_does_not_support_the_cruise_control_disable_command;
        case static_cast<std::uint8_t>(1):
            return CcssCruiseControlVehicleSpdCtrldiscmdsupportState::system_does_support_the_cruise_control_disable_command_feature;
        case static_cast<std::uint8_t>(2):
            return CcssCruiseControlVehicleSpdCtrldiscmdsupportState::reserved;
        case static_cast<std::uint8_t>(3):
            return CcssCruiseControlVehicleSpdCtrldiscmdsupportState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(CcssCruiseControlVehicleSpdCtrldiscmdsupportState value) -> std::string_view {
    switch (value) {
        case CcssCruiseControlVehicleSpdCtrldiscmdsupportState::system_does_not_support_the_cruise_control_disable_command:
            return "System does not support the 'Cruise Control Disable Command'";
        case CcssCruiseControlVehicleSpdCtrldiscmdsupportState::system_does_support_the_cruise_control_disable_command_feature:
            return "System does support the 'Cruise Control Disable Command' feature";
        case CcssCruiseControlVehicleSpdCtrldiscmdsupportState::reserved:
            return "Reserved";
        case CcssCruiseControlVehicleSpdCtrldiscmdsupportState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(CcssCruiseControlVehicleSpdCtrldiscmdsupportState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccss_cruise_control_vehicle_spd__ctrldiscmdsupport(const ValueStore& store) -> std::optional<CcssCruiseControlVehicleSpdCtrldiscmdsupportState> {
    auto raw = store.template get<SignalId::ccss_cruise_control_vehicle_spd__ctrldiscmdsupport>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccss_cruise_control_vehicle_spd__ctrldiscmdsupport(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class CcssCruiseControlVehicleSpdCtrlresumecmdsupportState : std::uint8_t {
    system_does_not_support_the_cruise_control_resume_command_feature = 0,
    system_does_support_the_cruise_control_resume_command_feature = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcssCruiseControlVehicleSpdCtrlresumecmdsupportStateChoices{ {
    ChoiceMeta{ 0, "System does not support the 'Cruise Control Resume Command' feature", "system_does_not_support_the_cruise_control_resume_command_feature" },
    ChoiceMeta{ 1, "System does support the 'Cruise Control Resume Command' feature", "system_does_support_the_cruise_control_resume_command_feature" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport(std::uint8_t raw)
    -> std::expected<CcssCruiseControlVehicleSpdCtrlresumecmdsupportState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return CcssCruiseControlVehicleSpdCtrlresumecmdsupportState::system_does_not_support_the_cruise_control_resume_command_feature;
        case static_cast<std::uint8_t>(1):
            return CcssCruiseControlVehicleSpdCtrlresumecmdsupportState::system_does_support_the_cruise_control_resume_command_feature;
        case static_cast<std::uint8_t>(2):
            return CcssCruiseControlVehicleSpdCtrlresumecmdsupportState::error;
        case static_cast<std::uint8_t>(3):
            return CcssCruiseControlVehicleSpdCtrlresumecmdsupportState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(CcssCruiseControlVehicleSpdCtrlresumecmdsupportState value) -> std::string_view {
    switch (value) {
        case CcssCruiseControlVehicleSpdCtrlresumecmdsupportState::system_does_not_support_the_cruise_control_resume_command_feature:
            return "System does not support the 'Cruise Control Resume Command' feature";
        case CcssCruiseControlVehicleSpdCtrlresumecmdsupportState::system_does_support_the_cruise_control_resume_command_feature:
            return "System does support the 'Cruise Control Resume Command' feature";
        case CcssCruiseControlVehicleSpdCtrlresumecmdsupportState::error:
            return "Error";
        case CcssCruiseControlVehicleSpdCtrlresumecmdsupportState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(CcssCruiseControlVehicleSpdCtrlresumecmdsupportState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport(const ValueStore& store) -> std::optional<CcssCruiseControlVehicleSpdCtrlresumecmdsupportState> {
    auto raw = store.template get<SignalId::ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccss_cruise_control_vehicle_spd__ctrlresumecmdsupport(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class CcssCruiseControlVehicleSpdCtrlpausecmdsupportState : std::uint8_t {
    system_does_not_support_the_cruise_control_pause_command_feature = 0,
    system_does_support_the_cruise_control_pause_command_feature = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcssCruiseControlVehicleSpdCtrlpausecmdsupportStateChoices{ {
    ChoiceMeta{ 0, "System does not support the 'Cruise Control Pause Command' feature", "system_does_not_support_the_cruise_control_pause_command_feature" },
    ChoiceMeta{ 1, "System does support the 'Cruise Control Pause Command' feature", "system_does_support_the_cruise_control_pause_command_feature" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport(std::uint8_t raw)
    -> std::expected<CcssCruiseControlVehicleSpdCtrlpausecmdsupportState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return CcssCruiseControlVehicleSpdCtrlpausecmdsupportState::system_does_not_support_the_cruise_control_pause_command_feature;
        case static_cast<std::uint8_t>(1):
            return CcssCruiseControlVehicleSpdCtrlpausecmdsupportState::system_does_support_the_cruise_control_pause_command_feature;
        case static_cast<std::uint8_t>(2):
            return CcssCruiseControlVehicleSpdCtrlpausecmdsupportState::error;
        case static_cast<std::uint8_t>(3):
            return CcssCruiseControlVehicleSpdCtrlpausecmdsupportState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(CcssCruiseControlVehicleSpdCtrlpausecmdsupportState value) -> std::string_view {
    switch (value) {
        case CcssCruiseControlVehicleSpdCtrlpausecmdsupportState::system_does_not_support_the_cruise_control_pause_command_feature:
            return "System does not support the 'Cruise Control Pause Command' feature";
        case CcssCruiseControlVehicleSpdCtrlpausecmdsupportState::system_does_support_the_cruise_control_pause_command_feature:
            return "System does support the 'Cruise Control Pause Command' feature";
        case CcssCruiseControlVehicleSpdCtrlpausecmdsupportState::error:
            return "Error";
        case CcssCruiseControlVehicleSpdCtrlpausecmdsupportState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(CcssCruiseControlVehicleSpdCtrlpausecmdsupportState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport(const ValueStore& store) -> std::optional<CcssCruiseControlVehicleSpdCtrlpausecmdsupportState> {
    auto raw = store.template get<SignalId::ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccss_cruise_control_vehicle_spd__ctrlpausecmdsupport(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class CcssCruiseControlVehicleSpdCtrlsetcmdsupportState : std::uint8_t {
    system_does_not_support_the_cruise_control_set_command_feature = 0,
    system_does_support_the_cruise_control_set_command_feature = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcssCruiseControlVehicleSpdCtrlsetcmdsupportStateChoices{ {
    ChoiceMeta{ 0, "System does not support the 'Cruise Control Set Command' feature", "system_does_not_support_the_cruise_control_set_command_feature" },
    ChoiceMeta{ 1, "System does support the 'Cruise Control Set Command' feature", "system_does_support_the_cruise_control_set_command_feature" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport(std::uint8_t raw)
    -> std::expected<CcssCruiseControlVehicleSpdCtrlsetcmdsupportState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return CcssCruiseControlVehicleSpdCtrlsetcmdsupportState::system_does_not_support_the_cruise_control_set_command_feature;
        case static_cast<std::uint8_t>(1):
            return CcssCruiseControlVehicleSpdCtrlsetcmdsupportState::system_does_support_the_cruise_control_set_command_feature;
        case static_cast<std::uint8_t>(2):
            return CcssCruiseControlVehicleSpdCtrlsetcmdsupportState::error;
        case static_cast<std::uint8_t>(3):
            return CcssCruiseControlVehicleSpdCtrlsetcmdsupportState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(CcssCruiseControlVehicleSpdCtrlsetcmdsupportState value) -> std::string_view {
    switch (value) {
        case CcssCruiseControlVehicleSpdCtrlsetcmdsupportState::system_does_not_support_the_cruise_control_set_command_feature:
            return "System does not support the 'Cruise Control Set Command' feature";
        case CcssCruiseControlVehicleSpdCtrlsetcmdsupportState::system_does_support_the_cruise_control_set_command_feature:
            return "System does support the 'Cruise Control Set Command' feature";
        case CcssCruiseControlVehicleSpdCtrlsetcmdsupportState::error:
            return "Error";
        case CcssCruiseControlVehicleSpdCtrlsetcmdsupportState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(CcssCruiseControlVehicleSpdCtrlsetcmdsupportState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport(const ValueStore& store) -> std::optional<CcssCruiseControlVehicleSpdCtrlsetcmdsupportState> {
    auto raw = store.template get<SignalId::ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccss_cruise_control_vehicle_spd__ctrlsetcmdsupport(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState : std::uint8_t {
    controller_does_not_support_system_based_cruise_control_pause_resume = 0,
    auto_resume = 1,
    stop_and_operator_go = 2,
    stop_and_auto_go = 3,
    reserved_4 = 4,
    reserved_5 = 5,
    reserved_6 = 6,
    reserved_7 = 7,
    reserved_8 = 8,
    reserved_9 = 9,
    reserved_10 = 10,
    reserved_11 = 11,
    reserved_12 = 12,
    reserved_13 = 13,
    reserved_14 = 14,
    not_available = 15
};

inline constexpr std::array<ChoiceMeta, 16> kCcssCruiseControlVehicleSpdPowertrainadaptivecctypeStateChoices{ {
    ChoiceMeta{ 0, "Controller does not support system based cruise control Pause/Resume", "controller_does_not_support_system_based_cruise_control_pause_resume" },
    ChoiceMeta{ 1, "Auto Resume", "auto_resume" },
    ChoiceMeta{ 2, "Stop and Operator Go", "stop_and_operator_go" },
    ChoiceMeta{ 3, "Stop and Auto Go", "stop_and_auto_go" },
    ChoiceMeta{ 4, "Reserved", "reserved_4" },
    ChoiceMeta{ 5, "Reserved", "reserved_5" },
    ChoiceMeta{ 6, "Reserved", "reserved_6" },
    ChoiceMeta{ 7, "Reserved", "reserved_7" },
    ChoiceMeta{ 8, "Reserved", "reserved_8" },
    ChoiceMeta{ 9, "Reserved", "reserved_9" },
    ChoiceMeta{ 10, "Reserved", "reserved_10" },
    ChoiceMeta{ 11, "Reserved", "reserved_11" },
    ChoiceMeta{ 12, "Reserved", "reserved_12" },
    ChoiceMeta{ 13, "Reserved", "reserved_13" },
    ChoiceMeta{ 14, "Reserved", "reserved_14" },
    ChoiceMeta{ 15, "Not Available", "not_available" }
} };

constexpr auto to_ccss_cruise_control_vehicle_spd__powertrainadaptivecctype(std::uint8_t raw)
    -> std::expected<CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::controller_does_not_support_system_based_cruise_control_pause_resume;
        case static_cast<std::uint8_t>(1):
            return CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::auto_resume;
        case static_cast<std::uint8_t>(2):
            return CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::stop_and_operator_go;
        case static_cast<std::uint8_t>(3):
            return CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::stop_and_auto_go;
        case static_cast<std::uint8_t>(4):
            return CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_4;
        case static_cast<std::uint8_t>(5):
            return CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_5;
        case static_cast<std::uint8_t>(6):
            return CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_6;
        case static_cast<std::uint8_t>(7):
            return CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_7;
        case static_cast<std::uint8_t>(8):
            return CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_8;
        case static_cast<std::uint8_t>(9):
            return CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_9;
        case static_cast<std::uint8_t>(10):
            return CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_10;
        case static_cast<std::uint8_t>(11):
            return CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_11;
        case static_cast<std::uint8_t>(12):
            return CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_12;
        case static_cast<std::uint8_t>(13):
            return CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_13;
        case static_cast<std::uint8_t>(14):
            return CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_14;
        case static_cast<std::uint8_t>(15):
            return CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState value) -> std::string_view {
    switch (value) {
        case CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::controller_does_not_support_system_based_cruise_control_pause_resume:
            return "Controller does not support system based cruise control Pause/Resume";
        case CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::auto_resume:
            return "Auto Resume";
        case CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::stop_and_operator_go:
            return "Stop and Operator Go";
        case CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::stop_and_auto_go:
            return "Stop and Auto Go";
        case CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_4:
            return "Reserved";
        case CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_5:
            return "Reserved";
        case CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_6:
            return "Reserved";
        case CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_7:
            return "Reserved";
        case CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_8:
            return "Reserved";
        case CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_9:
            return "Reserved";
        case CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_10:
            return "Reserved";
        case CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_11:
            return "Reserved";
        case CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_12:
            return "Reserved";
        case CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_13:
            return "Reserved";
        case CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::reserved_14:
            return "Reserved";
        case CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState::not_available:
            return "Not Available";
    }
    return "<unknown>";
}

constexpr auto to_raw(CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccss_cruise_control_vehicle_spd__powertrainadaptivecctype(const ValueStore& store) -> std::optional<CcssCruiseControlVehicleSpdPowertrainadaptivecctypeState> {
    auto raw = store.template get<SignalId::ccss_cruise_control_vehicle_spd__powertrainadaptivecctype>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccss_cruise_control_vehicle_spd__powertrainadaptivecctype(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdTwospeedaxleswitchState : std::uint8_t {
    low_speed_range = 0,
    high_speed_range = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcvs1CruiseControlVehspdTwospeedaxleswitchStateChoices{ {
    ChoiceMeta{ 0, "Low speed range", "low_speed_range" },
    ChoiceMeta{ 1, "High speed range", "high_speed_range" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__twospeedaxleswitch(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdTwospeedaxleswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdTwospeedaxleswitchState::low_speed_range;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdTwospeedaxleswitchState::high_speed_range;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdTwospeedaxleswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdTwospeedaxleswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdTwospeedaxleswitchState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdTwospeedaxleswitchState::low_speed_range:
            return "Low speed range";
        case Ccvs1CruiseControlVehspdTwospeedaxleswitchState::high_speed_range:
            return "High speed range";
        case Ccvs1CruiseControlVehspdTwospeedaxleswitchState::error:
            return "Error";
        case Ccvs1CruiseControlVehspdTwospeedaxleswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdTwospeedaxleswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__twospeedaxleswitch(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdTwospeedaxleswitchState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__twospeedaxleswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__twospeedaxleswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdParkingbrakeswitchState : std::uint8_t {
    parking_brake_not_set = 0,
    parking_brake_set = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcvs1CruiseControlVehspdParkingbrakeswitchStateChoices{ {
    ChoiceMeta{ 0, "Parking brake not set", "parking_brake_not_set" },
    ChoiceMeta{ 1, "Parking brake set", "parking_brake_set" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__parkingbrakeswitch(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdParkingbrakeswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdParkingbrakeswitchState::parking_brake_not_set;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdParkingbrakeswitchState::parking_brake_set;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdParkingbrakeswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdParkingbrakeswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdParkingbrakeswitchState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdParkingbrakeswitchState::parking_brake_not_set:
            return "Parking brake not set";
        case Ccvs1CruiseControlVehspdParkingbrakeswitchState::parking_brake_set:
            return "Parking brake set";
        case Ccvs1CruiseControlVehspdParkingbrakeswitchState::error:
            return "Error";
        case Ccvs1CruiseControlVehspdParkingbrakeswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdParkingbrakeswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__parkingbrakeswitch(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdParkingbrakeswitchState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__parkingbrakeswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__parkingbrakeswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdCruisectrlpauseswitchState : std::uint8_t {
    off = 0,
    on = 1,
    error_indicator = 2,
    take_no_action = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcvs1CruiseControlVehspdCruisectrlpauseswitchStateChoices{ {
    ChoiceMeta{ 0, "Off", "off" },
    ChoiceMeta{ 1, "On", "on" },
    ChoiceMeta{ 2, "Error Indicator", "error_indicator" },
    ChoiceMeta{ 3, "Take No Action", "take_no_action" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__cruisectrlpauseswitch(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdCruisectrlpauseswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdCruisectrlpauseswitchState::off;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdCruisectrlpauseswitchState::on;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdCruisectrlpauseswitchState::error_indicator;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdCruisectrlpauseswitchState::take_no_action;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdCruisectrlpauseswitchState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdCruisectrlpauseswitchState::off:
            return "Off";
        case Ccvs1CruiseControlVehspdCruisectrlpauseswitchState::on:
            return "On";
        case Ccvs1CruiseControlVehspdCruisectrlpauseswitchState::error_indicator:
            return "Error Indicator";
        case Ccvs1CruiseControlVehspdCruisectrlpauseswitchState::take_no_action:
            return "Take No Action";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdCruisectrlpauseswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__cruisectrlpauseswitch(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdCruisectrlpauseswitchState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__cruisectrlpauseswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__cruisectrlpauseswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdParkbrakereleaseinhibitrqState : std::uint8_t {
    park_brake_release_inhibit_not_requested = 0,
    park_brake_release_inhibit_requested = 1,
    sae_reserved = 2,
    unavailable = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcvs1CruiseControlVehspdParkbrakereleaseinhibitrqStateChoices{ {
    ChoiceMeta{ 0, "Park Brake Release Inhibit not requested", "park_brake_release_inhibit_not_requested" },
    ChoiceMeta{ 1, "Park Brake Release Inhibit requested", "park_brake_release_inhibit_requested" },
    ChoiceMeta{ 2, "SAE reserved", "sae_reserved" },
    ChoiceMeta{ 3, "Unavailable", "unavailable" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdParkbrakereleaseinhibitrqState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdParkbrakereleaseinhibitrqState::park_brake_release_inhibit_not_requested;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdParkbrakereleaseinhibitrqState::park_brake_release_inhibit_requested;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdParkbrakereleaseinhibitrqState::sae_reserved;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdParkbrakereleaseinhibitrqState::unavailable;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdParkbrakereleaseinhibitrqState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdParkbrakereleaseinhibitrqState::park_brake_release_inhibit_not_requested:
            return "Park Brake Release Inhibit not requested";
        case Ccvs1CruiseControlVehspdParkbrakereleaseinhibitrqState::park_brake_release_inhibit_requested:
            return "Park Brake Release Inhibit requested";
        case Ccvs1CruiseControlVehspdParkbrakereleaseinhibitrqState::sae_reserved:
            return "SAE reserved";
        case Ccvs1CruiseControlVehspdParkbrakereleaseinhibitrqState::unavailable:
            return "Unavailable";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdParkbrakereleaseinhibitrqState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdParkbrakereleaseinhibitrqState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__parkbrakereleaseinhibitrq(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdCruisectrlactiveState : std::uint8_t {
    cruise_control_switched_off = 0,
    cruise_control_switched_on = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcvs1CruiseControlVehspdCruisectrlactiveStateChoices{ {
    ChoiceMeta{ 0, "Cruise control switched off", "cruise_control_switched_off" },
    ChoiceMeta{ 1, "Cruise control switched on", "cruise_control_switched_on" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__cruisectrlactive(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdCruisectrlactiveState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdCruisectrlactiveState::cruise_control_switched_off;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdCruisectrlactiveState::cruise_control_switched_on;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdCruisectrlactiveState::error;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdCruisectrlactiveState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdCruisectrlactiveState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdCruisectrlactiveState::cruise_control_switched_off:
            return "Cruise control switched off";
        case Ccvs1CruiseControlVehspdCruisectrlactiveState::cruise_control_switched_on:
            return "Cruise control switched on";
        case Ccvs1CruiseControlVehspdCruisectrlactiveState::error:
            return "Error";
        case Ccvs1CruiseControlVehspdCruisectrlactiveState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdCruisectrlactiveState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__cruisectrlactive(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdCruisectrlactiveState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__cruisectrlactive>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__cruisectrlactive(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdCruisectrlenableswitchState : std::uint8_t {
    cruise_control_disabled = 0,
    cruise_control_enabled = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcvs1CruiseControlVehspdCruisectrlenableswitchStateChoices{ {
    ChoiceMeta{ 0, "Cruise control disabled", "cruise_control_disabled" },
    ChoiceMeta{ 1, "Cruise control enabled", "cruise_control_enabled" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__cruisectrlenableswitch(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdCruisectrlenableswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdCruisectrlenableswitchState::cruise_control_disabled;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdCruisectrlenableswitchState::cruise_control_enabled;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdCruisectrlenableswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdCruisectrlenableswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdCruisectrlenableswitchState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdCruisectrlenableswitchState::cruise_control_disabled:
            return "Cruise control disabled";
        case Ccvs1CruiseControlVehspdCruisectrlenableswitchState::cruise_control_enabled:
            return "Cruise control enabled";
        case Ccvs1CruiseControlVehspdCruisectrlenableswitchState::error:
            return "Error";
        case Ccvs1CruiseControlVehspdCruisectrlenableswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdCruisectrlenableswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__cruisectrlenableswitch(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdCruisectrlenableswitchState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__cruisectrlenableswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__cruisectrlenableswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdBrakeswitchState : std::uint8_t {
    brake_pedal_released = 0,
    brake_pedal_depressed = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcvs1CruiseControlVehspdBrakeswitchStateChoices{ {
    ChoiceMeta{ 0, "Brake pedal released", "brake_pedal_released" },
    ChoiceMeta{ 1, "Brake pedal depressed", "brake_pedal_depressed" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not Available", "not_available" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__brakeswitch(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdBrakeswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdBrakeswitchState::brake_pedal_released;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdBrakeswitchState::brake_pedal_depressed;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdBrakeswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdBrakeswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdBrakeswitchState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdBrakeswitchState::brake_pedal_released:
            return "Brake pedal released";
        case Ccvs1CruiseControlVehspdBrakeswitchState::brake_pedal_depressed:
            return "Brake pedal depressed";
        case Ccvs1CruiseControlVehspdBrakeswitchState::error:
            return "Error";
        case Ccvs1CruiseControlVehspdBrakeswitchState::not_available:
            return "Not Available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdBrakeswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__brakeswitch(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdBrakeswitchState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__brakeswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__brakeswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdClutchswitchState : std::uint8_t {
    clutch_pedal_released = 0,
    clutch_pedal_depressed = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcvs1CruiseControlVehspdClutchswitchStateChoices{ {
    ChoiceMeta{ 0, "Clutch pedal released", "clutch_pedal_released" },
    ChoiceMeta{ 1, "Clutch pedal depressed", "clutch_pedal_depressed" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__clutchswitch(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdClutchswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdClutchswitchState::clutch_pedal_released;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdClutchswitchState::clutch_pedal_depressed;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdClutchswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdClutchswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdClutchswitchState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdClutchswitchState::clutch_pedal_released:
            return "Clutch pedal released";
        case Ccvs1CruiseControlVehspdClutchswitchState::clutch_pedal_depressed:
            return "Clutch pedal depressed";
        case Ccvs1CruiseControlVehspdClutchswitchState::error:
            return "Error";
        case Ccvs1CruiseControlVehspdClutchswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdClutchswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__clutchswitch(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdClutchswitchState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__clutchswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__clutchswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdCruisectrlsetswitchState : std::uint8_t {
    cruise_control_activator_not_in_the_position_set = 0,
    cruise_control_activator_in_position_set = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcvs1CruiseControlVehspdCruisectrlsetswitchStateChoices{ {
    ChoiceMeta{ 0, "Cruise control activator not in the position 'set'", "cruise_control_activator_not_in_the_position_set" },
    ChoiceMeta{ 1, "Cruise control activator in position 'set'", "cruise_control_activator_in_position_set" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__cruisectrlsetswitch(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdCruisectrlsetswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdCruisectrlsetswitchState::cruise_control_activator_not_in_the_position_set;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdCruisectrlsetswitchState::cruise_control_activator_in_position_set;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdCruisectrlsetswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdCruisectrlsetswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdCruisectrlsetswitchState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdCruisectrlsetswitchState::cruise_control_activator_not_in_the_position_set:
            return "Cruise control activator not in the position 'set'";
        case Ccvs1CruiseControlVehspdCruisectrlsetswitchState::cruise_control_activator_in_position_set:
            return "Cruise control activator in position 'set'";
        case Ccvs1CruiseControlVehspdCruisectrlsetswitchState::error:
            return "Error";
        case Ccvs1CruiseControlVehspdCruisectrlsetswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdCruisectrlsetswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__cruisectrlsetswitch(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdCruisectrlsetswitchState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__cruisectrlsetswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__cruisectrlsetswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdCruisectrlcoastswitchState : std::uint8_t {
    cruise_control_activator_not_in_the_position_coast = 0,
    cruise_control_activator_in_position_coast = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcvs1CruiseControlVehspdCruisectrlcoastswitchStateChoices{ {
    ChoiceMeta{ 0, "Cruise control activator not in the position 'coast'", "cruise_control_activator_not_in_the_position_coast" },
    ChoiceMeta{ 1, "Cruise control activator in position 'coast'", "cruise_control_activator_in_position_coast" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__cruisectrlcoastswitch(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdCruisectrlcoastswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdCruisectrlcoastswitchState::cruise_control_activator_not_in_the_position_coast;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdCruisectrlcoastswitchState::cruise_control_activator_in_position_coast;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdCruisectrlcoastswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdCruisectrlcoastswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdCruisectrlcoastswitchState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdCruisectrlcoastswitchState::cruise_control_activator_not_in_the_position_coast:
            return "Cruise control activator not in the position 'coast'";
        case Ccvs1CruiseControlVehspdCruisectrlcoastswitchState::cruise_control_activator_in_position_coast:
            return "Cruise control activator in position 'coast'";
        case Ccvs1CruiseControlVehspdCruisectrlcoastswitchState::error:
            return "Error";
        case Ccvs1CruiseControlVehspdCruisectrlcoastswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdCruisectrlcoastswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__cruisectrlcoastswitch(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdCruisectrlcoastswitchState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__cruisectrlcoastswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__cruisectrlcoastswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdCruisectrlresumeswitchState : std::uint8_t {
    cruise_control_activator_not_in_the_position_resume = 0,
    cruise_control_activator_in_position_resume = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcvs1CruiseControlVehspdCruisectrlresumeswitchStateChoices{ {
    ChoiceMeta{ 0, "Cruise control activator not in the position 'resume'", "cruise_control_activator_not_in_the_position_resume" },
    ChoiceMeta{ 1, "Cruise control activator in position 'resume'", "cruise_control_activator_in_position_resume" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__cruisectrlresumeswitch(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdCruisectrlresumeswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdCruisectrlresumeswitchState::cruise_control_activator_not_in_the_position_resume;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdCruisectrlresumeswitchState::cruise_control_activator_in_position_resume;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdCruisectrlresumeswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdCruisectrlresumeswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdCruisectrlresumeswitchState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdCruisectrlresumeswitchState::cruise_control_activator_not_in_the_position_resume:
            return "Cruise control activator not in the position 'resume'";
        case Ccvs1CruiseControlVehspdCruisectrlresumeswitchState::cruise_control_activator_in_position_resume:
            return "Cruise control activator in position 'resume'";
        case Ccvs1CruiseControlVehspdCruisectrlresumeswitchState::error:
            return "Error";
        case Ccvs1CruiseControlVehspdCruisectrlresumeswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdCruisectrlresumeswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__cruisectrlresumeswitch(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdCruisectrlresumeswitchState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__cruisectrlresumeswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__cruisectrlresumeswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdCruisectrlaccelerateswitchState : std::uint8_t {
    cruise_control_activator_not_in_the_position_accelerate = 0,
    cruise_control_activator_in_position_accelerate = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcvs1CruiseControlVehspdCruisectrlaccelerateswitchStateChoices{ {
    ChoiceMeta{ 0, "Cruise control activator not in the position 'accelerate'", "cruise_control_activator_not_in_the_position_accelerate" },
    ChoiceMeta{ 1, "Cruise control activator in position 'accelerate'", "cruise_control_activator_in_position_accelerate" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdCruisectrlaccelerateswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdCruisectrlaccelerateswitchState::cruise_control_activator_not_in_the_position_accelerate;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdCruisectrlaccelerateswitchState::cruise_control_activator_in_position_accelerate;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdCruisectrlaccelerateswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdCruisectrlaccelerateswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdCruisectrlaccelerateswitchState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdCruisectrlaccelerateswitchState::cruise_control_activator_not_in_the_position_accelerate:
            return "Cruise control activator not in the position 'accelerate'";
        case Ccvs1CruiseControlVehspdCruisectrlaccelerateswitchState::cruise_control_activator_in_position_accelerate:
            return "Cruise control activator in position 'accelerate'";
        case Ccvs1CruiseControlVehspdCruisectrlaccelerateswitchState::error:
            return "Error";
        case Ccvs1CruiseControlVehspdCruisectrlaccelerateswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdCruisectrlaccelerateswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdCruisectrlaccelerateswitchState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__cruisectrlaccelerateswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdPtogovernorstateState : std::uint8_t {
    off_disabled = 0,
    hold = 1,
    remote_hold = 2,
    standby = 3,
    remote_standby = 4,
    set = 5,
    decelerate_coast = 6,
    resume = 7,
    accelerate = 8,
    accelerator_override = 9,
    preprogrammed_set_speed_1 = 10,
    preprogrammed_set_speed_2 = 11,
    preprogrammed_set_speed_3 = 12,
    preprogrammed_set_speed_4 = 13,
    preprogrammed_set_speed_5 = 14,
    preprogrammed_set_speed_6 = 15,
    preprogrammed_set_speed_7 = 16,
    preprogrammed_set_speed_8 = 17,
    pto_set_speed_memory_1 = 18,
    pto_set_speed_memory_2 = 19,
    pto_set_speed_memory_3 = 20,
    reserved_21 = 21,
    reserved_22 = 22,
    reserved_23 = 23,
    reserved_24 = 24,
    reserved_25 = 25,
    reserved_26 = 26,
    reserved_27 = 27,
    reserved_28 = 28,
    reserved_29 = 29,
    reseerved = 30,
    not_available = 31
};

inline constexpr std::array<ChoiceMeta, 32> kCcvs1CruiseControlVehspdPtogovernorstateStateChoices{ {
    ChoiceMeta{ 0, "Off/Disabled", "off_disabled" },
    ChoiceMeta{ 1, "Hold", "hold" },
    ChoiceMeta{ 2, "Remote Hold", "remote_hold" },
    ChoiceMeta{ 3, "Standby", "standby" },
    ChoiceMeta{ 4, "Remote Standby", "remote_standby" },
    ChoiceMeta{ 5, "Set", "set" },
    ChoiceMeta{ 6, "Decelerate/Coast", "decelerate_coast" },
    ChoiceMeta{ 7, "Resume", "resume" },
    ChoiceMeta{ 8, "Accelerate", "accelerate" },
    ChoiceMeta{ 9, "Accelerator Override", "accelerator_override" },
    ChoiceMeta{ 10, "Preprogrammed set speed 1", "preprogrammed_set_speed_1" },
    ChoiceMeta{ 11, "Preprogrammed set speed 2", "preprogrammed_set_speed_2" },
    ChoiceMeta{ 12, "Preprogrammed set speed 3", "preprogrammed_set_speed_3" },
    ChoiceMeta{ 13, "Preprogrammed set speed 4", "preprogrammed_set_speed_4" },
    ChoiceMeta{ 14, "Preprogrammed set speed 5", "preprogrammed_set_speed_5" },
    ChoiceMeta{ 15, "Preprogrammed set speed 6", "preprogrammed_set_speed_6" },
    ChoiceMeta{ 16, "Preprogrammed set speed 7", "preprogrammed_set_speed_7" },
    ChoiceMeta{ 17, "Preprogrammed set speed 8", "preprogrammed_set_speed_8" },
    ChoiceMeta{ 18, "PTO set speed memory 1", "pto_set_speed_memory_1" },
    ChoiceMeta{ 19, "PTO set speed memory 2", "pto_set_speed_memory_2" },
    ChoiceMeta{ 20, "PTO set speed memory 3", "pto_set_speed_memory_3" },
    ChoiceMeta{ 21, "Reserved", "reserved_21" },
    ChoiceMeta{ 22, "Reserved", "reserved_22" },
    ChoiceMeta{ 23, "Reserved", "reserved_23" },
    ChoiceMeta{ 24, "Reserved", "reserved_24" },
    ChoiceMeta{ 25, "Reserved", "reserved_25" },
    ChoiceMeta{ 26, "Reserved", "reserved_26" },
    ChoiceMeta{ 27, "Reserved", "reserved_27" },
    ChoiceMeta{ 28, "Reserved", "reserved_28" },
    ChoiceMeta{ 29, "Reserved", "reserved_29" },
    ChoiceMeta{ 30, "Reseerved", "reseerved" },
    ChoiceMeta{ 31, "Not available", "not_available" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__ptogovernorstate(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdPtogovernorstateState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::off_disabled;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::hold;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::remote_hold;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::standby;
        case static_cast<std::uint8_t>(4):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::remote_standby;
        case static_cast<std::uint8_t>(5):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::set;
        case static_cast<std::uint8_t>(6):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::decelerate_coast;
        case static_cast<std::uint8_t>(7):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::resume;
        case static_cast<std::uint8_t>(8):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::accelerate;
        case static_cast<std::uint8_t>(9):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::accelerator_override;
        case static_cast<std::uint8_t>(10):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::preprogrammed_set_speed_1;
        case static_cast<std::uint8_t>(11):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::preprogrammed_set_speed_2;
        case static_cast<std::uint8_t>(12):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::preprogrammed_set_speed_3;
        case static_cast<std::uint8_t>(13):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::preprogrammed_set_speed_4;
        case static_cast<std::uint8_t>(14):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::preprogrammed_set_speed_5;
        case static_cast<std::uint8_t>(15):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::preprogrammed_set_speed_6;
        case static_cast<std::uint8_t>(16):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::preprogrammed_set_speed_7;
        case static_cast<std::uint8_t>(17):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::preprogrammed_set_speed_8;
        case static_cast<std::uint8_t>(18):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::pto_set_speed_memory_1;
        case static_cast<std::uint8_t>(19):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::pto_set_speed_memory_2;
        case static_cast<std::uint8_t>(20):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::pto_set_speed_memory_3;
        case static_cast<std::uint8_t>(21):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_21;
        case static_cast<std::uint8_t>(22):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_22;
        case static_cast<std::uint8_t>(23):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_23;
        case static_cast<std::uint8_t>(24):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_24;
        case static_cast<std::uint8_t>(25):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_25;
        case static_cast<std::uint8_t>(26):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_26;
        case static_cast<std::uint8_t>(27):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_27;
        case static_cast<std::uint8_t>(28):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_28;
        case static_cast<std::uint8_t>(29):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_29;
        case static_cast<std::uint8_t>(30):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::reseerved;
        case static_cast<std::uint8_t>(31):
            return Ccvs1CruiseControlVehspdPtogovernorstateState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdPtogovernorstateState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdPtogovernorstateState::off_disabled:
            return "Off/Disabled";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::hold:
            return "Hold";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::remote_hold:
            return "Remote Hold";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::standby:
            return "Standby";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::remote_standby:
            return "Remote Standby";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::set:
            return "Set";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::decelerate_coast:
            return "Decelerate/Coast";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::resume:
            return "Resume";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::accelerate:
            return "Accelerate";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::accelerator_override:
            return "Accelerator Override";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::preprogrammed_set_speed_1:
            return "Preprogrammed set speed 1";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::preprogrammed_set_speed_2:
            return "Preprogrammed set speed 2";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::preprogrammed_set_speed_3:
            return "Preprogrammed set speed 3";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::preprogrammed_set_speed_4:
            return "Preprogrammed set speed 4";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::preprogrammed_set_speed_5:
            return "Preprogrammed set speed 5";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::preprogrammed_set_speed_6:
            return "Preprogrammed set speed 6";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::preprogrammed_set_speed_7:
            return "Preprogrammed set speed 7";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::preprogrammed_set_speed_8:
            return "Preprogrammed set speed 8";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::pto_set_speed_memory_1:
            return "PTO set speed memory 1";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::pto_set_speed_memory_2:
            return "PTO set speed memory 2";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::pto_set_speed_memory_3:
            return "PTO set speed memory 3";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_21:
            return "Reserved";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_22:
            return "Reserved";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_23:
            return "Reserved";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_24:
            return "Reserved";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_25:
            return "Reserved";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_26:
            return "Reserved";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_27:
            return "Reserved";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_28:
            return "Reserved";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::reserved_29:
            return "Reserved";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::reseerved:
            return "Reseerved";
        case Ccvs1CruiseControlVehspdPtogovernorstateState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdPtogovernorstateState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__ptogovernorstate(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdPtogovernorstateState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__ptogovernorstate>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__ptogovernorstate(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdCruisectrlstatesState : std::uint8_t {
    off_disabled = 0,
    hold = 1,
    accelerate = 2,
    decelerate = 3,
    resume = 4,
    set = 5,
    accelerator_override = 6,
    not_available = 7
};

inline constexpr std::array<ChoiceMeta, 8> kCcvs1CruiseControlVehspdCruisectrlstatesStateChoices{ {
    ChoiceMeta{ 0, "Off/Disabled", "off_disabled" },
    ChoiceMeta{ 1, "Hold", "hold" },
    ChoiceMeta{ 2, "Accelerate", "accelerate" },
    ChoiceMeta{ 3, "Decelerate", "decelerate" },
    ChoiceMeta{ 4, "Resume", "resume" },
    ChoiceMeta{ 5, "Set", "set" },
    ChoiceMeta{ 6, "Accelerator Override", "accelerator_override" },
    ChoiceMeta{ 7, "Not available", "not_available" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__cruisectrlstates(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdCruisectrlstatesState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdCruisectrlstatesState::off_disabled;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdCruisectrlstatesState::hold;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdCruisectrlstatesState::accelerate;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdCruisectrlstatesState::decelerate;
        case static_cast<std::uint8_t>(4):
            return Ccvs1CruiseControlVehspdCruisectrlstatesState::resume;
        case static_cast<std::uint8_t>(5):
            return Ccvs1CruiseControlVehspdCruisectrlstatesState::set;
        case static_cast<std::uint8_t>(6):
            return Ccvs1CruiseControlVehspdCruisectrlstatesState::accelerator_override;
        case static_cast<std::uint8_t>(7):
            return Ccvs1CruiseControlVehspdCruisectrlstatesState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdCruisectrlstatesState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdCruisectrlstatesState::off_disabled:
            return "Off/Disabled";
        case Ccvs1CruiseControlVehspdCruisectrlstatesState::hold:
            return "Hold";
        case Ccvs1CruiseControlVehspdCruisectrlstatesState::accelerate:
            return "Accelerate";
        case Ccvs1CruiseControlVehspdCruisectrlstatesState::decelerate:
            return "Decelerate";
        case Ccvs1CruiseControlVehspdCruisectrlstatesState::resume:
            return "Resume";
        case Ccvs1CruiseControlVehspdCruisectrlstatesState::set:
            return "Set";
        case Ccvs1CruiseControlVehspdCruisectrlstatesState::accelerator_override:
            return "Accelerator Override";
        case Ccvs1CruiseControlVehspdCruisectrlstatesState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdCruisectrlstatesState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__cruisectrlstates(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdCruisectrlstatesState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__cruisectrlstates>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__cruisectrlstates(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdEngidleincrementswitchState : std::uint8_t {
    off = 0,
    on = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcvs1CruiseControlVehspdEngidleincrementswitchStateChoices{ {
    ChoiceMeta{ 0, "Off", "off" },
    ChoiceMeta{ 1, "On", "on" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__engidleincrementswitch(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdEngidleincrementswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdEngidleincrementswitchState::off;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdEngidleincrementswitchState::on;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdEngidleincrementswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdEngidleincrementswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdEngidleincrementswitchState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdEngidleincrementswitchState::off:
            return "Off";
        case Ccvs1CruiseControlVehspdEngidleincrementswitchState::on:
            return "On";
        case Ccvs1CruiseControlVehspdEngidleincrementswitchState::error:
            return "Error";
        case Ccvs1CruiseControlVehspdEngidleincrementswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdEngidleincrementswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__engidleincrementswitch(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdEngidleincrementswitchState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__engidleincrementswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__engidleincrementswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdEngidledecrementswitchState : std::uint8_t {
    off = 0,
    on = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcvs1CruiseControlVehspdEngidledecrementswitchStateChoices{ {
    ChoiceMeta{ 0, "Off", "off" },
    ChoiceMeta{ 1, "On", "on" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__engidledecrementswitch(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdEngidledecrementswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdEngidledecrementswitchState::off;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdEngidledecrementswitchState::on;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdEngidledecrementswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdEngidledecrementswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdEngidledecrementswitchState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdEngidledecrementswitchState::off:
            return "Off";
        case Ccvs1CruiseControlVehspdEngidledecrementswitchState::on:
            return "On";
        case Ccvs1CruiseControlVehspdEngidledecrementswitchState::error:
            return "Error";
        case Ccvs1CruiseControlVehspdEngidledecrementswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdEngidledecrementswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__engidledecrementswitch(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdEngidledecrementswitchState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__engidledecrementswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__engidledecrementswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdEngtestmodeswitchState : std::uint8_t {
    off = 0,
    on = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcvs1CruiseControlVehspdEngtestmodeswitchStateChoices{ {
    ChoiceMeta{ 0, "Off", "off" },
    ChoiceMeta{ 1, "On", "on" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__engtestmodeswitch(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdEngtestmodeswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdEngtestmodeswitchState::off;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdEngtestmodeswitchState::on;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdEngtestmodeswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdEngtestmodeswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdEngtestmodeswitchState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdEngtestmodeswitchState::off:
            return "Off";
        case Ccvs1CruiseControlVehspdEngtestmodeswitchState::on:
            return "On";
        case Ccvs1CruiseControlVehspdEngtestmodeswitchState::error:
            return "Error";
        case Ccvs1CruiseControlVehspdEngtestmodeswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdEngtestmodeswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__engtestmodeswitch(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdEngtestmodeswitchState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__engtestmodeswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__engtestmodeswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ccvs1CruiseControlVehspdEngshutdownoverrideswitchState : std::uint8_t {
    off = 0,
    on = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kCcvs1CruiseControlVehspdEngshutdownoverrideswitchStateChoices{ {
    ChoiceMeta{ 0, "Off", "off" },
    ChoiceMeta{ 1, "On", "on" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ccvs1_cruise_control_vehspd__engshutdownoverrideswitch(std::uint8_t raw)
    -> std::expected<Ccvs1CruiseControlVehspdEngshutdownoverrideswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ccvs1CruiseControlVehspdEngshutdownoverrideswitchState::off;
        case static_cast<std::uint8_t>(1):
            return Ccvs1CruiseControlVehspdEngshutdownoverrideswitchState::on;
        case static_cast<std::uint8_t>(2):
            return Ccvs1CruiseControlVehspdEngshutdownoverrideswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ccvs1CruiseControlVehspdEngshutdownoverrideswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ccvs1CruiseControlVehspdEngshutdownoverrideswitchState value) -> std::string_view {
    switch (value) {
        case Ccvs1CruiseControlVehspdEngshutdownoverrideswitchState::off:
            return "Off";
        case Ccvs1CruiseControlVehspdEngshutdownoverrideswitchState::on:
            return "On";
        case Ccvs1CruiseControlVehspdEngshutdownoverrideswitchState::error:
            return "Error";
        case Ccvs1CruiseControlVehspdEngshutdownoverrideswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ccvs1CruiseControlVehspdEngshutdownoverrideswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ccvs1_cruise_control_vehspd__engshutdownoverrideswitch(const ValueStore& store) -> std::optional<Ccvs1CruiseControlVehspdEngshutdownoverrideswitchState> {
    auto raw = store.template get<SignalId::ccvs1_cruise_control_vehspd__engshutdownoverrideswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ccvs1_cruise_control_vehspd__engshutdownoverrideswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlAsrengctrlactiveState : std::uint8_t {
    asr_engine_control_passive_but_installed = 0,
    asr_engine_control_active = 1,
    reserved = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlAsrengctrlactiveStateChoices{ {
    ChoiceMeta{ 0, "ASR engine control passive but installed", "asr_engine_control_passive_but_installed" },
    ChoiceMeta{ 1, "ASR engine control active", "asr_engine_control_active" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__asrengctrlactive(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlAsrengctrlactiveState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlAsrengctrlactiveState::asr_engine_control_passive_but_installed;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlAsrengctrlactiveState::asr_engine_control_active;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlAsrengctrlactiveState::reserved;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlAsrengctrlactiveState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlAsrengctrlactiveState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlAsrengctrlactiveState::asr_engine_control_passive_but_installed:
            return "ASR engine control passive but installed";
        case Ebc1ElectronicBrakeCntrlAsrengctrlactiveState::asr_engine_control_active:
            return "ASR engine control active";
        case Ebc1ElectronicBrakeCntrlAsrengctrlactiveState::reserved:
            return "Reserved";
        case Ebc1ElectronicBrakeCntrlAsrengctrlactiveState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlAsrengctrlactiveState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__asrengctrlactive(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlAsrengctrlactiveState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__asrengctrlactive>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__asrengctrlactive(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlAsrbrakectrlactiveState : std::uint8_t {
    asr_brake_control_passive_but_installed = 0,
    asr_brake_control_active = 1,
    reserved = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlAsrbrakectrlactiveStateChoices{ {
    ChoiceMeta{ 0, "ASR brake control passive but installed", "asr_brake_control_passive_but_installed" },
    ChoiceMeta{ 1, "ASR brake control active", "asr_brake_control_active" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__asrbrakectrlactive(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlAsrbrakectrlactiveState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlAsrbrakectrlactiveState::asr_brake_control_passive_but_installed;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlAsrbrakectrlactiveState::asr_brake_control_active;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlAsrbrakectrlactiveState::reserved;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlAsrbrakectrlactiveState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlAsrbrakectrlactiveState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlAsrbrakectrlactiveState::asr_brake_control_passive_but_installed:
            return "ASR brake control passive but installed";
        case Ebc1ElectronicBrakeCntrlAsrbrakectrlactiveState::asr_brake_control_active:
            return "ASR brake control active";
        case Ebc1ElectronicBrakeCntrlAsrbrakectrlactiveState::reserved:
            return "Reserved";
        case Ebc1ElectronicBrakeCntrlAsrbrakectrlactiveState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlAsrbrakectrlactiveState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__asrbrakectrlactive(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlAsrbrakectrlactiveState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__asrbrakectrlactive>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__asrbrakectrlactive(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlAntilockbrakingactiveState : std::uint8_t {
    abs_passive_but_installed = 0,
    abs_active = 1,
    reserved = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlAntilockbrakingactiveStateChoices{ {
    ChoiceMeta{ 0, "ABS passive but installed", "abs_passive_but_installed" },
    ChoiceMeta{ 1, "ABS active", "abs_active" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__antilockbrakingactive(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlAntilockbrakingactiveState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlAntilockbrakingactiveState::abs_passive_but_installed;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlAntilockbrakingactiveState::abs_active;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlAntilockbrakingactiveState::reserved;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlAntilockbrakingactiveState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlAntilockbrakingactiveState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlAntilockbrakingactiveState::abs_passive_but_installed:
            return "ABS passive but installed";
        case Ebc1ElectronicBrakeCntrlAntilockbrakingactiveState::abs_active:
            return "ABS active";
        case Ebc1ElectronicBrakeCntrlAntilockbrakingactiveState::reserved:
            return "Reserved";
        case Ebc1ElectronicBrakeCntrlAntilockbrakingactiveState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlAntilockbrakingactiveState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__antilockbrakingactive(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlAntilockbrakingactiveState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__antilockbrakingactive>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__antilockbrakingactive(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlEbsbrakeswitchState : std::uint8_t {
    brake_pedal_is_not_being_pressed = 0,
    brake_pedal_is_being_pressed = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlEbsbrakeswitchStateChoices{ {
    ChoiceMeta{ 0, "Brake pedal is not being pressed", "brake_pedal_is_not_being_pressed" },
    ChoiceMeta{ 1, "Brake pedal is being pressed", "brake_pedal_is_being_pressed" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__ebsbrakeswitch(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlEbsbrakeswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlEbsbrakeswitchState::brake_pedal_is_not_being_pressed;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlEbsbrakeswitchState::brake_pedal_is_being_pressed;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlEbsbrakeswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlEbsbrakeswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlEbsbrakeswitchState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlEbsbrakeswitchState::brake_pedal_is_not_being_pressed:
            return "Brake pedal is not being pressed";
        case Ebc1ElectronicBrakeCntrlEbsbrakeswitchState::brake_pedal_is_being_pressed:
            return "Brake pedal is being pressed";
        case Ebc1ElectronicBrakeCntrlEbsbrakeswitchState::error:
            return "Error";
        case Ebc1ElectronicBrakeCntrlEbsbrakeswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlEbsbrakeswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__ebsbrakeswitch(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlEbsbrakeswitchState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__ebsbrakeswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__ebsbrakeswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlAbsoffroadswitchState : std::uint8_t {
    abs_off_road_switch_passive = 0,
    abs_off_road_switch_active = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlAbsoffroadswitchStateChoices{ {
    ChoiceMeta{ 0, "ABS off-road switch passive", "abs_off_road_switch_passive" },
    ChoiceMeta{ 1, "ABS off-road switch active", "abs_off_road_switch_active" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__absoffroadswitch(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlAbsoffroadswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlAbsoffroadswitchState::abs_off_road_switch_passive;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlAbsoffroadswitchState::abs_off_road_switch_active;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlAbsoffroadswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlAbsoffroadswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlAbsoffroadswitchState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlAbsoffroadswitchState::abs_off_road_switch_passive:
            return "ABS off-road switch passive";
        case Ebc1ElectronicBrakeCntrlAbsoffroadswitchState::abs_off_road_switch_active:
            return "ABS off-road switch active";
        case Ebc1ElectronicBrakeCntrlAbsoffroadswitchState::error:
            return "Error";
        case Ebc1ElectronicBrakeCntrlAbsoffroadswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlAbsoffroadswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__absoffroadswitch(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlAbsoffroadswitchState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__absoffroadswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__absoffroadswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlAsroffroadswitchState : std::uint8_t {
    asr_off_road_switch_passive = 0,
    asr_off_road_switch_active = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlAsroffroadswitchStateChoices{ {
    ChoiceMeta{ 0, "ASR off-road switch passive", "asr_off_road_switch_passive" },
    ChoiceMeta{ 1, "ASR off-road switch active", "asr_off_road_switch_active" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__asroffroadswitch(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlAsroffroadswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlAsroffroadswitchState::asr_off_road_switch_passive;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlAsroffroadswitchState::asr_off_road_switch_active;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlAsroffroadswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlAsroffroadswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlAsroffroadswitchState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlAsroffroadswitchState::asr_off_road_switch_passive:
            return "ASR off-road switch passive";
        case Ebc1ElectronicBrakeCntrlAsroffroadswitchState::asr_off_road_switch_active:
            return "ASR off-road switch active";
        case Ebc1ElectronicBrakeCntrlAsroffroadswitchState::error:
            return "Error";
        case Ebc1ElectronicBrakeCntrlAsroffroadswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlAsroffroadswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__asroffroadswitch(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlAsroffroadswitchState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__asroffroadswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__asroffroadswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlAsrhillholderswitchState : std::uint8_t {
    asr_hill_holder_switch_passive = 0,
    asr_hill_holder_switch_active = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlAsrhillholderswitchStateChoices{ {
    ChoiceMeta{ 0, "ASR 'hill holder' switch passive", "asr_hill_holder_switch_passive" },
    ChoiceMeta{ 1, "ASR 'hill holder' switch active", "asr_hill_holder_switch_active" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__asrhillholderswitch(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlAsrhillholderswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlAsrhillholderswitchState::asr_hill_holder_switch_passive;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlAsrhillholderswitchState::asr_hill_holder_switch_active;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlAsrhillholderswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlAsrhillholderswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlAsrhillholderswitchState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlAsrhillholderswitchState::asr_hill_holder_switch_passive:
            return "ASR 'hill holder' switch passive";
        case Ebc1ElectronicBrakeCntrlAsrhillholderswitchState::asr_hill_holder_switch_active:
            return "ASR 'hill holder' switch active";
        case Ebc1ElectronicBrakeCntrlAsrhillholderswitchState::error:
            return "Error";
        case Ebc1ElectronicBrakeCntrlAsrhillholderswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlAsrhillholderswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__asrhillholderswitch(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlAsrhillholderswitchState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__asrhillholderswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__asrhillholderswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlTractionctrloverrideswitchState : std::uint8_t {
    off = 0,
    on = 1,
    error = 2,
    not_available_or_not_installed = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlTractionctrloverrideswitchStateChoices{ {
    ChoiceMeta{ 0, "Off", "off" },
    ChoiceMeta{ 1, "On", "on" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available or not installed", "not_available_or_not_installed" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__tractionctrloverrideswitch(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlTractionctrloverrideswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlTractionctrloverrideswitchState::off;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlTractionctrloverrideswitchState::on;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlTractionctrloverrideswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlTractionctrloverrideswitchState::not_available_or_not_installed;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlTractionctrloverrideswitchState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlTractionctrloverrideswitchState::off:
            return "Off";
        case Ebc1ElectronicBrakeCntrlTractionctrloverrideswitchState::on:
            return "On";
        case Ebc1ElectronicBrakeCntrlTractionctrloverrideswitchState::error:
            return "Error";
        case Ebc1ElectronicBrakeCntrlTractionctrloverrideswitchState::not_available_or_not_installed:
            return "Not available or not installed";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlTractionctrloverrideswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__tractionctrloverrideswitch(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlTractionctrloverrideswitchState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__tractionctrloverrideswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__tractionctrloverrideswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlAccelinterlockswitchState : std::uint8_t {
    off = 0,
    on = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlAccelinterlockswitchStateChoices{ {
    ChoiceMeta{ 0, "Off", "off" },
    ChoiceMeta{ 1, "On", "on" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__accelinterlockswitch(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlAccelinterlockswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlAccelinterlockswitchState::off;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlAccelinterlockswitchState::on;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlAccelinterlockswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlAccelinterlockswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlAccelinterlockswitchState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlAccelinterlockswitchState::off:
            return "Off";
        case Ebc1ElectronicBrakeCntrlAccelinterlockswitchState::on:
            return "On";
        case Ebc1ElectronicBrakeCntrlAccelinterlockswitchState::error:
            return "Error";
        case Ebc1ElectronicBrakeCntrlAccelinterlockswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlAccelinterlockswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__accelinterlockswitch(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlAccelinterlockswitchState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__accelinterlockswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__accelinterlockswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlEngderateswitchState : std::uint8_t {
    off = 0,
    on = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlEngderateswitchStateChoices{ {
    ChoiceMeta{ 0, "Off", "off" },
    ChoiceMeta{ 1, "On", "on" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__engderateswitch(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlEngderateswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlEngderateswitchState::off;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlEngderateswitchState::on;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlEngderateswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlEngderateswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlEngderateswitchState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlEngderateswitchState::off:
            return "Off";
        case Ebc1ElectronicBrakeCntrlEngderateswitchState::on:
            return "On";
        case Ebc1ElectronicBrakeCntrlEngderateswitchState::error:
            return "Error";
        case Ebc1ElectronicBrakeCntrlEngderateswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlEngderateswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__engderateswitch(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlEngderateswitchState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__engderateswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__engderateswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlEngauxshutdownswitchState : std::uint8_t {
    off = 0,
    on = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlEngauxshutdownswitchStateChoices{ {
    ChoiceMeta{ 0, "Off", "off" },
    ChoiceMeta{ 1, "On", "on" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__engauxshutdownswitch(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlEngauxshutdownswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlEngauxshutdownswitchState::off;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlEngauxshutdownswitchState::on;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlEngauxshutdownswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlEngauxshutdownswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlEngauxshutdownswitchState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlEngauxshutdownswitchState::off:
            return "Off";
        case Ebc1ElectronicBrakeCntrlEngauxshutdownswitchState::on:
            return "On";
        case Ebc1ElectronicBrakeCntrlEngauxshutdownswitchState::error:
            return "Error";
        case Ebc1ElectronicBrakeCntrlEngauxshutdownswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlEngauxshutdownswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__engauxshutdownswitch(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlEngauxshutdownswitchState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__engauxshutdownswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__engauxshutdownswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlRemoteaccelenableswitchState : std::uint8_t {
    off = 0,
    on = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlRemoteaccelenableswitchStateChoices{ {
    ChoiceMeta{ 0, "Off", "off" },
    ChoiceMeta{ 1, "On", "on" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__remoteaccelenableswitch(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlRemoteaccelenableswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlRemoteaccelenableswitchState::off;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlRemoteaccelenableswitchState::on;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlRemoteaccelenableswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlRemoteaccelenableswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlRemoteaccelenableswitchState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlRemoteaccelenableswitchState::off:
            return "Off";
        case Ebc1ElectronicBrakeCntrlRemoteaccelenableswitchState::on:
            return "On";
        case Ebc1ElectronicBrakeCntrlRemoteaccelenableswitchState::error:
            return "Error";
        case Ebc1ElectronicBrakeCntrlRemoteaccelenableswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlRemoteaccelenableswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__remoteaccelenableswitch(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlRemoteaccelenableswitchState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__remoteaccelenableswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__remoteaccelenableswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlAbsfullyoperationalState : std::uint8_t {
    not_fully_operational = 0,
    fully_operational = 1,
    reserved = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlAbsfullyoperationalStateChoices{ {
    ChoiceMeta{ 0, "Not Fully Operational", "not_fully_operational" },
    ChoiceMeta{ 1, "Fully Operational", "fully_operational" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__absfullyoperational(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlAbsfullyoperationalState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlAbsfullyoperationalState::not_fully_operational;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlAbsfullyoperationalState::fully_operational;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlAbsfullyoperationalState::reserved;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlAbsfullyoperationalState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlAbsfullyoperationalState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlAbsfullyoperationalState::not_fully_operational:
            return "Not Fully Operational";
        case Ebc1ElectronicBrakeCntrlAbsfullyoperationalState::fully_operational:
            return "Fully Operational";
        case Ebc1ElectronicBrakeCntrlAbsfullyoperationalState::reserved:
            return "Reserved";
        case Ebc1ElectronicBrakeCntrlAbsfullyoperationalState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlAbsfullyoperationalState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__absfullyoperational(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlAbsfullyoperationalState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__absfullyoperational>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__absfullyoperational(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlEbsredwarningsignalState : std::uint8_t {
    off = 0,
    on = 1,
    reserved = 2,
    take_no_action = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlEbsredwarningsignalStateChoices{ {
    ChoiceMeta{ 0, "Off", "off" },
    ChoiceMeta{ 1, "On", "on" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Take no action", "take_no_action" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__ebsredwarningsignal(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlEbsredwarningsignalState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlEbsredwarningsignalState::off;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlEbsredwarningsignalState::on;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlEbsredwarningsignalState::reserved;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlEbsredwarningsignalState::take_no_action;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlEbsredwarningsignalState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlEbsredwarningsignalState::off:
            return "Off";
        case Ebc1ElectronicBrakeCntrlEbsredwarningsignalState::on:
            return "On";
        case Ebc1ElectronicBrakeCntrlEbsredwarningsignalState::reserved:
            return "Reserved";
        case Ebc1ElectronicBrakeCntrlEbsredwarningsignalState::take_no_action:
            return "Take no action";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlEbsredwarningsignalState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__ebsredwarningsignal(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlEbsredwarningsignalState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__ebsredwarningsignal>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__ebsredwarningsignal(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlAbsEbsamberwarningsignalState : std::uint8_t {
    off = 0,
    on = 1,
    reserved = 2,
    take_no_action = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlAbsEbsamberwarningsignalStateChoices{ {
    ChoiceMeta{ 0, "Off", "off" },
    ChoiceMeta{ 1, "On", "on" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Take no action", "take_no_action" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlAbsEbsamberwarningsignalState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlAbsEbsamberwarningsignalState::off;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlAbsEbsamberwarningsignalState::on;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlAbsEbsamberwarningsignalState::reserved;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlAbsEbsamberwarningsignalState::take_no_action;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlAbsEbsamberwarningsignalState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlAbsEbsamberwarningsignalState::off:
            return "Off";
        case Ebc1ElectronicBrakeCntrlAbsEbsamberwarningsignalState::on:
            return "On";
        case Ebc1ElectronicBrakeCntrlAbsEbsamberwarningsignalState::reserved:
            return "Reserved";
        case Ebc1ElectronicBrakeCntrlAbsEbsamberwarningsignalState::take_no_action:
            return "Take no action";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlAbsEbsamberwarningsignalState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlAbsEbsamberwarningsignalState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__abs_ebsamberwarningsignal(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlAtcAsrinformationsignalState : std::uint8_t {
    off = 0,
    on = 1,
    reserved = 2,
    take_no_action = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlAtcAsrinformationsignalStateChoices{ {
    ChoiceMeta{ 0, "Off", "off" },
    ChoiceMeta{ 1, "On", "on" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Take no action", "take_no_action" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__atc_asrinformationsignal(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlAtcAsrinformationsignalState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlAtcAsrinformationsignalState::off;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlAtcAsrinformationsignalState::on;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlAtcAsrinformationsignalState::reserved;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlAtcAsrinformationsignalState::take_no_action;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlAtcAsrinformationsignalState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlAtcAsrinformationsignalState::off:
            return "Off";
        case Ebc1ElectronicBrakeCntrlAtcAsrinformationsignalState::on:
            return "On";
        case Ebc1ElectronicBrakeCntrlAtcAsrinformationsignalState::reserved:
            return "Reserved";
        case Ebc1ElectronicBrakeCntrlAtcAsrinformationsignalState::take_no_action:
            return "Take no action";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlAtcAsrinformationsignalState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__atc_asrinformationsignal(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlAtcAsrinformationsignalState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__atc_asrinformationsignal>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__atc_asrinformationsignal(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlRailroadmodeswState : std::uint8_t {
    railroad_mode_switch_passive = 0,
    railroad_mode_switch_active = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlRailroadmodeswStateChoices{ {
    ChoiceMeta{ 0, "Railroad mode switch passive", "railroad_mode_switch_passive" },
    ChoiceMeta{ 1, "Railroad mode switch active", "railroad_mode_switch_active" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__railroadmodesw(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlRailroadmodeswState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlRailroadmodeswState::railroad_mode_switch_passive;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlRailroadmodeswState::railroad_mode_switch_active;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlRailroadmodeswState::error;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlRailroadmodeswState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlRailroadmodeswState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlRailroadmodeswState::railroad_mode_switch_passive:
            return "Railroad mode switch passive";
        case Ebc1ElectronicBrakeCntrlRailroadmodeswState::railroad_mode_switch_active:
            return "Railroad mode switch active";
        case Ebc1ElectronicBrakeCntrlRailroadmodeswState::error:
            return "Error";
        case Ebc1ElectronicBrakeCntrlRailroadmodeswState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlRailroadmodeswState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__railroadmodesw(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlRailroadmodeswState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__railroadmodesw>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__railroadmodesw(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlHaltbrakeswitchState : std::uint8_t {
    halt_brake_switch_passive = 0,
    halt_brake_switch_active = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlHaltbrakeswitchStateChoices{ {
    ChoiceMeta{ 0, "Halt brake switch passive", "halt_brake_switch_passive" },
    ChoiceMeta{ 1, "Halt brake switch active", "halt_brake_switch_active" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__haltbrakeswitch(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlHaltbrakeswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlHaltbrakeswitchState::halt_brake_switch_passive;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlHaltbrakeswitchState::halt_brake_switch_active;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlHaltbrakeswitchState::error;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlHaltbrakeswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlHaltbrakeswitchState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlHaltbrakeswitchState::halt_brake_switch_passive:
            return "Halt brake switch passive";
        case Ebc1ElectronicBrakeCntrlHaltbrakeswitchState::halt_brake_switch_active:
            return "Halt brake switch active";
        case Ebc1ElectronicBrakeCntrlHaltbrakeswitchState::error:
            return "Error";
        case Ebc1ElectronicBrakeCntrlHaltbrakeswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlHaltbrakeswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__haltbrakeswitch(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlHaltbrakeswitchState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__haltbrakeswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__haltbrakeswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlTrailerabsstatusState : std::uint8_t {
    trailer_abs_status_information_available_but_not_active = 0,
    trailer_abs_active = 1,
    reserved = 2,
    trailer_abs_status_information_not_available_or_parameter_not_supported = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlTrailerabsstatusStateChoices{ {
    ChoiceMeta{ 0, "Trailer ABS Status Information Available But Not Active", "trailer_abs_status_information_available_but_not_active" },
    ChoiceMeta{ 1, "Trailer ABS Active", "trailer_abs_active" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Trailer ABS Status Information Not Available or Parameter Not Supported", "trailer_abs_status_information_not_available_or_parameter_not_supported" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__trailerabsstatus(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlTrailerabsstatusState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlTrailerabsstatusState::trailer_abs_status_information_available_but_not_active;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlTrailerabsstatusState::trailer_abs_active;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlTrailerabsstatusState::reserved;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlTrailerabsstatusState::trailer_abs_status_information_not_available_or_parameter_not_supported;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlTrailerabsstatusState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlTrailerabsstatusState::trailer_abs_status_information_available_but_not_active:
            return "Trailer ABS Status Information Available But Not Active";
        case Ebc1ElectronicBrakeCntrlTrailerabsstatusState::trailer_abs_active:
            return "Trailer ABS Active";
        case Ebc1ElectronicBrakeCntrlTrailerabsstatusState::reserved:
            return "Reserved";
        case Ebc1ElectronicBrakeCntrlTrailerabsstatusState::trailer_abs_status_information_not_available_or_parameter_not_supported:
            return "Trailer ABS Status Information Not Available or Parameter Not Supported";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlTrailerabsstatusState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__trailerabsstatus(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlTrailerabsstatusState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__trailerabsstatus>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__trailerabsstatus(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class Ebc1ElectronicBrakeCntrlTrctrmntdtrailerabswarningsignalState : std::uint8_t {
    off = 0,
    on = 1,
    reserved = 2,
    take_no_action = 3
};

inline constexpr std::array<ChoiceMeta, 4> kEbc1ElectronicBrakeCntrlTrctrmntdtrailerabswarningsignalStateChoices{ {
    ChoiceMeta{ 0, "Off", "off" },
    ChoiceMeta{ 1, "On", "on" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Take no action", "take_no_action" }
} };

constexpr auto to_ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal(std::uint8_t raw)
    -> std::expected<Ebc1ElectronicBrakeCntrlTrctrmntdtrailerabswarningsignalState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return Ebc1ElectronicBrakeCntrlTrctrmntdtrailerabswarningsignalState::off;
        case static_cast<std::uint8_t>(1):
            return Ebc1ElectronicBrakeCntrlTrctrmntdtrailerabswarningsignalState::on;
        case static_cast<std::uint8_t>(2):
            return Ebc1ElectronicBrakeCntrlTrctrmntdtrailerabswarningsignalState::reserved;
        case static_cast<std::uint8_t>(3):
            return Ebc1ElectronicBrakeCntrlTrctrmntdtrailerabswarningsignalState::take_no_action;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(Ebc1ElectronicBrakeCntrlTrctrmntdtrailerabswarningsignalState value) -> std::string_view {
    switch (value) {
        case Ebc1ElectronicBrakeCntrlTrctrmntdtrailerabswarningsignalState::off:
            return "Off";
        case Ebc1ElectronicBrakeCntrlTrctrmntdtrailerabswarningsignalState::on:
            return "On";
        case Ebc1ElectronicBrakeCntrlTrctrmntdtrailerabswarningsignalState::reserved:
            return "Reserved";
        case Ebc1ElectronicBrakeCntrlTrctrmntdtrailerabswarningsignalState::take_no_action:
            return "Take no action";
    }
    return "<unknown>";
}

constexpr auto to_raw(Ebc1ElectronicBrakeCntrlTrctrmntdtrailerabswarningsignalState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal(const ValueStore& store) -> std::optional<Ebc1ElectronicBrakeCntrlTrctrmntdtrailerabswarningsignalState> {
    auto raw = store.template get<SignalId::ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_ebc1_electronic_brake_cntrl__trctrmntdtrailerabswarningsignal(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngidleshutdownhasshutdownengState : std::uint8_t {
    no = 0,
    yes = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngidleshutdownhasshutdownengStateChoices{ {
    ChoiceMeta{ 0, "No", "no" },
    ChoiceMeta{ 1, "Yes", "yes" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_shutdn__engidleshutdownhasshutdowneng(std::uint8_t raw)
    -> std::expected<ShutdnEngidleshutdownhasshutdownengState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngidleshutdownhasshutdownengState::no;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngidleshutdownhasshutdownengState::yes;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngidleshutdownhasshutdownengState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngidleshutdownhasshutdownengState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngidleshutdownhasshutdownengState value) -> std::string_view {
    switch (value) {
        case ShutdnEngidleshutdownhasshutdownengState::no:
            return "No";
        case ShutdnEngidleshutdownhasshutdownengState::yes:
            return "Yes";
        case ShutdnEngidleshutdownhasshutdownengState::error:
            return "Error";
        case ShutdnEngidleshutdownhasshutdownengState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngidleshutdownhasshutdownengState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engidleshutdownhasshutdowneng(const ValueStore& store) -> std::optional<ShutdnEngidleshutdownhasshutdownengState> {
    auto raw = store.template get<SignalId::shutdn__engidleshutdownhasshutdowneng>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engidleshutdownhasshutdowneng(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngidleshutdowndriveralertmodeState : std::uint8_t {
    inactive = 0,
    active = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngidleshutdowndriveralertmodeStateChoices{ {
    ChoiceMeta{ 0, "Inactive", "inactive" },
    ChoiceMeta{ 1, "Active", "active" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_shutdn__engidleshutdowndriveralertmode(std::uint8_t raw)
    -> std::expected<ShutdnEngidleshutdowndriveralertmodeState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngidleshutdowndriveralertmodeState::inactive;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngidleshutdowndriveralertmodeState::active;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngidleshutdowndriveralertmodeState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngidleshutdowndriveralertmodeState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngidleshutdowndriveralertmodeState value) -> std::string_view {
    switch (value) {
        case ShutdnEngidleshutdowndriveralertmodeState::inactive:
            return "Inactive";
        case ShutdnEngidleshutdowndriveralertmodeState::active:
            return "Active";
        case ShutdnEngidleshutdowndriveralertmodeState::error:
            return "Error";
        case ShutdnEngidleshutdowndriveralertmodeState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngidleshutdowndriveralertmodeState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engidleshutdowndriveralertmode(const ValueStore& store) -> std::optional<ShutdnEngidleshutdowndriveralertmodeState> {
    auto raw = store.template get<SignalId::shutdn__engidleshutdowndriveralertmode>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engidleshutdowndriveralertmode(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngidleshutdowntimeroverrideState : std::uint8_t {
    inactive = 0,
    active = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngidleshutdowntimeroverrideStateChoices{ {
    ChoiceMeta{ 0, "Inactive", "inactive" },
    ChoiceMeta{ 1, "Active", "active" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_shutdn__engidleshutdowntimeroverride(std::uint8_t raw)
    -> std::expected<ShutdnEngidleshutdowntimeroverrideState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngidleshutdowntimeroverrideState::inactive;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngidleshutdowntimeroverrideState::active;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngidleshutdowntimeroverrideState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngidleshutdowntimeroverrideState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngidleshutdowntimeroverrideState value) -> std::string_view {
    switch (value) {
        case ShutdnEngidleshutdowntimeroverrideState::inactive:
            return "Inactive";
        case ShutdnEngidleshutdowntimeroverrideState::active:
            return "Active";
        case ShutdnEngidleshutdowntimeroverrideState::error:
            return "Error";
        case ShutdnEngidleshutdowntimeroverrideState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngidleshutdowntimeroverrideState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engidleshutdowntimeroverride(const ValueStore& store) -> std::optional<ShutdnEngidleshutdowntimeroverrideState> {
    auto raw = store.template get<SignalId::shutdn__engidleshutdowntimeroverride>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engidleshutdowntimeroverride(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngidleshutdowntimerstateState : std::uint8_t {
    inactive = 0,
    active = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngidleshutdowntimerstateStateChoices{ {
    ChoiceMeta{ 0, "Inactive", "inactive" },
    ChoiceMeta{ 1, "Active", "active" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_shutdn__engidleshutdowntimerstate(std::uint8_t raw)
    -> std::expected<ShutdnEngidleshutdowntimerstateState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngidleshutdowntimerstateState::inactive;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngidleshutdowntimerstateState::active;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngidleshutdowntimerstateState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngidleshutdowntimerstateState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngidleshutdowntimerstateState value) -> std::string_view {
    switch (value) {
        case ShutdnEngidleshutdowntimerstateState::inactive:
            return "Inactive";
        case ShutdnEngidleshutdowntimerstateState::active:
            return "Active";
        case ShutdnEngidleshutdowntimerstateState::error:
            return "Error";
        case ShutdnEngidleshutdowntimerstateState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngidleshutdowntimerstateState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engidleshutdowntimerstate(const ValueStore& store) -> std::optional<ShutdnEngidleshutdowntimerstateState> {
    auto raw = store.template get<SignalId::shutdn__engidleshutdowntimerstate>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engidleshutdowntimerstate(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngidleshutdowntimerfunctionState : std::uint8_t {
    disabled_in_calibration = 0,
    enabled_in_calibration = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngidleshutdowntimerfunctionStateChoices{ {
    ChoiceMeta{ 0, "Disabled in calibration", "disabled_in_calibration" },
    ChoiceMeta{ 1, "Enabled in calibration", "enabled_in_calibration" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_shutdn__engidleshutdowntimerfunction(std::uint8_t raw)
    -> std::expected<ShutdnEngidleshutdowntimerfunctionState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngidleshutdowntimerfunctionState::disabled_in_calibration;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngidleshutdowntimerfunctionState::enabled_in_calibration;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngidleshutdowntimerfunctionState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngidleshutdowntimerfunctionState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngidleshutdowntimerfunctionState value) -> std::string_view {
    switch (value) {
        case ShutdnEngidleshutdowntimerfunctionState::disabled_in_calibration:
            return "Disabled in calibration";
        case ShutdnEngidleshutdowntimerfunctionState::enabled_in_calibration:
            return "Enabled in calibration";
        case ShutdnEngidleshutdowntimerfunctionState::error:
            return "Error";
        case ShutdnEngidleshutdowntimerfunctionState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngidleshutdowntimerfunctionState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engidleshutdowntimerfunction(const ValueStore& store) -> std::optional<ShutdnEngidleshutdowntimerfunctionState> {
    auto raw = store.template get<SignalId::shutdn__engidleshutdowntimerfunction>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engidleshutdowntimerfunction(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnAChighpressfanswitchState : std::uint8_t {
    pressure_normal = 0,
    pressure_high = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnAChighpressfanswitchStateChoices{ {
    ChoiceMeta{ 0, "Pressure normal", "pressure_normal" },
    ChoiceMeta{ 1, "Pressure high", "pressure_high" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_shutdn__a_chighpressfanswitch(std::uint8_t raw)
    -> std::expected<ShutdnAChighpressfanswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnAChighpressfanswitchState::pressure_normal;
        case static_cast<std::uint8_t>(1):
            return ShutdnAChighpressfanswitchState::pressure_high;
        case static_cast<std::uint8_t>(2):
            return ShutdnAChighpressfanswitchState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnAChighpressfanswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnAChighpressfanswitchState value) -> std::string_view {
    switch (value) {
        case ShutdnAChighpressfanswitchState::pressure_normal:
            return "Pressure normal";
        case ShutdnAChighpressfanswitchState::pressure_high:
            return "Pressure high";
        case ShutdnAChighpressfanswitchState::error:
            return "Error";
        case ShutdnAChighpressfanswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnAChighpressfanswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__a_chighpressfanswitch(const ValueStore& store) -> std::optional<ShutdnAChighpressfanswitchState> {
    auto raw = store.template get<SignalId::shutdn__a_chighpressfanswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__a_chighpressfanswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnRefrigerantlowpressswitchState : std::uint8_t {
    pressure_normal = 0,
    pressure_too_low = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnRefrigerantlowpressswitchStateChoices{ {
    ChoiceMeta{ 0, "Pressure normal", "pressure_normal" },
    ChoiceMeta{ 1, "Pressure too low", "pressure_too_low" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_shutdn__refrigerantlowpressswitch(std::uint8_t raw)
    -> std::expected<ShutdnRefrigerantlowpressswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnRefrigerantlowpressswitchState::pressure_normal;
        case static_cast<std::uint8_t>(1):
            return ShutdnRefrigerantlowpressswitchState::pressure_too_low;
        case static_cast<std::uint8_t>(2):
            return ShutdnRefrigerantlowpressswitchState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnRefrigerantlowpressswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnRefrigerantlowpressswitchState value) -> std::string_view {
    switch (value) {
        case ShutdnRefrigerantlowpressswitchState::pressure_normal:
            return "Pressure normal";
        case ShutdnRefrigerantlowpressswitchState::pressure_too_low:
            return "Pressure too low";
        case ShutdnRefrigerantlowpressswitchState::error:
            return "Error";
        case ShutdnRefrigerantlowpressswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnRefrigerantlowpressswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__refrigerantlowpressswitch(const ValueStore& store) -> std::optional<ShutdnRefrigerantlowpressswitchState> {
    auto raw = store.template get<SignalId::shutdn__refrigerantlowpressswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__refrigerantlowpressswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnRefrigeranthighpressswitchState : std::uint8_t {
    pressure_normal = 0,
    pressure_too_high = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnRefrigeranthighpressswitchStateChoices{ {
    ChoiceMeta{ 0, "Pressure normal", "pressure_normal" },
    ChoiceMeta{ 1, "Pressure too high", "pressure_too_high" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_shutdn__refrigeranthighpressswitch(std::uint8_t raw)
    -> std::expected<ShutdnRefrigeranthighpressswitchState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnRefrigeranthighpressswitchState::pressure_normal;
        case static_cast<std::uint8_t>(1):
            return ShutdnRefrigeranthighpressswitchState::pressure_too_high;
        case static_cast<std::uint8_t>(2):
            return ShutdnRefrigeranthighpressswitchState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnRefrigeranthighpressswitchState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnRefrigeranthighpressswitchState value) -> std::string_view {
    switch (value) {
        case ShutdnRefrigeranthighpressswitchState::pressure_normal:
            return "Pressure normal";
        case ShutdnRefrigeranthighpressswitchState::pressure_too_high:
            return "Pressure too high";
        case ShutdnRefrigeranthighpressswitchState::error:
            return "Error";
        case ShutdnRefrigeranthighpressswitchState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnRefrigeranthighpressswitchState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__refrigeranthighpressswitch(const ValueStore& store) -> std::optional<ShutdnRefrigeranthighpressswitchState> {
    auto raw = store.template get<SignalId::shutdn__refrigeranthighpressswitch>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__refrigeranthighpressswitch(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngwaittostartlampState : std::uint8_t {
    off = 0,
    on = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngwaittostartlampStateChoices{ {
    ChoiceMeta{ 0, "Off", "off" },
    ChoiceMeta{ 1, "On", "on" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_shutdn__engwaittostartlamp(std::uint8_t raw)
    -> std::expected<ShutdnEngwaittostartlampState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngwaittostartlampState::off;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngwaittostartlampState::on;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngwaittostartlampState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngwaittostartlampState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngwaittostartlampState value) -> std::string_view {
    switch (value) {
        case ShutdnEngwaittostartlampState::off:
            return "Off";
        case ShutdnEngwaittostartlampState::on:
            return "On";
        case ShutdnEngwaittostartlampState::error:
            return "Error";
        case ShutdnEngwaittostartlampState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngwaittostartlampState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engwaittostartlamp(const ValueStore& store) -> std::optional<ShutdnEngwaittostartlampState> {
    auto raw = store.template get<SignalId::shutdn__engwaittostartlamp>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engwaittostartlamp(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngprtectionsystemhasshutdownengState : std::uint8_t {
    no = 0,
    yes = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngprtectionsystemhasshutdownengStateChoices{ {
    ChoiceMeta{ 0, "No", "no" },
    ChoiceMeta{ 1, "Yes", "yes" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_shutdn__engprtectionsystemhasshutdowneng(std::uint8_t raw)
    -> std::expected<ShutdnEngprtectionsystemhasshutdownengState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngprtectionsystemhasshutdownengState::no;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngprtectionsystemhasshutdownengState::yes;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngprtectionsystemhasshutdownengState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngprtectionsystemhasshutdownengState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngprtectionsystemhasshutdownengState value) -> std::string_view {
    switch (value) {
        case ShutdnEngprtectionsystemhasshutdownengState::no:
            return "No";
        case ShutdnEngprtectionsystemhasshutdownengState::yes:
            return "Yes";
        case ShutdnEngprtectionsystemhasshutdownengState::error:
            return "Error";
        case ShutdnEngprtectionsystemhasshutdownengState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngprtectionsystemhasshutdownengState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engprtectionsystemhasshutdowneng(const ValueStore& store) -> std::optional<ShutdnEngprtectionsystemhasshutdownengState> {
    auto raw = store.template get<SignalId::shutdn__engprtectionsystemhasshutdowneng>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engprtectionsystemhasshutdowneng(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngprtctnsystmapprachingshutdownState : std::uint8_t {
    not_approaching = 0,
    approaching = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngprtctnsystmapprachingshutdownStateChoices{ {
    ChoiceMeta{ 0, "Not approaching", "not_approaching" },
    ChoiceMeta{ 1, "Approaching", "approaching" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_shutdn__engprtctnsystmapprachingshutdown(std::uint8_t raw)
    -> std::expected<ShutdnEngprtctnsystmapprachingshutdownState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngprtctnsystmapprachingshutdownState::not_approaching;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngprtctnsystmapprachingshutdownState::approaching;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngprtctnsystmapprachingshutdownState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngprtctnsystmapprachingshutdownState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngprtctnsystmapprachingshutdownState value) -> std::string_view {
    switch (value) {
        case ShutdnEngprtctnsystmapprachingshutdownState::not_approaching:
            return "Not approaching";
        case ShutdnEngprtctnsystmapprachingshutdownState::approaching:
            return "Approaching";
        case ShutdnEngprtctnsystmapprachingshutdownState::error:
            return "Error";
        case ShutdnEngprtctnsystmapprachingshutdownState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngprtctnsystmapprachingshutdownState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engprtctnsystmapprachingshutdown(const ValueStore& store) -> std::optional<ShutdnEngprtctnsystmapprachingshutdownState> {
    auto raw = store.template get<SignalId::shutdn__engprtctnsystmapprachingshutdown>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engprtctnsystmapprachingshutdown(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngprotectionsystemtimeroverrideState : std::uint8_t {
    inactive = 0,
    active = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngprotectionsystemtimeroverrideStateChoices{ {
    ChoiceMeta{ 0, "Inactive", "inactive" },
    ChoiceMeta{ 1, "Active", "active" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_shutdn__engprotectionsystemtimeroverride(std::uint8_t raw)
    -> std::expected<ShutdnEngprotectionsystemtimeroverrideState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngprotectionsystemtimeroverrideState::inactive;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngprotectionsystemtimeroverrideState::active;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngprotectionsystemtimeroverrideState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngprotectionsystemtimeroverrideState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngprotectionsystemtimeroverrideState value) -> std::string_view {
    switch (value) {
        case ShutdnEngprotectionsystemtimeroverrideState::inactive:
            return "Inactive";
        case ShutdnEngprotectionsystemtimeroverrideState::active:
            return "Active";
        case ShutdnEngprotectionsystemtimeroverrideState::error:
            return "Error";
        case ShutdnEngprotectionsystemtimeroverrideState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngprotectionsystemtimeroverrideState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engprotectionsystemtimeroverride(const ValueStore& store) -> std::optional<ShutdnEngprotectionsystemtimeroverrideState> {
    auto raw = store.template get<SignalId::shutdn__engprotectionsystemtimeroverride>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engprotectionsystemtimeroverride(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngprotectionsystemtimerstateState : std::uint8_t {
    inactive = 0,
    active = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngprotectionsystemtimerstateStateChoices{ {
    ChoiceMeta{ 0, "Inactive", "inactive" },
    ChoiceMeta{ 1, "Active", "active" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_shutdn__engprotectionsystemtimerstate(std::uint8_t raw)
    -> std::expected<ShutdnEngprotectionsystemtimerstateState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngprotectionsystemtimerstateState::inactive;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngprotectionsystemtimerstateState::active;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngprotectionsystemtimerstateState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngprotectionsystemtimerstateState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngprotectionsystemtimerstateState value) -> std::string_view {
    switch (value) {
        case ShutdnEngprotectionsystemtimerstateState::inactive:
            return "Inactive";
        case ShutdnEngprotectionsystemtimerstateState::active:
            return "Active";
        case ShutdnEngprotectionsystemtimerstateState::error:
            return "Error";
        case ShutdnEngprotectionsystemtimerstateState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngprotectionsystemtimerstateState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engprotectionsystemtimerstate(const ValueStore& store) -> std::optional<ShutdnEngprotectionsystemtimerstateState> {
    auto raw = store.template get<SignalId::shutdn__engprotectionsystemtimerstate>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engprotectionsystemtimerstate(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngprotectionsystemconfigState : std::uint8_t {
    disabled_in_calibration = 0,
    enabled_in_calibration = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngprotectionsystemconfigStateChoices{ {
    ChoiceMeta{ 0, "Disabled in calibration", "disabled_in_calibration" },
    ChoiceMeta{ 1, "Enabled in calibration", "enabled_in_calibration" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_shutdn__engprotectionsystemconfig(std::uint8_t raw)
    -> std::expected<ShutdnEngprotectionsystemconfigState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngprotectionsystemconfigState::disabled_in_calibration;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngprotectionsystemconfigState::enabled_in_calibration;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngprotectionsystemconfigState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngprotectionsystemconfigState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngprotectionsystemconfigState value) -> std::string_view {
    switch (value) {
        case ShutdnEngprotectionsystemconfigState::disabled_in_calibration:
            return "Disabled in calibration";
        case ShutdnEngprotectionsystemconfigState::enabled_in_calibration:
            return "Enabled in calibration";
        case ShutdnEngprotectionsystemconfigState::error:
            return "Error";
        case ShutdnEngprotectionsystemconfigState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngprotectionsystemconfigState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engprotectionsystemconfig(const ValueStore& store) -> std::optional<ShutdnEngprotectionsystemconfigState> {
    auto raw = store.template get<SignalId::shutdn__engprotectionsystemconfig>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engprotectionsystemconfig(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngalarmacknowledgeState : std::uint8_t {
    engine_alarm_acknowledge_not_active = 0,
    engine_alarm_acknowledge_active = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngalarmacknowledgeStateChoices{ {
    ChoiceMeta{ 0, "Engine Alarm Acknowledge  Not Active", "engine_alarm_acknowledge_not_active" },
    ChoiceMeta{ 1, "Engine Alarm Acknowledge Active", "engine_alarm_acknowledge_active" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not Available", "not_available" }
} };

constexpr auto to_shutdn__engalarmacknowledge(std::uint8_t raw)
    -> std::expected<ShutdnEngalarmacknowledgeState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngalarmacknowledgeState::engine_alarm_acknowledge_not_active;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngalarmacknowledgeState::engine_alarm_acknowledge_active;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngalarmacknowledgeState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngalarmacknowledgeState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngalarmacknowledgeState value) -> std::string_view {
    switch (value) {
        case ShutdnEngalarmacknowledgeState::engine_alarm_acknowledge_not_active:
            return "Engine Alarm Acknowledge  Not Active";
        case ShutdnEngalarmacknowledgeState::engine_alarm_acknowledge_active:
            return "Engine Alarm Acknowledge Active";
        case ShutdnEngalarmacknowledgeState::error:
            return "Error";
        case ShutdnEngalarmacknowledgeState::not_available:
            return "Not Available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngalarmacknowledgeState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engalarmacknowledge(const ValueStore& store) -> std::optional<ShutdnEngalarmacknowledgeState> {
    auto raw = store.template get<SignalId::shutdn__engalarmacknowledge>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engalarmacknowledge(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngalarmoutputcmdstatusState : std::uint8_t {
    engine_alarm_output_command_not_active = 0,
    engine_alarm_output_command_active = 1,
    reserved = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngalarmoutputcmdstatusStateChoices{ {
    ChoiceMeta{ 0, "Engine Alarm Output Command Not Active", "engine_alarm_output_command_not_active" },
    ChoiceMeta{ 1, "Engine Alarm Output Command Active", "engine_alarm_output_command_active" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Not Available", "not_available" }
} };

constexpr auto to_shutdn__engalarmoutputcmdstatus(std::uint8_t raw)
    -> std::expected<ShutdnEngalarmoutputcmdstatusState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngalarmoutputcmdstatusState::engine_alarm_output_command_not_active;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngalarmoutputcmdstatusState::engine_alarm_output_command_active;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngalarmoutputcmdstatusState::reserved;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngalarmoutputcmdstatusState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngalarmoutputcmdstatusState value) -> std::string_view {
    switch (value) {
        case ShutdnEngalarmoutputcmdstatusState::engine_alarm_output_command_not_active:
            return "Engine Alarm Output Command Not Active";
        case ShutdnEngalarmoutputcmdstatusState::engine_alarm_output_command_active:
            return "Engine Alarm Output Command Active";
        case ShutdnEngalarmoutputcmdstatusState::reserved:
            return "Reserved";
        case ShutdnEngalarmoutputcmdstatusState::not_available:
            return "Not Available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngalarmoutputcmdstatusState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engalarmoutputcmdstatus(const ValueStore& store) -> std::optional<ShutdnEngalarmoutputcmdstatusState> {
    auto raw = store.template get<SignalId::shutdn__engalarmoutputcmdstatus>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engalarmoutputcmdstatus(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngairshutoffcmdstatusState : std::uint8_t {
    air_shutoff_disabled = 0,
    air_shutoff_enabled = 1,
    reserved = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngairshutoffcmdstatusStateChoices{ {
    ChoiceMeta{ 0, "Air Shutoff Disabled", "air_shutoff_disabled" },
    ChoiceMeta{ 1, "Air Shutoff Enabled", "air_shutoff_enabled" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Not Available", "not_available" }
} };

constexpr auto to_shutdn__engairshutoffcmdstatus(std::uint8_t raw)
    -> std::expected<ShutdnEngairshutoffcmdstatusState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngairshutoffcmdstatusState::air_shutoff_disabled;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngairshutoffcmdstatusState::air_shutoff_enabled;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngairshutoffcmdstatusState::reserved;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngairshutoffcmdstatusState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngairshutoffcmdstatusState value) -> std::string_view {
    switch (value) {
        case ShutdnEngairshutoffcmdstatusState::air_shutoff_disabled:
            return "Air Shutoff Disabled";
        case ShutdnEngairshutoffcmdstatusState::air_shutoff_enabled:
            return "Air Shutoff Enabled";
        case ShutdnEngairshutoffcmdstatusState::reserved:
            return "Reserved";
        case ShutdnEngairshutoffcmdstatusState::not_available:
            return "Not Available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngairshutoffcmdstatusState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engairshutoffcmdstatus(const ValueStore& store) -> std::optional<ShutdnEngairshutoffcmdstatusState> {
    auto raw = store.template get<SignalId::shutdn__engairshutoffcmdstatus>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engairshutoffcmdstatus(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngoverspeedtestState : std::uint8_t {
    engine_overspeed_test_not_active = 0,
    engine_overspeed_test_active = 1,
    reserved = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngoverspeedtestStateChoices{ {
    ChoiceMeta{ 0, "Engine Overspeed Test Not Active", "engine_overspeed_test_not_active" },
    ChoiceMeta{ 1, "Engine Overspeed Test Active", "engine_overspeed_test_active" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Not Available", "not_available" }
} };

constexpr auto to_shutdn__engoverspeedtest(std::uint8_t raw)
    -> std::expected<ShutdnEngoverspeedtestState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngoverspeedtestState::engine_overspeed_test_not_active;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngoverspeedtestState::engine_overspeed_test_active;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngoverspeedtestState::reserved;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngoverspeedtestState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngoverspeedtestState value) -> std::string_view {
    switch (value) {
        case ShutdnEngoverspeedtestState::engine_overspeed_test_not_active:
            return "Engine Overspeed Test Not Active";
        case ShutdnEngoverspeedtestState::engine_overspeed_test_active:
            return "Engine Overspeed Test Active";
        case ShutdnEngoverspeedtestState::reserved:
            return "Reserved";
        case ShutdnEngoverspeedtestState::not_available:
            return "Not Available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngoverspeedtestState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engoverspeedtest(const ValueStore& store) -> std::optional<ShutdnEngoverspeedtestState> {
    auto raw = store.template get<SignalId::shutdn__engoverspeedtest>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engoverspeedtest(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngairshutoffstatusState : std::uint8_t {
    air_flow_allowed_to_engine = 0,
    air_flow_restricted = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngairshutoffstatusStateChoices{ {
    ChoiceMeta{ 0, "Air flow allowed to engine", "air_flow_allowed_to_engine" },
    ChoiceMeta{ 1, "Air flow restricted", "air_flow_restricted" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not Available", "not_available" }
} };

constexpr auto to_shutdn__engairshutoffstatus(std::uint8_t raw)
    -> std::expected<ShutdnEngairshutoffstatusState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngairshutoffstatusState::air_flow_allowed_to_engine;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngairshutoffstatusState::air_flow_restricted;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngairshutoffstatusState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngairshutoffstatusState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngairshutoffstatusState value) -> std::string_view {
    switch (value) {
        case ShutdnEngairshutoffstatusState::air_flow_allowed_to_engine:
            return "Air flow allowed to engine";
        case ShutdnEngairshutoffstatusState::air_flow_restricted:
            return "Air flow restricted";
        case ShutdnEngairshutoffstatusState::error:
            return "Error";
        case ShutdnEngairshutoffstatusState::not_available:
            return "Not Available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngairshutoffstatusState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engairshutoffstatus(const ValueStore& store) -> std::optional<ShutdnEngairshutoffstatusState> {
    auto raw = store.template get<SignalId::shutdn__engairshutoffstatus>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engairshutoffstatus(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnPtoshutdownhasshutdownengState : std::uint8_t {
    no = 0,
    yes = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnPtoshutdownhasshutdownengStateChoices{ {
    ChoiceMeta{ 0, "No", "no" },
    ChoiceMeta{ 1, "Yes", "yes" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not available", "not_available" }
} };

constexpr auto to_shutdn__ptoshutdownhasshutdowneng(std::uint8_t raw)
    -> std::expected<ShutdnPtoshutdownhasshutdownengState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnPtoshutdownhasshutdownengState::no;
        case static_cast<std::uint8_t>(1):
            return ShutdnPtoshutdownhasshutdownengState::yes;
        case static_cast<std::uint8_t>(2):
            return ShutdnPtoshutdownhasshutdownengState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnPtoshutdownhasshutdownengState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnPtoshutdownhasshutdownengState value) -> std::string_view {
    switch (value) {
        case ShutdnPtoshutdownhasshutdownengState::no:
            return "No";
        case ShutdnPtoshutdownhasshutdownengState::yes:
            return "Yes";
        case ShutdnPtoshutdownhasshutdownengState::error:
            return "Error";
        case ShutdnPtoshutdownhasshutdownengState::not_available:
            return "Not available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnPtoshutdownhasshutdownengState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__ptoshutdownhasshutdowneng(const ValueStore& store) -> std::optional<ShutdnPtoshutdownhasshutdownengState> {
    auto raw = store.template get<SignalId::shutdn__ptoshutdownhasshutdowneng>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__ptoshutdownhasshutdowneng(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnClntlvlengprtctionshutdownstatusState : std::uint8_t {
    disabled = 0,
    enabled = 1,
    reserved = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnClntlvlengprtctionshutdownstatusStateChoices{ {
    ChoiceMeta{ 0, "Disabled", "disabled" },
    ChoiceMeta{ 1, "Enabled", "enabled" },
    ChoiceMeta{ 2, "Reserved", "reserved" },
    ChoiceMeta{ 3, "Not Available", "not_available" }
} };

constexpr auto to_shutdn__clntlvlengprtctionshutdownstatus(std::uint8_t raw)
    -> std::expected<ShutdnClntlvlengprtctionshutdownstatusState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnClntlvlengprtctionshutdownstatusState::disabled;
        case static_cast<std::uint8_t>(1):
            return ShutdnClntlvlengprtctionshutdownstatusState::enabled;
        case static_cast<std::uint8_t>(2):
            return ShutdnClntlvlengprtctionshutdownstatusState::reserved;
        case static_cast<std::uint8_t>(3):
            return ShutdnClntlvlengprtctionshutdownstatusState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnClntlvlengprtctionshutdownstatusState value) -> std::string_view {
    switch (value) {
        case ShutdnClntlvlengprtctionshutdownstatusState::disabled:
            return "Disabled";
        case ShutdnClntlvlengprtctionshutdownstatusState::enabled:
            return "Enabled";
        case ShutdnClntlvlengprtctionshutdownstatusState::reserved:
            return "Reserved";
        case ShutdnClntlvlengprtctionshutdownstatusState::not_available:
            return "Not Available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnClntlvlengprtctionshutdownstatusState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__clntlvlengprtctionshutdownstatus(const ValueStore& store) -> std::optional<ShutdnClntlvlengprtctionshutdownstatusState> {
    auto raw = store.template get<SignalId::shutdn__clntlvlengprtctionshutdownstatus>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__clntlvlengprtctionshutdownstatus(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

enum class ShutdnEngoilpressswState : std::uint8_t {
    ok = 0,
    not_ok = 1,
    error = 2,
    not_available = 3
};

inline constexpr std::array<ChoiceMeta, 4> kShutdnEngoilpressswStateChoices{ {
    ChoiceMeta{ 0, "OK", "ok" },
    ChoiceMeta{ 1, "Not OK", "not_ok" },
    ChoiceMeta{ 2, "Error", "error" },
    ChoiceMeta{ 3, "Not Available", "not_available" }
} };

constexpr auto to_shutdn__engoilpresssw(std::uint8_t raw)
    -> std::expected<ShutdnEngoilpressswState, ChoiceError> {
    switch (raw) {
        case static_cast<std::uint8_t>(0):
            return ShutdnEngoilpressswState::ok;
        case static_cast<std::uint8_t>(1):
            return ShutdnEngoilpressswState::not_ok;
        case static_cast<std::uint8_t>(2):
            return ShutdnEngoilpressswState::error;
        case static_cast<std::uint8_t>(3):
            return ShutdnEngoilpressswState::not_available;
        default:
            return std::unexpected(ChoiceError::unknown_raw_value);
    }
}

constexpr auto to_string(ShutdnEngoilpressswState value) -> std::string_view {
    switch (value) {
        case ShutdnEngoilpressswState::ok:
            return "OK";
        case ShutdnEngoilpressswState::not_ok:
            return "Not OK";
        case ShutdnEngoilpressswState::error:
            return "Error";
        case ShutdnEngoilpressswState::not_available:
            return "Not Available";
    }
    return "<unknown>";
}

constexpr auto to_raw(ShutdnEngoilpressswState value) -> std::uint8_t {
    return static_cast<std::uint8_t>(value);
}

constexpr auto try_get_shutdn__engoilpresssw(const ValueStore& store) -> std::optional<ShutdnEngoilpressswState> {
    auto raw = store.template get<SignalId::shutdn__engoilpresssw>();
    if (!raw) {
        return std::nullopt;
    }

    auto converted = to_shutdn__engoilpresssw(*raw);
    if (!converted) {
        return std::nullopt;
    }
    return *converted;
}

} // namespace duramax