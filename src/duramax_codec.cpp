#include "duramax/duramax_codec.hpp"
#include "duramax/duramax_metadata.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <limits>
#include <type_traits>

namespace duramax {
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
        const unsigned shift =  bit_in_byte;

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
    case 0x18FDD500u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Eec5ElectronicEngineControl5 msg{};
        msg.engine_turbocharger_1_calculated =
            detail::to_physical_unsigned(
                data,
                size,
                0U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );
        msg.commanded_vgt_position =
            detail::to_physical_unsigned(
                data,
                size,
                32U,
                16U,
                ByteOrder::little_endian,
                0.0025,
                0.0
            );
        msg.engine_variable_geometry_turboch =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    48U,
                    2U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.engine_fuel_control_control_mode =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    50U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engine_vgt_control_mode =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    52U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.actual_vgt_position =
            detail::to_physical_unsigned(
                data,
                size,
                56U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );

        return MessageVariant{msg};
    }
    case 0x10FCFD00u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Eec9ElectronicEngineControl9 msg{};
        msg.engine_exhaust_gas_recirculation =
            detail::to_physical_unsigned(
                data,
                size,
                0U,
                16U,
                ByteOrder::little_endian,
                0.0025,
                0.0
            );
        msg.commanded_fuel_rail_pressure =
            detail::to_physical_unsigned(
                data,
                size,
                32U,
                16U,
                ByteOrder::little_endian,
                0.00390625,
                0.0
            );
        msg.commanded_engine_fuel_injection =
            detail::to_physical_unsigned(
                data,
                size,
                48U,
                16U,
                ByteOrder::little_endian,
                0.00390625,
                0.0
            );

        return MessageVariant{msg};
    }
    case 0x10FCE300u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        EbccEngineExhaustBrakeCont msg{};
        msg.actual_boost_pressure =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    0U,
                    8U,
                    ByteOrder::little_endian,
                    2.0,
                    0.0
                )
            );
        msg.desired_boost_pressure =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    8U,
                    8U,
                    ByteOrder::little_endian,
                    2.0,
                    0.0
                )
            );
        msg.engine_exhaust_brake_actuator_co =
            detail::to_physical_unsigned(
                data,
                size,
                16U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );
        msg.engine_turbocharger_2_turbine_ou =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    24U,
                    8U,
                    ByteOrder::little_endian,
                    2.0,
                    0.0
                )
            );
        msg.desired_engine_turbocharger_2_tu =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    32U,
                    8U,
                    ByteOrder::little_endian,
                    2.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x18FE6900u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Et3EngineTemperature3 msg{};
        msg.engine_intake_manifold_1_air_tem =
            detail::to_physical_unsigned(
                data,
                size,
                0U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );
        msg.engine_coolant_temperature_high =
            detail::to_physical_unsigned(
                data,
                size,
                16U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );
        msg.engine_intake_valve_actuation_sy =
            detail::to_physical_unsigned(
                data,
                size,
                32U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );
        msg.engine_cac_outlet_temperature =
            detail::to_physical_unsigned(
                data,
                size,
                48U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );

        return MessageVariant{msg};
    }
    case 0x18C1FF00u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Dm21DiagnosticReadiness2 msg{};
        msg.engine_run_time_with_mil_on =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    32U,
                    16U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x18FDB800u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Dm26DiagnosticReadiness3 msg{};
        msg.time_since_engine_start =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    0U,
                    16U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x18FEF600u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Ic1IntakeExhaustCond1 msg{};
        msg.aft1dpfinpress =
            detail::to_physical_unsigned(
                data,
                size,
                0U,
                8U,
                ByteOrder::little_endian,
                0.5,
                0.0
            );
        msg.engintakemanifold1press =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    8U,
                    8U,
                    ByteOrder::little_endian,
                    2.0,
                    0.0
                )
            );
        msg.engintakemanifold1temp =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    16U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -40.0
                )
            );
        msg.engairintakepress =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    24U,
                    8U,
                    ByteOrder::little_endian,
                    2.0,
                    0.0
                )
            );
        msg.engairfilter1diffpress =
            detail::to_physical_unsigned(
                data,
                size,
                32U,
                8U,
                ByteOrder::little_endian,
                0.05,
                0.0
            );
        msg.engexhaustgastemp =
            detail::to_physical_unsigned(
                data,
                size,
                40U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );
        msg.engcoolantfilterdiffpress =
            detail::to_physical_unsigned(
                data,
                size,
                56U,
                8U,
                ByteOrder::little_endian,
                0.5,
                0.0
            );

        return MessageVariant{msg};
    }
    case 0x18FEF500u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        AmbAmbientConditions msg{};
        msg.barometric_pressurebarometric_pr =
            detail::to_physical_unsigned(
                data,
                size,
                0U,
                8U,
                ByteOrder::little_endian,
                0.5,
                0.0
            );
        msg.cabinteriortemp =
            detail::to_physical_unsigned(
                data,
                size,
                8U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );
        msg.ambient_air_temperature =
            detail::to_physical_unsigned(
                data,
                size,
                24U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );
        msg.engine_air_intake_temperature =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    40U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -40.0
                )
            );
        msg.roadsurfacetemp =
            detail::to_physical_unsigned(
                data,
                size,
                48U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );

        return MessageVariant{msg};
    }
    case 0x0CF00400u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Eec1ElectronicEngineControl1 msg{};
        msg.engine_torque_mode =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    0U,
                    4U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.actlengprcnttorquehighresolution =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    4U,
                    4U,
                    ByteOrder::little_endian
                )
            );
        msg.drivers_demand_engine_prcnt_torq =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    8U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -125.0
                )
            );
        msg.actual_engine_percent_torque =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    16U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -125.0
                )
            );
        msg.engine_speed =
            detail::to_physical_unsigned(
                data,
                size,
                24U,
                16U,
                ByteOrder::little_endian,
                0.125,
                0.0
            );
        msg.srcaddrssofcntrllngdvcforengctrl =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    40U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.engstartermode =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    48U,
                    4U,
                    ByteOrder::little_endian
                )
            );
        msg.engine_demand_percent_torque =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    56U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -125.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x0CF00300u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Eec2ElectronicEngineControl2 msg{};
        msg.accelpedal1lowidleswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    0U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.accelpedalkickdownswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    2U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.roadspeedlimitstatus =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    4U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.accelpedal2lowidleswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    6U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.accelpedalpos1 =
            detail::to_physical_unsigned(
                data,
                size,
                8U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );
        msg.engpercentloadatcurrentspeed =
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
        msg.remoteaccelpedalpos =
            detail::to_physical_unsigned(
                data,
                size,
                24U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );
        msg.accelpedalpos2 =
            detail::to_physical_unsigned(
                data,
                size,
                32U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );
        msg.vhcleaccelerationratelimitstatus =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    40U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.mmntaryengmaxpowerenablefeedback =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    42U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.dpfthermalmanagementactive =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    44U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.scrthermalmanagementactive =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    46U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.actlmaxavailableengpercenttorque =
            detail::to_physical_unsigned(
                data,
                size,
                48U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );
        msg.estpumpingpercenttorque =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    56U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -125.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x18FEDF00u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Eec3ElectronicEngineControl3 msg{};
        msg.nominalfrictionpercenttorque =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    0U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -125.0
                )
            );
        msg.enginesdesiredoperatingspeed =
            detail::to_physical_unsigned(
                data,
                size,
                8U,
                16U,
                ByteOrder::little_endian,
                0.125,
                0.0
            );
        msg.engnsdsrdoprtngspdasymmtryadjstm =
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
        msg.estengprsiticlossespercenttorque =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    32U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -125.0
                )
            );
        msg.aft1exhgasmfr =
            detail::to_physical_unsigned(
                data,
                size,
                40U,
                16U,
                ByteOrder::little_endian,
                0.2,
                0.0
            );
        msg.aft1indewpoint =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    56U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.aft1exhdewpoint =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    58U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.aft2indewpoint =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    60U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.aft2exhdewpoint =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    62U,
                    2U,
                    ByteOrder::little_endian
                )
            );

        return MessageVariant{msg};
    }
    case 0x18FEEF00u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        EflP1EngFluidLevelPress1 msg{};
        msg.engfueldeliverypress =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    0U,
                    8U,
                    ByteOrder::little_endian,
                    4.0,
                    0.0
                )
            );
        msg.engexcrankcaseblowbypress =
            detail::to_physical_unsigned(
                data,
                size,
                8U,
                8U,
                ByteOrder::little_endian,
                0.05,
                0.0
            );
        msg.engoillevel =
            detail::to_physical_unsigned(
                data,
                size,
                16U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );
        msg.engoilpress =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    24U,
                    8U,
                    ByteOrder::little_endian,
                    4.0,
                    0.0
                )
            );
        msg.engcrankcasepress =
            detail::to_physical_unsigned(
                data,
                size,
                32U,
                16U,
                ByteOrder::little_endian,
                0.0078125,
                -250.0
            );
        msg.engcoolantpress =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    48U,
                    8U,
                    ByteOrder::little_endian,
                    2.0,
                    0.0
                )
            );
        msg.engcoolantlevel =
            detail::to_physical_unsigned(
                data,
                size,
                56U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );

        return MessageVariant{msg};
    }
    case 0x18FEDB00u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        EflP2EngFluidLevelPress2 msg{};
        msg.enginjectionctrlpress =
            detail::to_physical_unsigned(
                data,
                size,
                0U,
                16U,
                ByteOrder::little_endian,
                0.00390625,
                0.0
            );
        msg.enginjectormeteringrail1press =
            detail::to_physical_unsigned(
                data,
                size,
                16U,
                16U,
                ByteOrder::little_endian,
                0.00390625,
                0.0
            );
        msg.enginjectortimingrail1press =
            detail::to_physical_unsigned(
                data,
                size,
                32U,
                16U,
                ByteOrder::little_endian,
                0.00390625,
                0.0
            );
        msg.enginjectormeteringrail2press =
            detail::to_physical_unsigned(
                data,
                size,
                48U,
                16U,
                ByteOrder::little_endian,
                0.00390625,
                0.0
            );

        return MessageVariant{msg};
    }
    case 0x18FEEE00u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Et1EngineTemperature1 msg{};
        msg.engcoolanttemp =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    0U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -40.0
                )
            );
        msg.engfueltemp1 =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    8U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -40.0
                )
            );
        msg.engoiltemp1 =
            detail::to_physical_unsigned(
                data,
                size,
                16U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );
        msg.engturbooiltemp =
            detail::to_physical_unsigned(
                data,
                size,
                32U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );
        msg.engintercoolertemp =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    48U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -40.0
                )
            );
        msg.engintercoolerthermostatopening =
            detail::to_physical_unsigned(
                data,
                size,
                56U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );

        return MessageVariant{msg};
    }
    case 0x18FEF200u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Lfe1FuelEconomyLiquid1 msg{};
        msg.engfuelrate =
            detail::to_physical_unsigned(
                data,
                size,
                0U,
                16U,
                ByteOrder::little_endian,
                0.05,
                0.0
            );
        msg.enginstantaneousfueleconomy =
            detail::to_physical_unsigned(
                data,
                size,
                16U,
                16U,
                ByteOrder::little_endian,
                0.00195312,
                0.0
            );
        msg.engaveragefueleconomy =
            detail::to_physical_unsigned(
                data,
                size,
                32U,
                16U,
                ByteOrder::little_endian,
                0.00195312,
                0.0
            );
        msg.engthrottlevalve1pos =
            detail::to_physical_unsigned(
                data,
                size,
                48U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );
        msg.engthrottlevalve2pos =
            detail::to_physical_unsigned(
                data,
                size,
                56U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );

        return MessageVariant{msg};
    }
    case 0x18ECFF00u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        TransportprotocolHeader msg{};
        msg.controlbyte =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    0U,
                    8U,
                    ByteOrder::little_endian
                )
            );
        msg.totalmessagesizeeoma =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    8U,
                    16U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.connectionabortreason =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    8U,
                    8U,
                    ByteOrder::little_endian
                )
            );
        msg.totalmessagesize =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    8U,
                    16U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.numberofpacketsthatcanbesent =
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
        msg.totalmessagesizebam =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    8U,
                    16U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.nextpacketnumbertobesent =
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
        msg.totalnumberofpackets =
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
        msg.totalnumberofpacketseoma =
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
        msg.totalnumberofpacketsbam =
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
        msg.maximumnumberofpackets =
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
        msg.pgnumber =
            static_cast<std::uint32_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    40U,
                    24U,
                    ByteOrder::little_endian
                )
            );

        return MessageVariant{msg};
    }
    case 0x18EBFF00u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        TransportprotocolData msg{};
        msg.sequencenumber =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    0U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x18FECA00u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Dm01ActiveDiagnostics msg{};
        msg.protectlampstatus =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    0U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.amberwarninglampstatus =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    2U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.redstoplampstate =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    4U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.malfunctionindicatorlampstatus =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    6U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.flashprotectlamp =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    8U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.flashamberwarninglamp =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    10U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.flashredstoplamp =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    12U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.flashmalfuncindicatorlamp =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    14U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.dtc1 =
            static_cast<std::uint32_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    16U,
                    32U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x0C000031u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Tsc131 msg{};
        msg.engoverridectrlmode =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    0U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engrequestedspeedctrlconditions =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    2U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.overridectrlmodepriority =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    4U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engrequestedspeed_speedlimit =
            detail::to_physical_unsigned(
                data,
                size,
                8U,
                16U,
                ByteOrder::little_endian,
                0.125,
                0.0
            );
        msg.engrequestedtorque_torquelimit =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    24U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -125.0
                )
            );
        msg.tsc1transrate =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    32U,
                    3U,
                    ByteOrder::little_endian
                )
            );
        msg.tsc1ctrlpurpose =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    35U,
                    5U,
                    ByteOrder::little_endian
                )
            );
        msg.engrequestedtorquehighresolution =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    40U,
                    4U,
                    ByteOrder::little_endian
                )
            );
        msg.messagecounter =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    56U,
                    4U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.messagechecksum =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    60U,
                    4U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x18FCF600u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Cac1ChargeAirCooler1 msg{};
        msg.engine_charge_air_cooler_1_intak =
            detail::to_physical_unsigned(
                data,
                size,
                0U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );
        msg.engine_charge_air_cooler_1_ambie =
            detail::to_physical_unsigned(
                data,
                size,
                16U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );
        msg.engine_charge_air_cooler_1_effic =
            detail::to_physical_unsigned(
                data,
                size,
                32U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );

        return MessageVariant{msg};
    }
    case 0x18FEE500u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        HoursEngineHoursRevolutions msg{};
        msg.engine_total_hours_of_operation =
            detail::to_physical_unsigned(
                data,
                size,
                0U,
                32U,
                ByteOrder::little_endian,
                0.05,
                0.0
            );
        msg.engine_total_revolutions_249 =
            detail::to_physical_unsigned(
                data,
                size,
                32U,
                32U,
                ByteOrder::little_endian,
                1000.0,
                0.0
            );

        return MessageVariant{msg};
    }
    case 0x18FE9700u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Tci5TurbochargerInformation5 msg{};
        msg.engine_turbocharger_1_turbine_ou =
            detail::to_physical_unsigned(
                data,
                size,
                0U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );
        msg.engine_turbocharger_2_turbine_ou =
            detail::to_physical_unsigned(
                data,
                size,
                16U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );
        msg.engine_turbocharger_3_turbine_ou =
            detail::to_physical_unsigned(
                data,
                size,
                32U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );
        msg.engine_turbocharger_4_turbine_ou =
            detail::to_physical_unsigned(
                data,
                size,
                48U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );

        return MessageVariant{msg};
    }
    case 0x18FEF700u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Vep1VehicleElectricalPower1 msg{};
        msg.net_battery_current_114 =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    0U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -125.0
                )
            );
        msg.alternator_current_115 =
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
        msg.charging_system_potential_volta =
            detail::to_physical_unsigned(
                data,
                size,
                16U,
                16U,
                ByteOrder::little_endian,
                0.05,
                0.0
            );
        msg.battery_potential_power_input_1 =
            detail::to_physical_unsigned(
                data,
                size,
                32U,
                16U,
                ByteOrder::little_endian,
                0.05,
                0.0
            );
        msg.keyswitch_battery_potential_158 =
            detail::to_physical_unsigned(
                data,
                size,
                48U,
                16U,
                ByteOrder::little_endian,
                0.05,
                0.0
            );

        return MessageVariant{msg};
    }
    case 0x18FC0B00u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Eec20ElectronicEngineControl msg{};
        msg.absolute_engine_load =
            detail::to_physical_unsigned(
                data,
                size,
                40U,
                16U,
                ByteOrder::little_endian,
                0.025,
                0.0
            );

        return MessageVariant{msg};
    }
    case 0x0CF03900u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        EasiEngineAirSystemInfo msg{};
        msg.engine_intake_maf =
            detail::to_physical_unsigned(
                data,
                size,
                16U,
                16U,
                ByteOrder::little_endian,
                0.000976562,
                0.0
            );

        return MessageVariant{msg};
    }
    case 0x0C000003u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Tsc103 msg{};
        msg.engoverridectrlmode =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    0U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engrequestedspeedctrlconditions =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    2U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.overridectrlmodepriority =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    4U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engrequestedspeed_speedlimit =
            detail::to_physical_unsigned(
                data,
                size,
                8U,
                16U,
                ByteOrder::little_endian,
                0.125,
                0.0
            );
        msg.engrequestedtorque_torquelimit =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    24U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -125.0
                )
            );
        msg.tsc1transrate =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    32U,
                    3U,
                    ByteOrder::little_endian
                )
            );
        msg.tsc1ctrlpurpose =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    35U,
                    5U,
                    ByteOrder::little_endian
                )
            );
        msg.engrequestedtorquehighresolution =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    40U,
                    4U,
                    ByteOrder::little_endian
                )
            );
        msg.messagecounter =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    56U,
                    4U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.messagechecksum =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    60U,
                    4U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x0C00000Bu: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Tsc10b msg{};
        msg.engoverridectrlmode =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    0U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engrequestedspeedctrlconditions =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    2U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.overridectrlmodepriority =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    4U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engrequestedspeed_speedlimit =
            detail::to_physical_unsigned(
                data,
                size,
                8U,
                16U,
                ByteOrder::little_endian,
                0.125,
                0.0
            );
        msg.engrequestedtorque_torquelimit =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    24U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -125.0
                )
            );
        msg.tsc1transrate =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    32U,
                    3U,
                    ByteOrder::little_endian
                )
            );
        msg.tsc1ctrlpurpose =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    35U,
                    5U,
                    ByteOrder::little_endian
                )
            );
        msg.engrequestedtorquehighresolution =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    40U,
                    4U,
                    ByteOrder::little_endian
                )
            );
        msg.messagecounter =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    56U,
                    4U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.messagechecksum =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    60U,
                    4U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x18E3005Eu: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Dm07 msg{};
        msg.testidentifier =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    0U,
                    8U,
                    ByteOrder::little_endian
                )
            );
        msg.spn1 =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    8U,
                    16U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.failuremodeidentifier1 =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    24U,
                    5U,
                    ByteOrder::little_endian
                )
            );
        msg.spn1high =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    29U,
                    3U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x18FED000u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Dm08 msg{};
        msg.testidentifier =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    0U,
                    8U,
                    ByteOrder::little_endian
                )
            );
        msg.testtype =
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
        msg.testvalue =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    16U,
                    16U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.testlimitmaximum =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    32U,
                    16U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.testlimitminimum =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    48U,
                    16U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x18F00029u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Erc1ElectronicRetarderCntrl msg{};
        msg.retardertorquemode =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    0U,
                    4U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.retarderenablebrakeassistswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    4U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.retarderenableshiftassistswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    6U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.actualretarderpercenttorque =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    8U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -125.0
                )
            );
        msg.intendedretarderpercenttorque =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    16U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -125.0
                )
            );
        msg.engcoolantloadincrease =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    24U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.retarderrequestingbrakelight =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    26U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.retarderroadspeedlimitswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    28U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.retarderroadspeedexceededstatus =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    30U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.srcaddrssofcntrllngdvcfrrtrdrctr =
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
        msg.drvrsdemandretarderpercenttorque =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    40U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -125.0
                )
            );
        msg.retarderselectionnonengine =
            detail::to_physical_unsigned(
                data,
                size,
                48U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );
        msg.actlmxavlblretarderpercenttorque =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    56U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -125.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x0CF00203u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Etc1ElectronicTransCntrl1 msg{};
        msg.transdrivelineengaged =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    0U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.trnstorqueconverterlockupengaged =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    2U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.transshiftinprocess =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    4U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.trnstrqcnvrtrlckptrnstninprocess =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    6U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.transoutputshaftspeed =
            detail::to_physical_unsigned(
                data,
                size,
                8U,
                16U,
                ByteOrder::little_endian,
                0.125,
                0.0
            );
        msg.percentclutchslip =
            detail::to_physical_unsigned(
                data,
                size,
                24U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );
        msg.engmomentaryoverspeedenable =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    32U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.progressiveshiftdisable =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    34U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.momentaryengmaxpowerenable =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    36U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.transinputshaftspeed =
            detail::to_physical_unsigned(
                data,
                size,
                40U,
                16U,
                ByteOrder::little_endian,
                0.125,
                0.0
            );
        msg.srcaddrssofcntrllngdvcfrtrnsctrl =
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
    case 0x18F00503u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Etc2ElectronicTransCntrl2 msg{};
        msg.transselectedgear =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    0U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -125.0
                )
            );
        msg.transactualgearratio =
            detail::to_physical_unsigned(
                data,
                size,
                8U,
                16U,
                ByteOrder::little_endian,
                0.001,
                0.0
            );
        msg.transcurrentgear =
            static_cast<std::int16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    24U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    -125.0
                )
            );
        msg.transrequestedrange =
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
        msg.transcurrentrange =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
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
    case 0x18EA005Eu: {
        if (size != 3U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Rqst005e msg{};
        msg.parametergroupnumber =
            static_cast<std::uint32_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    0U,
                    24U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x18EA0021u: {
        if (size != 3U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Rqst0021 msg{};
        msg.parametergroupnumber =
            static_cast<std::uint32_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    0U,
                    24U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x18EAFF5Eu: {
        if (size != 3U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        RqstGlobal5e msg{};
        msg.parametergroupnumber =
            static_cast<std::uint32_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    0U,
                    24U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x18EAFF03u: {
        if (size != 3U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        RqstGlobal03 msg{};
        msg.parametergroupnumber =
            static_cast<std::uint32_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    0U,
                    24U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x18FD8321u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        TciTransferCaseInformation msg{};
        msg.transfercasestatus =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    0U,
                    3U,
                    ByteOrder::little_endian
                )
            );
        msg.dirstatus =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    3U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.actualgearratio =
            detail::to_physical_unsigned(
                data,
                size,
                8U,
                16U,
                ByteOrder::little_endian,
                0.01,
                0.0
            );
        msg.messagecounter =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    56U,
                    4U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.messagechecksum =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    60U,
                    4U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );

        return MessageVariant{msg};
    }
    case 0x18FEF803u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Trf1TransmissionFluids1 msg{};
        msg.clutchpress =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    0U,
                    8U,
                    ByteOrder::little_endian,
                    16.0,
                    0.0
                )
            );
        msg.transoillevel1 =
            detail::to_physical_unsigned(
                data,
                size,
                8U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );
        msg.transfilterdiffpress =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    16U,
                    8U,
                    ByteOrder::little_endian,
                    2.0,
                    0.0
                )
            );
        msg.transoilpress =
            static_cast<std::uint16_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    24U,
                    8U,
                    ByteOrder::little_endian,
                    16.0,
                    0.0
                )
            );
        msg.transoiltemp1 =
            detail::to_physical_unsigned(
                data,
                size,
                32U,
                16U,
                ByteOrder::little_endian,
                0.03125,
                -273.0
            );
        msg.transoillevel1high_low =
            detail::to_physical_unsigned(
                data,
                size,
                48U,
                8U,
                ByteOrder::little_endian,
                0.5,
                -62.5
            );
        msg.transoillevel1countdowntimer =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    56U,
                    4U,
                    ByteOrder::little_endian
                )
            );
        msg.transoillevel1measurementstatus =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    60U,
                    4U,
                    ByteOrder::little_endian
                )
            );

        return MessageVariant{msg};
    }
    case 0x18FEED00u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        CcssCruiseControlVehicleSpd msg{};
        msg.maxvehiclespeedlimit =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    0U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.cruisectrlhighsetlimitspeed =
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
        msg.cruisectrllowsetlimitspeed =
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
        msg.maxvehiclespeedlimit6808 =
            detail::to_physical_unsigned(
                data,
                size,
                24U,
                16U,
                ByteOrder::little_endian,
                0.00390625,
                0.0
            );
        msg.ctrlsyslowsetlmtspd =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    40U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.ctrldiscmdsupport =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    48U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.ctrlresumecmdsupport =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    50U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.ctrlpausecmdsupport =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    52U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.ctrlsetcmdsupport =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    54U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.powertrainadaptivecctype =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    56U,
                    4U,
                    ByteOrder::little_endian
                )
            );

        return MessageVariant{msg};
    }
    case 0x18FEF100u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Ccvs1CruiseControlVehspd msg{};
        msg.twospeedaxleswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    0U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.parkingbrakeswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    2U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.cruisectrlpauseswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    4U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.parkbrakereleaseinhibitrq =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    6U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.wheelbasedvehiclespeed =
            detail::to_physical_unsigned(
                data,
                size,
                8U,
                16U,
                ByteOrder::little_endian,
                0.00390625,
                0.0
            );
        msg.cruisectrlactive =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    24U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.cruisectrlenableswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    26U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.brakeswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    28U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.clutchswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    30U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.cruisectrlsetswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    32U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.cruisectrlcoastswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    34U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.cruisectrlresumeswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    36U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.cruisectrlaccelerateswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    38U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.cruisectrlsetspeed =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    40U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.ptogovernorstate =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    48U,
                    5U,
                    ByteOrder::little_endian
                )
            );
        msg.cruisectrlstates =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    53U,
                    3U,
                    ByteOrder::little_endian
                )
            );
        msg.engidleincrementswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    56U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engidledecrementswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    58U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engtestmodeswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    60U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engshutdownoverrideswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    62U,
                    2U,
                    ByteOrder::little_endian
                )
            );

        return MessageVariant{msg};
    }
    case 0x18F0010Bu: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Ebc1ElectronicBrakeCntrl msg{};
        msg.asrengctrlactive =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    0U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.asrbrakectrlactive =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    2U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.antilockbrakingactive =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    4U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.ebsbrakeswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    6U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.brakepedalpos =
            detail::to_physical_unsigned(
                data,
                size,
                8U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );
        msg.absoffroadswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    16U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.asroffroadswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    18U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.asrhillholderswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    20U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.tractionctrloverrideswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    22U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.accelinterlockswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    24U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engderateswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    26U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engauxshutdownswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    28U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.remoteaccelenableswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    30U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engretarderselection =
            detail::to_physical_unsigned(
                data,
                size,
                32U,
                8U,
                ByteOrder::little_endian,
                0.4,
                0.0
            );
        msg.absfullyoperational =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    40U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.ebsredwarningsignal =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    42U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.abs_ebsamberwarningsignal =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    44U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.atc_asrinformationsignal =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    46U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.srcaddrssofcntrllngdvcfrbrkectrl =
            static_cast<std::uint8_t>(
                detail::to_physical_unsigned(
                    data,
                    size,
                    48U,
                    8U,
                    ByteOrder::little_endian,
                    1.0,
                    0.0
                )
            );
        msg.railroadmodesw =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    56U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.haltbrakeswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    58U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.trailerabsstatus =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    60U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.trctrmntdtrailerabswarningsignal =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    62U,
                    2U,
                    ByteOrder::little_endian
                )
            );

        return MessageVariant{msg};
    }
    case 0x18FEE400u: {
        if (size != 8U) {
            return std::unexpected(DecodeError::bad_dlc);
        }

        Shutdn msg{};
        msg.engidleshutdownhasshutdowneng =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    0U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engidleshutdowndriveralertmode =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    2U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engidleshutdowntimeroverride =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    4U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engidleshutdowntimerstate =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    6U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engidleshutdowntimerfunction =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    14U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.a_chighpressfanswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    16U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.refrigerantlowpressswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    18U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.refrigeranthighpressswitch =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    20U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engwaittostartlamp =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    24U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engprtectionsystemhasshutdowneng =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    32U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engprtctnsystmapprachingshutdown =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    34U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engprotectionsystemtimeroverride =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    36U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engprotectionsystemtimerstate =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    38U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engprotectionsystemconfig =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    46U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engalarmacknowledge =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    48U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engalarmoutputcmdstatus =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    50U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engairshutoffcmdstatus =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    52U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engoverspeedtest =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    54U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engairshutoffstatus =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    56U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.ptoshutdownhasshutdowneng =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    58U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.clntlvlengprtctionshutdownstatus =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    60U,
                    2U,
                    ByteOrder::little_endian
                )
            );
        msg.engoilpresssw =
            static_cast<std::uint8_t>(
                detail::decode_unsigned(
                    data,
                    size,
                    62U,
                    2U,
                    ByteOrder::little_endian
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

            if constexpr (std::is_same_v<T, Eec5ElectronicEngineControl5>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engine_turbocharger_1_calculated,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.commanded_vgt_position,
                        0.0025,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        32U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.engine_variable_geometry_turboch),
                        1.0,
                        0.0,
                        2U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        48U,
                        2U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engine_fuel_control_control_mode),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    50U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engine_fuel_control_control_mode)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engine_vgt_control_mode),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    52U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engine_vgt_control_mode)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.actual_vgt_position,
                        0.4,
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
            if constexpr (std::is_same_v<T, Eec9ElectronicEngineControl9>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engine_exhaust_gas_recirculation,
                        0.0025,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.commanded_fuel_rail_pressure,
                        0.00390625,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        32U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.commanded_engine_fuel_injection,
                        0.00390625,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        48U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, EbccEngineExhaustBrakeCont>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.actual_boost_pressure),
                        2.0,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.desired_boost_pressure),
                        2.0,
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
                        m.engine_exhaust_brake_actuator_co,
                        0.4,
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
                        static_cast<double>(m.engine_turbocharger_2_turbine_ou),
                        2.0,
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
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.desired_engine_turbocharger_2_tu),
                        2.0,
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

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Et3EngineTemperature3>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engine_intake_manifold_1_air_tem,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engine_coolant_temperature_high,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        16U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engine_intake_valve_actuation_sy,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        32U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engine_cac_outlet_temperature,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        48U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Dm21DiagnosticReadiness2>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.engine_run_time_with_mil_on),
                        1.0,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        32U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Dm26DiagnosticReadiness3>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.time_since_engine_start),
                        1.0,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Ic1IntakeExhaustCond1>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        m.aft1dpfinpress,
                        0.5,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.engintakemanifold1press),
                        2.0,
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
                        static_cast<double>(m.engintakemanifold1temp),
                        1.0,
                        -40.0,
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
                        static_cast<double>(m.engairintakepress),
                        2.0,
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
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engairfilter1diffpress,
                        0.05,
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
                        m.engexhaustgastemp,
                        0.03125,
                        -273.0,
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
                        m.engcoolantfilterdiffpress,
                        0.5,
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
            if constexpr (std::is_same_v<T, AmbAmbientConditions>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        m.barometric_pressurebarometric_pr,
                        0.5,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.cabinteriortemp,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        8U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.ambient_air_temperature,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        24U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.engine_air_intake_temperature),
                        1.0,
                        -40.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        40U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.roadsurfacetemp,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        48U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Eec1ElectronicEngineControl1>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.engine_torque_mode),
                        1.0,
                        0.0,
                        4U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        4U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.actlengprcnttorquehighresolution),
                                           4U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    4U,
                    4U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.actlengprcnttorquehighresolution)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.drivers_demand_engine_prcnt_torq),
                        1.0,
                        -125.0,
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
                        static_cast<double>(m.actual_engine_percent_torque),
                        1.0,
                        -125.0,
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
                        m.engine_speed,
                        0.125,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        24U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.srcaddrssofcntrllngdvcforengctrl),
                        1.0,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        40U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engstartermode),
                                           4U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    48U,
                    4U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engstartermode)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.engine_demand_percent_torque),
                        1.0,
                        -125.0,
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
            if constexpr (std::is_same_v<T, Eec2ElectronicEngineControl2>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.accelpedal1lowidleswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    0U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.accelpedal1lowidleswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.accelpedalkickdownswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    2U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.accelpedalkickdownswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.roadspeedlimitstatus),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    4U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.roadspeedlimitstatus)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.accelpedal2lowidleswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    6U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.accelpedal2lowidleswitch)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.accelpedalpos1,
                        0.4,
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
                        static_cast<double>(m.engpercentloadatcurrentspeed),
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
                        m.remoteaccelpedalpos,
                        0.4,
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
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.accelpedalpos2,
                        0.4,
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
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.vhcleaccelerationratelimitstatus),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    40U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.vhcleaccelerationratelimitstatus)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.mmntaryengmaxpowerenablefeedback),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    42U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.mmntaryengmaxpowerenablefeedback)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.dpfthermalmanagementactive),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    44U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.dpfthermalmanagementactive)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.scrthermalmanagementactive),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    46U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.scrthermalmanagementactive)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.actlmaxavailableengpercenttorque,
                        0.4,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        48U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.estpumpingpercenttorque),
                        1.0,
                        -125.0,
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
            if constexpr (std::is_same_v<T, Eec3ElectronicEngineControl3>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.nominalfrictionpercenttorque),
                        1.0,
                        -125.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.enginesdesiredoperatingspeed,
                        0.125,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        8U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.engnsdsrdoprtngspdasymmtryadjstm),
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
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.estengprsiticlossespercenttorque),
                        1.0,
                        -125.0,
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
                        m.aft1exhgasmfr,
                        0.2,
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
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.aft1indewpoint),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    56U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.aft1indewpoint)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.aft1exhdewpoint),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    58U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.aft1exhdewpoint)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.aft2indewpoint),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    60U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.aft2indewpoint)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.aft2exhdewpoint),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    62U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.aft2exhdewpoint)
                );

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, EflP1EngFluidLevelPress1>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.engfueldeliverypress),
                        4.0,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engexcrankcaseblowbypress,
                        0.05,
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
                        m.engoillevel,
                        0.4,
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
                        static_cast<double>(m.engoilpress),
                        4.0,
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
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engcrankcasepress,
                        0.0078125,
                        -250.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        32U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.engcoolantpress),
                        2.0,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        48U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engcoolantlevel,
                        0.4,
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
            if constexpr (std::is_same_v<T, EflP2EngFluidLevelPress2>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        m.enginjectionctrlpress,
                        0.00390625,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.enginjectormeteringrail1press,
                        0.00390625,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        16U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.enginjectortimingrail1press,
                        0.00390625,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        32U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.enginjectormeteringrail2press,
                        0.00390625,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        48U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Et1EngineTemperature1>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.engcoolanttemp),
                        1.0,
                        -40.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.engfueltemp1),
                        1.0,
                        -40.0,
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
                        m.engoiltemp1,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        16U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engturbooiltemp,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        32U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.engintercoolertemp),
                        1.0,
                        -40.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        48U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engintercoolerthermostatopening,
                        0.4,
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
            if constexpr (std::is_same_v<T, Lfe1FuelEconomyLiquid1>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engfuelrate,
                        0.05,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.enginstantaneousfueleconomy,
                        0.00195312,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        16U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engaveragefueleconomy,
                        0.00195312,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        32U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engthrottlevalve1pos,
                        0.4,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        48U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engthrottlevalve2pos,
                        0.4,
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
            if constexpr (std::is_same_v<T, TransportprotocolHeader>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.controlbyte),
                                           8U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    0U,
                    8U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.controlbyte)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.totalmessagesizeeoma),
                        1.0,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        8U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.connectionabortreason),
                                           8U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    8U,
                    8U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.connectionabortreason)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.totalmessagesize),
                        1.0,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        8U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.numberofpacketsthatcanbesent),
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
                        static_cast<double>(m.totalmessagesizebam),
                        1.0,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        8U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.nextpacketnumbertobesent),
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
                        static_cast<double>(m.totalnumberofpackets),
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
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.totalnumberofpacketseoma),
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
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.totalnumberofpacketsbam),
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
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.maximumnumberofpackets),
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
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.pgnumber),
                                           24U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    40U,
                    24U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.pgnumber)
                );

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, TransportprotocolData>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.sequencenumber),
                        1.0,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Dm01ActiveDiagnostics>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.protectlampstatus),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    0U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.protectlampstatus)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.amberwarninglampstatus),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    2U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.amberwarninglampstatus)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.redstoplampstate),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    4U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.redstoplampstate)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.malfunctionindicatorlampstatus),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    6U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.malfunctionindicatorlampstatus)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.flashprotectlamp),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    8U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.flashprotectlamp)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.flashamberwarninglamp),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    10U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.flashamberwarninglamp)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.flashredstoplamp),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    12U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.flashredstoplamp)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.flashmalfuncindicatorlamp),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    14U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.flashmalfuncindicatorlamp)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.dtc1),
                        1.0,
                        0.0,
                        32U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        16U,
                        32U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Tsc131>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engoverridectrlmode),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    0U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engoverridectrlmode)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engrequestedspeedctrlconditions),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    2U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engrequestedspeedctrlconditions)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.overridectrlmodepriority),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    4U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.overridectrlmodepriority)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engrequestedspeed_speedlimit,
                        0.125,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        8U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.engrequestedtorque_torquelimit),
                        1.0,
                        -125.0,
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
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.tsc1transrate),
                                           3U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    32U,
                    3U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.tsc1transrate)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.tsc1ctrlpurpose),
                                           5U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    35U,
                    5U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.tsc1ctrlpurpose)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engrequestedtorquehighresolution),
                                           4U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    40U,
                    4U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engrequestedtorquehighresolution)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.messagecounter),
                        1.0,
                        0.0,
                        4U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        56U,
                        4U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.messagechecksum),
                        1.0,
                        0.0,
                        4U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        60U,
                        4U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Cac1ChargeAirCooler1>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engine_charge_air_cooler_1_intak,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engine_charge_air_cooler_1_ambie,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        16U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engine_charge_air_cooler_1_effic,
                        0.4,
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

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, HoursEngineHoursRevolutions>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engine_total_hours_of_operation,
                        0.05,
                        0.0,
                        32U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        32U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engine_total_revolutions_249,
                        1000.0,
                        0.0,
                        32U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        32U,
                        32U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Tci5TurbochargerInformation5>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engine_turbocharger_1_turbine_ou,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engine_turbocharger_2_turbine_ou,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        16U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engine_turbocharger_3_turbine_ou,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        32U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engine_turbocharger_4_turbine_ou,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        48U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Vep1VehicleElectricalPower1>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.net_battery_current_114),
                        1.0,
                        -125.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.alternator_current_115),
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
                        m.charging_system_potential_volta,
                        0.05,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        16U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.battery_potential_power_input_1,
                        0.05,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        32U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.keyswitch_battery_potential_158,
                        0.05,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        48U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Eec20ElectronicEngineControl>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        m.absolute_engine_load,
                        0.025,
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

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, EasiEngineAirSystemInfo>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engine_intake_maf,
                        0.000976562,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        16U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Tsc103>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engoverridectrlmode),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    0U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engoverridectrlmode)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engrequestedspeedctrlconditions),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    2U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engrequestedspeedctrlconditions)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.overridectrlmodepriority),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    4U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.overridectrlmodepriority)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engrequestedspeed_speedlimit,
                        0.125,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        8U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.engrequestedtorque_torquelimit),
                        1.0,
                        -125.0,
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
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.tsc1transrate),
                                           3U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    32U,
                    3U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.tsc1transrate)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.tsc1ctrlpurpose),
                                           5U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    35U,
                    5U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.tsc1ctrlpurpose)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engrequestedtorquehighresolution),
                                           4U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    40U,
                    4U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engrequestedtorquehighresolution)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.messagecounter),
                        1.0,
                        0.0,
                        4U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        56U,
                        4U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.messagechecksum),
                        1.0,
                        0.0,
                        4U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        60U,
                        4U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Tsc10b>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engoverridectrlmode),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    0U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engoverridectrlmode)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engrequestedspeedctrlconditions),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    2U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engrequestedspeedctrlconditions)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.overridectrlmodepriority),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    4U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.overridectrlmodepriority)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engrequestedspeed_speedlimit,
                        0.125,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        8U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.engrequestedtorque_torquelimit),
                        1.0,
                        -125.0,
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
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.tsc1transrate),
                                           3U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    32U,
                    3U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.tsc1transrate)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.tsc1ctrlpurpose),
                                           5U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    35U,
                    5U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.tsc1ctrlpurpose)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engrequestedtorquehighresolution),
                                           4U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    40U,
                    4U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engrequestedtorquehighresolution)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.messagecounter),
                        1.0,
                        0.0,
                        4U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        56U,
                        4U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.messagechecksum),
                        1.0,
                        0.0,
                        4U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        60U,
                        4U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Dm07>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.testidentifier),
                                           8U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    0U,
                    8U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.testidentifier)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.spn1),
                        1.0,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        8U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.failuremodeidentifier1),
                                           5U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    24U,
                    5U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.failuremodeidentifier1)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.spn1high),
                        1.0,
                        0.0,
                        3U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        29U,
                        3U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Dm08>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.testidentifier),
                                           8U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    0U,
                    8U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.testidentifier)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.testtype),
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
                        static_cast<double>(m.testvalue),
                        1.0,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        16U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.testlimitmaximum),
                        1.0,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        32U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.testlimitminimum),
                        1.0,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        48U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Erc1ElectronicRetarderCntrl>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.retardertorquemode),
                        1.0,
                        0.0,
                        4U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        4U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.retarderenablebrakeassistswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    4U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.retarderenablebrakeassistswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.retarderenableshiftassistswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    6U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.retarderenableshiftassistswitch)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.actualretarderpercenttorque),
                        1.0,
                        -125.0,
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
                        static_cast<double>(m.intendedretarderpercenttorque),
                        1.0,
                        -125.0,
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
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engcoolantloadincrease),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    24U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engcoolantloadincrease)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.retarderrequestingbrakelight),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    26U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.retarderrequestingbrakelight)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.retarderroadspeedlimitswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    28U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.retarderroadspeedlimitswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.retarderroadspeedexceededstatus),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    30U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.retarderroadspeedexceededstatus)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.srcaddrssofcntrllngdvcfrrtrdrctr),
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
                        static_cast<double>(m.drvrsdemandretarderpercenttorque),
                        1.0,
                        -125.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        40U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.retarderselectionnonengine,
                        0.4,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        48U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.actlmxavlblretarderpercenttorque),
                        1.0,
                        -125.0,
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
            if constexpr (std::is_same_v<T, Etc1ElectronicTransCntrl1>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.transdrivelineengaged),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    0U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.transdrivelineengaged)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.trnstorqueconverterlockupengaged),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    2U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.trnstorqueconverterlockupengaged)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.transshiftinprocess),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    4U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.transshiftinprocess)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.trnstrqcnvrtrlckptrnstninprocess),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    6U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.trnstrqcnvrtrlckptrnstninprocess)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.transoutputshaftspeed,
                        0.125,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        8U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.percentclutchslip,
                        0.4,
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
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engmomentaryoverspeedenable),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    32U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engmomentaryoverspeedenable)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.progressiveshiftdisable),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    34U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.progressiveshiftdisable)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.momentaryengmaxpowerenable),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    36U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.momentaryengmaxpowerenable)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.transinputshaftspeed,
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
                        static_cast<double>(m.srcaddrssofcntrllngdvcfrtrnsctrl),
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
            if constexpr (std::is_same_v<T, Etc2ElectronicTransCntrl2>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.transselectedgear),
                        1.0,
                        -125.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.transactualgearratio,
                        0.001,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        8U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.transcurrentgear),
                        1.0,
                        -125.0,
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
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.transrequestedrange),
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
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.transcurrentrange),
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
            if constexpr (std::is_same_v<T, Rqst005e>) {
                constexpr std::uint8_t kDlc = 3U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.parametergroupnumber),
                        1.0,
                        0.0,
                        24U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        24U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Rqst0021>) {
                constexpr std::uint8_t kDlc = 3U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.parametergroupnumber),
                        1.0,
                        0.0,
                        24U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        24U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, RqstGlobal5e>) {
                constexpr std::uint8_t kDlc = 3U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.parametergroupnumber),
                        1.0,
                        0.0,
                        24U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        24U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, RqstGlobal03>) {
                constexpr std::uint8_t kDlc = 3U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.parametergroupnumber),
                        1.0,
                        0.0,
                        24U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        24U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, TciTransferCaseInformation>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.transfercasestatus),
                                           3U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    0U,
                    3U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.transfercasestatus)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.dirstatus),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    3U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.dirstatus)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.actualgearratio,
                        0.01,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        8U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.messagecounter),
                        1.0,
                        0.0,
                        4U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        56U,
                        4U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.messagechecksum),
                        1.0,
                        0.0,
                        4U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        60U,
                        4U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Trf1TransmissionFluids1>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.clutchpress),
                        16.0,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.transoillevel1,
                        0.4,
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
                        static_cast<double>(m.transfilterdiffpress),
                        2.0,
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
                        static_cast<double>(m.transoilpress),
                        16.0,
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
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.transoiltemp1,
                        0.03125,
                        -273.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        32U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.transoillevel1high_low,
                        0.5,
                        -62.5,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        48U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.transoillevel1countdowntimer),
                                           4U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    56U,
                    4U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.transoillevel1countdowntimer)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.transoillevel1measurementstatus),
                                           4U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    60U,
                    4U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.transoillevel1measurementstatus)
                );

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, CcssCruiseControlVehicleSpd>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.maxvehiclespeedlimit),
                        1.0,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        0U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.cruisectrlhighsetlimitspeed),
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
                        static_cast<double>(m.cruisectrllowsetlimitspeed),
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
                        m.maxvehiclespeedlimit6808,
                        0.00390625,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        24U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.ctrlsyslowsetlmtspd),
                        1.0,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        40U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.ctrldiscmdsupport),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    48U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.ctrldiscmdsupport)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.ctrlresumecmdsupport),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    50U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.ctrlresumecmdsupport)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.ctrlpausecmdsupport),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    52U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.ctrlpausecmdsupport)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.ctrlsetcmdsupport),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    54U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.ctrlsetcmdsupport)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.powertrainadaptivecctype),
                                           4U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    56U,
                    4U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.powertrainadaptivecctype)
                );

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Ccvs1CruiseControlVehspd>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.twospeedaxleswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    0U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.twospeedaxleswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.parkingbrakeswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    2U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.parkingbrakeswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.cruisectrlpauseswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    4U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.cruisectrlpauseswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.parkbrakereleaseinhibitrq),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    6U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.parkbrakereleaseinhibitrq)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.wheelbasedvehiclespeed,
                        0.00390625,
                        0.0,
                        16U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        8U,
                        16U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.cruisectrlactive),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    24U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.cruisectrlactive)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.cruisectrlenableswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    26U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.cruisectrlenableswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.brakeswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    28U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.brakeswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.clutchswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    30U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.clutchswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.cruisectrlsetswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    32U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.cruisectrlsetswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.cruisectrlcoastswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    34U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.cruisectrlcoastswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.cruisectrlresumeswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    36U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.cruisectrlresumeswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.cruisectrlaccelerateswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    38U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.cruisectrlaccelerateswitch)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.cruisectrlsetspeed),
                        1.0,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        40U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.ptogovernorstate),
                                           5U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    48U,
                    5U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.ptogovernorstate)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.cruisectrlstates),
                                           3U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    53U,
                    3U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.cruisectrlstates)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engidleincrementswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    56U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engidleincrementswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engidledecrementswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    58U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engidledecrementswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engtestmodeswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    60U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engtestmodeswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engshutdownoverrideswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    62U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engshutdownoverrideswitch)
                );

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Ebc1ElectronicBrakeCntrl>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.asrengctrlactive),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    0U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.asrengctrlactive)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.asrbrakectrlactive),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    2U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.asrbrakectrlactive)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.antilockbrakingactive),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    4U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.antilockbrakingactive)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.ebsbrakeswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    6U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.ebsbrakeswitch)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.brakepedalpos,
                        0.4,
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
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.absoffroadswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    16U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.absoffroadswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.asroffroadswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    18U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.asroffroadswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.asrhillholderswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    20U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.asrhillholderswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.tractionctrloverrideswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    22U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.tractionctrloverrideswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.accelinterlockswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    24U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.accelinterlockswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engderateswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    26U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engderateswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engauxshutdownswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    28U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engauxshutdownswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.remoteaccelenableswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    30U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.remoteaccelenableswitch)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        m.engretarderselection,
                        0.4,
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
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.absfullyoperational),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    40U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.absfullyoperational)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.ebsredwarningsignal),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    42U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.ebsredwarningsignal)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.abs_ebsamberwarningsignal),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    44U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.abs_ebsamberwarningsignal)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.atc_asrinformationsignal),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    46U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.atc_asrinformationsignal)
                );
                {
                    auto raw = detail::encode_unsigned_physical(
                        static_cast<double>(m.srcaddrssofcntrllngdvcfrbrkectrl),
                        1.0,
                        0.0,
                        8U
                    );
                    if (!raw) {
                        return std::unexpected(raw.error());
                    }
                    detail::insert_raw(
                        tmp,
                        48U,
                        8U,
                        ByteOrder::little_endian,
                        *raw
                    );
                }
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.railroadmodesw),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    56U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.railroadmodesw)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.haltbrakeswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    58U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.haltbrakeswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.trailerabsstatus),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    60U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.trailerabsstatus)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.trctrmntdtrailerabswarningsignal),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    62U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.trctrmntdtrailerabswarningsignal)
                );

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }
            if constexpr (std::is_same_v<T, Shutdn>) {
                constexpr std::uint8_t kDlc = 8U;

                if (out_size < kDlc) {
                    return std::unexpected(EncodeError::buffer_too_small);
                }

                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engidleshutdownhasshutdowneng),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    0U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engidleshutdownhasshutdowneng)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engidleshutdowndriveralertmode),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    2U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engidleshutdowndriveralertmode)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engidleshutdowntimeroverride),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    4U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engidleshutdowntimeroverride)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engidleshutdowntimerstate),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    6U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engidleshutdowntimerstate)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engidleshutdowntimerfunction),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    14U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engidleshutdowntimerfunction)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.a_chighpressfanswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    16U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.a_chighpressfanswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.refrigerantlowpressswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    18U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.refrigerantlowpressswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.refrigeranthighpressswitch),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    20U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.refrigeranthighpressswitch)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engwaittostartlamp),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    24U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engwaittostartlamp)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engprtectionsystemhasshutdowneng),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    32U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engprtectionsystemhasshutdowneng)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engprtctnsystmapprachingshutdown),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    34U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engprtctnsystmapprachingshutdown)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engprotectionsystemtimeroverride),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    36U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engprotectionsystemtimeroverride)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engprotectionsystemtimerstate),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    38U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engprotectionsystemtimerstate)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engprotectionsystemconfig),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    46U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engprotectionsystemconfig)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engalarmacknowledge),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    48U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engalarmacknowledge)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engalarmoutputcmdstatus),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    50U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engalarmoutputcmdstatus)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engairshutoffcmdstatus),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    52U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engairshutoffcmdstatus)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engoverspeedtest),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    54U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engoverspeedtest)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engairshutoffstatus),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    56U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engairshutoffstatus)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.ptoshutdownhasshutdowneng),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    58U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.ptoshutdownhasshutdowneng)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.clntlvlengprtctionshutdownstatus),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    60U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.clntlvlengprtctionshutdownstatus)
                );
                if (!detail::fits_unsigned(static_cast<std::uint64_t>(m.engoilpresssw),
                                           2U)) {
                    return std::unexpected(EncodeError::value_out_of_range);
                }
                detail::insert_raw(
                    tmp,
                    62U,
                    2U,
                    ByteOrder::little_endian,
                    static_cast<std::uint64_t>(m.engoilpresssw)
                );

                std::copy_n(tmp.begin(), kDlc, out);
                return kDlc;
            }

            return std::unexpected(EncodeError::unsupported_message);
        },
        msg
    );
}

} // namespace duramax