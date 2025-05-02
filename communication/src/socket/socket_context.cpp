
#include "socket_context.h"
#include "ip_v4.h"
#include "ip_v6.h"
#include <array>
#include <cstdint>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>


communication::Socket_Context::Socket_Context( void ): socket( -1 ), hint_mut{} {}

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

const int& communication::Socket_Context::get_socket( void ) const {
  return socket;
}

const bool communication::Socket_Context::is_socket_context_valid( void ) const {
  return socket != -1;
}

template<>
communication::Ip_V4 communication::Socket_Context::get_ip< communication::Ip_V4 >( void ) const {
  if( this->hint_mut.ss_family != AF_INET || ! is_socket_context_valid() ) { return Ip_V4(); }
  const sockaddr_in& hint = reinterpret_cast< const sockaddr_in& >( this->hint_mut );
  const uint16_t port = ntohs( hint.sin_port ); 
  const uint32_t address = htonl( hint.sin_addr.s_addr );
  return Ip_V4( address, port );
}

template<>
communication::Ip_V6 communication::Socket_Context::get_ip< communication::Ip_V6 >( void ) const {
  if( this->hint_mut.ss_family != AF_INET6 || is_socket_context_valid() ) { return Ip_V6(); }
  const sockaddr_in6& hint = reinterpret_cast< const sockaddr_in6& >( this->hint_mut );
  const uint16_t port = ntohs( hint.sin6_port ); 
  std::array< uint8_t, 16 > address_mut = { 0 };
  ::memcpy( address_mut.data(), &hint.sin6_addr, address_mut.size() );
  return Ip_V6( address_mut, port );
}

void communication::Socket_Context::make_context_invalid( void ) {
  if( ! is_socket_context_valid() ) { return; }
  socket = -1;
}

const bool communication::Socket_Context::close_socket( void ) {
  if( ! is_socket_context_valid() ) { return 0; }
  const bool rtr = close( socket ) == 0;
  if( rtr ) make_context_invalid();
  return rtr;
}
