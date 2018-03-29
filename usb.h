#pragma once 
#include "cytypes.h"
#include <stdbool.h>

#define USB_CHANNELS 6
/// setup usb connectivity 
void usb_setup();

/// write stored payload
void usb_write();

/// set value of given axis
void usb_set_axis(uint8 axis, int8 value);

/// set value of given button
void usb_set_button(uint8 button, bool value);