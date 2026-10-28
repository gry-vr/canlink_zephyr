#pragma once
#include <array>
#include <cstdint>
#include <optional>

namespace canfw::throttle {
inline constexpr std::uint16_t low_band_max = 10400; // 1300 rpm
inline constexpr std::uint16_t low_band_output = 10000; // 1250 rpm
inline constexpr std::uint16_t middle_band_max = 16008; // 2001 rpm
inline constexpr std::uint16_t middle_band_output = 16000; // 2000 rpm
inline constexpr double max_rpm = 8031.875; // maximum valid raw = 64255

/** Legacy step mapping in raw 0.125-rpm units, ported from gry-vr/CanLink
 * src/main.cpp canopen_throttle (main blob 4f26d88e5e0dccdee0915aef3ae9b7a7080bca87).
 * 10400 -> 10000, 10401 -> 16000, 16008 -> 16000, 16009 -> 16009.
 * Consequently 1500.125 rpm -> 2000 rpm. This is deliberately not linear.
 */
constexpr std::uint16_t map_throttle_raw(std::uint16_t raw) {
    return raw <= low_band_max ? low_band_output :
           raw <= middle_band_max ? middle_band_output : raw;
}
constexpr std::uint16_t requested_raw(std::uint16_t raw, bool bands) {
    return bands ? map_throttle_raw(raw) : raw;
}
// Comparisons reject NaN and both infinities before any integer conversion.
constexpr std::optional<std::uint16_t> validate_rpm(double rpm) {
    if (!(rpm >= 0.0 && rpm <= max_rpm)) return std::nullopt;
    return static_cast<std::uint16_t>(rpm * 8.0 + 0.5);
}
struct Source {
    std::uint32_t timestamp_ms{};
    std::uint32_t sequence{};
    std::uint32_t rejected{};
    std::uint32_t frame_id{};
    bool valid{};
};
struct Output { std::uint16_t raw{}; bool enabled{}; };
struct Policy {
    std::uint16_t raw{};
    std::uint32_t timestamp_ms{}, sequence{}, rejected{}, stale_events{};
    bool accepted{}, stale{};
    constexpr bool accept(double rpm, const Source& source) {
        if (!source.valid || source.frame_id != 0x200) return false;
        if (accepted && source.sequence == sequence) return false;
        auto candidate = validate_rpm(rpm);
        if (!candidate) { ++rejected; return false; }
        raw = *candidate; timestamp_ms = source.timestamp_ms;
        sequence = source.sequence; accepted = true; stale = false;
        return true;
    }
    constexpr Output evaluate(std::uint32_t now, bool bands, bool timeout, std::uint32_t limit) {
        if (!accepted) return {};
        if (timeout && static_cast<std::uint32_t>(now - timestamp_ms) >= limit) {
            if (!stale) { stale = true; ++stale_events; }
        }
        // Once stale, only a fresh accepted source sequence can re-enable output.
        if (stale) return {};
        return {requested_raw(raw, bands), true};
    }
};
constexpr std::uint8_t checksum(std::uint32_t id, const std::uint8_t* data, std::uint8_t arc) {
    std::uint32_t sum = arc & 0x0f;
    for (unsigned i = 0; i < 7; ++i) sum += data[i];
    for (unsigned i = 0; i < 4; ++i) sum += (id >> (i * 8)) & 0xff;
    return (((sum >> 6) & 3) + (sum >> 3) + sum) & 7;
}
constexpr void finish_frame(std::uint8_t* bytes, Output output, std::uint8_t arc) {
    // TSC1_31: bits 1:0=1 speed control; 3:2=0 transient/non-lockup;
    // 5:4=3 low priority; undefined bits 7:6=11. Disabled byte is exactly 00.
    // Legacy's speed_high < 0x21 branch was unreachable after its 1250-rpm floor.
    bytes[0] = output.enabled ? 0xf1 : 0x00;
    bytes[1] = output.raw & 0xff; bytes[2] = output.raw >> 8;
    // Legacy unavailable/reserved wire encodings: not valid typed torque values.
    // Byte 4: TransRate=7 (10 ms), CtrlPurpose=31 (Temporary Powertrain Control).
    for (unsigned i = 3; i <= 6; ++i) bytes[i] = 0xff;
    bytes[7] = (checksum(0x0c000031, bytes, arc) << 4) | (arc & 7);
}
} // namespace canfw::throttle
