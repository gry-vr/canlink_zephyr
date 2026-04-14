



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

// duramax::ValueStore tx_store_{};
// duramax::MessageId desired_tx_msg = duramax::MessageId::eec5_electronic_engine_control_5;



// auto encoded_payload(duramx::MessageId, duramax::ValueStore) 
// -> struct can_frame{
//   auto find_message_
// } 


int main() {
   
    


    auto ao_result = DuramaxCanAo::create(dm_bus);
    if (!ao_result) {
        printk("DuramaxRxAo init failed: %d\n", static_cast<int>(ao_result.error()));
        return -1;
    }

    auto duramax_rx = std::move(*ao_result);
    duramax::ValueStore tx_store{};

    duramax::Cac1ChargeAirCooler1 cac1{34,90,12}; 

    update_from(tx_store, cac1, 1238U);


    auto msg = duramax::build_cac1_charge_air_cooler_1_from_store(tx_store);
    if(!msg){
      printk("you dumb fuck");
      return 1;
    }

    TxCommand tx_this = {*msg , TxPolicy::periodic_enable, 1000};

    printk("Duramax RX AO started.\n");

    duramax_rx->post_tx(tx_this, K_FOREVER);

    int x = 0;
    while (true) {
      printk("hello \n");
        k_sleep(K_SECONDS(1));
        x++;
        if(x > 15){
          TxCommand tx_that {*msg, TxPolicy::periodic_disable};
          duramax_rx->post_tx(tx_that, K_FOREVER);
        }

        // optional health reporting
        // printk("decode_fail=%u\n",
        //        duramax_rx->decode_failures());
    }

    return 0;
}