
#include "base_protocol.h"


communication::Base_Protocol::Base_Protocol(): payload_mut(), payload_length_mut( 0 ) {}

communication::Base_Protocol::Base_Protocol( std::unique_ptr< uint8_t[] > payload_mut, const uint32_t& payload_length_mut )
    : payload_mut( std::move( payload_mut ) ), payload_length_mut( std::move( payload_length_mut ) ) {}

bool communication::Base_Protocol::is_valid() const { return !! this->payload_mut; }