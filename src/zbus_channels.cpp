#include "zbus_channels.h"

// here in the implementation we just need to do this macro call.
// name
// type
// validator
// user_data
// obervers
// init_val
// ZBUS_CHAN_DEFINE(_name, _type, _validator, _user_data, _observers, _init_val)


// an example macro call would be 


ZBUS_CHAN_DEFINE(
    my_chan,
    struct my_msg,
    NULL,
    NULL,
    ZBUS_OBS_DECLARE(),
    ZBUS_MSG_INIT((0,0))
);