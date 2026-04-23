#pragma once

#include "signal_table.hpp"

struct throttle_rpm_to_speedlimit {
    constexpr auto operator()(std::uint16_t rpm) const -> double {
        return static_cast<double>(rpm);
    }
};

template <typename ReacherDb, typename DuramaxDb>
struct ReacherToDuramaxTranslations
{
    using type = std::tuple<
        SignalTranslation<
            ReacherDb,
            DuramaxDb,
            ReacherDb::SignalId::reacher_ctrl__throttle_rpm,
            DuramaxDb::SignalId::tsc1_31__engrequestedspeed_speedlimit,
            throttle_rpm_to_speedlimit,
            false,
            OverflowPolicy::reject
        >
    >;
};