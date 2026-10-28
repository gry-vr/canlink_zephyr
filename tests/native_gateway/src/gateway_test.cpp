#include <zephyr/ztest.h>
#include <zephyr/drivers/can.h>
#include <zephyr/kernel.h>
#include <array>
#include <atomic>
#include <cmath>
#include <cstring>
#include <limits>
#include "duramax/duramax_db.hpp"
#include "reacher/reacher_db.hpp"
#include "reacher_to_duramax_signal_table.hpp"
#include "throttle_policy.hpp"
#include "can_active_object.hpp"
#include "duramax/duramax_hooks.hpp"
#include "reacher/reacher_hooks.hpp"
#include "../../oracle/legacy_throttle.hpp"

// The production entry point is renamed only by this test target's compiler
// definition. The target compiles the production sources without test patches.
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
using DmSnapshot = canfw::SnapshotReply<duramax::DuramaxDb>;
using ReSnapshot = canfw::SnapshotReply<reacher::ReacherDb>;
K_MSGQ_DEFINE(dm_snapshot_q, sizeof(DmSnapshot), 1, 8);
K_MSGQ_DEFINE(re_snapshot_q, sizeof(ReSnapshot), 1, 8);
static DmSnapshot dm_snapshot;
static ReSnapshot re_snapshot;
const ReSnapshot& read_re_snapshot() {
    auto ao=canfw::CanActiveObject<reacher::ReacherDb,ReacherHooks>::create(re,{},false);
    zassert_true(ao.has_value());
    zassert_true((*ao)->endpoint().request_snapshot_into(re_snapshot_q,re_snapshot).has_value());
    return re_snapshot;
}
const DmSnapshot& read_dm_snapshot() {
    auto ao=canfw::CanActiveObject<duramax::DuramaxDb,DuramaxHooks>::create(dm,{},true);
    zassert_true(ao.has_value());
    zassert_true((*ao)->endpoint().request_snapshot_into(dm_snapshot_q,dm_snapshot).has_value());
    return dm_snapshot;
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
    // Before any test can inject a valid Reacher command, startup remains disabled.
    const auto startup = next_frame(dm_capture,0x0c000031);
    zassert_equal(startup.frame.data[0],0);
    zassert_equal(startup.frame.data[1],0); zassert_equal(startup.frame.data[2],0);
    for(unsigned i=3;i<7;++i) zassert_equal(startup.frame.data[i],0xff);
    inject(re,0x200,false,{0,0,0,0,0,0xff,0xff,0});
    k_sleep(K_MSEC(150)); fresh_capture();
    const auto rejected_startup=next_frame(dm_capture,0x0c000031);
    zassert_equal(rejected_startup.frame.data[0],0);
    zassert_equal(rejected_startup.frame.data[1],0); zassert_equal(rejected_startup.frame.data[2],0);
    zassert_equal(read_re_snapshot().rejected_throttle_inputs,1);
    zassert_false(re_snapshot.command_source.valid);
    printk("Task2 sizes: DM AO=%zu RE AO=%zu DM snapshot=%zu RE snapshot=%zu source=%zu\n",
        sizeof(canfw::CanActiveObject<duramax::DuramaxDb,DuramaxHooks>),
        sizeof(canfw::CanActiveObject<reacher::ReacherDb,ReacherHooks>),
        sizeof(DmSnapshot),sizeof(ReSnapshot),sizeof(canfw::throttle::Source));
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
    zassert_within(tsc.engrequestedspeed_speedlimit,(IS_ENABLED(CONFIG_CANLINK_THROTTLE_BAND_MAPPING)?2000.0:1500.0),0.001);
    zassert_equal(tsc.engoverridectrlmode,1);
}

ZTEST(canlink_gateway, test_fractional_rpm_characterization) {
    command_rpm(12001);
    zassert_within(next_tsc().engrequestedspeed_speedlimit,
        IS_ENABLED(CONFIG_CANLINK_THROTTLE_BAND_MAPPING)?2000.0:1500.125,0.001);
    command_rpm(16009);
    zassert_within(next_tsc().engrequestedspeed_speedlimit,2001.125,0.001);
}

ZTEST(canlink_gateway, test_stale_command_characterization) {
    command_rpm(16000);
    k_sleep(K_MSEC(600)); fresh_capture();
    const auto stale=next_tsc();
    zassert_equal(stale.engoverridectrlmode,0);
    zassert_within(stale.engrequestedspeed_speedlimit,0.0,0.001);
    command_rpm(16009);
    const auto recovered=next_tsc();
    zassert_equal(recovered.engoverridectrlmode,1);
    zassert_within(recovered.engrequestedspeed_speedlimit,2001.125,0.001);
}

