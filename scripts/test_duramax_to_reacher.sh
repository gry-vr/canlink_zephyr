#!/usr/bin/bash


echo "hi we will now be sending some duramax messages!"

#ic1
# - engine intake manifold pressure == 34 kPa -> 3281 mBar
cansend vcan0 18FEF600#FF11FFFFFFFFFFFF

#eec1
# - engine_speed == 2560 rpm -> 20480 rpm
cansend vcan0 0CF00400#FFFFFF0050FFFFFF

#eec2
# - remote accel pedal pos = 64% -> 0.0 %
cansend vcan0 0CF00300#FFFFFFA0FFFFFFFF


#eec9
# - commanded fuel rail pressure = 64.3125 Mpa -> 16577 Bar
cansend vcan0 10FCFD00#FFFFFFFF5040FFFF

#efl_p1
# - engine oil pressure == 20 kPa
cansend vcan0 18FEEF00#FFFFFF05FFFFFFFF

#et1
# - engine coolant temp == 121
# - engine oil temp ==  279.09375
cansend vcan0 18FEEE00#A1FF0345FFFFFFFF

#tci5
# - engine turbocharger_1_turbine_ou == -131.96875 degc
cansend vcan0 18FE9700#A111FFFFFFFFFFFF

#vep1
# - keyswitch battery potential == 3092.8V
cansend vcan0 18FEF700#FFFFFFFFFFFFA0F1
