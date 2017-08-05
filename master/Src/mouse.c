#include "mouse.h"
#include "stm32f1xx_hal.h"

//instance
mouse_t mouse;

__ALIGN_BEGIN static uint8_t HID_MOUSE_ReportDesc[]  __ALIGN_END =
{
  0x05,   0x01,
  0x09,   0x02,
  0xA1,   0x01,
  0x85,   0x01,
  0x09,   0x01,
  
  0xA1,   0x00,
  0x05,   0x09,
  0x19,   0x01,
  0x29,   0x03,
  
  0x15,   0x00,
  0x25,   0x01,
  0x95,   0x03,
  0x75,   0x01,
  
  0x81,   0x02,
  0x95,   0x01,
  0x75,   0x05,
  0x81,   0x01,
  
  0x05,   0x01,
  0x09,   0x30,
  0x09,   0x31,
  0x09,   0x38,
  
  0x15,   0x81,
  0x25,   0x7F,
  0x75,   0x08,
  0x95,   0x03,
  
  0x81,   0x06,
  0xC0,   0x09,
  0x3c,   0x05,
  0xff,   0x09,
  
  0x01,   0x15,
  0x00,   0x25,
  0x01,   0x75,
  0x01,   0x95,
  
  0x02,   0xb1,
  0x22,   0x75,
  0x06,   0x95,
  0x01,   0xb1,
  
  0x01,   0xc0
}; 

void init_mouse(){
  mouse.buttonState=0;
  memset(mouse.report,0,sizeof(mouse.report));
  mouse.device.ReportDescriptor=HID_MOUSE_ReportDesc;
  mouse.device.ReportDescriptorSize=sizeof(HID_MOUSE_ReportDesc);
}

void mouse_sendReport(uint8_t buttonState, int8_t x, int8_t y, int8_t wheel) {

  mouse.report[0] = mouse.device.HIDReportID;
  mouse.report[1] = buttonState;
  mouse.report[2] = x;
  mouse.report[3] = y;
  mouse.report[4] = wheel;

  int timeout_millis = HID_FS_BINTERVAL;
  while (USBD_HID_SendReport(mouse.device.usbDevice, mouse.report, sizeof(mouse.report)) != USBD_OK && timeout_millis > 0) {
    HAL_Delay(1);
    timeout_millis--;
  }
}

void mouse_setButtonState(uint8_t newButtonState) {
  if (newButtonState != mouse.buttonState) {
    mouse.buttonState = newButtonState;
    mouse_sendReport(mouse.buttonState, 0, 0, 0);
  }
}

void mouse_setButton(uint8_t set, uint8_t button) {
  if (set) {
    mouse_press(button); 
  } else {
    mouse_release(button);
  }
}

void mouse_click(uint8_t button) {
  mouse_press(button);
  mouse_release(button);
}

void mouse_press(uint8_t button) {
  mouse_setButtonState(mouse.buttonState | button);
}

void mouse_release(uint8_t button) {
  mouse_setButtonState(button & ~button);
}

void mouse_move(int8_t x, int8_t y, int8_t wheel) {
  mouse_sendReport(mouse.buttonState, x, y, wheel);
}

int8_t mouse_isPressed(uint8_t button) {
  return mouse.buttonState & button;
}


