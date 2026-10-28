#include "throttle_policy.hpp"
#include "../oracle/legacy_throttle.hpp"
#include <cassert>
#include <cstdio>
#include <limits>
using namespace canfw::throttle;
static_assert(map_throttle_raw(10400) == 10000);
static_assert(map_throttle_raw(10401) == 16000);
static_assert(map_throttle_raw(16008) == 16000);
static_assert(map_throttle_raw(16009) == 16009);
static_assert(validate_rpm(2001.1875) == 16010); // nearest, positive tie upward
static_assert(sizeof(Source) == 20);
int main() {
    constexpr std::uint16_t inputs[]{0,10399,10400,10401,16007,16008,16009,16010,0x7fff,0xffff};
    constexpr std::uint16_t mapped[]{10000,10000,10000,16000,16000,16000,16009,16010,0x7fff,0xffff};
    for (bool bands : {false, true}) {
        for (unsigned n=0;n<10;++n) {
            Policy p;
            assert(!p.evaluate(0,bands,true,500).enabled);
            const bool valid = p.accept(inputs[n]*0.125, Source{100,1,0,0x200,true});
            assert(valid == (inputs[n] <= 64255));
            for (unsigned arc=0;arc<8;++arc) {
                const auto output=p.evaluate(100,bands,true,500);
                std::array<std::uint8_t,8> wire{};
                finish_frame(wire.data(), output, arc);
                if (!valid) { assert(!output.enabled && output.raw==0); continue; }
                assert(output.raw == (bands ? mapped[n] : inputs[n]));
                if (bands) assert(wire==legacy_oracle::frame(inputs[n],arc));
                else { // Independent full-byte pass-through/checksum assertion.
                    assert(wire[0]==0xf1 && wire[1]==(inputs[n]&255) && wire[2]==(inputs[n]>>8));
                    unsigned sum=0xf1+wire[1]+wire[2]+4*255+arc+0x0c+0x31;
                    assert(wire[7]==((((sum>>6)&3)+(sum>>3)+sum)&7)*16+arc);
                }
            }
        }
        Policy p;
        assert(p.accept(1500.125,Source{100,1,0,0x200,true}));
        assert(p.evaluate(599,bands,true,500).raw==(bands?16000:12001));
        assert(p.evaluate(599,bands,true,500).enabled);
        assert(!p.evaluate(600,bands,true,500).enabled);
        assert(!p.evaluate(601,bands,true,500).enabled);
        assert(p.stale_events==1);
        assert(!p.accept(1500.125,Source{100,1,0,0x200,true})); // old snapshot never refreshes
        for (double bad : {-0.125, -1., std::numeric_limits<double>::quiet_NaN(),
            std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(),
            8031.876,8191.875}) {
            assert(!p.accept(bad,Source{700,2,0,0x200,true}));
            assert(p.raw==12001 && p.timestamp_ms==100);
            assert(!p.evaluate(700,bands,true,500).enabled);
        }
        assert(p.rejected==7);
        assert(p.accept(2001.125,Source{701,3,0,0x200,true}));
        assert(p.evaluate(701,bands,true,500).raw==16009);
        assert(p.evaluate(701,bands,true,500).enabled);
        assert(!p.evaluate(1201,bands,true,500).enabled && p.stale_events==2);
        Policy no_timeout;
        assert(no_timeout.accept(0,Source{10,1,0,0x200,true}));
        assert(no_timeout.evaluate(100000,bands,false,500).enabled);
        Policy wrap;
        assert(wrap.accept(0,Source{0xffffff00U,1,0,0x200,true}));
        assert(wrap.evaluate(243,bands,true,500).enabled);
        assert(!wrap.evaluate(244,bands,true,500).enabled);
    }
    // Full 8-byte golden frames for all ARC values at the 2000-rpm band.
    for(unsigned arc=0;arc<8;++arc) {
        std::array<std::uint8_t,8> expected{0xf1,0x80,0x3e,0xff,0xff,0xff,0xff,static_cast<std::uint8_t>(arc*17)};
        assert(legacy_oracle::frame(12001,arc)==expected);
        std::array<std::uint8_t,8> actual{};
        finish_frame(actual.data(),{16000,true},arc); assert(actual==expected);
    }
    // Disabled startup/stale golden, including checksum carry at ARC 7.
    constexpr std::uint8_t disabled_checksum_arc[]{0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x17};
    for(unsigned arc=0;arc<8;++arc) {
        std::array<std::uint8_t,8> wire{};
        finish_frame(wire.data(),{},arc);
        const std::array<std::uint8_t,8> expected{0,0,0,0xff,0xff,0xff,0xff,disabled_checksum_arc[arc]};
        assert(wire==expected);
    }
    assert(validate_rpm(8031.875)==64255);
    std::puts("throttle policy: bands on/off, all vectors/ARC, startup, rejection, stale/recovery, wrap PASS");
}
