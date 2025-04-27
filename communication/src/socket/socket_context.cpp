
#include "socket_context.h"
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>


communication::Socket_Context::Socket_Context(): socket( -1 ), hint_mut{} {}

communication::Socket_Context::Socket_Context( const int& socket, const sockaddr_storage& hint ): socket( socket ), hint_mut( hint ) {}

communication::Socket_Context::Socket_Context( Socket_Context&& other ): socket( other.socket ), hint_mut( other.hint_mut ) {
  other.make_context_invalid();
}

const bool communication::Socket_Context::operator==( const Socket_Context& other ) const {
  return socket == other.socket && ( ::memcmp( &hint_mut, &other.hint_mut, sizeof( sockaddr_storage ) ) == 0 );
}

const bool communication::Socket_Context::operator!=( const Socket_Context& other ) const {
  return socket == other.socket && ( ::memcmp( &hint_mut, &other.hint_mut, sizeof( sockaddr_storage ) ) == 0 );
}

const bool communication::Socket_Context::is_socket_context_valid() const {
  return socket != -1;
}

void communication::Socket_Context::make_context_invalid() {
  socket = -1;
}

const bool communication::Socket_Context::close_socket() {
  const bool rtr = close( socket ) == 0;
  if( rtr ) make_context_invalid();
  return rtr;
}
