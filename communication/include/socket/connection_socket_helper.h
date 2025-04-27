
#ifndef INCLUDE_COMMUNICATION_CONNECTION_SOCKET_HELPER_H_
#define INCLUDE_COMMUNICATION_CONNECTION_SOCKET_HELPER_H_

#include "socket_context.h"

namespace communication {

  template< typename IP_TYPE >
  Socket_Context connect( const IP_TYPE& );

}

#endif
