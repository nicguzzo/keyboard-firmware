#include "./usb.h"
#include "usb_device.h"
#include "usbd_hid.h"
#include "usbd_composite.h"
#include <usbd_cdc_if.h>
#include "usb_descriptors.h"

void attachUSB(HIDDevice_t *dev,USBD_HandleTypeDef *usbDevice, uint8_t HIDReportID) {
    dev->usbDevice = usbDevice;
    dev->HIDReportID = HIDReportID;
}


void setHID(uint8_t descriptor[], uint16_t descriptorSize, HIDDevice_t *hidDevice1, HIDDevice_t *hidDevice2) {
    uint16_t reportDescriptorSize = 0;
    
    attachUSB(hidDevice1,&hUsbDeviceFS, 1);
    HID_Handle.reportDescriptors[0] = hidDevice1->ReportDescriptor;
    HID_Handle.reportDescriptorSizes[0] = hidDevice1->ReportDescriptorSize;
    reportDescriptorSize += HID_Handle.reportDescriptorSizes[0];
    
    if (hidDevice2 != NULL) {
        attachUSB(hidDevice2,&hUsbDeviceFS, 2);
        
        HID_Handle.reportDescriptors[1] = hidDevice2->ReportDescriptor;
        HID_Handle.reportDescriptorSizes[1] = hidDevice2->ReportDescriptorSize;
        
        reportDescriptorSize += HID_Handle.reportDescriptorSizes[1];
    }
    
    for(int offset = 0; offset < descriptorSize; offset += descriptor[offset]) {
        if (descriptor[offset + 1] == HID_DESCRIPTOR_TYPE) {
            descriptor[offset + 7] = reportDescriptorSize;
            break;
        }
    }
}

void beginHID(HIDDevice_t *hidDevice1, HIDDevice_t *hidDevice2) {
    
    
    USBD_Init(&hUsbDeviceFS, &FS_Desc_Without_Driver, DEVICE_FS);
    USBD_RegisterClass(&hUsbDeviceFS, &USBD_HID);
    USBD_Start(&hUsbDeviceFS);
    
    setHID(USBD_HID_CfgDesc, USB_HID_CONFIG_DESC_SIZ, hidDevice1, hidDevice2);
};

void beginSerialHID(HIDDevice_t *hidDevice1, HIDDevice_t *hidDevice2) {
    USBD_Composite_Set_Descriptor(COMPOSITE_CDC_HID_DESCRIPTOR, COMPOSITE_CDC_HID_DESCRIPTOR_SIZE);
    
    USBD_Composite_Set_Classes(&USBD_CDC, &USBD_HID);
    
    USBD_MAX_NUM_INTERFACES = 2  + 1 ;//2 CDC interface 1 HID interface
    
    interface_to_class[2] = 1; //HID interface to HID class
    in_endpoint_to_class[HID_EPIN_ADDR & 0x7F] = 1; // HID endpoint to HID class
    
    //reenumerate();
    USBD_Init(&hUsbDeviceFS, &FS_Desc_CDC_Interface_0, DEVICE_FS);
    USBD_RegisterClass(&hUsbDeviceFS, &USBD_Composite);
    USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS);
    USBD_Start(&hUsbDeviceFS);
    
    setHID(COMPOSITE_CDC_HID_DESCRIPTOR, COMPOSITE_CDC_HID_DESCRIPTOR_SIZE, hidDevice1, hidDevice2);
};