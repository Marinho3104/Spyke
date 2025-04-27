

#ifndef INCLUDE_COMMUNICATION_SERVER_SOCKET_HELPER_H_
#define INCLUDE_COMMUNICATION_SERVER_SOCKET_HELPER_H_

#include "socket_context.h"

namespace communication {

  template< typename IP_TYPE >
  Socket_Context start_server( const IP_TYPE&, const int& );

  template< typename IP_TYPE >
  Socket_Context accept_new_connection_request( const int& );

}

#endif
