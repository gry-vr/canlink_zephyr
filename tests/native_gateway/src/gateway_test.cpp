#include <zephyr/ztest.h>
#include <zephyr/drivers/can.h>
#include <zephyr/kernel.h>
#include <array>
#include <atomic>
#include <cmath>
#include <cstring>
#include "duramax/duramax_db.hpp"
#include "reacher/reacher_db.hpp"
#include "reacher_to_duramax_signal_table.hpp"

// The production entry point is renamed only by this test target's compiler
// definition. All production source bytes remain unchanged.
int canlink_gateway_main(void);
namespace {
const device* const dm = DEVICE_DT_GET(DT_ALIAS(can0));
const device* const re = DEVICE_DT_GET(DT_ALIAS(can1));
struct Captured { can_frame frame; uint32_t at_ms; };
K_MSGQ_DEFINE(dm_capture, sizeof(Captured), 256, 4);
K_MSGQ_DEFINE(re_capture, sizeof(Captured), 256, 4);
K_KERNEL_STACK_DEFINE(gateway_stack, 32768);
k_thread gateway_thread;
std::atomic<int> gateway_returned{0};
std::atomic<unsigned> capture_drops{0};

void capture(const device*, can_frame* frame, void* arg) {
    const Captured item{*frame, k_uptime_get_32()};
    if (k_msgq_put(static_cast<k_msgq*>(arg), &item, K_NO_WAIT) != 0) {
        capture_drops.fetch_add(1);
    }
}
void gateway_entry(void*, void*, void*) {
    (void)canlink_gateway_main();
    gateway_returned.store(1);
}
void inject(const device* dev, uint32_t id, bool extended,
            std::array<uint8_t, 8> bytes, uint8_t dlc=8) {
    can_frame frame{};
    frame.id=id; frame.flags=extended ? CAN_FRAME_IDE : 0;
    frame.dlc=dlc; std::memcpy(frame.data, bytes.data(), 8);
    zassert_equal(can_send(dev, &frame, K_MSEC(100), nullptr, nullptr), 0);
}
Captured next_frame(k_msgq& queue, uint32_t id, uint32_t timeout_ms=250) {
    Captured result{};
    const auto end=k_uptime_get_32()+timeout_ms;
    while (static_cast<int32_t>(end-k_uptime_get_32()) > 0) {
        if (k_msgq_get(&queue, &result, K_MSEC(1))==0 && result.frame.id==id)
            return result;
    }
    zassert_unreachable("No captured frame id=0x%x", id);
    return result;
}
void fresh_capture() {
    k_msgq_purge(&dm_capture); k_msgq_purge(&re_capture);
    capture_drops.store(0);
}
void command_rpm(uint16_t raw) {
    inject(re, 0x200, false, {1,0,1,0,0,
        static_cast<uint8_t>(raw), static_cast<uint8_t>(raw>>8),0});
    k_sleep(K_MSEC(150)); fresh_capture();
}
void seed_engine() {
    inject(dm,0x18FEF600,true,{0xff,0x11,0xff,0xff,0xff,0xff,0xff,0xff});
    inject(dm,0x0CF00400,true,{0xff,0xff,0xff,0x00,0x50,0xff,0xff,0xff});
    inject(dm,0x0CF00300,true,{0xff,0xff,0xff,0xa0,0xff,0xff,0xff,0xff});
    inject(dm,0x10FCFD00,true,{0xff,0xff,0xff,0xff,0x50,0x40,0xff,0xff});
    inject(dm,0x18FEEF00,true,{0xff,0xff,0xff,0x05,0xff,0xff,0xff,0xff});
    inject(dm,0x18FEEE00,true,{0xa1,0xff,0x03,0x45,0xff,0xff,0xff,0xff});
    inject(dm,0x18FE9700,true,{0xa1,0x11,0xff,0xff,0xff,0xff,0xff,0xff});
    inject(dm,0x18FEF700,true,{0xff,0xff,0xff,0xff,0xff,0xff,0x18,0x01});
    k_sleep(K_MSEC(150)); fresh_capture();
}
template<typename T> T decode_re(const Captured& c) {
    auto result=reacher::Codec::decode(c.frame.id,c.frame.data,c.frame.dlc);
    zassert_true(result.has_value());
    zassert_true(std::holds_alternative<T>(*result));
    return std::get<T>(*result);
}
duramax::Tsc131 next_tsc() {
    auto c=next_frame(dm_capture,0x0c000031);
    auto msg=duramax::Codec::decode(c.frame.id,c.frame.data,c.frame.dlc);
    zassert_true(msg.has_value());
    return std::get<duramax::Tsc131>(*msg);
}
void* setup() {
    zassert_true(device_is_ready(dm)); zassert_true(device_is_ready(re));
    zassert_equal(can_set_mode(dm,CAN_MODE_LOOPBACK),0);
    zassert_equal(can_set_mode(re,CAN_MODE_LOOPBACK),0);
    can_filter dm_filter{}; dm_filter.flags=CAN_FILTER_IDE;
    can_filter re_filter{};
    zassert_true(can_add_rx_filter(dm,capture,&dm_capture,&dm_filter)>=0);
    zassert_true(can_add_rx_filter(re,capture,&re_capture,&re_filter)>=0);
    k_thread_create(&gateway_thread,gateway_stack,K_KERNEL_STACK_SIZEOF(gateway_stack),
        gateway_entry,nullptr,nullptr,nullptr,10,0,K_NO_WAIT);
    k_sleep(K_MSEC(1200));
    zassert_equal(gateway_returned.load(),0,"Production main returned early");
    fresh_capture();
    return nullptr;
}
}

