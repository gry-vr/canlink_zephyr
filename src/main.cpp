



#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/can.h>

#include <expected>
#include <array>
#include <cstring>
#include "duramax_ids.hpp"
#include "duramax_metadata.hpp"
#include "duramax_types.hpp"
#include "duramax_store.hpp"
#include "duramax_choices.hpp"
#include "duramax_codec.hpp"

#include "duramax_ao.hpp"

const device *dm_bus = DEVICE_DT_GET(DT_ALIAS(can0));
const device *ffw_bus = DEVICE_DT_GET(DT_ALIAS(can1));

#define STATUS_LED_NODE DT_ALIAS(status_led)

static const struct gpio_dt_spec status_led = GPIO_DT_SPEC_GET(STATUS_LED_NODE, gpios);

std::expected<int, int> foo(bool ok){
  if(ok){
    return 42;
  }
  return std::unexpected(7);
}

int main() {
    
    auto ao_result = DuramaxRxAo::create(dm_bus);
    if (!ao_result) {
        printk("DuramaxRxAo init failed: %d\n", static_cast<int>(ao_result.error()));
        return -1;
    }

    auto duramax_rx = std::move(*ao_result);

    printk("Duramax RX AO started.\n");

    while (true) {
        k_sleep(K_SECONDS(1));

        // optional health reporting
        printk("decode_fail=%u\n",
               duramax_rx->decode_failures());
    }

    return 0;
}