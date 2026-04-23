#include "reacher/reacher_codec.hpp"
#include "reacher/reacher_metadata.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <limits>
#include <type_traits>

namespace reacher {
namespace detail {

constexpr auto mask64(unsigned width) -> std::uint64_t {
    return (width >= 64U) ? ~0ULL : ((1ULL << width) - 1ULL);
}

constexpr auto sign_extend(std::uint64_t raw, unsigned width) -> std::int64_t {
    if (width == 0U || width >= 64U) {
        return static_cast<std::int64_t>(raw);
    }
    const std::uint64_t sign_bit = 1ULL << (width - 1U);
    const std::uint64_t full_mask = ~0ULL << width;
    const std::uint64_t extended = (raw & sign_bit) ? (raw | full_mask) : raw;
    return static_cast<std::int64_t>(extended);
}

inline auto load_u64_le(const std::uint8_t* data, std::size_t size) -> std::uint64_t {
    std::uint64_t out = 0;
    const std::size_t n = (size > 8U) ? 8U : size;
    for (std::size_t i = 0; i < n; ++i) {
        out |= (static_cast<std::uint64_t>(data[i]) << (8U * i));
    }
    return out;
}

inline auto extract_le(const std::uint8_t* data,
                       std::size_t size,
                       unsigned start_bit,
                       unsigned bit_length) -> std::uint64_t {
    const std::uint64_t packed = load_u64_le(data, size);
    return (packed >> start_bit) & mask64(bit_length);
}

// Motorola helper for signals that fit within 64 bits.
inline auto extract_be(const std::uint8_t* data,
                       std::size_t size,
                       unsigned start_bit,
                       unsigned bit_length) -> std::uint64_t {
    std::uint64_t out = 0;
    unsigned current_bit = start_bit;

    for (unsigned i = 0; i < bit_length; ++i) {
        const unsigned byte_index = current_bit / 8U;
        const unsigned bit_in_byte = current_bit % 8U;
        const unsigned shift = bit_in_byte;

        if (byte_index >= size) {
            break;
        }

        const std::uint64_t bit =
            (static_cast<std::uint64_t>(data[byte_index]) >> shift) & 0x1ULL;
        out = (out << 1U) | bit;

        if (bit_in_byte == 0U) {
            current_bit += 15U;
        } else {
            current_bit -= 1U;
        }
    }

    return out;
}

inline auto extract_raw(const std::uint8_t* data,
                        std::size_t size,
                        unsigned start_bit,
                        unsigned bit_length,
                        ByteOrder order) -> std::uint64_t {
    return (order == ByteOrder::little_endian)
        ? extract_le(data, size, start_bit, bit_length)
        : extract_be(data, size, start_bit, bit_length);
}

inline auto decode_unsigned(const std::uint8_t* data,
                            std::size_t size,
                            unsigned start_bit,
                            unsigned bit_length,
                            ByteOrder order) -> std::uint64_t {
    return extract_raw(data, size, start_bit, bit_length, order);
}

inline auto decode_signed(const std::uint8_t* data,
                          std::size_t size,
                          unsigned start_bit,
                          unsigned bit_length,
                          ByteOrder order) -> std::int64_t {
    const auto raw = extract_raw(data, size, start_bit, bit_length, order);
    return sign_extend(raw, bit_length);
}

inline auto to_physical_unsigned(const std::uint8_t* data,
                                 std::size_t size,
                                 unsigned start_bit,
                                 unsigned bit_length,
                                 ByteOrder order,
                                 double scale,
                                 double offset) -> double {
    return static_cast<double>(
        decode_unsigned(data, size, start_bit, bit_length, order)
    ) * scale + offset;
}

inline auto to_physical_signed(const std::uint8_t* data,
                               std::size_t size,
                               unsigned start_bit,
                               unsigned bit_length,
                               ByteOrder order,
                               double scale,
                               double offset) -> double {
    return static_cast<double>(
        decode_signed(data, size, start_bit, bit_length, order)
    ) * scale + offset;
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
    const std::int64_t minv = -(static_cast<std::int64_t>(1ULL << (bit_length - 1U)));
    const std::int64_t maxv =  static_cast<std::int64_t>((1ULL << (bit_length - 1U)) - 1ULL);
    return value >= minv && value <= maxv;
}

inline void insert_le(std::array<std::uint8_t, 8>& data,
                      unsigned start_bit,
                      unsigned bit_length,
                      std::uint64_t raw)
{
    for (unsigned i = 0; i < bit_length; ++i) {
        const unsigned bit_index = start_bit + i;
        const unsigned byte_index = bit_index / 8U;
        const unsigned bit_in_byte = bit_index % 8U;

        const std::uint8_t bit = static_cast<std::uint8_t>((raw >> i) & 0x1ULL);
        data[byte_index] &= static_cast<std::uint8_t>(~(1U << bit_in_byte));
        data[byte_index] |= static_cast<std::uint8_t>(bit << bit_in_byte);
    }
}

inline void insert_be(std::array<std::uint8_t, 8>& data,
                      unsigned start_bit,
                      unsigned bit_length,
                      std::uint64_t raw)
{
    unsigned current_bit = start_bit;

    for (unsigned i = 0; i < bit_length; ++i) {
        const unsigned src_shift = bit_length - 1U - i;
        const std::uint8_t bit = static_cast<std::uint8_t>((raw >> src_shift) & 0x1ULL);

        const unsigned byte_index = current_bit / 8U;
        const unsigned bit_in_byte = current_bit % 8U;
        const unsigned shift = bit_in_byte;

        data[byte_index] &= static_cast<std::uint8_t>(~(1U << shift));
        data[byte_index] |= static_cast<std::uint8_t>(bit << shift);

        if (bit_in_byte == 0U) {
            current_bit += 15U;
        } else {
            current_bit -= 1U;
        }
    }
}

inline void insert_raw(std::array<std::uint8_t, 8>& data,
                       unsigned start_bit,
                       unsigned bit_length,
                       ByteOrder order,
                       std::uint64_t raw)
{
    if (order == ByteOrder::little_endian) {
        insert_le(data, start_bit, bit_length, raw);
    } else {
        insert_be(data, start_bit, bit_length, raw);
    }
}

inline auto encode_unsigned_physical(double physical,
                                     double scale,
                                     double offset,
                                     unsigned bit_length)
    -> std::expected<std::uint64_t, EncodeError>
{
    if (scale == 0.0) {
        return std::unexpected(EncodeError::value_out_of_range);
    }

    const double raw_f = (physical - offset) / scale;
    if (!std::isfinite(raw_f)) {
        return std::unexpected(EncodeError::value_out_of_range);
    }

    const double rounded = std::round(raw_f);
    if (rounded < 0.0) {
        return std::unexpected(EncodeError::value_out_of_range);
    }

    if (rounded > static_cast<double>(std::numeric_limits<std::uint64_t>::max())) {
        return std::unexpected(EncodeError::value_out_of_range);
    }

    const auto raw = static_cast<std::uint64_t>(rounded);
    if (!fits_unsigned(raw, bit_length)) {
        return std::unexpected(EncodeError::value_out_of_range);
    }

    return raw;
}

inline auto encode_signed_physical(double physical,
                                   double scale,
                                   double offset,
                                   unsigned bit_length)
    -> std::expected<std::uint64_t, EncodeError>
{
    if (scale == 0.0) {
        return std::unexpected(EncodeError::value_out_of_range);
    }

    const double raw_f = (physical - offset) / scale;
    if (!std::isfinite(raw_f)) {
        return std::unexpected(EncodeError::value_out_of_range);
    }

    const double rounded = std::round(raw_f);
    if (rounded < static_cast<double>(std::numeric_limits<std::int64_t>::min()) ||
        rounded > static_cast<double>(std::numeric_limits<std::int64_t>::max())) {
        return std::unexpected(EncodeError::value_out_of_range);
    }

    const auto raw_signed = static_cast<std::int64_t>(rounded);
    if (!fits_signed(raw_signed, bit_length)) {
        return std::unexpected(EncodeError::value_out_of_range);
    }

    return static_cast<std::uint64_t>(raw_signed) & mask64(bit_length);
}

} // namespace detail

auto Codec::decode(std::uint32_t can_id,
                   const std::uint8_t* data,
                   std::size_t size)
    -> std::expected<MessageVariant, DecodeError>
{
    switch (can_id) {
    case 0x00000200u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        ReacherCtrl msg{};
        msg.eng_on =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    0U,
                    8U,
                    ByteOrder::little_endian
                )
            );
        msg.start =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    8U,
                    8U,
                    ByteOrder::little_endian
                )
            );
        msg.arm =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    16U,
                    8U,
                    ByteOrder::little_endian
                )
            );
        msg.test =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    24U,
                    8U,
                    ByteOrder::little_endian
                )
            );
        msg.aux_1 =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    32U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.throttle_rpm =
            detail::to_physical_unsigned(
                data,
                size,
                40U,
                16U,
                ByteOrder::little_endian,
                0.125,
                0.0
            );
        msg.aux_2 =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    56U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x00000202u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        ReacherEngineFeedback msg{};
        msg.ecu_on =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    8U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.f_pump_on =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    16U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.st_solenoid_on =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    24U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x00000300u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Export0 msg{};
        msg.eng_speed =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    7U,
                    16U,
                    ByteOrder::big_endian,
                    1.0,
                    0.0
                )
            );
        msg.actual_throttle =
            detail::to_physical_unsigned(
                data,
                size,
                23U,
                8U,
                ByteOrder::big_endian,
                0.4,
                0.0
            );
        msg.manifold_press =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    39U,
                    16U,
                    ByteOrder::big_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x00000303u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Export3 msg{};
        msg.fuel_rail_pressure =
            static_cast<std::int16_t>(
                detail::to_physical_signed(
                    data,
                    size,
                    55U,
                    16U,
                    ByteOrder::big_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x00000308u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Export8 msg{};
        msg.battery_bus_voltage =
            detail::to_physical_unsigned(
                data,
                size,
                7U,
                16U,
                ByteOrder::big_endian,
                0.05,
                0.0
            );

        return MessageVariant{msg};
    }
    case 0x0000030Bu: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        ExportB msg{};
        msg.coolant_temp =
            detail::to_physical_unsigned(
                data,
                size,
                7U,
                8U,
                ByteOrder::big_endian,
                1.8,
                -40.0
            );
        msg.oil_temp =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    15U,
                    16U,
                    ByteOrder::big_endian,
                    1.0,
                    0.0
                )
            );
        msg.oil_pressure =
            detail::to_physical_unsigned(
                data,
                size,
                39U,
                8U,
                ByteOrder::big_endian,
                0.580152,
                0.0
            );
        msg.exhaust_gas_temp =
            detail::to_physical_unsigned(
                data,
                size,
                55U,
                16U,
                ByteOrder::big_endian,
                0.05625,
                -459.4
            );

        return MessageVariant{msg};
    }
    case 0x00000501u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        ServoBatt msg{};
        msg.servo_bus_voltage =
            static_cast<std::uint32_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    15U,
                    16U,
                    ByteOrder::big_endian,
                    100.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    default:
        return std::unexpected(DecodeError::unknown_message);
    }
}

