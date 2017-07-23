#include "Keyboard.h"
#include "Mouse.h"

extern "C" void init_keyboard(){
  USBDevice.beginSerialHID(&Mouse, &Keyboard);
}

extern "C" void test_kb(){
  Keyboard.press('Q');
}