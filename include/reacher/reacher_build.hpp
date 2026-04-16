#pragma once

#include "reacher_metadata.hpp"
#include "reacher_store.hpp"
#include "reacher_types.hpp"

#include <expected>

namespace reacher {

enum class BuildError : std::uint8_t {
    missing_signal,
    type_mismatch,
    unsupported_message
};

auto build_reacher_ctrl_from_store(const ValueStore& store)
    -> std::expected<ReacherCtrl, BuildError>;
auto build_reacher_engine_feedback_from_store(const ValueStore& store)
    -> std::expected<ReacherEngineFeedback, BuildError>;
auto build_export_0_from_store(const ValueStore& store)
    -> std::expected<Export0, BuildError>;
auto build_export_3_from_store(const ValueStore& store)
    -> std::expected<Export3, BuildError>;
auto build_export_8_from_store(const ValueStore& store)
    -> std::expected<Export8, BuildError>;
auto build_export_b_from_store(const ValueStore& store)
    -> std::expected<ExportB, BuildError>;
auto build_servo_batt_from_store(const ValueStore& store)
    -> std::expected<ServoBatt, BuildError>;

auto build_message_from_store(MessageId id, const ValueStore& store)
    -> std::expected<MessageVariant, BuildError>;

auto validate_message_buildable(MessageId id, const ValueStore& store)
    -> std::expected<void, BuildError>;

} // namespace reacher