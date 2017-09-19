#ifndef KEYBOARD_h
#define KEYBOARD_h

#include "./usb.h"
#include "usbd_hid.h"
#include "usb_key_scancodes.h"

void Log(const char* fmt, ...);

#define MODIFIER_SHIFT 0x02

#define IS_KEY_CODE 0x80

typedef struct {
    HIDDevice_t device;
    uint8_t report[9];
}keyboard_t;
        
void keyboard_pressScanCode(uint8_t keyCode);
void keyboard_releaseScanCode(uint8_t keyCode);
void keyboard_setModifiers(uint8_t modifiers);
void keyboard_sendReport() ;        
void init_keyboard();

extern keyboard_t keyboard;

#endif
