
#include "ip_v6.h"

communication::Ip_V6::Ip_V6() : address{}, port( 0 ) {}

communication::Ip_V6::Ip_V6( const std::array< uint32_t, 4 >& id, const uint16_t& port ) : address( std::move( id ) ), port( port ) {}

const bool communication::Ip_V6::operator==( const Ip_V6& other ) const { return address == other.address && port == other.port; }

const bool communication::Ip_V6::operator!=( const Ip_V6& other ) const { return address != other.address || port != other.port; }

const bool communication::Ip_V6::is_valid() const { return port != 0; }
