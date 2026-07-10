#pragma once

// Pure TX scheduling logic: no Zephyr dependencies, fully constexpr.
//
// Extracted from can_active_object.hpp so the timing policy (fixed-rate
// grid, resync-on-stall, u32 wrap safety) is testable on the host --
// including as static_asserts, where a behavioral regression fails the
// build itself. See tests/tx_schedule_test.cpp.

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>

namespace canfw {

enum class ScheduleError : std::uint8_t {
    zero_period,
};

// Wrap-safe "has `deadline` been reached?" for k_uptime_get_32() timestamps.
//
// Interprets the unsigned difference as signed, so it is correct across the
// 32-bit rollover (~49.7 days) as long as |now - deadline| < 2^31 ms
// (~24.8 days). All periods in this system are milliseconds-to-seconds,
// so the horizon is not a practical constraint.
constexpr auto time_reached(std::uint32_t now_ms, std::uint32_t deadline_ms) -> bool {
    return static_cast<std::int32_t>(now_ms - deadline_ms) >= 0;
}

struct TxScheduleSlot {
    bool enabled{};
    std::uint32_t period_ms{};
    std::uint32_t next_due_ms{};

    [[nodiscard]] constexpr auto due(std::uint32_t now_ms) const -> bool {
        return enabled && period_ms != 0U && time_reached(now_ms, next_due_ms);
    }

    // Milliseconds until this slot is due (0 if already due or inactive-for-
    // scheduling; callers filter on due()/enabled as needed).
    [[nodiscard]] constexpr auto until_due_ms(std::uint32_t now_ms) const -> std::uint32_t {
        return time_reached(now_ms, next_due_ms) ? 0U : (next_due_ms - now_ms);
    }

    // Fixed-rate advance, called after a send attempt at `now_ms`:
    // the deadline walks the period grid (next_due += period) instead of
    // restarting from the wake time, so wake latency, tick rounding, and
    // drain time do not accumulate as period drift. If the slot has fallen
    // more than one full period behind (bus stall, long drain), it resyncs
    // to now + period rather than bursting to catch up.
    constexpr void advance_after_send(std::uint32_t now_ms) {
        next_due_ms += period_ms;
        if (time_reached(now_ms, next_due_ms)) {
            next_due_ms = now_ms + period_ms;
        }
    }
};

template <typename Db>
class TxScheduler {
public:
    using MessageId = typename Db::MessageId;

    std::array<TxScheduleSlot, Db::kMessageCount> slots{};
    std::array<MessageId, Db::kMessageCount> active_ids{};
    std::size_t active_count{0};

    // Fixed-rate semantics: a freshly enabled message is due immediately
    // (next_due_ms = now_ms), then holds the `period_ms` grid from there.
    //
    // A period of 0 is rejected rather than silently parking the slot: an
    // enabled-but-never-transmitting message is exactly the kind of
    // invisible failure this codebase is trying to make unrepresentable.
    [[nodiscard]] constexpr auto enable(MessageId id,
                                        std::uint32_t period_ms,
                                        std::uint32_t now_ms)
        -> std::expected<void, ScheduleError>
    {
        if (period_ms == 0U) {
            return std::unexpected{ScheduleError::zero_period};
        }

        auto& s = slots[Db::to_index(id)];
        if (!s.enabled) {
            s.enabled = true;
            s.period_ms = period_ms;
            s.next_due_ms = now_ms;
            active_ids[active_count++] = id;
            return {};
        }

        // Re-enable of an already-periodic message: adopt the new period but
        // keep the existing phase, clamping so a shortened period takes
        // effect within one new period instead of waiting out the old one.
        s.period_ms = period_ms;
        const std::uint32_t latest_allowed = now_ms + period_ms;
        if (!time_reached(latest_allowed, s.next_due_ms)) {
            s.next_due_ms = latest_allowed;
        }
        return {};
    }

    // Swap-remove: move the last active id into the vacated hole and shrink.
    //
    // Invariant that makes this valid: nothing depends on active_ids order.
    // run_due_tx() and time_until_next_due_tx() treat it as a set, and
    // enable() guards against duplicates, so active_count <= kMessageCount
    // always holds. No shifting is required. (The only classic hazard with
    // swap-remove -- skipping the swapped-in element while iterating the same
    // array -- cannot occur here, because disable() is only invoked from
    // command draining, which is sequenced before run_due_tx() in the loop.)
    constexpr void disable(MessageId id) {
        auto& s = slots[Db::to_index(id)];
        if (!s.enabled) {
            return;
        }

        s.enabled = false;

        for (std::size_t i = 0; i < active_count; ++i) {
            if (active_ids[i] == id) {
                active_ids[i] = active_ids[active_count - 1];
                --active_count;
                break;
            }
        }
    }
};

} // namespace canfw
