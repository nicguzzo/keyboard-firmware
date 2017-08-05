#ifndef MOUSE_h
#define MOUSE_h

#include "./usb.h"
#include "usbd_hid.h"

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 4
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE)

typedef struct{
    HIDDevice_t device;
    uint8_t buttonState;
    uint8_t report[5];
}mouse_t;

void mouse_click(uint8_t button);
void mouse_move(int8_t x, int8_t y, int8_t wheel); 
void mouse_setButton(uint8_t set, uint8_t button);
void mouse_press(uint8_t button);
void mouse_release(uint8_t button);
int8_t mouse_isPressed(uint8_t button);
        
void init_mouse();

extern mouse_t mouse;

#endif
