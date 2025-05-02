
#ifndef INCLUDE_COMMUNICATION_SERVER_SERVER_H_
#define INCLUDE_COMMUNICATION_SERVER_SERVER_H_

#include "connection.h"
#include "socket_context.h"
#include <sys/socket.h>
namespace communication {

  template< typename IP_TYPE >
  class Server {

    private:

      const IP_TYPE ip;
      const int listen_size;

    private:

      Socket_Context socket_context_mut;

    public:

      Server( const Server& ) = delete;

      Server( const Server&& ) = delete;

      Server( void ) = delete;

    public:

      ~Server( void );

      Server( const IP_TYPE&, const int& );

      Server( Server&& );

      const bool operator==( const Server& ) const;

      const bool operator!=( const Server& ) const;

      const bool is_up( void ) const;

      const bool start( void );

      Connection< IP_TYPE > accept_new_connection_request( void ) const;

  };

}

#endif
