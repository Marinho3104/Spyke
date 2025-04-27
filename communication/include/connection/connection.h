
#ifndef INCLUDE_COMMUNICATION_CONNECTION_CONNECTION_H_
#define INCLUDE_COMMUNICATION_CONNECTION_CONNECTION_H_

#include "socket_context.h"

namespace communication {

  template< typename IP_TYPE >
  class Connection {

    private:

      const IP_TYPE ip;
      
    private:

      Socket_Context socket_context_mut;

    public:
  
      Connection( const Connection& ) = delete;

      Connection( const Connection&& ) = delete;

      Connection() = delete;

    public:

      ~Connection();

      Connection( const IP_TYPE& );

      Connection( Connection&& );

      const bool operator==( const Connection& ) const;

      const bool operator!=( const Connection& ) const;

      const bool is_connected() const;

      const bool connect();

  };

}

#endif
