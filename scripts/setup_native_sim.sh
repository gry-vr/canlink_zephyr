#!/usr/bin/bash


echo "Hi we're gonna set up our vcans"

[ "$EUID" -eq 0 ] || exec sudo "$0" "$@"

ip link add dev vcan0 type vcan

if [ "$?" -ne 0 ]; then
  echo "couldn't setup a vcan"
fi 


ip link add dev vcan1 type vcan


ip link set vcan0 up 
ip link set vcan1 up


