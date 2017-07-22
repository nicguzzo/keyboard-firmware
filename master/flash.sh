#make
killall com

#stm32flash -i -dtr,-dtr,-dtr,-dtr,dtr,dtr,dtr,dtr,dtr,dtr,-dtr,-dtr,-dtr,-dtr,-dtr: -w  build/usb_kb.bin -g 0x0 /dev/ttyUSB0

stm32flash -w  build/master.bin -g 0x0 /dev/ttyUSB0
