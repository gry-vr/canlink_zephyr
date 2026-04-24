#!/usr/bin/bash


echo "hi we will now be sending some duramax messages!"

#ic1
# - engine intake manifold pressure == 34 kPa -> 340 mBar (3281 mBar big endian issue)
cansend vcan0 18FEF600#FF11FFFFFFFFFFFF

#eec1
# - engine_speed == 2560 rpm -> 2560 (20480 rpm if this comes out then it's doing the wrong shifting thing for extract_be and insert_be it's reversing bits in a byte)
cansend vcan0 0CF00400#FFFFFF0050FFFFFF

#eec2
# - remote accel pedal pos = 64% -> 64% (0.0 % weird dbc encoding issue with range and such)
cansend vcan0 0CF00300#FFFFFFA0FFFFFFFF


#eec9
# - commanded fuel rail pressure = 64.3125 Mpa -> 643 Bar (16577 Bar big endian mistakes)
cansend vcan0 10FCFD00#FFFFFFFF5040FFFF

#efl_p1
# - engine oil pressure == 20 kPa -> 2.90075
cansend vcan0 18FEEF00#FFFFFF05FFFFFFFF

#et1
# - engine coolant temp == 121 -> 249.8
# - engine oil temp ==  279.09375 -> 534.2
cansend vcan0 18FEEE00#A1FF0345FFFFFFFF

#tci5
# - engine turbocharger_1_turbine_ou == -131.96875 degc -> -203.8
cansend vcan0 18FE9700#A111FFFFFFFFFFFF

#vep1
# - keyswitch battery potential == 3092.8V -> 3092.8V
cansend vcan0 18FEF700#FFFFFFFFFFFFA0F1
