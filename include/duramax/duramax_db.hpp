#pragma once

#include "duramax_build.hpp"
#include "duramax_codec.hpp"
#include "duramax_concepts.hpp"
#include "duramax_metadata.hpp"
#include "duramax_store.hpp"
#include "duramax_types.hpp"

#include <cstddef>
#include <cstdint>
#include <expected>
#include <span>
#include <string_view>

namespace duramax {

struct DuramaxDb {
    using MessageId = duramax::MessageId;
    using SignalId = duramax::SignalId;
    using MessageVariant = duramax::MessageVariant;
    using ValueStore = duramax::ValueStore;
    using MessageMeta = duramax::MessageMeta;
    using SignalMeta = duramax::SignalMeta;
    using DecodeError = duramax::DecodeError;
    using EncodeError = duramax::EncodeError;
    using BuildError = duramax::BuildError;
    using StoreAccessError = duramax::StoreAccessError;
    using SignalPhysicalValue = duramax::SignalPhysicalValue;

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

    static constexpr std::size_t kMessageCount = duramax::kMessageCount;
    static constexpr std::size_t kSignalCount = duramax::kSignalCount;

    static constexpr auto to_index(MessageId id) -> std::size_t {
        return duramax::to_index(id);
    }

    static constexpr auto to_index(SignalId id) -> std::size_t {
        return duramax::to_index(id);
    }

    static auto decode(std::uint32_t can_id,
                       const std::uint8_t* data,
                       std::size_t size)
        -> std::expected<MessageVariant, DecodeError>
    {
        return duramax::Codec::decode(can_id, data, size);
    }

    static auto encode(const MessageVariant& msg,
                       std::uint8_t* out,
                       std::size_t out_size)
        -> std::expected<std::uint8_t, EncodeError>
    {
        return duramax::Codec::encode(msg, out, out_size);
    }

    template <GeneratedMessage Msg>
    static auto encode(const Msg& msg,
                       std::uint8_t* out,
                       std::size_t out_size)
        -> std::expected<std::uint8_t, EncodeError>
    {
        return duramax::Codec::encode(msg, out, out_size);
    }

    static constexpr auto message_meta(MessageId id) -> const duramax::MessageMeta& {
        return duramax::message_meta(id);
    }

    static constexpr auto signal_meta(SignalId id) -> const duramax::SignalMeta& {
        return duramax::signal_meta(id);
    }

    static constexpr auto message_name(MessageId id) -> std::string_view {
        return duramax::message_name(id);
    }

    static constexpr auto signal_name(SignalId id) -> std::string_view {
        return duramax::signal_name(id);
    }

    static constexpr auto signal_unit(SignalId id) -> std::string_view {
        return duramax::signal_unit(id);
    }

    static constexpr auto signal_parent_message_name(SignalId id) -> std::string_view {
        return duramax::signal_parent_message_name(id);
    }

    static constexpr auto parent_message_id(SignalId sid) -> MessageId {
        return duramax::parent_message_id(sid);
    }

    static constexpr auto message_cycle_time_ms(MessageId id) -> std::uint32_t {
        return duramax::message_cycle_time_ms(id);
    }

    static constexpr auto message_signals(MessageId id) -> std::span<const SignalId> {
        return duramax::message_signals(id);
    }

    static constexpr auto find_message_by_frame_id(std::uint32_t frame_id)
        -> const duramax::MessageMeta*
    {
        return duramax::find_message_by_frame_id(frame_id);
    }

    static auto build_message_from_store(MessageId id, const ValueStore& store)
        -> std::expected<MessageVariant, BuildError>
    {
        return duramax::build_message_from_store(id, store);
    }

    static auto validate_message_buildable(MessageId id, const ValueStore& store)
        -> std::expected<void, BuildError>
    {
        return duramax::validate_message_buildable(id, store);
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
        auto built = duramax::build_message_from_store(id, store);
        if (!built) {
            return std::unexpected(EncodeFromStoreError::from_build(built.error()));
        }

        auto encoded = duramax::Codec::encode(*built, out, out_size);
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
        duramax::apply_to_store(store, msg, now_ms);
    }

    static void apply_to_store(ValueStore& store,
                               const MessageVariant& msg,
                               std::uint32_t now_ms)
    {
        duramax::apply_to_store(store, msg, now_ms);
    }
};

static_assert(CanDatabase<DuramaxDb>);

} // namespace duramax