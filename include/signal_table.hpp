#pragma once

#include <concepts>
#include <cstdint>
#include <tuple>
#include <type_traits>
#include <utility>

enum class OverflowPolicy : std::uint8_t {
    reject,
    clamp
};

struct identity_transform {
    template <typename T>
    constexpr auto operator()(T v) const -> T {
        return v;
    }
};



template <typename SrcDb, typename DstDb>
concept PairableDatabases =
    std::same_as<
        typename SrcDb::SignalPhysicalValue,
        typename DstDb::SignalPhysicalValue
    >;

template <typename Db, auto SigId>
using db_signal_value_t = typename Db::template signal_value_t<SigId>;

template <
    typename SrcDb,
    typename DstDb,
    auto SrcSignal,
    auto DstSignal,
    typename Transform = identity_transform,
    bool TriggerParentSend = false,
    OverflowPolicy Overflow = OverflowPolicy::reject
>
struct SignalTranslation
{
    using src_value_t = std::remove_cvref_t<db_signal_value_t<SrcDb, SrcSignal>>;
    using dst_value_t = std::remove_cvref_t<db_signal_value_t<DstDb, DstSignal>>;
    using transform_t = Transform;

    static constexpr auto src_signal = SrcSignal;
    static constexpr auto dst_signal = DstSignal;
    static constexpr bool trigger_parent_send = TriggerParentSend;
    static constexpr OverflowPolicy overflow_policy = Overflow;

    static_assert(
        std::invocable<const Transform&, const src_value_t&>,
        "Transform must be invocable with the source signal value type"
    );

    using transformed_t =
        std::remove_cvref_t<std::invoke_result_t<const Transform&, const src_value_t&>>;

    static_assert(
        std::convertible_to<transformed_t, dst_value_t>,
        "Transform result must be convertible to the destination signal value type"
    );

    static_assert(
        std::constructible_from<typename DstDb::SignalPhysicalValue, dst_value_t>,
        "Destination signal value type must be constructible into DstDb::SignalPhysicalValue"
    );

    static constexpr auto apply(const src_value_t& value) -> dst_value_t {
        return static_cast<dst_value_t>(Transform{}(value));
    }
};


template <typename Db, auto Message, std::uint32_t PeriodMs>
struct PeriodicMessagePolicy
{
    static constexpr auto message_id = Message;
    static constexpr std::uint32_t period_ms = PeriodMs;
};

