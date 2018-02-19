#!/bin/sh
make || exit
./start_dfu.rb
sleep 4
sudo dfu-util -a 0 -s 0x08004000:leave -D build/master.bin