ZTEST_SUITE(canlink_gateway,nullptr,setup,nullptr,nullptr,nullptr);

ZTEST(canlink_gateway, test_all_nine_engine_exports) {
    seed_engine();
    const auto raw=next_frame(re_capture,0x300);
    // Independent Motorola wire assertions for 2560 RPM and 340 mbar.
    zassert_equal(raw.frame.data[0],0x0a); zassert_equal(raw.frame.data[1],0x00);
    const auto e0=decode_re<reacher::Export0>(raw);
    zassert_equal(e0.eng_speed,2560); zassert_equal(e0.manifold_press,340);
    zassert_within(e0.actual_throttle,64.0,0.001);
    const auto e3=decode_re<reacher::Export3>(next_frame(re_capture,0x303));
    zassert_equal(e3.fuel_rail_pressure,643);
    const auto e8=decode_re<reacher::Export8>(next_frame(re_capture,0x308));
    zassert_within(e8.battery_bus_voltage,14.0,0.001);
    const auto eb=decode_re<reacher::ExportB>(next_frame(re_capture,0x30b));
    zassert_within(eb.coolant_temp,249.8,0.001);
    zassert_equal(eb.oil_temp,534);
    zassert_within(eb.oil_pressure,2.90076,0.001);
    zassert_within(eb.exhaust_gas_temp,-205.54375,0.06);
    zassert_equal(capture_drops.load(),0);
}

ZTEST(canlink_gateway, test_reverse_rpm_and_disabled_override) {
    command_rpm(12000); // 1500 physical RPM
    const auto tsc=next_tsc();
    zassert_within(tsc.engrequestedspeed_speedlimit,1500.0,0.001);
    zassert_equal(tsc.engoverridectrlmode,0);
}

ZTEST(canlink_gateway, test_fractional_rpm_characterization) {
    command_rpm(12001); // 1500.125 RPM; current transform truncates to uint16_t
    const auto tsc=next_tsc();
    zassert_within(tsc.engrequestedspeed_speedlimit,1500.0,0.001);
    printk("OBSERVED: requested 1500.125 RPM, translated 1500 RPM\n");
}

ZTEST(canlink_gateway, test_stale_command_characterization) {
    command_rpm(16000); // 2000 RPM, then stop injecting commands
    k_sleep(K_MSEC(600)); fresh_capture();
    zassert_within(next_tsc().engrequestedspeed_speedlimit,2000.0,0.001);
    printk("OBSERVED: command still retransmitted after 600 ms without input\n");
}

ZTEST(canlink_gateway, test_bad_dlc_and_unknown_id_preserve_value) {
    command_rpm(12000);
    inject(re,0x200,false,{0,0,0,0,0,0,0,0},7);
    inject(re,0x201,false,{0,0,0,0,0,0,0,0},8);
    k_sleep(K_MSEC(150)); fresh_capture();
    zassert_within(next_tsc().engrequestedspeed_speedlimit,1500.0,0.001);
}

ZTEST(canlink_gateway, test_tsc_counter_checksum_and_timing) {
    command_rpm(12000);
    uint32_t previous_time=0; uint8_t previous_counter=0;
    for (unsigned i=0;i<24;++i) {
        const auto c=next_frame(dm_capture,0x0c000031);
        const auto counter=static_cast<uint8_t>(c.frame.data[7]&0x0f);
        const auto checksum=static_cast<uint8_t>(c.frame.data[7]>>4);
        unsigned sum=counter+0x0c+0x31;
        for (unsigned b=0;b<7;++b) sum+=c.frame.data[b];
        const unsigned expected=(sum+(sum>>3)+((sum>>6)&3))&7;
        zassert_true(counter<8); zassert_equal(checksum,expected);
        if(i) {
            zassert_equal(counter,static_cast<uint8_t>((previous_counter+1)%8));
            zassert_equal(c.at_ms-previous_time,10);
        }
        previous_time=c.at_ms; previous_counter=counter;
    }
}

ZTEST(canlink_gateway, test_export_periods) {
    constexpr std::array<uint32_t,4> ids{0x300,0x303,0x308,0x30b};
    constexpr std::array<uint32_t,4> periods{50,50,100,50};
    for(unsigned n=0;n<ids.size();++n) {
        fresh_capture();
        auto prev=next_frame(re_capture,ids[n]);
        for(unsigned i=0;i<6;++i) {
            auto cur=next_frame(re_capture,ids[n]);
            zassert_equal(cur.at_ms-prev.at_ms,periods[n]); prev=cur;
        }
    }
}
