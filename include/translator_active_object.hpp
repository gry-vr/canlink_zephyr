#pragma once

#include <zephyr/kernel.h>

#include <array>

#include "can_endpoint.hpp"

template <typename DuramaxDb, typename ReacherDb>
class Translator {
public:
    using DuramaxEndpoint = canfw::CanEndpoint<DuramaxDb>;
    using ReacherEndpoint = canfw::CanEndpoint<ReacherDb>;
    using ReacherSnapshot = canfw::SnapshotReply<ReacherDb>;

    Translator(DuramaxEndpoint duramax_out,
               ReacherEndpoint reacher_out)
        : duramax_out_{duramax_out},
          reacher_out_{reacher_out}
    {
        k_msgq_init(&reacher_reply_q_,
                    reinterpret_cast<char*>(reacher_reply_storage_.data()),
                    sizeof(ReacherSnapshot),
                    1);
    }

    void step_once() {
        auto maybe = reacher_out_.request_snapshot_blocking(reacher_reply_q_);
        if (!maybe || !maybe->valid) {
            return;
        }

        auto throttle =
            maybe->store.template get<ReacherDb::SignalId::reacher_ctrl__throttle_rpm>();

        if (!throttle) {
            return;
        }

        (void)duramax_out_.update_signal(
            DuramaxDb::SignalId::tsc1_31__engrequestedspeed_speedlimit,
            static_cast<double>(*throttle),
            false);
    }

private:
    DuramaxEndpoint duramax_out_;
    ReacherEndpoint reacher_out_;

    k_msgq reacher_reply_q_{};
    alignas(ReacherSnapshot) std::array<ReacherSnapshot, 1> reacher_reply_storage_{};
};