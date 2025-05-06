
#include "disconnect_protocol.h"


communication::Disconnect_Protocol::Disconnect_Protocol(): Base_Protocol() {}

communication::Disconnect_Protocol::Disconnect_Protocol( std::unique_ptr< uint8_t[] > payload_mut, const uint32_t& payload_length )
    : Base_Protocol( std::move( payload_mut ), payload_length ) {}