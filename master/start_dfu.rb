#!/usr/bin/ruby
require 'rubyserial'


$serialport = Serial.new '/dev/ttyACM0', 115200

$serialport.write("1EAF1EAF")
sleep(0.5);
$serialport.close()
