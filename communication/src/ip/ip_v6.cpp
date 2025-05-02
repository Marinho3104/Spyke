
#include "ip_v6.h"
#include <cstdint>

communication::Ip_V6::Ip_V6( void ) : address{}, port( 0 ) {}

communication::Ip_V6::Ip_V6( const std::array< uint8_t, 16 >& id, const uint16_t& port ) : address( std::move( id ) ), port( port ) {}

const bool communication::Ip_V6::operator==( const Ip_V6& other ) const { return address == other.address && port == other.port; }

const bool communication::Ip_V6::operator!=( const Ip_V6& other ) const { return address != other.address || port != other.port; }

const bool communication::Ip_V6::is_valid( void ) const { return port != 0; }
