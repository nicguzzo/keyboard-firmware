#include "Mouse.h"
#include "stm32f1xx_hal.h"
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

uint8_t *MouseClass::getReportDescriptor() {
    return HID_MOUSE_ReportDesc;
}

uint16_t MouseClass::getReportDescriptorSize() {
    return sizeof(HID_MOUSE_ReportDesc);
}
        
void MouseClass::setButton(bool set, uint8_t button) {
    if (set) {
        press(button); 
    } else {
        release(button);
    }
}

void MouseClass::click(uint8_t button) {
    press(button);
    release(button);
}

void MouseClass::press(uint8_t button) {
    setButtonState(buttonState | button);
}

void MouseClass::release(uint8_t button) {
    setButtonState(button & ~button);
}

void MouseClass::setButtonState(uint8_t newButtonState) {
    if (newButtonState != buttonState) {
        buttonState = newButtonState;
        sendReport(buttonState, 0, 0, 0);
    }
}

void MouseClass::move(int8_t x, int8_t y, int8_t wheel) {
    sendReport(buttonState, x, y, wheel);
}

void MouseClass::sendReport(uint8_t buttonState, int8_t x, int8_t y, int8_t wheel) {
    uint8_t report[5];
    report[0] = HIDReportID;
    report[1] = buttonState;
    report[2] = x;
    report[3] = y;
    report[4] = wheel;
    
    int timeout_millis = HID_FS_BINTERVAL;
    while (USBD_HID_SendReport(usbDevice, report, sizeof(report)) != USBD_OK && timeout_millis > 0) {
        HAL_Delay(1);
        timeout_millis--;
    }
}


bool MouseClass::isPressed(uint8_t button) {
    return buttonState & button;
}

MouseClass Mouse;
