#pragma once

#include "reacher_build.hpp"
#include "reacher_codec.hpp"
#include "reacher_concepts.hpp"
#include "reacher_metadata.hpp"
#include "reacher_store.hpp"
#include "reacher_types.hpp"
#include "reacher_validate.hpp"

#include <cstddef>
#include <cstdint>
#include <expected>
#include <span>
#include <string_view>

namespace reacher {

struct ReacherDb {
    using MessageId = reacher::MessageId;
    using SignalId = reacher::SignalId;
    using MessageVariant = reacher::MessageVariant;
    using ValueStore = reacher::ValueStore;
    using MessageMeta = reacher::MessageMeta;
    using SignalMeta = reacher::SignalMeta;
    using DecodeError = reacher::DecodeError;
    using EncodeError = reacher::EncodeError;
    using BuildError = reacher::BuildError;
    using StoreAccessError = reacher::StoreAccessError;
    using SignalPhysicalValue = reacher::SignalPhysicalValue;
    using ValidationError = reacher::ValidationError;
    using ValidationIssue = reacher::ValidationIssue;

    template <SignalId Id>
    using signal_traits = reacher::signal_traits<Id>;

    template <SignalId Id>
    using signal_value_t = reacher::signal_value_t<Id>;


    template <SignalId Id>
    static auto validate_signal_encodable(signal_value_t<Id> value)
        -> std::expected<void, ValidationIssue>
    {
        return reacher::validate_signal_encodable<Id>(value);
    }

    template <SignalId Id>
    static auto validate_signal_within_dbc_range(signal_value_t<Id> value)
        -> std::expected<void, ValidationIssue>
    {
        return reacher::validate_signal_within_dbc_range<Id>(value);
    }

    template <SignalId Id>
    static auto validate_signal_value(signal_value_t<Id> value)
        -> std::expected<void, ValidationIssue>
    {
        return reacher::validate_signal_value<Id>(value);
    }

    template <GeneratedMessage Msg>
    static auto validate_message(const Msg& msg)
        -> std::expected<void, ValidationIssue>
    {
        return reacher::validate_message(msg);
    }

    static auto validate_message(const MessageVariant& msg)
        -> std::expected<void, ValidationIssue>
    {
        return reacher::validate_message(msg);
    }

    struct EncodeFromStoreError {
        enum class Stage : std::uint8_t {
            build,
            encode
        };

        Stage stage{};
        BuildError build_error{BuildError::unsupported_message};
        EncodeError encode_error{EncodeError::unsupported_message};

        static constexpr auto from_build(BuildError e) -> EncodeFromStoreError {
            return EncodeFromStoreError{.stage = Stage::build, .build_error = e};
        }

        static constexpr auto from_encode(EncodeError e) -> EncodeFromStoreError {
            return EncodeFromStoreError{.stage = Stage::encode, .encode_error = e};
        }
    };

    static constexpr std::size_t kMessageCount = reacher::kMessageCount;
    static constexpr std::size_t kSignalCount = reacher::kSignalCount;

    static constexpr auto to_index(MessageId id) -> std::size_t {
        return reacher::to_index(id);
    }

    static constexpr auto to_index(SignalId id) -> std::size_t {
        return reacher::to_index(id);
    }

    static auto decode(std::uint32_t can_id,
                       const std::uint8_t* data,
                       std::size_t size)
        -> std::expected<MessageVariant, DecodeError>
    {
        return reacher::Codec::decode(can_id, data, size);
    }

    static auto encode(const MessageVariant& msg,
                       std::uint8_t* out,
                       std::size_t out_size)
        -> std::expected<std::uint8_t, EncodeError>
    {
        return reacher::Codec::encode(msg, out, out_size);
    }

    template <GeneratedMessage Msg>
    static auto encode(const Msg& msg,
                       std::uint8_t* out,
                       std::size_t out_size)
        -> std::expected<std::uint8_t, EncodeError>
    {
        return reacher::Codec::encode(msg, out, out_size);
    }

