#pragma once

#include "duramax_metadata.hpp"
#include "duramax_types.hpp"

#include <array>
#include <cstdint>
#include <optional>
#include <variant>

namespace duramax {

union SignalValueUnion {
    std::uint8_t  u8;
    std::uint16_t u16;
    std::int16_t  i16;
    std::uint32_t u32;
    double        f64;
    bool          b;

    constexpr SignalValueUnion() : u32(0) {}
};

struct SignalSlot {
    bool valid{};
    std::uint32_t timestamp_ms{};
    std::uint32_t source_message_time_ms{};
    SignalType type{};
    SignalValueUnion value{};
};

struct MessageFreshness {
    bool seen{};
    std::uint32_t last_rx_ms{};
};

class ValueStore {
public:
    std::array<SignalSlot, kSignalCount> slots{};
    std::array<MessageFreshness, kMessageCount> messages{};

    constexpr void mark_message_rx(MessageId id, std::uint32_t now_ms) {
        auto& m = messages[to_index(id)];
        m.seen = true;
        m.last_rx_ms = now_ms;
    }

    constexpr auto message_seen(MessageId id) const -> bool {
        return messages[to_index(id)].seen;
    }

    constexpr auto message_last_rx_ms(MessageId id) const -> std::uint32_t {
        return messages[to_index(id)].last_rx_ms;
    }

    constexpr auto signal_last_update_ms(SignalId id) const -> std::uint32_t {
        return slots[to_index(id)].timestamp_ms;
    }

    constexpr auto signal_source_message_time_ms(SignalId id) const -> std::uint32_t {
        return slots[to_index(id)].source_message_time_ms;
    }

    constexpr void set_signal_u8(SignalId id, std::uint8_t value, std::uint32_t now_ms) {
        auto& s = slots[to_index(id)];
        s.valid = true;
        s.timestamp_ms = now_ms;
        s.source_message_time_ms = now_ms;
        s.type = SignalType::u8;
        s.value.u8 = value;
    }

    constexpr void set_signal_u16(SignalId id, std::uint16_t value, std::uint32_t now_ms) {
        auto& s = slots[to_index(id)];
        s.valid = true;
        s.timestamp_ms = now_ms;
        s.source_message_time_ms = now_ms;
        s.type = SignalType::u16;
        s.value.u16 = value;
    }

    constexpr void set_signal_i16(SignalId id, std::int16_t value, std::uint32_t now_ms) {
        auto& s = slots[to_index(id)];
        s.valid = true;
        s.timestamp_ms = now_ms;
        s.source_message_time_ms = now_ms;
        s.type = SignalType::i16;
        s.value.i16 = value;
    }

    constexpr void set_signal_u32(SignalId id, std::uint32_t value, std::uint32_t now_ms) {
        auto& s = slots[to_index(id)];
        s.valid = true;
        s.timestamp_ms = now_ms;
        s.source_message_time_ms = now_ms;
        s.type = SignalType::u32;
        s.value.u32 = value;
    }

    constexpr void set_signal_f64(SignalId id, double value, std::uint32_t now_ms) {
        auto& s = slots[to_index(id)];
        s.valid = true;
        s.timestamp_ms = now_ms;
        s.source_message_time_ms = now_ms;
        s.type = SignalType::f64;
        s.value.f64 = value;
    }

    constexpr void set_signal_bool(SignalId id, bool value, std::uint32_t now_ms) {
        auto& s = slots[to_index(id)];
        s.valid = true;
        s.timestamp_ms = now_ms;
        s.source_message_time_ms = now_ms;
        s.type = SignalType::boolean;
        s.value.b = value;
    }

    constexpr auto try_get_u8(SignalId id) const -> std::optional<std::uint8_t> {
        const auto& s = slots[to_index(id)];
        if (!s.valid || s.type != SignalType::u8) {
            return std::nullopt;
        }
        return s.value.u8;
    }

    constexpr auto try_get_u16(SignalId id) const -> std::optional<std::uint16_t> {
        const auto& s = slots[to_index(id)];
        if (!s.valid || s.type != SignalType::u16) {
            return std::nullopt;
        }
        return s.value.u16;
    }

    constexpr auto try_get_i16(SignalId id) const -> std::optional<std::int16_t> {
        const auto& s = slots[to_index(id)];
        if (!s.valid || s.type != SignalType::i16) {
            return std::nullopt;
        }
        return s.value.i16;
    }

