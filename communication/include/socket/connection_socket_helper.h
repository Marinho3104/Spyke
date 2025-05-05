
#ifndef INCLUDE_COMMUNICATION_CONNECTION_SOCKET_HELPER_H_
#define INCLUDE_COMMUNICATION_CONNECTION_SOCKET_HELPER_H_

#include "socket_context.h"
#include <memory>

namespace communication {

  template< typename IP_TYPE >
  Socket_Context connect( const IP_TYPE& );

  bool send( const int&, const uint8_t*&, const uint32_t& );

  ssize_t receive( const int&, uint8_t*, const uint32_t& );

  bool receive_until( const int&, uint8_t*, const uint32_t& );

}

#endif