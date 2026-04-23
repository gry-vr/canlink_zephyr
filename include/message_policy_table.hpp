#pragma once

#include "signal_table.hpp"

template <typename ReacherDb>
struct ReacherPeriodicPolicies
{
    using type = std::tuple<
        PeriodicMessagePolicy<ReacherDb, ReacherDb::MessageId::export_0, 50>,
        PeriodicMessagePolicy<ReacherDb, ReacherDb::MessageId::export_3, 50>,
        PeriodicMessagePolicy<ReacherDb, ReacherDb::MessageId::export_8, 100>,
        PeriodicMessagePolicy<ReacherDb, ReacherDb::MessageId::export_b, 50>
    >;
};

template <typename DuramaxDb>
struct DuramaxPeriodicPolicies
{
    using type = std::tuple<
        PeriodicMessagePolicy<DuramaxDb, DuramaxDb::MessageId::tsc1_31, 10>
    >;
};