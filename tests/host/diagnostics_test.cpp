#include "can_diagnostics.hpp"
#include <cassert>
#include <cstdio>
using namespace canfw::diag;
constexpr bool ring_test() {
    Ring<int, 2> r{};
    r.push(1);
    r.push(2);
    r.push(3);
    return r.count == 2 && r.overwritten == 1 && r.at(0) == 2 && r.at(1) == 3;
}
static_assert(ring_test());
constexpr std::uint8_t check[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
static_assert(crc32(check, 9) == 0xCBF43926);
static_assert(sizeof(Record) == 40 && std::is_trivially_copyable_v<Record>);
int main() {
    RecoveryPolicy p(100, 800, 50);
    p.observe(State::bus_off, 0);
    assert(p.due(0, true) == Action::recover);
    assert(p.due(1, true) == Action::none);
    std::uint32_t t = 0;
    for (auto delay : {100U, 200U, 400U, 800U, 800U, 800U}) {
        p.result(t, false);
        assert(p.due(t + delay - 1, true) == Action::none);
        t += delay;
        assert(p.due(t, true) == Action::recover);
    }
    p.result(t, true);
    assert(p.suppress());
    assert(p.due(t + 799, true) == Action::none);
    assert(p.due(t + 800, true) == Action::recover);
    p.observe(State::active, t + 51);
    assert(!p.suppress());
    p.observe(State::stopped, t + 52);
    assert(p.due(t + 52, true) == Action::start);
    p.result(t + 52, false);
    p.observe(State::active, t + 53);
    assert(p.due(t + 10000, true) == Action::none);
    p.observe(State::bus_off, 0xFFFFFFF0);
    assert(p.due(0xFFFFFFF0, false) == Action::observe);
    p.result(0xFFFFFFF0, false);
    assert(p.due(83, false) == Action::none);
    assert(p.due(84, false) == Action::observe);
    // No terminal failure count: retry continues at the cap indefinitely.
    RecoveryPolicy persistent(1, 8, 1);
    persistent.observe(State::bus_off, 0);
    for (std::uint32_t now = 0; now < 100000; now += 8) {
        assert(persistent.due(now, true) == Action::recover);
        persistent.result(now, false);
    }
    persistent.observe(State::warning, 100001);
    assert(!persistent.suppress());
    persistent.observe(State::passive, 100002);
    assert(!persistent.suppress());
    using J = Journal<4>;
    J::Region region{};
    J j(region);
    Record r{};
    r.kind = Event::boot;
    j.boot(r);
    for (int i = 0; i < 6; ++i) {
        r.kind = Event::transition;
        r.arg0 = i;
        j.append(r);
        j.commit();
    }
    assert(j.current().data.events.overwritten == 3);
    assert(j.current().data.events.at(3).arg0 == 5);
    J reboot(region);
    r.kind = Event::boot;
    reboot.boot(r);
    assert(J::valid(reboot.previous()));
    assert(reboot.previous().data.events.at(3).arg0 == 5);
    assert(reboot.current().boot == 2);
    // Corrupt newest current commit: previous valid current/previous boot survives.
    int latest = -1;
    for (int i = 0; i < 3; ++i)
        if (region.banks[i].boot == 2 && J::valid(region.banks[i]))
            latest = i;
    assert(latest >= 0);
    region.banks[latest].data.events.entries[0].arg0 ^= 1;
    J interrupted(region);
    interrupted.boot(r);
    assert(J::valid(interrupted.previous()));
    assert(interrupted.previous().boot == 1);
    for (auto &b : region.banks)
        b.crc ^= 1;
    J corrupt(region);
    corrupt.boot(r);
    assert(!J::valid(corrupt.previous()));
    assert(corrupt.current().boot == 1);
    corrupt.clear(r);
    assert(!J::valid(corrupt.previous()));
    assert(J::valid(corrupt.current()));
    // Every byte in a committed image is covered by validation or CRC.
    auto original = corrupt.current();
    for (std::size_t i = 0; i < sizeof(original); ++i) {
        auto v = original;
        reinterpret_cast<unsigned char *>(&v)[i] ^= 1;
        assert(!J::valid(v));
    }
    std::printf("diagnostics: ring/CRC/layout/backoff/wrap/reboot/torn/corrupt/clear PASS; "
                "record=%zu bank64=%zu region64=%zu counters=%zu driver=%zu\n",
                sizeof(Record), sizeof(Bank<64>), sizeof(RetainedRegion<64>), sizeof(Counters),
                sizeof(DriverSnapshot));
}
