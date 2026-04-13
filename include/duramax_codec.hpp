#pragma once

#include "duramax_types.hpp"

#include <cstddef>
#include <cstdint>
#include <expected>
#include <type_traits>

namespace duramax {

enum class DecodeError : std::uint8_t {
    unknown_message,
    bad_dlc,
    malformed
};

enum class EncodeError : std::uint8_t {
    buffer_too_small,
    value_out_of_range,
    unsupported_message
};

class Codec {
public:
    static auto decode(std::uint32_t can_id,
                       const std::uint8_t* data,
                       std::size_t size)
        -> std::expected<MessageVariant, DecodeError>;

    static auto encode(const MessageVariant& msg,
                       std::uint8_t* out,
                       std::size_t out_size)
        -> std::expected<std::uint8_t, EncodeError>;

    template <typename Msg>
    static auto encode(const Msg& msg,
                       std::uint8_t* out,
                       std::size_t out_size)
        -> std::expected<std::uint8_t, EncodeError>
    {
        return encode(MessageVariant{msg}, out, out_size);
    }
};

} // namespace duramax