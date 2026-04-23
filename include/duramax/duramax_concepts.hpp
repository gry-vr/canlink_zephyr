#pragma once

#include "duramax_metadata.hpp"
#include "duramax_types.hpp"

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <span>
#include <type_traits>

namespace duramax {

template <typename T>
concept GeneratedMessage =
    requires(T msg) {
        { T::id } -> std::convertible_to<MessageId>;
        { message_id_of(msg) } -> std::same_as<MessageId>;
    };

template <typename E>
concept ChoiceEnum = std::is_enum_v<E>;

template <typename Db>
concept CanDatabase =
    requires(const typename Db::ValueStore& store,
             typename Db::ValueStore& mutable_store,
             typename Db::MessageId msg_id,
             typename Db::SignalId sig_id,
             const typename Db::MessageVariant& mv,
             std::uint8_t* out,
             std::size_t out_size,
             std::uint32_t can_id,
             const std::uint8_t* data,
             std::size_t size,
             std::uint32_t now_ms) {
        typename Db::MessageId;
        typename Db::SignalId;
        typename Db::MessageVariant;
        typename Db::ValueStore;
        { Db::kMessageCount } -> std::convertible_to<std::size_t>;
        { Db::kSignalCount } -> std::convertible_to<std::size_t>;
        { Db::to_index(msg_id) } -> std::same_as<std::size_t>;
        { Db::to_index(sig_id) } -> std::same_as<std::size_t>;
        { Db::decode(can_id, data, size) };
        { Db::encode(mv, out, out_size) };
        { Db::build_message_from_store(msg_id, store) };
        { Db::validate_message_buildable(msg_id, store) };
        { Db::message_meta(msg_id) };
        { Db::signal_meta(sig_id) };
        { Db::message_signals(msg_id) } -> std::same_as<std::span<const typename Db::SignalId>>;
        { Db::find_message_by_frame_id(can_id) };
        { Db::message_cycle_time_ms(msg_id) } -> std::same_as<std::uint32_t>;
        { Db::parent_message_id(sig_id) } -> std::same_as<typename Db::MessageId>;
        Db::apply_to_store(mutable_store, mv, now_ms);
    };

template <typename SrcDb, auto SrcSig, typename DstDb, auto DstSig>
concept compatible_signal_types =
    requires {
        typename SrcDb::template signal_value_t<SrcSig>;
        typename DstDb::template signal_value_t<DstSig>;
    } &&
    std::same_as<
        typename SrcDb::template signal_value_t<SrcSig>,
        typename DstDb::template signal_value_t<DstSig>
    >;

} // namespace duramax