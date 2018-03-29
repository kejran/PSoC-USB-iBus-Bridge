#pragma once
    
#include <stdbool.h>
#include "cytypes.h"   
    
#define IBUS_PACKET_LENGTH 32
#define IBUS_CHANNELS 14
#define IBUS_HEADER 0x4020 // note that low byte arrives first

/// pass one received ibus byte from uart
void ibus_handle_rx(uint8 data);

/// if packet was detected to be received incorrectly, drop it
void ibus_invalidate_packet();

/// obtain channel data from last packet; data range from -500 to 500
int16* ibus_channel_data();
        