
#include "ip_v4.h"


communication::Ip_V4::Ip_V4() : address( 0 ), port( 0 ) {}

communication::Ip_V4::Ip_V4( const uint32_t& ip, const uint16_t& port ) : address( ip ), port( port ) {}

const bool communication::Ip_V4::operator==( const Ip_V4& other ) const { return address == other.address && port == other.port; }

const bool communication::Ip_V4::operator!=( const Ip_V4& other ) const { return address != other.address || port != other.port; }

const bool communication::Ip_V4::is_valid() const { return port != 0; }

