#include "ibus.h"

/// static structures ///

static volatile int16 channel_data[IBUS_CHANNELS];
static volatile uint8 packet_position = 0;

// abuse c11's anonymous structs for nice aliasing
union {
    uint8 bytes[IBUS_PACKET_LENGTH];
    struct {
        uint16 header;
        uint16 channel_data[IBUS_CHANNELS];
        uint16 checksum;
    };
} ibus_buffer;

/// internal helpers ///

static void parse_packet() {
    // received value is in range [1000:2000]        
    for (int i = 0; i < IBUS_CHANNELS; ++i)
        channel_data[i] = ibus_buffer.channel_data[i] - 1500; 
}

static bool verify_packet() { 
   
    if (ibus_buffer.header != IBUS_HEADER) return false;
    
    uint16 checksum = 0xffff;
    for (int i = 0; i < IBUS_PACKET_LENGTH - 2; ++i)
        checksum -= ibus_buffer.bytes[i];

    return ibus_buffer.checksum == checksum;
}

/// public methods ///

void ibus_handle_rx(uint8 data) {
    ibus_buffer.bytes[packet_position] = data;
    ++packet_position;
    if (packet_position == IBUS_PACKET_LENGTH)
        if (verify_packet())
            parse_packet();
}

void ibus_invalidate_packet() {
    packet_position = 0;
}

int16* ibus_channel_data() {
    return (int16*)channel_data;
}