    static constexpr auto message_meta(MessageId id) -> const reacher::MessageMeta& {
        return reacher::message_meta(id);
    }

    static constexpr auto signal_meta(SignalId id) -> const reacher::SignalMeta& {
        return reacher::signal_meta(id);
    }

    static constexpr auto message_name(MessageId id) -> std::string_view {
        return reacher::message_name(id);
    }

    static constexpr auto signal_name(SignalId id) -> std::string_view {
        return reacher::signal_name(id);
    }

    static constexpr auto signal_unit(SignalId id) -> std::string_view {
        return reacher::signal_unit(id);
    }

    static constexpr auto signal_parent_message_name(SignalId id) -> std::string_view {
        return reacher::signal_parent_message_name(id);
    }

    static constexpr auto parent_message_id(SignalId sid) -> MessageId {
        return reacher::parent_message_id(sid);
    }

    static constexpr auto signal_has_minimum(SignalId id) -> bool {
        return reacher::signal_has_minimum(id);
    }

    static constexpr auto signal_minimum(SignalId id) -> double {
        return reacher::signal_minimum(id);
    }

    static constexpr auto signal_has_maximum(SignalId id) -> bool {
        return reacher::signal_has_maximum(id);
    }

    static constexpr auto signal_maximum(SignalId id) -> double {
        return reacher::signal_maximum(id);
    }

    static constexpr auto message_cycle_time_ms(MessageId id) -> std::uint32_t {
        return reacher::message_cycle_time_ms(id);
    }

    static constexpr auto message_signals(MessageId id) -> std::span<const SignalId> {
        return reacher::message_signals(id);
    }

    static constexpr auto find_message_by_frame_id(std::uint32_t frame_id)
        -> const reacher::MessageMeta*
    {
        return reacher::find_message_by_frame_id(frame_id);
    }

    static auto build_message_from_store(MessageId id, const ValueStore& store)
        -> std::expected<MessageVariant, BuildError>
    {
        return reacher::build_message_from_store(id, store);
    }

    static auto validate_message_buildable(MessageId id, const ValueStore& store)
        -> std::expected<void, BuildError>
    {
        return reacher::validate_message_buildable(id, store);
    }

    static auto set_signal_physical(ValueStore& store,
                                    SignalId id,
                                    const SignalPhysicalValue& value,
                                    std::uint32_t now_ms)
        -> std::expected<void, StoreAccessError>
    {
        return store.set_signal_physical(id, value, now_ms);
    }

    static auto get_signal_physical(const ValueStore& store,
                                    SignalId id)
        -> std::expected<SignalPhysicalValue, StoreAccessError>
    {
        return store.get_signal_physical(id);
    }

    static auto encode_from_store(MessageId id,
                                  const ValueStore& store,
                                  std::uint8_t* out,
                                  std::size_t out_size)
        -> std::expected<std::uint8_t, EncodeFromStoreError>
    {
        auto built = reacher::build_message_from_store(id, store);
        if (!built) {
            return std::unexpected(EncodeFromStoreError::from_build(built.error()));
        }

        auto encoded = reacher::Codec::encode(*built, out, out_size);
        if (!encoded) {
            return std::unexpected(EncodeFromStoreError::from_encode(encoded.error()));
        }

        return *encoded;
    }

    template <GeneratedMessage Msg>
    static void apply_to_store(ValueStore& store,
                               const Msg& msg,
                               std::uint32_t now_ms)
    {
        reacher::apply_to_store(store, msg, now_ms);
    }

    static void apply_to_store(ValueStore& store,
                               const MessageVariant& msg,
                               std::uint32_t now_ms)
    {
        reacher::apply_to_store(store, msg, now_ms);
    }
};

static_assert(CanDatabase<ReacherDb>);

} // namespace reacher