#pragma once
#include <array>
#include <cstdint>

// Independent reference transcribed from the actual public source, not the
// production policy. gry-vr/CanLink main, src/main.cpp lines 633-730,
// blob 4f26d88e5e0dccdee0915aef3ae9b7a7080bca87; subscriptions lines 208-280.
// The source's local init lambda assigns its pointer, not the pointed object.
// This oracle has fully initialized state and models one received command.
namespace legacy_oracle {
constexpr std::array<std::uint8_t, 8> frame(std::uint16_t request, std::uint8_t arc) {
    std::uint16_t speed_value = request;
    speed_value = ((speed_value > 10400) ? (speed_value > 16008) ? speed_value : 16000 : 10000);
    std::uint8_t speed_high = (speed_value >> 8) & 0xff;
    std::uint8_t speed_low = speed_value & 0xff;
    std::array<std::uint8_t, 8> data{
        static_cast<std::uint8_t>((speed_high < 0x21) ? 0x00 : 0xf1),
        speed_low, speed_high, 0xff, 0xff, 0xff, 0xff, 0xff};
    std::uint32_t id = 0x0c000031, sum = 0;
    for (int i = 0; i < 7; i++) sum += data[i];
    sum += arc & 0x0f;
    sum += static_cast<std::uint8_t>(id);
    sum += static_cast<std::uint8_t>(id >> 8);
    sum += static_cast<std::uint8_t>(id >> 16);
    sum += static_cast<std::uint8_t>(id >> 24);
    const auto chk = ((((sum >> 6) & 0x03) + (sum >> 3) + sum) & 0x07);
    data[7] = ((chk & 0x0f) << 4) | (arc & 0x0f);
    return data;
}
}