ZTEST(canlink_gateway, test_bad_dlc_and_unknown_id_preserve_value) {
    command_rpm(12000);
    inject(re,0x200,false,{0,0,0,0,0,0,0,0},7);
    inject(re,0x201,false,{0,0,0,0,0,0,0,0},8);
    k_sleep(K_MSEC(150)); fresh_capture();
    zassert_within(next_tsc().engrequestedspeed_speedlimit,(IS_ENABLED(CONFIG_CANLINK_THROTTLE_BAND_MAPPING)?2000.0:1500.0),0.001);
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

ZTEST(canlink_gateway, test_boundary_wire_frames) {
    constexpr std::uint16_t values[]{0,10399,10400,10401,16007,16008,16009,16010,0x7fff};
    for(auto raw : values) {
        command_rpm(raw);
        auto captured=next_frame(dm_capture,0x0c000031);
        auto arc=captured.frame.data[7]&7;
        auto expected=legacy_oracle::frame(raw,arc);
        if (!IS_ENABLED(CONFIG_CANLINK_THROTTLE_BAND_MAPPING)) {
            expected[1]=raw&255; expected[2]=raw>>8;
            unsigned sum=arc+0x0c+0x31;
            for(unsigned i=0;i<7;++i) sum+=expected[i];
            expected[7]=((((sum>>6)&3)+(sum>>3)+sum)&7)*16+arc;
        }
        zassert_mem_equal(captured.frame.data,expected.data(),8,"raw=%u",raw);
    }
    // Invalid wire request retains the last accepted value, without refreshing age.
    command_rpm(16009);
    command_rpm(0xffff);
    zassert_within(next_tsc().engrequestedspeed_speedlimit,2001.125,0.001);
}

ZTEST(canlink_gateway, test_timeout_boundary_and_invalid_does_not_refresh) {
    command_rpm(16009);
    const auto stale_count=read_dm_snapshot().stale_timeout_events;
    // Re-send at a known time, rather than using command_rpm's 150-ms wait.
    const auto sent=k_uptime_get_32();
    inject(re,0x200,false,{0,0,0,0,0,0x89,0x3e,0});
    k_sleep(K_MSEC(350));
    inject(re,0x200,false,{0,0,0,0,0,0xff,0xff,0});
    fresh_capture();
    auto before=next_frame(dm_capture,0x0c000031);
    zassert_equal(before.frame.data[0],0xf1);
    Captured transition{};
    do { transition=next_frame(dm_capture,0x0c000031); }
    while(transition.frame.data[0]!=0);
    // 1-ms source processing, 10-ms TX grid. Translator replay cannot reset age.
    zassert_between_inclusive(transition.at_ms-sent,500,520);
    zassert_equal(transition.frame.data[1],0); zassert_equal(transition.frame.data[2],0);
    zassert_equal(read_dm_snapshot().stale_timeout_events,stale_count+1);
    k_sleep(K_MSEC(30));
    zassert_equal(read_dm_snapshot().stale_timeout_events,stale_count+1);
    command_rpm(0);
    auto recovered=next_frame(dm_capture,0x0c000031);
    zassert_equal(recovered.frame.data[0],0xf1);
    auto raw=recovered.frame.data[1]+256*recovered.frame.data[2];
    zassert_equal(raw,IS_ENABLED(CONFIG_CANLINK_THROTTLE_BAND_MAPPING)?10000:0);
}

ZTEST(canlink_gateway, test_valid_then_invalid_preserves_source_age) {
    auto rejected=read_re_snapshot().rejected_throttle_inputs;
    inject(re,0x200,false,{0,0,0,0,0,0x89,0x3e,0});
    k_sleep(K_MSEC(1));
    const auto original=read_re_snapshot().command_source;
    inject(re,0x200,false,{0,0,0,0,0,0xff,0xff,0});
    k_sleep(K_MSEC(1));
    const auto& after=read_re_snapshot();
    zassert_equal(after.rejected_throttle_inputs,rejected+1);
    zassert_equal(after.command_source.timestamp_ms,original.timestamp_ms);
    zassert_equal(after.command_source.sequence,original.sequence);
    zassert_within(*after.store.get<reacher::SignalId::reacher_ctrl__throttle_rpm>(),2001.125,0.001);
    k_sleep(K_MSEC(150)); fresh_capture();
    auto actual=next_frame(dm_capture,0x0c000031);
    zassert_equal(actual.frame.data[0],0xf1);
    zassert_equal(actual.frame.data[1],0x89); zassert_equal(actual.frame.data[2],0x3e);
}

ZTEST(canlink_gateway, test_invalid_api_updates_retain_last_request) {
    command_rpm(16009);
    const auto source=read_re_snapshot().command_source;
    const auto count=read_dm_snapshot().rejected_throttle_inputs;
    auto ao=canfw::CanActiveObject<duramax::DuramaxDb,DuramaxHooks>::create(dm,{},true);
    auto candidate=source; ++candidate.sequence;
    for(double bad : {-1.0,std::numeric_limits<double>::quiet_NaN(),
            std::numeric_limits<double>::infinity(),-std::numeric_limits<double>::infinity(),8031.876}) {
        zassert_equal((*ao)->endpoint().update_signal(
            duramax::SignalId::tsc1_31__engrequestedspeed_speedlimit,
            duramax::SignalPhysicalValue{bad},false,K_NO_WAIT,candidate),0);
    }
    // Type-mismatched variants must not change hook state before store validation.
    zassert_equal((*ao)->endpoint().update_signal(
        duramax::SignalId::tsc1_31__engrequestedspeed_speedlimit,
        duramax::SignalPhysicalValue{std::uint16_t{2000}},false,K_NO_WAIT,candidate),0);
    zassert_equal(read_dm_snapshot().rejected_throttle_inputs,count+6);
    fresh_capture();
    auto wire=next_frame(dm_capture,0x0c000031);
    zassert_equal(wire.frame.data[0],0xf1);
    zassert_equal(wire.frame.data[1],0x89); zassert_equal(wire.frame.data[2],0x3e);
}
