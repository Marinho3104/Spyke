
#ifndef INCLUDE_COMMUNICATION_IP_IP_V4_H_
#define INCLUDE_COMMUNICATION_IP_IP_V4_H_

#include <cstdint>

namespace communication {

  class Ip_V4 {

    public:

      const uint32_t address;
      const uint16_t port;

    public:

      Ip_V4( void );

      Ip_V4( const uint32_t&, const uint16_t& );

      const bool operator==( const Ip_V4& ) const;

      const bool operator!=( const Ip_V4& ) const;

      const bool is_valid( void ) const;

  };

}

#endif
