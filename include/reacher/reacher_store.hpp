#pragma once

#include "reacher_metadata.hpp"
#include "reacher_types.hpp"

#include <array>
#include <cstdint>
#include <expected>
#include <optional>
#include <type_traits>
#include <variant>

namespace reacher {

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

enum class StoreAccessError : std::uint8_t {
    missing_signal,
    type_mismatch,
    unsupported_signal_type
};

using SignalPhysicalValue = std::variant<
    std::uint8_t,
    std::uint16_t,
    std::int16_t,
    std::uint32_t,
    double,
    bool
>;

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

    constexpr auto signal_valid(SignalId id) const -> bool {
        return slots[to_index(id)].valid;
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

    template <SignalId Id>
    constexpr void set(signal_value_t<Id> value, std::uint32_t now_ms) {
        constexpr auto ty = signal_traits<Id>::signal_type;
        if constexpr (ty == SignalType::u8) {
            set_signal_u8(Id, value, now_ms);
        } else if constexpr (ty == SignalType::u16) {
            set_signal_u16(Id, value, now_ms);
        } else if constexpr (ty == SignalType::i16) {
            set_signal_i16(Id, value, now_ms);
        } else if constexpr (ty == SignalType::u32) {
            set_signal_u32(Id, value, now_ms);
        } else if constexpr (ty == SignalType::f64) {
            set_signal_f64(Id, value, now_ms);
        } else if constexpr (ty == SignalType::boolean) {
            set_signal_bool(Id, value, now_ms);
        }
    }

    template <SignalId Id>
    constexpr auto get() const -> std::optional<signal_value_t<Id>> {
        constexpr auto ty = signal_traits<Id>::signal_type;
        if constexpr (ty == SignalType::u8) {
            return try_get_u8(Id);
        } else if constexpr (ty == SignalType::u16) {
            return try_get_u16(Id);
        } else if constexpr (ty == SignalType::i16) {
            return try_get_i16(Id);
        } else if constexpr (ty == SignalType::u32) {
            return try_get_u32(Id);
        } else if constexpr (ty == SignalType::f64) {
            return try_get_f64(Id);
        } else {
            return try_get_bool(Id);
        }
    }

    auto set_signal_physical(SignalId id,
                             const SignalPhysicalValue& value,
                             std::uint32_t now_ms)
        -> std::expected<void, StoreAccessError>
    {
        switch (signal_meta(id).type) {
        case SignalType::u8:
            if (const auto* v = std::get_if<std::uint8_t>(&value)) {
                set_signal_u8(id, *v, now_ms);
                return {};
            }
            return std::unexpected(StoreAccessError::type_mismatch);
        case SignalType::u16:
            if (const auto* v = std::get_if<std::uint16_t>(&value)) {
                set_signal_u16(id, *v, now_ms);
                return {};
            }
            return std::unexpected(StoreAccessError::type_mismatch);
        case SignalType::i16:
            if (const auto* v = std::get_if<std::int16_t>(&value)) {
                set_signal_i16(id, *v, now_ms);
                return {};
            }
            return std::unexpected(StoreAccessError::type_mismatch);
        case SignalType::u32:
            if (const auto* v = std::get_if<std::uint32_t>(&value)) {
                set_signal_u32(id, *v, now_ms);
                return {};
            }
            return std::unexpected(StoreAccessError::type_mismatch);
        case SignalType::f64:
            if (const auto* v = std::get_if<double>(&value)) {
                set_signal_f64(id, *v, now_ms);
                return {};
            }
            return std::unexpected(StoreAccessError::type_mismatch);
        case SignalType::boolean:
            if (const auto* v = std::get_if<bool>(&value)) {
                set_signal_bool(id, *v, now_ms);
                return {};
            }
            return std::unexpected(StoreAccessError::type_mismatch);
        }
        return std::unexpected(StoreAccessError::unsupported_signal_type);
    }

    auto get_signal_physical(SignalId id) const
        -> std::expected<SignalPhysicalValue, StoreAccessError>
    {
        switch (signal_meta(id).type) {
        case SignalType::u8: {
            auto v = try_get_u8(id);
            if (!v) return std::unexpected(StoreAccessError::missing_signal);
            return SignalPhysicalValue{*v};
        }
        case SignalType::u16: {
            auto v = try_get_u16(id);
            if (!v) return std::unexpected(StoreAccessError::missing_signal);
            return SignalPhysicalValue{*v};
        }
        case SignalType::i16: {
            auto v = try_get_i16(id);
            if (!v) return std::unexpected(StoreAccessError::missing_signal);
            return SignalPhysicalValue{*v};
        }
        case SignalType::u32: {
            auto v = try_get_u32(id);
            if (!v) return std::unexpected(StoreAccessError::missing_signal);
            return SignalPhysicalValue{*v};
        }
        case SignalType::f64: {
            auto v = try_get_f64(id);
            if (!v) return std::unexpected(StoreAccessError::missing_signal);
            return SignalPhysicalValue{*v};
        }
        case SignalType::boolean: {
            auto v = try_get_bool(id);
            if (!v) return std::unexpected(StoreAccessError::missing_signal);
            return SignalPhysicalValue{*v};
        }
        }
        return std::unexpected(StoreAccessError::unsupported_signal_type);
    }
};

struct ReacherCtrl;
void update_from(ValueStore& store, const ReacherCtrl& m, std::uint32_t now_ms);
struct ReacherEngineFeedback;
void update_from(ValueStore& store, const ReacherEngineFeedback& m, std::uint32_t now_ms);
struct Export0;
void update_from(ValueStore& store, const Export0& m, std::uint32_t now_ms);
struct Export3;
void update_from(ValueStore& store, const Export3& m, std::uint32_t now_ms);
struct Export8;
void update_from(ValueStore& store, const Export8& m, std::uint32_t now_ms);
struct ExportB;
void update_from(ValueStore& store, const ExportB& m, std::uint32_t now_ms);
struct ServoBatt;
void update_from(ValueStore& store, const ServoBatt& m, std::uint32_t now_ms);

inline void apply_to_store(ValueStore& store,
                           const ReacherCtrl& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const ReacherEngineFeedback& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Export0& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Export3& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const Export8& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const ExportB& msg,
                           std::uint32_t now_ms) {
    update_from(store, msg, now_ms);
}
inline void apply_to_store(ValueStore& store,
                           const ServoBatt& msg,
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

} // namespace reacher