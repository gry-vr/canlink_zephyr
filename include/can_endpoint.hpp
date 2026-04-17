#pragma once

#include <zephyr/kernel.h>

#include <cstdint>
#include <optional>
#include <utility>

#include "can_commands.hpp"

namespace canfw {

template <typename Db, typename Hooks>
class CanActiveObject;

template <typename Db>
class CanEndpoint {
public:
    using Command = typename TxCommand<Db>::Variant;
    using MessageId = typename Db::MessageId;
    using MessageVariant = typename Db::MessageVariant;
    using SignalId = typename Db::SignalId;
    using SignalPhysicalValue = typename Db::SignalPhysicalValue;

    constexpr CanEndpoint() = default;

    [[nodiscard]] bool valid() const {
        return tx_q_ != nullptr;
    }

    int post(const Command& cmd, k_timeout_t timeout = K_NO_WAIT) const {
        if (tx_q_ == nullptr) {
            return -EINVAL;
        }
        return k_msgq_put(tx_q_, &cmd, timeout);
    }

    int disable_message(MessageId id, k_timeout_t timeout = K_NO_WAIT) const {
        typename TxCommand<Db>::DisableMessage cmd{};
        cmd.message_id = id;
        return post(Command{cmd}, timeout);
    }

    int update_signal(SignalId signal_id,
                      SignalPhysicalValue value,
                      bool trigger_parent_send = false,
                      k_timeout_t timeout = K_NO_WAIT) const {
        typename TxCommand<Db>::UpdateSignal cmd{};
        cmd.signal_id = signal_id;
        cmd.value = std::move(value);
        cmd.trigger_parent_send = trigger_parent_send;
        return post(Command{cmd}, timeout);
    }

    int send_message(const MessageVariant& mv,
                     TxPolicy policy = TxPolicy::send_once,
                     std::uint32_t period_ms_override = 0,
                     k_timeout_t timeout = K_NO_WAIT) const {
        typename TxCommand<Db>::SendMessage cmd{};
        cmd.message = mv;
        cmd.policy = policy;
        cmd.period_ms_override = period_ms_override;
        return post(Command{cmd}, timeout);
    }

    template <typename Msg>
    int send_message(const Msg& msg,
                     TxPolicy policy = TxPolicy::send_once,
                     std::uint32_t period_ms_override = 0,
                     k_timeout_t timeout = K_NO_WAIT) const {
        return send_message(MessageVariant{msg}, policy, period_ms_override, timeout);
    }

    int enable_periodic(const MessageVariant& mv,
                        std::uint32_t period_ms_override = 0,
                        k_timeout_t timeout = K_NO_WAIT) const {
        return send_message(mv, TxPolicy::periodic_enable, period_ms_override, timeout);
    }

    template <typename Msg>
    int enable_periodic(const Msg& msg,
                        std::uint32_t period_ms_override = 0,
                        k_timeout_t timeout = K_NO_WAIT) const {
        return send_message(msg, TxPolicy::periodic_enable, period_ms_override, timeout);
    }

    int request_snapshot(k_msgq* reply_q,
                         k_timeout_t timeout = K_NO_WAIT) const {
        if (reply_q == nullptr) {
            return -EINVAL;
        }

        typename TxCommand<Db>::RequestSnapshot cmd{};
        cmd.reply_q = reply_q;
        return post(Command{cmd}, timeout);
    }

    std::optional<SnapshotReply<Db>>
    request_snapshot_blocking(k_msgq& reply_q,
                              k_timeout_t post_timeout = K_NO_WAIT,
                              k_timeout_t reply_timeout = K_MSEC(10)) const {
        const int rc = request_snapshot(&reply_q, post_timeout);
        if (rc != 0) {
            return std::nullopt;
        }

        SnapshotReply<Db> reply{};
        if (k_msgq_get(&reply_q, &reply, reply_timeout) != 0) {
            return std::nullopt;
        }

        return reply;
    }

private:
    template <typename Db2, typename Hooks2>
    friend class CanActiveObject;

    explicit constexpr CanEndpoint(k_msgq* tx_q)
        : tx_q_{tx_q} {}

    k_msgq* tx_q_{nullptr};
};

} // namespace canfw