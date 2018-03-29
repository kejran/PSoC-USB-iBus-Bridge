#include "project.h"
#include "usb.h"

struct {
    int8 channels[USB_CHANNELS];
    uint8 buttons;
} usb_data;

void usb_setup() {
    
    for (int i = 0; i < USB_CHANNELS; ++i)
        usb_data.channels[i] = 0;
    usb_data.buttons = 0;

    USBFS_Start(0, USBFS_DWR_VDDD_OPERATION);
    while (!USBFS_bGetConfiguration());
    USBFS_LoadInEP(1, (uint8*)&usb_data, USB_CHANNELS + 1);
}

void usb_write() {
    
    while(!USBFS_bGetEPAckState(1));
    USBFS_LoadInEP(1, (uint8*)&usb_data, USB_CHANNELS + 1);
}

void usb_set_axis(uint8 axis, int8 value) {
    
    usb_data.channels[axis] = value;
}

void usb_set_button(uint8 button, bool value) {
    
    if (value)
        usb_data.buttons |= 1 << button;
    else 
        usb_data.buttons &= ~(1 << button);
}