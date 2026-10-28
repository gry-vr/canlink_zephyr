#pragma once

#include <zephyr/kernel.h>

#include <cstdint>
#include <variant>
#include "throttle_policy.hpp"

namespace canfw {

enum class TxPolicy : std::uint8_t {
    send_once,
    periodic_enable,
    periodic_disable,
};

template <typename Db>
struct SnapshotReply {
    typename Db::ValueStore store{};
    throttle::Source command_source{};
    std::uint32_t rejected_throttle_inputs{};
    std::uint32_t stale_timeout_events{};
    bool valid{false};
    std::uint32_t timestamp_ms{0};
};

template <typename Db>
concept HasDbSignalPhysicalValue = requires {
    typename Db::SignalPhysicalValue;
};

template <typename Db>
using SignalPhysicalValueT = typename Db::SignalPhysicalValue;

template <typename Db>
struct TxCommand {
    using MessageId = typename Db::MessageId;
    using MessageVariant = typename Db::MessageVariant;
    using SignalId = typename Db::SignalId;
    using SignalPhysicalValue = SignalPhysicalValueT<Db>;

    struct SendMessage {
        MessageVariant message;
        TxPolicy policy{TxPolicy::periodic_enable};
        std::uint32_t period_ms_override{0};
    };

    struct UpdateSignal {
        SignalId signal_id;
        SignalPhysicalValue value;
        bool trigger_parent_send{false};
        throttle::Source source{};
    };

    struct DisableMessage {
        MessageId message_id;
    };

    struct RequestSnapshot {
        k_msgq* reply_q{nullptr};
    };

    struct RequestDiagnostics {
        k_msgq* reply_q{nullptr};
        bool previous_boot{false};
        bool clear{false};
    };

    using Variant = std::variant<
        SendMessage,
        UpdateSignal,
        DisableMessage,
        RequestSnapshot,
        RequestDiagnostics
    >;
};

} // namespace canfw