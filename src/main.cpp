#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/disk.h>

#include <zephyr/usb/usb_device.h>

#include <zephyr/storage/disk_access.h>

#include <tuple>
#include <utility>
#include <string.h>

#include <zephyr/app_version.h>

#include "can_active_object.hpp"
#include "can_endpoint.hpp"

#include "duramax/duramax_db.hpp"
#include "duramax/duramax_hooks.hpp"
#include "duramax/duramax_choices.hpp"

#include "reacher/reacher_db.hpp"
#include "reacher/reacher_hooks.hpp"

#include "translator_active_object.hpp"
#include "duramax_to_reacher_signal_table.hpp"
#include "reacher_to_duramax_signal_table.hpp"
#include "message_policy_table.hpp"

namespace {
#define MY_LED_NODE DT_ALIAS(status_led)

using DuramaxAo = canfw::CanActiveObject<duramax::DuramaxDb, DuramaxHooks>;
using ReacherAo = canfw::CanActiveObject<reacher::ReacherDb, ReacherHooks>;

using DuramaxToReacherTranslator =
    Translator<
        duramax::DuramaxDb,
        reacher::ReacherDb,
        DuramaxToReacherTranslations<duramax::DuramaxDb, reacher::ReacherDb>
    >;

using ReacherToDuramaxTranslator =
    Translator<
        reacher::ReacherDb,
        duramax::DuramaxDb,
        ReacherToDuramaxTranslations<reacher::ReacherDb, duramax::DuramaxDb>
    >;

const device* const dm_bus = DEVICE_DT_GET(DT_ALIAS(can0));
const device* const reacher_bus = DEVICE_DT_GET(DT_ALIAS(can1));

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(MY_LED_NODE, gpios);

// Stats print every Nth 100 ms iteration. Main runs at a higher priority
// than the AO threads by default (CONFIG_MAIN_THREAD_PRIORITY=0 vs 5), and
// synchronous printk spin-polls the UART, so every character printed here
// is time stolen from the 10 ms TSC1 schedule. Printing at 2 s instead of
// 100 ms cuts that starvation twentyfold; the real fix (deferred logging +
// priority inversion) is tracked for Phase 1.
constexpr std::uint8_t kStatsDivider = 20;

template <typename Endpoint, typename Msg>
void enable_periodic_checked(const Endpoint& ep,
                             const Msg& msg,
                             std::uint32_t period_ms,
                             const char* name)
{
    const int rc = ep.enable_periodic(msg, period_ms);
    if (rc != 0) {
        printk("enable_periodic(%s) failed: %d\n", name, rc);
    }
}

} // namespace