    constexpr auto try_get_u32(SignalId id) const -> std::optional<std::uint32_t> {
        const auto& s = slots[to_index(id)];
        if (!s.valid || s.type != SignalType::u32) {
            return std::nullopt;
        }
        return s.value.u32;
    }

    constexpr auto try_get_f64(SignalId id) const -> std::optional<double> {
        const auto& s = slots[to_index(id)];
        if (!s.valid || s.type != SignalType::f64) {
            return std::nullopt;
        }
        return s.value.f64;
    }

    constexpr auto try_get_bool(SignalId id) const -> std::optional<bool> {
        const auto& s = slots[to_index(id)];
        if (!s.valid || s.type != SignalType::boolean) {
            return std::nullopt;
        }
        return s.value.b;
    }
};

struct Eec5ElectronicEngineControl5;
void update_from(ValueStore& store, const Eec5ElectronicEngineControl5& m, std::uint32_t now_ms);
struct Eec9ElectronicEngineControl9;
void update_from(ValueStore& store, const Eec9ElectronicEngineControl9& m, std::uint32_t now_ms);
struct EbccEngineExhaustBrakeCont;
void update_from(ValueStore& store, const EbccEngineExhaustBrakeCont& m, std::uint32_t now_ms);
struct Et3EngineTemperature3;
void update_from(ValueStore& store, const Et3EngineTemperature3& m, std::uint32_t now_ms);
struct Dm21DiagnosticReadiness2;
void update_from(ValueStore& store, const Dm21DiagnosticReadiness2& m, std::uint32_t now_ms);
struct Dm26DiagnosticReadiness3;
void update_from(ValueStore& store, const Dm26DiagnosticReadiness3& m, std::uint32_t now_ms);
struct Ic1IntakeExhaustCond1;
void update_from(ValueStore& store, const Ic1IntakeExhaustCond1& m, std::uint32_t now_ms);
struct AmbAmbientConditions;
void update_from(ValueStore& store, const AmbAmbientConditions& m, std::uint32_t now_ms);
struct Eec1ElectronicEngineControl1;
void update_from(ValueStore& store, const Eec1ElectronicEngineControl1& m, std::uint32_t now_ms);
struct Eec2ElectronicEngineControl2;
void update_from(ValueStore& store, const Eec2ElectronicEngineControl2& m, std::uint32_t now_ms);
struct Eec3ElectronicEngineControl3;
void update_from(ValueStore& store, const Eec3ElectronicEngineControl3& m, std::uint32_t now_ms);
struct EflP1EngFluidLevelPress1;
void update_from(ValueStore& store, const EflP1EngFluidLevelPress1& m, std::uint32_t now_ms);
struct EflP2EngFluidLevelPress2;
void update_from(ValueStore& store, const EflP2EngFluidLevelPress2& m, std::uint32_t now_ms);
struct Et1EngineTemperature1;
void update_from(ValueStore& store, const Et1EngineTemperature1& m, std::uint32_t now_ms);
struct Lfe1FuelEconomyLiquid1;
void update_from(ValueStore& store, const Lfe1FuelEconomyLiquid1& m, std::uint32_t now_ms);
struct TransportprotocolHeader;
void update_from(ValueStore& store, const TransportprotocolHeader& m, std::uint32_t now_ms);
struct TransportprotocolData;
void update_from(ValueStore& store, const TransportprotocolData& m, std::uint32_t now_ms);
struct Dm01ActiveDiagnostics;
void update_from(ValueStore& store, const Dm01ActiveDiagnostics& m, std::uint32_t now_ms);
struct Tsc131;
void update_from(ValueStore& store, const Tsc131& m, std::uint32_t now_ms);
struct Cac1ChargeAirCooler1;
void update_from(ValueStore& store, const Cac1ChargeAirCooler1& m, std::uint32_t now_ms);
struct HoursEngineHoursRevolutions;
void update_from(ValueStore& store, const HoursEngineHoursRevolutions& m, std::uint32_t now_ms);
struct Tci5TurbochargerInformation5;
void update_from(ValueStore& store, const Tci5TurbochargerInformation5& m, std::uint32_t now_ms);
struct Vep1VehicleElectricalPower1;
void update_from(ValueStore& store, const Vep1VehicleElectricalPower1& m, std::uint32_t now_ms);
struct Eec20ElectronicEngineControl;
void update_from(ValueStore& store, const Eec20ElectronicEngineControl& m, std::uint32_t now_ms);
struct EasiEngineAirSystemInfo;
void update_from(ValueStore& store, const EasiEngineAirSystemInfo& m, std::uint32_t now_ms);
struct Tsc103;
void update_from(ValueStore& store, const Tsc103& m, std::uint32_t now_ms);
struct Tsc10b;
void update_from(ValueStore& store, const Tsc10b& m, std::uint32_t now_ms);
struct Dm07;
void update_from(ValueStore& store, const Dm07& m, std::uint32_t now_ms);
struct Dm08;
void update_from(ValueStore& store, const Dm08& m, std::uint32_t now_ms);
struct Erc1ElectronicRetarderCntrl;
void update_from(ValueStore& store, const Erc1ElectronicRetarderCntrl& m, std::uint32_t now_ms);
struct Etc1ElectronicTransCntrl1;
void update_from(ValueStore& store, const Etc1ElectronicTransCntrl1& m, std::uint32_t now_ms);
struct Etc2ElectronicTransCntrl2;
void update_from(ValueStore& store, const Etc2ElectronicTransCntrl2& m, std::uint32_t now_ms);
struct Rqst005e;
void update_from(ValueStore& store, const Rqst005e& m, std::uint32_t now_ms);
struct Rqst0021;
void update_from(ValueStore& store, const Rqst0021& m, std::uint32_t now_ms);
struct RqstGlobal5e;
void update_from(ValueStore& store, const RqstGlobal5e& m, std::uint32_t now_ms);
struct RqstGlobal03;
void update_from(ValueStore& store, const RqstGlobal03& m, std::uint32_t now_ms);
struct TciTransferCaseInformation;
void update_from(ValueStore& store, const TciTransferCaseInformation& m, std::uint32_t now_ms);
struct Trf1TransmissionFluids1;
void update_from(ValueStore& store, const Trf1TransmissionFluids1& m, std::uint32_t now_ms);
struct CcssCruiseControlVehicleSpd;
void update_from(ValueStore& store, const CcssCruiseControlVehicleSpd& m, std::uint32_t now_ms);
struct Ccvs1CruiseControlVehspd;
void update_from(ValueStore& store, const Ccvs1CruiseControlVehspd& m, std::uint32_t now_ms);
struct Ebc1ElectronicBrakeCntrl;
void update_from(ValueStore& store, const Ebc1ElectronicBrakeCntrl& m, std::uint32_t now_ms);
struct Shutdn;
void update_from(ValueStore& store, const Shutdn& m, std::uint32_t now_ms);

// Clearer TX-facing alias.
// For now this is just a semantic wrapper around update_from(...).
inline void apply_to_store(ValueStore& store,
                           const Eec5ElectronicEngineControl5& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Eec9ElectronicEngineControl9& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const EbccEngineExhaustBrakeCont& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Et3EngineTemperature3& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Dm21DiagnosticReadiness2& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Dm26DiagnosticReadiness3& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Ic1IntakeExhaustCond1& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const AmbAmbientConditions& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Eec1ElectronicEngineControl1& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Eec2ElectronicEngineControl2& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Eec3ElectronicEngineControl3& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const EflP1EngFluidLevelPress1& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const EflP2EngFluidLevelPress2& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Et1EngineTemperature1& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Lfe1FuelEconomyLiquid1& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const TransportprotocolHeader& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const TransportprotocolData& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Dm01ActiveDiagnostics& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Tsc131& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Cac1ChargeAirCooler1& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const HoursEngineHoursRevolutions& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Tci5TurbochargerInformation5& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Vep1VehicleElectricalPower1& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Eec20ElectronicEngineControl& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const EasiEngineAirSystemInfo& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Tsc103& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Tsc10b& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Dm07& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Dm08& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Erc1ElectronicRetarderCntrl& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Etc1ElectronicTransCntrl1& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Etc2ElectronicTransCntrl2& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Rqst005e& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Rqst0021& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const RqstGlobal5e& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const RqstGlobal03& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const TciTransferCaseInformation& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Trf1TransmissionFluids1& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const CcssCruiseControlVehicleSpd& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Ccvs1CruiseControlVehspd& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Ebc1ElectronicBrakeCntrl& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Shutdn& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}

inline void apply_to_store(ValueStore& store,
                           const MessageVariant& msg,
                           std::uint32_t now_ms) {
    std::visit([&](const auto& m) {
        apply_to_store(store, m, now_ms);
    }, msg);
}

} // namespace duramax