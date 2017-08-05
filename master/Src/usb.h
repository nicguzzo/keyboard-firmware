#ifndef _USB_H_INCLUDED
#define _USB_H_INCLUDED
#include <usbd_def.h>

typedef struct {
    uint8_t  HIDReportID;
    USBD_HandleTypeDef *usbDevice;
    uint8_t *ReportDescriptor;
    uint16_t ReportDescriptorSize;
}HIDDevice_t;

void attachUSB(HIDDevice_t *dev,USBD_HandleTypeDef *usbDevice, uint8_t HIDReportID);

void setHID(uint8_t descriptor[], uint16_t descriptorSize, HIDDevice_t *hidDevice1, HIDDevice_t *hidDevice2);
      
void beginHID(HIDDevice_t *hidDevice1, HIDDevice_t *hidDevice2);
void beginSerialHID(HIDDevice_t *hidDevice1, HIDDevice_t *hidDevice2 );

#endif