



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


int main(void)
{
  if(!gpio_is_ready_dt(&status_led))
  {
    return -1;
  }

  gpio_pin_configure_dt(&status_led, GPIO_OUTPUT_INACTIVE);
  gpio_pin_set_dt(&status_led, 1);

  if (!device_is_ready(dm_bus)){
    printk("canbus was not ready :(\n");
  }
  int error = can_start(dm_bus);

  duramax::Eec9ElectronicEngineControl9 msg{};

  msg.engine_exhaust_gas_recirculation = 10;
  msg.commanded_fuel_rail_pressure = 10;
  msg.commanded_engine_fuel_injection = 10;

  std::array<std::uint8_t,8> payload{};
  auto encoded = duramax::Codec::encode(msg, payload.data(), payload.size());
  if(!encoded){
    printk("something stupid happened!\n");

  }


  struct can_frame frame{};
  frame.id = duramax::message_meta(duramax::MessageId::eec9_electronic_engine_control_9).frame_id;
  frame.dlc = payload.size();
  frame.flags = CAN_FRAME_IDE;   // only if this message uses a 29-bit ID
  std::memcpy(frame.data, payload.data(), payload.size());

  can_send(
    dm_bus,
    &frame,
    K_MSEC(1000),
    NULL,
    NULL
  );



  while(1) {


    printk("Hello from c++ \n");
    k_sleep(K_SECONDS(1));
    gpio_pin_toggle_dt(&status_led);

    can_send(
      dm_bus,
      &frame,
      K_MSEC(1000),
      NULL,
      NULL
    );
  }

}
