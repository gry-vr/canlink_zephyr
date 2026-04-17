#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "can_active_object.hpp"
#include "can_endpoint.hpp"

#include "duramax/duramax_db.hpp"
#include "duramax/duramax_hooks.hpp"
#include "duramax/duramax_choices.hpp"

#include "reacher/reacher_db.hpp"
#include "reacher/reacher_hooks.hpp"

namespace {

using DuramaxAo = canfw::CanActiveObject<duramax::DuramaxDb, DuramaxHooks>;
using ReacherAo = canfw::CanActiveObject<reacher::ReacherDb, ReacherHooks>;

const device* const dm_bus = DEVICE_DT_GET(DT_ALIAS(can0));
const device* const reacher_bus = DEVICE_DT_GET(DT_ALIAS(can1));

K_MSGQ_DEFINE(reacher_reply_q,
              sizeof(canfw::SnapshotReply<reacher::ReacherDb>),
              1,
              alignof(canfw::SnapshotReply<reacher::ReacherDb>));

} // namespace

int main(void)
{
    auto duramax_result = DuramaxAo::create(dm_bus, DuramaxHooks{}, true);
    if (!duramax_result) {
        printk("DuramaxAo init failed: %d\n", static_cast<int>(duramax_result.error()));
        return -1;
    }

    auto reacher_result = ReacherAo::create(reacher_bus, ReacherHooks{}, false);
    if (!reacher_result) {
        printk("ReacherAo init failed: %d\n", static_cast<int>(reacher_result.error()));
        return -1;
    }

    auto* duramax_ao = *duramax_result;
    auto* reacher_ao = *reacher_result;

    auto duramax_ep = duramax_ao->endpoint();
    auto reacher_ep = reacher_ao->endpoint();

    duramax::Tsc131 tsc1{};
    tsc1.engoverridectrlmode = 0;
    tsc1.engrequestedspeedctrlconditions = 0;
    tsc1.overridectrlmodepriority = 0;
    tsc1.engrequestedspeed_speedlimit = 0;
    tsc1.engrequestedtorque_torquelimit = -125;
    tsc1.tsc1transrate = std::to_underlying(
        duramax::Tsc131Tsc1transrateState::use_standard_tsc1_transmission_rates_of_10_ms_to_engine);
    tsc1.tsc1ctrlpurpose = 0;
    tsc1.engrequestedtorquehighresolution = 0;

    int rc = duramax_ep.enable_periodic(tsc1, 10);
    if (rc != 0) {
        printk("enable_periodic failed: %d\n", rc);
    }

    while (true) {
        auto maybe_snapshot = reacher_ep.request_snapshot_blocking(reacher_reply_q);

        if (maybe_snapshot && maybe_snapshot->valid) {
            auto throttle =
                maybe_snapshot->store.template get<reacher::SignalId::reacher_ctrl__throttle_rpm>();

            if (throttle) {
                printk("reacher throttle rpm: %d\n", static_cast<int>(*throttle));

                rc = duramax_ep.update_signal(
                    duramax::SignalId::tsc1_31__engrequestedspeed_speedlimit,
                    static_cast<double>(*throttle),
                    false);

                if (rc != 0) {
                    printk("update_signal failed: %d\n", rc);
                }
            } else {
                printk("reacher throttle rpm: <missing>\n");
            }
        } else {
            printk("snapshot request failed or timed out\n");
        }

        printk("duramax decode_failures=%u tx_build_failures=%u tx_encode_failures=%u\n",
               duramax_ao->decode_failures(),
               duramax_ao->tx_build_failures(),
               duramax_ao->tx_encode_failures());

        printk("reacher decode_failures=%u tx_build_failures=%u tx_encode_failures=%u\n",
               reacher_ao->decode_failures(),
               reacher_ao->tx_build_failures(),
               reacher_ao->tx_encode_failures());

        k_sleep(K_SECONDS(1));
    }

    return 0;
}