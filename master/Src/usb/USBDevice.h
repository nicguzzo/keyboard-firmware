#ifndef _USB_H_INCLUDED
#define _USB_H_INCLUDED

#include <usbd_def.h>
class HIDDevice {
    public:
        void attachUSB(USBD_HandleTypeDef *usbDevice, uint8_t HIDReportID);
        virtual uint8_t *getReportDescriptor()=0;
        virtual uint16_t getReportDescriptorSize()=0;
        
        uint8_t HIDReportID;
        USBD_HandleTypeDef *usbDevice;
};


class USBDeviceClass {
    public:
        void reenumerate();
        
        void setHID(uint8_t descriptor[], uint16_t descriptorSize, HIDDevice *hidDevice1, HIDDevice *hidDevice2);
        
        void beginHID(HIDDevice *hidDevice1, HIDDevice *hidDevice2 = NULL);
        void beginSerialHID(HIDDevice *hidDevice1, HIDDevice *hidDevice2 = NULL);
};

extern USBDeviceClass USBDevice;

#endif