auto Codec::encode(const MessageVariant& msg,
                   std::uint8_t* out,
                   std::size_t out_size)
    -> std::expected<std::uint8_t, EncodeError>
{
    return std::visit(
        [&](const auto& m) -> std::expected<std::uint8_t, EncodeError> {
            using T = std::decay_t<decltype(m)>;

            std::array<std::uint8_t, 8> tmp{};
            tmp.fill(0);

            if constexpr (std::is_same_v<T, ReacherCtrl>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.eng_on),
                                           8U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    0U,
                    8U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.eng_on)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.start),
                                           8U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    8U,
                    8U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.start)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.arm),
                                           8U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    16U,
                    8U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.arm)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.test),
                                           8U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    24U,
                    8U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.test)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.aux_1),
                        1.0,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        32U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.throttle_rpm,
                        0.125,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        40U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.aux_2),
                        1.0,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        56U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, ReacherEngineFeedback>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.ecu_on),
                        1.0,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        8U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.f_pump_on),
                        1.0,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        16U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.st_solenoid_on),
                        1.0,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        24U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Export0>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.eng_speed),
                        1.0,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        7U,
                        16U,
                        ByteOrder::big_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.actual_throttle,
                        0.4,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        23U,
                        8U,
                        ByteOrder::big_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.manifold_press),
                        1.0,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        39U,
                        16U,
                        ByteOrder::big_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Export3>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_signed_physical(
                        static_cast<double>(m.fuel_rail_pressure),
                        1.0,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        55U,
                        16U,
                        ByteOrder::big_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Export8>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        m.battery_bus_voltage,
                        0.05,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        7U,
                        16U,
                        ByteOrder::big_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, ExportB>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        m.coolant_temp,
                        1.8,
                        -40.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        7U,
                        8U,
                        ByteOrder::big_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.oil_temp),
                        1.0,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        15U,
                        16U,
                        ByteOrder::big_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.oil_pressure,
                        0.580152,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        39U,
                        8U,
                        ByteOrder::big_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.exhaust_gas_temp,
                        0.05625,
                        -459.4,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        55U,
                        16U,
                        ByteOrder::big_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, ServoBatt>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.servo_bus_voltage),
                        100.0,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        15U,
                        16U,
                        ByteOrder::big_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }

            return std::unexpected(EncodeError::unsupported_message);
        },
        msg
    );
}

} // namespace reacher