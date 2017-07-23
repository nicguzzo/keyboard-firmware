#ifndef MOUSE_h
#define MOUSE_h

#include "USBDevice.h"
#include "usbd_hid.h"

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 4
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE)

class MouseClass: public HIDDevice {
    public:
        void click(uint8_t button = MOUSE_LEFT);
        void move(int8_t x, int8_t y, int8_t wheel = 0); 
        void setButton(bool set, uint8_t button = MOUSE_LEFT);
        void press(uint8_t button = MOUSE_LEFT);
        void release(uint8_t button = MOUSE_LEFT);
        bool isPressed(uint8_t button = MOUSE_LEFT);
        
        virtual uint8_t *getReportDescriptor();
        virtual uint16_t getReportDescriptorSize();
        
    private:
        void sendReport(uint8_t buttonState, int8_t x, int8_t y, int8_t wheel);
        void setButtonState(uint8_t newButtonState);
        
        uint8_t buttonState = 0;
};

extern MouseClass Mouse;

#endif
