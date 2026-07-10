// Host-side tests for tx_schedule.hpp -- no Zephyr, no test framework.
//
// The static_asserts are the primary tests: they exercise the real
// TxScheduleSlot / TxScheduler code in constant-evaluated context, so a
// behavioral regression in the scheduler fails THE BUILD, not a test run.
// main() adds a longer randomized-jitter simulation as a runtime sanity
// check (constexpr step limits make million-cycle loops impractical at
// compile time).
//
// Build:
//   g++ -std=c++23 -Wall -Wextra -Werror -I<path-to-canfw-headers>
//       tx_schedule_test.cpp -o tx_schedule_test && ./tx_schedule_test
//
// This file is also safe to add to a target build: if it compiles, the
// compile-time suite passed.

#include "tx_schedule.hpp"

#include <cassert>
#include <cstdint>
#include <cstdio>

namespace {

// Minimal stand-in database: the scheduler only needs MessageId,
// kMessageCount, and to_index.
struct FakeDb {
    enum class MessageId : std::uint8_t { alpha = 0, bravo = 1, charlie = 2 };
    static constexpr std::size_t kMessageCount = 3;
    static constexpr auto to_index(MessageId id) -> std::size_t {
        return static_cast<std::size_t>(id);
    }
};

using Id = FakeDb::MessageId;
using Scheduler = canfw::TxScheduler<FakeDb>;

// --- time_reached: wraparound-safe comparisons ----------------------------

static_assert(canfw::time_reached(1000U, 1000U), "deadline reached exactly");
static_assert(canfw::time_reached(1001U, 1000U), "deadline in the past");
static_assert(!canfw::time_reached(999U, 1000U), "deadline in the future");

// Across the 32-bit rollover: now has wrapped, deadline has not.
static_assert(canfw::time_reached(5U, 0xFFFFFFF0U),
              "now wrapped past a pre-wrap deadline: reached");
// Deadline is ahead across the wrap boundary.
static_assert(!canfw::time_reached(0xFFFFFFF0U, 5U),
              "deadline is ahead across the wrap: not reached");

// --- fresh enable is due immediately ---------------------------------------

consteval bool fresh_enable_is_due_immediately() {
    Scheduler sched{};
    const auto enabled = sched.enable(Id::alpha, 10U, 1000U);
    return enabled.has_value()
        && sched.active_count == 1
        && sched.slots[FakeDb::to_index(Id::alpha)].due(1000U);
}
static_assert(fresh_enable_is_due_immediately());

// --- zero period is rejected, slot untouched -------------------------------

consteval bool zero_period_is_rejected() {
    Scheduler sched{};
    const auto enabled = sched.enable(Id::alpha, 0U, 500U);
    return !enabled.has_value()
        && enabled.error() == canfw::ScheduleError::zero_period
        && sched.active_count == 0
        && !sched.slots[0].enabled;
}
static_assert(zero_period_is_rejected());

// --- fixed-rate: the grid holds under consistently late wakes --------------
//
// This is the behavior change under test. With the old fixed-delay scheme
// (last_tx_ms = now), a 2 ms wake latency stretches every period to 12 ms.
// With the fixed-rate grid, deadlines stay at enable_time + k * period no
// matter how late each individual wake is (short of a full-period stall).

consteval bool grid_holds_under_late_wakes() {
    canfw::TxScheduleSlot slot{.enabled = true, .period_ms = 10U, .next_due_ms = 1000U};

    std::uint32_t wake_ms = 1002U;  // every wake 2 ms late
    for (int cycle = 0; cycle < 5; ++cycle) {
        if (!slot.due(wake_ms)) {
            return false;
        }
        slot.advance_after_send(wake_ms);
        wake_ms += 10U;
    }

    // After 5 sends from a t=1000 grid: next deadline is exactly 1050.
    // Fixed-delay would have produced 1000 + 5 * 12 = 1060 (drift).
    return slot.next_due_ms == 1050U;
}
static_assert(grid_holds_under_late_wakes());

// Longer horizon: 200 cycles of 3 ms-late wakes accumulate zero drift.
consteval bool no_drift_over_200_cycles() {
    canfw::TxScheduleSlot slot{.enabled = true, .period_ms = 10U, .next_due_ms = 0U};

    std::uint32_t sends = 0;
    for (std::uint32_t wake_ms = 3U; wake_ms < 2000U; wake_ms += 10U) {
        if (slot.due(wake_ms)) {
            slot.advance_after_send(wake_ms);
            ++sends;
        }
    }
    // 2000 ms / 10 ms period = exactly 200 sends; deadline back on the grid.
    return sends == 200U && slot.next_due_ms == 2000U;
}
static_assert(no_drift_over_200_cycles());

// --- resync after a stall: no catch-up burst --------------------------------

consteval bool stall_resyncs_instead_of_bursting() {
    canfw::TxScheduleSlot slot{.enabled = true, .period_ms = 10U, .next_due_ms = 1000U};

    // The AO was starved until t=1095 (9.5 periods behind).
    if (!slot.due(1095U)) {
        return false;
    }
    slot.advance_after_send(1095U);

    // One grid step (-> 1010) is still in the past, so the slot resyncs to
    // now + period rather than firing 9 back-to-back catch-up frames.
    return slot.next_due_ms == 1105U && !slot.due(1095U);
}
static_assert(stall_resyncs_instead_of_bursting());

// --- deadline arithmetic survives the u32 rollover --------------------------

consteval bool schedule_survives_u32_wrap() {
    canfw::TxScheduleSlot slot{
        .enabled = true, .period_ms = 10U, .next_due_ms = 0xFFFFFFFBU};

    if (!slot.due(0xFFFFFFFBU)) {
        return false;
    }
    slot.advance_after_send(0xFFFFFFFBU);

    // 0xFFFFFFFB + 10 wraps to 5.
    if (slot.next_due_ms != 5U) {
        return false;
    }
    if (slot.due(0U)) {
        return false;  // 5 ms early, post-wrap: must not be due
    }
    if (slot.until_due_ms(3U) != 2U) {
        return false;
    }
    return slot.due(5U);
}
static_assert(schedule_survives_u32_wrap());

// --- re-enable: shortened period takes effect promptly, no duplicates ------

consteval bool reenable_clamps_shortened_period() {
    Scheduler sched{};
    (void)sched.enable(Id::alpha, 100U, 1000U);
    auto& slot = sched.slots[FakeDb::to_index(Id::alpha)];
    slot.advance_after_send(1000U);  // consume the immediate send -> due 1100

    const auto reenabled = sched.enable(Id::alpha, 10U, 1005U);
    return reenabled.has_value()
        && sched.active_count == 1     // no duplicate active_ids entry
        && slot.next_due_ms == 1015U;  // clamped to now + new period
}
static_assert(reenable_clamps_shortened_period());

consteval bool reenable_keeps_phase_when_lengthened() {
    Scheduler sched{};
    (void)sched.enable(Id::alpha, 10U, 1000U);
    auto& slot = sched.slots[FakeDb::to_index(Id::alpha)];
    slot.advance_after_send(1000U);  // due 1010

    (void)sched.enable(Id::alpha, 100U, 1002U);
    // 1010 is already sooner than now + 100, so the phase is preserved.
    return slot.period_ms == 100U && slot.next_due_ms == 1010U;
}
static_assert(reenable_keeps_phase_when_lengthened());

// --- disable: swap-remove keeps the active set correct ----------------------

consteval bool disable_swap_removes_correctly() {
    Scheduler sched{};
    (void)sched.enable(Id::alpha, 10U, 0U);
    (void)sched.enable(Id::bravo, 20U, 0U);
    (void)sched.enable(Id::charlie, 30U, 0U);

    sched.disable(Id::bravo);

    if (sched.active_count != 2) {
        return false;
    }
    // Set semantics: order is irrelevant, membership is not.
    const bool has_alpha =
        sched.active_ids[0] == Id::alpha || sched.active_ids[1] == Id::alpha;
    const bool has_charlie =
        sched.active_ids[0] == Id::charlie || sched.active_ids[1] == Id::charlie;
    if (!has_alpha || !has_charlie) {
        return false;
    }
    if (sched.slots[FakeDb::to_index(Id::bravo)].due(1000U)) {
        return false;  // disabled slot must never report due
    }

    sched.disable(Id::bravo);  // double-disable is a no-op
    return sched.active_count == 2;
}
static_assert(disable_swap_removes_correctly());

}  // namespace

