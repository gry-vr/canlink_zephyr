#pragma once

#include <concepts>
#include <tuple>
#include <type_traits>

template <typename Db, auto SigId>
using signal_value_t = typename Db::template signal_type_t<SigId>;
// or whatever your codegen exposes:
// using signal_value_t = typename Db::template SignalType<SigId>::value_type;
// using signal_value_t = typename Db::template signal_value_type<SigId>;

template <typename DuramaxDb,
          typename ReacherDb,
          auto DuramaxSignal,
          auto ReacherSignal>
struct SignalPair
{
    using duramax_value_t =
        std::remove_cvref_t<signal_value_t<DuramaxDb, DuramaxSignal>>;
    using reacher_value_t =
        std::remove_cvref_t<signal_value_t<ReacherDb, ReacherSignal>>;

    static_assert(
        std::same_as<duramax_value_t, reacher_value_t>,
        "SignalPair requires both mapped signals to have the same value type"
    );

    static constexpr auto duramax_signal = DuramaxSignal;
    static constexpr auto reacher_signal = ReacherSignal;

    using value_type = duramax_value_t;
};