#include <zephyr/zbus/zbus.h>


// random MACRO name that I found right here.
// ZBUS_CHANNEL_NAME_INIT


// CORRECT WAY OF HANDLING THIS
// zbus channel needs to be declared here!
// as well as the struct type that the zbus messaging will use


// ZBUS_CHAN_DECLARE(my_chan)

struct my_msg {
    uint32_t a;
    uint32_t b;
};


ZBUS_CHAN_DECLARE(my_chan);



namespace Event{


    enum 


};