#include "project.h"
#include "ibus.h"
#include "usb.h"

CY_ISR(IBUS_TIMEOUT_ISR) {
    ibus_invalidate_packet();
}

CY_ISR(IBUS_ISR) {
    while (UART_IBUS_GetRxBufferSize()) {
        uint8 data = UART_IBUS_GetChar();        
        ibus_handle_rx(data);   
    };   
}

void setup() {

    CyGlobalIntEnable;

    // set up components
    IBUS_INT_StartEx(IBUS_ISR);
    IBUS_TIMEOUT_INT_StartEx(IBUS_TIMEOUT_ISR);
    UART_IBUS_Start();
    Timer_IBUS_Timeout_Start();
    
    // connect to usb host
    usb_setup();    
}

int main() {

    while (true) {
        
        int16* rx_data = ibus_channel_data();
        
        int mode = rx_data[8]; // use channel 9 (3-pos switch) as mode selector
        if (mode > 200) mode = 1;
        else if (mode < 200) mode = -1; 
        else mode = 0;
        
        for (int i = 0; i < USB_CHANNELS; ++i) {
            int8 value = (rx_data[i] + 2) >> 2; // -500/500 -> -125/125
            if (mode == 0) // todo: why does this not work?
                if (i == 1) value = -value; // reverses Y axis to mirror default gamepad layout
            if (mode == 1) 
                value = value / 2 + 64; // mode 2: remap [-1, 1] to [0, 1] - freerider likes them more?
            usb_set_axis(i, value); 
        }
        for (int i = 0; i < 4; ++i)
            usb_set_button(i, rx_data[i + USB_CHANNELS] > 0); 
        CyDelay(10);        
        usb_write();   
    }
}
