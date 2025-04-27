
#include "server_socket_helper.h"
#include "ip_v4.h"
#include "ip_v6.h"
#include "socket_context.h"
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <type_traits>
#include <unistd.h>


template<>
communication::Socket_Context communication::start_server< communication::Ip_V4 >( const communication::Ip_V4& ip, const int& listen_size ) {

  const int socket = ::socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
  if( socket == -1 ) { /* perror( "socket" ); */ return Socket_Context(); }

  sockaddr_storage hint_mut = { 0 };
  sockaddr_in& hint_ip_v4_mut = reinterpret_cast< sockaddr_in& >( hint_mut );

  hint_ip_v4_mut.sin_family = AF_INET;
  hint_ip_v4_mut.sin_port = htons( ip.port );
  hint_ip_v4_mut.sin_addr.s_addr = htonl( ip.address );

  const int sts_bind = bind( socket, reinterpret_cast< const sockaddr* >( &hint_mut ), sizeof( hint_ip_v4_mut ) );
  if( sts_bind == -1 ) { /* perror( "bind" ); */ close( socket ); return Socket_Context(); }

  const int sts_listen = listen( socket, listen_size );
  if( sts_listen == -1 ) { /* perror( "listen" ); */ close( socket ); return Socket_Context(); }

  return Socket_Context( socket, hint_mut );
  
}

template<>
communication::Socket_Context communication::start_server< communication::Ip_V6 >( const communication::Ip_V6& ip, const int& listen_size ) {

  const int socket = ::socket( AF_INET6, SOCK_STREAM, IPPROTO_TCP );
  if( socket == -1 ) { /* perror( "socket" ); */ return Socket_Context(); }

  sockaddr_storage hint_mut = { 0 };
  sockaddr_in6& hint_ip_v6_mut = reinterpret_cast< sockaddr_in6& >( hint_mut );

  hint_ip_v6_mut.sin6_family = AF_INET6;
  hint_ip_v6_mut.sin6_port = htons( ip.port );
  std::memcpy( hint_ip_v6_mut.sin6_addr.s6_addr, ip.address.data(), 16 );

  const int sts_bind = ::bind( socket, reinterpret_cast< const sockaddr* >( &hint_mut ), sizeof( hint_ip_v6_mut ) );
  if( sts_bind == -1 ) { /* perror( "bind" ); */ close( socket ); return Socket_Context(); }

  const int sts_listen = ::listen( socket, listen_size );
  if( sts_listen == -1 ) { /* perror( "listen" ); */ close( socket ); return Socket_Context(); }

  return Socket_Context( socket, hint_mut );

}

template< typename IP_TYPE >
communication::Socket_Context communication::accept_new_connection_request( const int& server_socket ) {

  sockaddr_storage hint_mut = { 0 };
  socklen_t hint_size_mut = { 0 };

  if constexpr( std::is_same< IP_TYPE, Ip_V4 >::value ) {
    hint_size_mut = sizeof( sockaddr_in );
  }
  else if constexpr( std::is_same< IP_TYPE, Ip_V6 >::value ) {
    hint_size_mut = sizeof( sockaddr_in6 );
  }

  const int socket = ::accept( server_socket, reinterpret_cast< sockaddr* >( &hint_mut ), reinterpret_cast< socklen_t* >( &hint_size_mut ) );
  if( socket == -1 ) { return Socket_Context(); }

  return Socket_Context( socket, hint_mut );

}

template<> communication::Socket_Context communication::accept_new_connection_request< communication::Ip_V4 >( const int& );
template<> communication::Socket_Context communication::accept_new_connection_request< communication::Ip_V6 >( const int& );

