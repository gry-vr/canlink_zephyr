#include <zephyr/ztest.h>
#include <zephyr/irq_offload.h>
#include <zephyr/drivers/can/can_fake.h>
#include "can_active_object.hpp"
#include "reacher/reacher_db.hpp"
#include <atomic>
DEFINE_FFF_GLOBALS;
using namespace canfw;
using Db = reacher::ReacherDb;
static const device *devices[] = {DEVICE_DT_GET(DT_NODELABEL(fake0)),
                                  DEVICE_DT_GET(DT_NODELABEL(fake1))};
struct Pending {
    can_tx_callback_t cb;
    void *user;
    std::uint32_t id;
};
struct Backend {
    std::atomic<int> state{CAN_STATE_STOPPED}, start_failures{0}, filter_failures{0},
        recover_failures{0};
    std::atomic<int> reject{0}, completion_error{0}, send_calls{0}, recover_calls{0},
        start_calls{0}, removed{0}, filters{0};
    std::atomic<bool> false_success{false}, hold{false};
    std::atomic<int> recovery_return_delay_ms{0}, recovery_errno{-EAGAIN};
    std::atomic<bool> in_recovery{false};
    std::atomic<unsigned> hooks{0}, post_encode_hooks{0};
    std::atomic<k_tid_t> send_thread{nullptr}, recovery_thread{nullptr};
    can_state_change_callback_t state_cb{};
    void *state_user{};
    can_rx_callback_t rx_cb{};
    void *rx_user{};
    std::array<Pending, CONFIG_CANLINK_TX_CONTEXTS> pending{};
    unsigned pending_count{};
};
static Backend backend[2];
static int idx(const device *d) { return d == devices[0] ? 0 : 1; }
struct StateInterrupt {
    int bus;
    int state;
};
static void state_irq(const void *arg) {
    auto x = *static_cast<const StateInterrupt *>(arg);
    auto &b = backend[x.bus];
    b.state = x.state;
    if (b.state_cb)
        b.state_cb(devices[x.bus], static_cast<can_state>(x.state),
                   can_bus_err_cnt{std::uint8_t(x.state == CAN_STATE_BUS_OFF ? 255 : 16), 8},
                   b.state_user);
}
static void change(int bus, int state) {
    StateInterrupt x{bus, state};
    irq_offload(state_irq, &x);
}
struct DoneInterrupt {
    int bus;
    Pending pending;
    int error;
};
static void done_irq(const void *arg) {
    const auto &x = *static_cast<const DoneInterrupt *>(arg);
    x.pending.cb(devices[x.bus], x.error, x.pending.user);
}
static int start(const device *d) {
    auto &b = backend[idx(d)];
    ++b.start_calls;
    if (b.start_failures > 0) {
        --b.start_failures;
        return -EIO;
    }
    b.state = CAN_STATE_ERROR_ACTIVE;
    return 0;
}
static int capabilities(const device *, can_mode_t *c) {
    *c = CAN_MODE_MANUAL_RECOVERY;
    return 0;
}
static int mode(const device *d, can_mode_t m) {
    static_cast<can_driver_data *>(d->data)->mode = m;
    return 0;
}
static int state(const device *d, can_state *s, can_bus_err_cnt *e) {
    auto &b = backend[idx(d)];
    if (s)
        *s = static_cast<can_state>(b.state.load());
    if (e)
        *e = {std::uint8_t(b.state == CAN_STATE_BUS_OFF ? 255 : 16), 8};
    return 0;
}
static void set_callback(const device *d, can_state_change_callback_t cb, void *u) {
    auto &b = backend[idx(d)];
    b.state_cb = cb;
    b.state_user = u;
}
static int add_filter(const device *d, can_rx_callback_t cb, void *u, const can_filter *) {
    auto &b = backend[idx(d)];
    if (b.filter_failures > 0) {
        --b.filter_failures;
        return -ENOSPC;
    }
    b.rx_cb = cb;
    b.rx_user = u;
    ++b.filters;
    return 7;
}
static void remove_filter(const device *d, int id) {
    zassert_equal(id, 7);
    auto &b = backend[idx(d)];
    ++b.removed;
    --b.filters;
    b.rx_cb = nullptr;
}
static int recover(const device *d, k_timeout_t t) {
    auto &b = backend[idx(d)];
    zassert_true(K_TIMEOUT_EQ(t, K_NO_WAIT));
    b.recovery_thread = k_current_get();
    ++b.recover_calls;
    if (b.recover_failures > 0) {
        --b.recover_failures;
        return b.recovery_errno;
    }
    if (!b.false_success) {
        b.in_recovery = true;
        change(idx(d), CAN_STATE_ERROR_ACTIVE);
        if (b.recovery_return_delay_ms)
            k_sleep(K_MSEC(b.recovery_return_delay_ms.load()));
        b.in_recovery = false;
    }
    return 0;
}
static int send(const device *d, const can_frame *f, k_timeout_t t, can_tx_callback_t cb, void *u) {
    auto &b = backend[idx(d)];
    zassert_true(K_TIMEOUT_EQ(t, K_NO_WAIT));
    b.send_thread = k_current_get();
    ++b.send_calls;
    if (b.reject)
        return b.reject;
    Pending p{cb, u, f->id};
    if (b.hold) {
        zassert_true(b.pending_count < b.pending.size());
        b.pending[b.pending_count++] = p;
    } else {
        DoneInterrupt x{idx(d), p, b.completion_error};
        irq_offload(done_irq, &x);
    }
    return 0;
}
template <int Bus> struct Hooks {
    template <class M, class S> void on_before_send(M &, S &, std::uint32_t) {
        ++backend[Bus].hooks;
    }
    template <class M> void on_after_encode(const M&, std::uint8_t*, std::uint8_t, std::uint32_t) {
        ++backend[Bus].post_encode_hooks;
    }
};
using Ao0 = CanActiveObject<Db, Hooks<0>>;
using Ao1 = CanActiveObject<Db, Hooks<1>>;
static DiagnosticClient client;
static const DiagnosticSnapshot &snapshot(CanEndpoint<Db> ep, bool previous = false,
                                          bool clear = false) {
    zassert_equal(ep.request_diagnostics(client.reply_queue(), previous, clear), 0);
    zassert_equal(client.receive(K_MSEC(100)), 0);
    return client.snapshot();
}
static bool event(const DiagnosticSnapshot &s, diag::Event kind, int error = 0,
                  std::uint32_t id = 0) {
    for (unsigned i = 0; i < s.data.events.count; ++i) {
        const auto &r = s.data.events.at(i);
        if (r.kind == kind && (!error || r.error == error) && (!id || r.can_id == id))
            return true;
    }
    return false;
}
static void rx_burst(const void *arg) {
    int n = *static_cast<const int *>(arg);
    can_frame f{};
    f.id = 0x200;
    f.dlc = 8;
    for (int i = 0; i < n; ++i)
        backend[0].rx_cb(devices[0], &f, backend[0].rx_user);
}
static void state_burst(const void *) {
    for (int i = 0; i < 100; ++i) {
        StateInterrupt x{0, i % 2 ? CAN_STATE_ERROR_WARNING : CAN_STATE_ERROR_PASSIVE};
        state_irq(&x);
    }
    StateInterrupt x{0, CAN_STATE_BUS_OFF};
    state_irq(&x);
}
ZTEST(robustness, test_real_queues_poll_and_fault_backend) {
    fake_can_start_fake.custom_fake = start;
    fake_can_set_mode_fake.custom_fake = mode;
    fake_can_get_capabilities_fake.custom_fake = capabilities;
    fake_can_get_state_fake.custom_fake = state;
    fake_can_set_state_change_callback_fake.custom_fake = set_callback;
    fake_can_add_rx_filter_fake.custom_fake = add_filter;
    fake_can_remove_rx_filter_fake.custom_fake = remove_filter;
    fake_can_recover_fake.custom_fake = recover;
    fake_can_send_fake.custom_fake = send;
    backend[0].filter_failures = 1;
    auto failed = Ao0::create(devices[0]);
    zassert_false(failed.has_value());
    zassert_equal(failed.error(), InitError::rx_filter_install_failed);
    backend[0].start_failures = 1;
    failed = Ao0::create(devices[0]);
    zassert_false(failed.has_value());
    zassert_equal(failed.error(), InitError::can_start_failed);
    zassert_equal(backend[0].removed, 1);
    zassert_equal(backend[0].filters, 0);
    auto a = Ao0::create(devices[0]);
    auto b = Ao1::create(devices[1]);
    zassert_true(a && b);
    auto ep = (*a)->endpoint();
    auto ep1 = (*b)->endpoint();
    reacher::ReacherCtrl msg{};
    zassert_equal(ep.enable_periodic(msg, 10), 0);
    zassert_equal(ep1.enable_periodic(msg, 10), 0);
    k_sleep(K_MSEC(30));
    zassert_true(backend[0].send_calls > 0);
    auto initial = snapshot(ep).data.counters;
    zassert_equal(initial.filter_failures, 1);
    CAN_STATS_ACK_ERROR_INC(devices[0]);
    CAN_STATS_RX_OVERRUN_INC(devices[0]);
    k_sleep(K_MSEC(6));
    const auto &hardware = snapshot(ep).data.driver;
    zassert_equal(hardware.configured_bitrate, 500000);
    zassert_equal(hardware.sample_point, 875);
    zassert_equal(hardware.core_clock_hz, 80000000);
    zassert_true(hardware.mode & CAN_MODE_MANUAL_RECOVERY);
    zassert_equal(hardware.stats[5], 1);
    zassert_equal(hardware.stats[6], 1);
    change(0, CAN_STATE_ERROR_WARNING);
    k_sleep(K_MSEC(2));
    change(0, CAN_STATE_ERROR_PASSIVE);
    k_sleep(K_MSEC(2));
    backend[0].recover_failures = 3;
    backend[0].false_success = true;
    change(0, CAN_STATE_BUS_OFF);
    k_sleep(K_MSEC(10));
    const auto sends = backend[0].send_calls.load();
    const auto hooks = backend[0].hooks.load();
    const auto other = backend[1].send_calls.load();
    k_sleep(K_MSEC(160));
    zassert_equal(backend[0].send_calls, sends);
    zassert_equal(backend[0].hooks, hooks);
    zassert_true(backend[1].send_calls > other);
    auto off = snapshot(ep).data.counters;
    zassert_true(off.tx_suppressed >= 10);
    zassert_true(off.recovery_attempts >= 5);
    zassert_true(off.recovery_failures >= 3);
    zassert_true(off.recovery_timeouts >= 1);
    zassert_not_equal(backend[0].send_thread.load(), backend[0].recovery_thread.load());
    backend[0].false_success = false;
    k_sleep(K_MSEC(60));
    auto recovered = snapshot(ep).data.counters;
    zassert_equal(recovered.state, diag::State::active);
    for (unsigned state_index = 0; state_index < 4; ++state_index)
        zassert_true(recovered.transitions[state_index] > 0);
    zassert_equal(recovered.entry_tec, 255);
    zassert_equal(recovered.entry_rec, 8);
    zassert_equal(recovered.exit_tec, 16);
    zassert_equal(recovered.bus_offs, 1);
    zassert_equal(recovered.recovery_successes, 1);
    zassert_true(recovered.last_bus_off_ms >= 170);
    zassert_equal(backend[0].filters, 1);
    zassert_true(event(client.snapshot(), diag::Event::recovery_complete));
    // An ACTIVE callback can precede release of the driver's internal mutex.
    // Keep the CAN worker responsive and defer TX until the executor returns.
    backend[0].recovery_return_delay_ms = 30;
    backend[0].recover_failures = 1;
    backend[0].recovery_errno = -ETIMEDOUT;
    change(0, CAN_STATE_BUS_OFF);
    for (unsigned tries = 0; tries < 20 && !backend[0].in_recovery; ++tries)
        k_sleep(K_MSEC(1));
    zassert_true(backend[0].in_recovery);
    const auto pending_sends = backend[0].send_calls.load();
    const auto pending_hooks = backend[0].hooks.load();
    zassert_equal(snapshot(ep).data.counters.state, diag::State::active);
    k_sleep(K_MSEC(10));
    zassert_equal(backend[0].send_calls, pending_sends);
    zassert_equal(backend[0].hooks, pending_hooks);
    k_sleep(K_MSEC(25));
    backend[0].recovery_return_delay_ms = 0;
    zassert_true(event(snapshot(ep), diag::Event::recovery_result, -ETIMEDOUT));
    const auto starts = backend[0].start_calls.load();
    backend[0].start_failures = 2;
    change(0, CAN_STATE_STOPPED);
    k_sleep(K_MSEC(80));
    zassert_true(backend[0].start_calls >= starts + 3);
    zassert_equal(snapshot(ep).data.counters.state, diag::State::active);
    reacher::Export0 other_message{};
    backend[0].completion_error = -EIO;
    zassert_equal(ep.send_message(other_message), 0);
    k_sleep(K_MSEC(2));
    zassert_true(event(snapshot(ep), diag::Event::tx_completion_error, -EIO, 0x300));
    backend[0].completion_error = 0;
    for (int err : {-ENETUNREACH, -EIO, -ETIMEDOUT, -ENETDOWN, -EAGAIN}) {
        backend[0].completion_error = err;
        k_sleep(K_MSEC(12));
        zassert_true(event(snapshot(ep), diag::Event::tx_completion_error, err, 0x200));
    }
    backend[0].completion_error = 0;
    backend[0].reject = -EIO;
    k_sleep(K_MSEC(12));
    zassert_true(event(snapshot(ep), diag::Event::tx_rejected, -EIO, 0x200));
    backend[0].reject = 0;
    zassert_equal((*a)->tx_send_failures(),
                  (*a)->tx_immediate_rejections() + (*a)->tx_completion_errors());
    // Fill all callback contexts, force backpressure, then complete in reverse order.
    backend[0].hold = true;
    k_sleep(K_MSEC(100));
    zassert_equal(backend[0].pending_count, CONFIG_CANLINK_TX_CONTEXTS);
    zassert_true(snapshot(ep).data.counters.context_exhausted > 0);
    // Includes bus-off suppression, immediate rejection and local pool exhaustion:
    // the ARC-consuming post hook runs exactly once per driver offer, never sooner.
    zassert_equal(backend[0].post_encode_hooks.load(),backend[0].send_calls.load());
    backend[0].hold = false;
    for (unsigned i = backend[0].pending_count; i > 0; --i) {
        DoneInterrupt x{0, backend[0].pending[i - 1], -ETIMEDOUT};
        irq_offload(done_irq, &x);
    }
    backend[0].pending_count = 0;
    k_sleep(K_MSEC(20));
    int count = 100;
    irq_offload(rx_burst, &count);
    k_sleep(K_MSEC(15));
    auto rx = snapshot(ep).data.counters;
    zassert_true(rx.rx_drops >= 36);
    zassert_true(rx.last_good_rx_ms > 0);
    zassert_equal(rx.last_rx_id, 0x200);
    zassert_true(event(client.snapshot(), diag::Event::rx_overflow));
    zassert_equal(client.snapshot().data.raw.count, CONFIG_CANLINK_RAW_FRAME_DEPTH);
    zassert_true(client.snapshot().data.raw.overwritten > 0);
    backend[0].false_success = true;
    irq_offload(state_burst, nullptr);
    k_sleep(K_MSEC(10));
    zassert_true(snapshot(ep).data.counters.event_drops > 0);
    zassert_equal(client.snapshot().data.counters.state, diag::State::bus_off);
    zassert_true(event(client.snapshot(), diag::Event::queue_overflow));
    backend[0].false_success = false;
    k_sleep(K_MSEC(60));
    zassert_equal(snapshot(ep).data.counters.state, diag::State::active);
    zassert_equal(snapshot(ep1).data.counters.bus_offs, 0);
    zassert_equal(client.snapshot().data.counters.tx_completion_errors, 0);
    // Real command/reply queue retrieval and clear; current counters survive clear.
    auto before_clear = snapshot(ep).data.counters;
    zassert_true(DiagnosticJournal::valid(snapshot(ep, false, true)));
    zassert_equal(client.snapshot().data.counters.bus_offs, before_clear.bus_offs);
    zassert_true(event(client.snapshot(), diag::Event::cleared));
    client.print();
    zassert_false(DiagnosticJournal::valid(snapshot(ep, true)));
    printk("sizes: CanDiagnostics=%zu snapshot=%zu retained/bus=%zu client=%zu actor=%zu "
           "raw-depth=%d\n",
           sizeof(CanDiagnostics), sizeof(DiagnosticSnapshot), sizeof(DiagnosticJournal::Region),
           sizeof(DiagnosticClient), sizeof(Ao0), CONFIG_CANLINK_RAW_FRAME_DEPTH);
    // Stop test-owned schedules; AO threads remain alive through ztest completion.
    ep.disable_message(reacher::MessageId::reacher_ctrl);
    ep1.disable_message(reacher::MessageId::reacher_ctrl);
}
ZTEST_SUITE(robustness, nullptr, nullptr, nullptr, nullptr, nullptr);
