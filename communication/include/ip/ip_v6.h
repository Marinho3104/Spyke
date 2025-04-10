
#ifndef INCLUDE_COMMUNICATION_IP_IP_V6_H_
#define INCLUDE_COMMUNICATION_IP_IP_V6_H_

#include <array>
#include <cstdint>
namespace communication {

  class Ip_V6 {

    public:

      const std::array< uint32_t, 4 > address;
      const uint16_t port;

    public:

      Ip_V6();

      Ip_V6( const std::array< uint32_t, 4 >&, const uint16_t& );

      const bool operator==( const Ip_V6& ) const;

      const bool operator!=( const Ip_V6& ) const;

      const bool is_valid() const;

  };

}

#endif
