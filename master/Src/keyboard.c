#include "keyboard.h"
#include "stm32f1xx_hal.h"

void Log(const char* fmt, ...);

//instance
keyboard_t keyboard;

// Keyboard Protocol 1, HID 1.11 spec, Appendix B, page 59-60
__ALIGN_BEGIN static uint8_t HID_KEYBOARD_ReportDesc[]  __ALIGN_END = {

0x05, 0x01,  // USAGE_PAGE (Generic Desktop)
0x09, 0x06,  // USAGE (Keyboard)
0xa1, 0x01,  // COLLECTION (Application)
0x85, 0x01,  //   REPORT_ID (1)
0x05, 0x07,  //   USAGE_PAGE (Keyboard)

0x19, 0xe0,  //   USAGE_MINIMUM (Keyboard LeftControl)
0x29, 0xe7,  //   USAGE_MAXIMUM (Keyboard Right GUI)
0x15, 0x00,  //   LOGICAL_MINIMUM (0)
0x25, 0x01,  //   LOGICAL_MAXIMUM (1)
0x75, 0x01,  //   REPORT_SIZE (1)

0x95, 0x08,  //   REPORT_COUNT (8)
0x81, 0x02,  //   INPUT (Data,Var,Abs)
0x95, 0x01,  //   REPORT_COUNT (1)
0x75, 0x08,  //   REPORT_SIZE (8)
0x81, 0x03,  //   INPUT (Cnst,Var,Abs)

0x95, 0x06,  //   REPORT_COUNT (6)
0x75, 0x08,  //   REPORT_SIZE (8)
0x15, 0x00,  //   LOGICAL_MINIMUM (0)
0x25, 0xff,  //   LOGICAL_MAXIMUM (104)
0x05, 0x07,  //   USAGE_PAGE (Keyboard)

0x19, 0x00,  //   USAGE_MINIMUM (Reserved (no event indicated))
0x29, 0xff,  //   USAGE_MAXIMUM (Keyboard Application)
0x81, 0x00,  //   INPUT (Data,Ary,Abs)
0xc0,        // END_COLLECTION

};


void init_keyboard(){
    memset(keyboard.report,0,sizeof(keyboard.report));
    keyboard.device.ReportDescriptor=HID_KEYBOARD_ReportDesc;
    keyboard.device.ReportDescriptorSize=sizeof(HID_KEYBOARD_ReportDesc);
}
char dolog=0;
#define SHIFT 0x80

void keyboard_sendReport() {
    keyboard.report[0] = keyboard.device.HIDReportID;
    if(dolog){
        dolog=0;
        //Log("mod: %#x keys: [%#x %#x %#x %#x %#x %#x]\r\n",keyboard.report[1],keyboard.report[3],keyboard.report[4],keyboard.report[5],keyboard.report[6],keyboard.report[7],keyboard.report[8]);
    }
    
    
    int timeout_millis = HID_FS_BINTERVAL;
    while (USBD_HID_SendReport(keyboard.device.usbDevice, keyboard.report, sizeof(keyboard.report)) != USBD_OK && timeout_millis > 0) {
        //delay(1);
        HAL_Delay(1);
        timeout_millis--;
    }
}

void keyboard_pressScanCode(uint8_t keyCode) {
    for(int i=3; i<9; i++) {
        if (keyboard.report[i] == 0) {
            keyboard.report[i] = keyCode & 0x7F;
            dolog=1;
            break;
        }
    }    
    //keyboard_sendReport();
}

void keyboard_releaseScanCode(uint8_t keyCode) {
    for(int i=3; i<9; i++) {
        if (keyboard.report[i] == (keyCode & 0x7F)) {
            keyboard.report[i] = 0;
            break;
        }
    }
    //keyboard_sendReport();
}

void keyboard_setModifiers(uint8_t modifiers) {
    keyboard.report[1] = modifiers;
}
