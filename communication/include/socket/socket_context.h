
#ifndef INCLUDE_COMMUNICATION_SOCKET_SOCKET_CONTEXT_H_
#define INCLUDE_COMMUNICATION_SOCKET_SOCKET_CONTEXT_H_

#include <sys/socket.h>
namespace communication {

  class Socket_Context {

    private:
      
      const sockaddr_storage hint_mut;

    private:

      int socket;

    public:

      Socket_Context( const Socket_Context& ) = delete;

    public:

      Socket_Context();

      Socket_Context( const int&, const sockaddr_storage& );

      Socket_Context( Socket_Context&& );

      const bool operator==( const Socket_Context& ) const;
      
      const bool operator!=( const Socket_Context& ) const;

      const int& get_socket() const;

      const bool is_socket_context_valid() const;

      template< typename IP_TYPE >
      IP_TYPE get_ip() const;

      void make_context_invalid();

      const bool close_socket();

  };

}

#endif
