
#include "connection_socket_helper.h"
#include "ip_v4.h"
#include "ip_v6.h"
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

template<>
const int communication::connect< communication::Ip_V4 >( const communication::Ip_V4& ip ) {
  
  const struct sockaddr_in hint = {

    .sin_family = AF_INET,
    .sin_port = htons( ip.port ),
    .sin_addr = { .s_addr = htonl( ip.address ) }
    
  };

  int socket = ::socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
  if( socket == -1 ) { /* perror( "socket" ); */ return -1; }

  const int sts_connect = ::connect( socket, ( struct sockaddr* ) &hint, sizeof( hint ) );
  if( sts_connect == -1 ) { /* perror( "connect" ); */ return -1; }

  return socket;

}

template<>
const int communication::connect< communication::Ip_V6 >( const communication::Ip_V6& ip ) {

  struct sockaddr_in6 hint = {

    .sin6_family = AF_INET6,
    .sin6_port = htons( ip.port ),

  };

  std::memcpy( hint.sin6_addr.s6_addr, ip.address.data(), 16 );

  int socket = ::socket( AF_INET6, SOCK_STREAM, IPPROTO_TCP );
  if( socket == -1 ) { /* perror( "socket" ); */ return -1; }

  const int sts_connect = ::connect( socket, ( struct sockaddr* ) &hint, sizeof( hint ) );
  if( sts_connect == -1 ) { /* perror( "connect" ); */ return -1; }

  return socket;

}
