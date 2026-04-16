#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "can_active_object.hpp"
#include "duramax/duramax_db.hpp"
#include "duramax/duramax_hooks.hpp"

#include "reacher/reacher_db.hpp"
#include "reacher/reacher_hooks.hpp"



namespace {

using DuramaxAo = canfw::CanActiveObject<duramax::DuramaxDb, DuramaxHooks>;
using DuramaxTx = canfw::TxCommand<duramax::DuramaxDb>;

const device* const dm_bus = DEVICE_DT_GET(DT_ALIAS(can0));

using ReacherAo = canfw::CanActiveObject<reacher::ReacherDb, ReacherHooks>;
using ReacherTx = canfw::TxCommand<reacher::ReacherDb>;

const device* const reacher_bus = DEVICE_DT_GET(DT_ALIAS(can1));

} // namespace

int main(void)
{

    auto ao_result = DuramaxAo::create(dm_bus, DuramaxHooks{}, true);
    if (!ao_result) {
        printk("DuramaxAo init failed: %d\n", static_cast<int>(ao_result.error()));
        return -1;
    }

    auto reacher_ao_result = ReacherAo::create(reacher_bus, ReacherHooks{}, false);
    if(!reacher_ao_result){
        printk("Reacher init failed %d\n", static_cast<int>(reacher_ao_result.error()));
        return -1;
    }




    auto* reacher_ao = *reacher_ao_result;

    // here I am going to do reacher related canbus things

    auto& reacher_store = reacher_ao->rx_store();

    auto vehicle_command = reacher_store.get<reacher::SignalId::reacher_ctrl__throttle_rpm>();


    if(!vehicle_command){
        printk("welp the api sucks");
    }



    auto* ao = *ao_result;

    duramax::Cac1ChargeAirCooler1 cac1{};
    cac1.engine_charge_air_cooler_1_intak = 50;
    cac1.engine_charge_air_cooler_1_ambie = 34;
    cac1.engine_charge_air_cooler_1_effic = 90;

    DuramaxTx::SendMessage send_cmd{};
    send_cmd.message = duramax::MessageVariant{cac1};
    send_cmd.policy = canfw::TxPolicy::periodic_enable;
    send_cmd.period_ms_override = 1000;

    int rc = ao->post_tx(DuramaxTx::Variant{send_cmd}, K_NO_WAIT);
    if (rc != 0) {
        printk("post_tx failed: %d\n", rc);
    }
    uint16_t counter = 0;
    DuramaxTx::UpdateSignal update_signal{};
    update_signal.signal_id = duramax::SignalId::cac1_charge_air_cooler_1__engine_charge_air_cooler_1_ambie;
    update_signal.trigger_parent_send = false;
    double value = 50;
    update_signal.value = value;
    

    while (true) {
        ++counter;

        printk("duramax decode_failures=%u tx_build_failures=%u tx_encode_failures=%u\n",
            ao->decode_failures(),
            ao->tx_build_failures(),
            ao->tx_encode_failures());

        printk("reacher decode_failures=%u tx_build_failures=%u tx_encode_failures=%u\n",
            reacher_ao->decode_failures(),
            reacher_ao->tx_build_failures(),
            reacher_ao->tx_encode_failures());

        if ((counter % 20) == 0) {
            value += 1.0;
            update_signal.value = value;
            rc = ao->post_tx(DuramaxTx::Variant{update_signal}, K_NO_WAIT);
            if (rc != 0) {
                printk("post tx failed: %d\n", rc);
            }
        }

        auto vehicle_command =
            reacher_ao->rx_store().get<reacher::SignalId::reacher_ctrl__throttle_rpm>();

        if (vehicle_command) {
            printk("reacher throttle rpm: %d\n", static_cast<int>(*vehicle_command));
        } else {
            printk("reacher throttle rpm: <missing>\n");
        }

        k_sleep(K_SECONDS(1));
    }

    return 0;
}
