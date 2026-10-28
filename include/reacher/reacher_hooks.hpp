#pragma once
#include "reacher_db.hpp"
#include "can_commands.hpp"

struct ReacherHooks {
    template <typename Msg>
    void on_rx_message(const Msg&, reacher::ReacherDb::ValueStore&, std::uint32_t) {}

    void on_rx_message(const reacher::ReacherCtrl& msg,
                       reacher::ReacherDb::ValueStore& store, std::uint32_t now) {
        constexpr auto sid = reacher::SignalId::reacher_ctrl__throttle_rpm;
        auto& slot = store.slots[reacher::to_index(sid)];
        if (!canfw::throttle::validate_rpm(msg.throttle_rpm)) {
            ++source_.rejected;
            // apply_to_store ran first. Restore only this command signal, including
            // its original timestamp; invalid traffic must never refresh freshness.
            slot = last_valid_;
            return;
        }
        last_valid_ = slot;
        source_.timestamp_ms = now;
        ++source_.sequence;
        source_.frame_id = 0x200;
        source_.valid = true;
    }
    void on_snapshot(canfw::SnapshotReply<reacher::ReacherDb>& reply) const {
        reply.command_source = source_;
        reply.rejected_throttle_inputs = source_.rejected;
    }
private:
    reacher::SignalSlot last_valid_{};
    canfw::throttle::Source source_{};
};
