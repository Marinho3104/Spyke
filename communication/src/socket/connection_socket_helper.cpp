
#include "connection_socket_helper.h"
#include "ip_v4.h"
#include "ip_v6.h"
#include "socket_context.h"
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

template<>
communication::Socket_Context communication::connect< communication::Ip_V4 >( const communication::Ip_V4& ip ) {

  sockaddr_storage hint_mut = { 0 };
  sockaddr_in& hint_ip_v4_mut = reinterpret_cast< sockaddr_in& >( hint_mut );
  
  hint_ip_v4_mut.sin_family = AF_INET;
  hint_ip_v4_mut.sin_port = htons( ip.port );
  hint_ip_v4_mut.sin_addr.s_addr = htonl( ip.address );

  const int socket = ::socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
  if( socket == -1 ) { /* perror( "socket" ); */ return Socket_Context(); }

  const int sts_connect = ::connect( socket, reinterpret_cast< const sockaddr* >( &hint_mut ), sizeof( hint_ip_v4_mut ) );
  if( sts_connect == -1 ) { /* perror( "connect" ); */ close( socket ); return Socket_Context(); }

  return Socket_Context( socket, hint_mut );

}

template<>
communication::Socket_Context communication::connect< communication::Ip_V6 >( const communication::Ip_V6& ip ) {

  sockaddr_storage hint_mut = { 0 };
  sockaddr_in6& hint_ip_v6_mut = reinterpret_cast< sockaddr_in6& >( hint_mut );

  hint_ip_v6_mut.sin6_family = AF_INET6;
  hint_ip_v6_mut.sin6_port = htons( ip.port );

  std::memcpy( hint_ip_v6_mut.sin6_addr.s6_addr, ip.address.data(), ip.address.size() );

  const int socket = ::socket( AF_INET6, SOCK_STREAM, IPPROTO_TCP );
  if( socket == -1 ) { /* perror( "socket" ); */ return Socket_Context(); }

  const int sts_connect = ::connect( socket, reinterpret_cast< const sockaddr* >( &hint_mut ), sizeof( hint_ip_v6_mut ) );
  if( sts_connect == -1 ) { /* perror( "connect" ); */ close( socket ); return Socket_Context(); }

  return Socket_Context( socket, hint_mut );

}