// eMMC bring-up scaffolding, kept for bench use. Not called from main():
// it never returns, which left the entire CAN path below unreachable.
int fake_main(){
    static int counter = 0;
    const char *disk = "KINGSTON";

    int rc = disk_access_ioctl(disk, DISK_IOCTL_CTRL_INIT, NULL);
    printk("disk_access_init(%s) = %d\n", disk, rc);

    uint32_t sector_count = 0;
    uint32_t sector_size = 0;

    rc = disk_access_ioctl(disk, DISK_IOCTL_GET_SECTOR_COUNT, &sector_count);
    printk("sector_count rc=%d count=%u\n", rc, sector_count);

    rc = disk_access_ioctl(disk, DISK_IOCTL_GET_SECTOR_SIZE, &sector_size);
    printk("sector_size rc=%d size=%u\n", rc, sector_size);

    __aligned(32) static uint8_t write_buf[512];
    __aligned(32) static uint8_t read_buf[512];

    if (sector_size > sizeof(write_buf)){
        printk("Sector size too large for test buffer\n");
        return -1;
    }

    // returned a value that indicates this ioctl command returned no useful data...
    // fudge...
    uint32_t erase_block_size = 0;
    rc = disk_access_ioctl(disk, DISK_IOCTL_GET_ERASE_BLOCK_SZ, &erase_block_size);
    printk("erase block size rc=%d, size=%u\n", rc, erase_block_size);


    uint32_t id = 0;
    rc = disk_access_ioctl(disk, DISK_IOCTL_GET_CARD_CID, &id);
    printk("disk cid:: rc=%d, id=%u\n", rc, id);

    memset(write_buf, 0x00, sizeof(write_buf));
    memset(read_buf, 0x00, sizeof(read_buf));

    // const char *msg = "CANLINK EMMC TEST V1";

    // memcpy(write_buf, msg, strlen(msg) + 1);

     uint32_t test_sector = 128;
    // rc = disk_access_write(disk, write_buf, test_sector, 1);

    // printk("WRITE rc=%d\n", rc);
    // if (rc){
    //     return rc;
    // }

    rc = disk_access_ioctl(disk, DISK_IOCTL_CTRL_SYNC, NULL);

    printk("SYNC rc=%d\n", rc);
    if(rc){
        return rc;
    }

    printk("about to READ\n");
    rc = disk_access_read(disk, read_buf, test_sector, 1);

    printk("READ rc=%d", rc);
    if (rc){
        return rc;
    }

    printk("READBACK: %s\n", read_buf);

    while (1) {
        k_sleep(K_SECONDS(1));
        if (counter > 5){
            printk("stuck in the loop!\n");
        }
        counter = (counter + 1) % 6;
    }
}