// --- runtime: randomized-jitter soaks ----------------------------------------

namespace {

struct SoakResult {
    std::uint32_t sends{};
    std::uint32_t final_next_due_ms{};
};

// Simulates run_due_tx against wakes with gaps of 1..max_gap_ms, driven by
// a deterministic LCG so failures reproduce.
SoakResult run_soak(std::uint32_t sim_end_ms, std::uint32_t max_gap_ms) {
    canfw::TxScheduleSlot slot{.enabled = true, .period_ms = 10U, .next_due_ms = 0U};

    std::uint32_t seed = 0x2026'0709U;
    std::uint32_t now_ms = 0U;
    std::uint32_t sends = 0U;

    while (now_ms < sim_end_ms) {
        seed = seed * 1664525U + 1013904223U;
        now_ms += 1U + (seed % max_gap_ms);

        if (slot.due(now_ms)) {
            slot.advance_after_send(now_ms);
            ++sends;
        }
    }
    return {sends, slot.next_due_ms};
}

}  // namespace

int main() {
    constexpr std::uint32_t kSimEndMs = 600'000U;  // 10 simulated minutes
    constexpr std::uint32_t kExpected = kSimEndMs / 10U;

    // Soak A -- light jitter (gaps 1..8 ms, always < period): every deadline
    // is serviced within one period, so the fixed-rate grid must be tracked
    // EXACTLY: one send per grid point, and the deadline stays on the grid.
    // The old fixed-delay scheme fails this badly (~ -31% sends at mean
    // gap 4.5 ms of added latency per period).
    {
        const auto r = run_soak(kSimEndMs, 8U);
        std::printf("light jitter: %u sends (expected %u), next_due %% 10 = %u\n",
                    r.sends, kExpected, r.final_next_due_ms % 10U);
        assert(r.sends >= kExpected - 1U && r.sends <= kExpected + 1U);
        assert(r.final_next_due_ms % 10U == 0U);  // grid phase preserved
    }

    // Soak B -- heavy jitter (gaps 1..16 ms, can exceed the period): the
    // wake source itself under-services the grid, and late-by-more-than-a-
    // period deadlines RESYNC by design (skipping missed grid points, and
    // re-phasing -- losses compound; measured ~73.5% delivery for this
    // distribution). The properties under test are therefore: bounded,
    // burst-free degradation -- never MORE sends than grid points. Frames
    // lost to a starved scheduler are a service problem the AO must solve
    // upstream (thread priority, no printk in the hot path), not something
    // the schedule may "fix" by bursting stale frames onto the bus.
    {
        const auto r = run_soak(kSimEndMs, 16U);
        std::printf("heavy jitter: %u sends (expected <= %u, >= %u)\n",
                    r.sends, kExpected + 1U, (kExpected * 7U) / 10U);
        assert(r.sends <= kExpected + 1U);          // no bursting, ever
        assert(r.sends >= (kExpected * 7U) / 10U);  // loss bounded (measured 73.5%)
    }

    std::printf("tx_schedule_test: all runtime checks passed "
                "(compile-time suite passed by compiling)\n");
    return 0;
}