int main(void)
{
    const struct device *const dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));
    if (!device_is_ready(dev)){
        printk("console not ready\n");
        return -1;
    }

    // DISABLED SECTION DUE TO KCONFIG 
    // CONFIG_USB_DEVICE_INITIALIZE_AT_BOOT=y
    // int ret = usb_enable(NULL);

    // if (ret != 0){
    //     printk("usb_enable failed: %d\n", ret);
    //     return -1;
    // }


    k_sleep(K_SECONDS(1));

    // To run the eMMC bench test instead of the CAN gateway:
    //return fake_main();

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

    if (!duramax_ep.valid() || !reacher_ep.valid()) {
        printk("Endpoint invalid\n");
        return -1;
    }

    // Seed periodic Reacher export messages.
    //
    // The k_sleep between enables is deliberate phase staggering: a freshly
    // enabled message is due immediately, and the fixed-rate scheduler then
    // holds that phase forever. Enabling all four in one command batch put
    // them on the SAME 50 ms phase, so every cycle they hit can_send at the
    // same instant -- with K_NO_WAIT mailbox acquisition, only the first
    // wins and the rest count as tx_send_failures (observed ~50/s on
    // native_sim). A few ms of offset spreads the grid points apart for good.
    {
        reacher::Export0 export0{};
        export0.eng_speed = 0;
        export0.actual_throttle = 0.0;
        export0.manifold_press = 0;
        enable_periodic_checked(reacher_ep, export0, 50, "export0");
        k_sleep(K_MSEC(2));

        reacher::Export3 export3{};
        export3.fuel_rail_pressure = 0;
        enable_periodic_checked(reacher_ep, export3, 50, "export3");
        k_sleep(K_MSEC(3));

        reacher::Export8 export8{};
        export8.battery_bus_voltage = 0.0;
        enable_periodic_checked(reacher_ep, export8, 100, "export8");
        k_sleep(K_MSEC(2));

        reacher::ExportB exportb{};
        exportb.coolant_temp = 50.0;
        exportb.oil_temp = 0.0;
        exportb.oil_pressure = 0.0;
        exportb.exhaust_gas_temp = 0.0;
        enable_periodic_checked(reacher_ep, exportb, 50, "exportb");
    }

    // Seed periodic Duramax TSC1
    {
        duramax::Tsc131 tsc1{};
        tsc1.engoverridectrlmode = 0;
        tsc1.engrequestedspeedctrlconditions = 0;
        tsc1.overridectrlmodepriority = 0;
        tsc1.engrequestedspeed_speedlimit = 0.0;
        tsc1.engrequestedtorque_torquelimit = -125;
        tsc1.tsc1transrate = std::to_underlying(
            duramax::Tsc131Tsc1transrateState::use_standard_tsc1_transmission_rates_of_10_ms_to_engine);
        tsc1.tsc1ctrlpurpose = 0;
        tsc1.engrequestedtorquehighresolution = 0;
        tsc1.messagecounter = 0;
        tsc1.messagechecksum = 0;

        if (auto ok = duramax::DuramaxDb::validate_message(tsc1); !ok) {
            printk("Initial TSC1 validation failed: signal=%u error=%u\n",
                   static_cast<unsigned>(duramax::DuramaxDb::to_index(ok.error().signal_id)),
                   static_cast<unsigned>(ok.error().error));
            return -1;
        }

        enable_periodic_checked(duramax_ep, tsc1, 10, "tsc1");
    }

    // Static storage duration is mandatory: each Translator owns two
    // SnapshotReply-sized buffers (~14 KB for the Duramax direction). As
    // function locals these overflowed the main stack; as function-local
    // statics they live in .bss and are still constructed here, after the
    // endpoints exist. -Wframe-larger-than guards against regression.
    static DuramaxToReacherTranslator duramax_to_reacher{duramax_ep, reacher_ep};
    static ReacherToDuramaxTranslator reacher_to_duramax{reacher_ep, duramax_ep};

    if (!duramax_to_reacher.valid() || !reacher_to_duramax.valid()) {
        printk("Translator invalid\n");
        return -1;
    }

    if(!gpio_is_ready_dt(&led)){
        return -1;
    }

    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    static uint8_t num = 0;
    static uint8_t stats_div = 0;

    while (true) {
        duramax_to_reacher.step_once();
        reacher_to_duramax.step_once();

        if (stats_div == 0) {
            printk("D->R posted=%u val_fail=%u upd_fail=%u src_missing=%u snap_fail=%u\n",
                   duramax_to_reacher.updates_posted(),
                   duramax_to_reacher.validation_failures(),
                   duramax_to_reacher.update_failures(),
                   duramax_to_reacher.source_missing_count(),
                   duramax_to_reacher.snapshot_failures());

            printk("R->D posted=%u val_fail=%u upd_fail=%u src_missing=%u snap_fail=%u\n",
                   reacher_to_duramax.updates_posted(),
                   reacher_to_duramax.validation_failures(),
                   reacher_to_duramax.update_failures(),
                   reacher_to_duramax.source_missing_count(),
                   reacher_to_duramax.snapshot_failures());

            printk("duramax sent=%u decode_fail=%u build_fail=%u encode_fail=%u val_fail=%u send_fail=%u sched_fail=%u\n",
                   duramax_ao->tx_frames_sent(),
                   duramax_ao->decode_failures(),
                   duramax_ao->tx_build_failures(),
                   duramax_ao->tx_encode_failures(),
                   duramax_ao->tx_validation_failures(),
                   duramax_ao->tx_send_failures(),
                   duramax_ao->tx_schedule_failures());

            printk("reacher sent=%u decode_fail=%u build_fail=%u encode_fail=%u val_fail=%u send_fail=%u sched_fail=%u\n",
                   reacher_ao->tx_frames_sent(),
                   reacher_ao->decode_failures(),
                   reacher_ao->tx_build_failures(),
                   reacher_ao->tx_encode_failures(),
                   reacher_ao->tx_validation_failures(),
                   reacher_ao->tx_send_failures(),
                   reacher_ao->tx_schedule_failures());
        }
        stats_div = (stats_div + 1) % kStatsDivider;

        if(num == 0){
            gpio_pin_toggle_dt(&led);
        }
        num = (num + 1) % 17;

        k_sleep(K_MSEC(100));
    }

    return 0;
}
