
#include "server_socket_helper.h"
#include "ip_v4.h"
#include "ip_v6.h"
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>


template<>
const int communication::start_server< communication::Ip_V4 >( const communication::Ip_V4& ip, int listen_size ) {

  int socket = ::socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
  if( socket == -1 ) { /* perror( "socket" ); */ return -1; }

  struct sockaddr_in hint = {

    .sin_family = AF_INET,
    .sin_port = htons( ip.port ),
    .sin_addr = { .s_addr = htonl( ip.address ) }

  };

  const int sts_bind = bind( socket, ( sockaddr* ) &hint, sizeof( hint ) );
  if( sts_bind == -1 ) { /* perror( "bind" ); */ close( socket ); return -1; }

  const int sts_listen = listen( socket, listen_size );
  if( sts_listen == -1 ) { /* perror( "listen" ); */ close( socket ); return -1; }

  return socket;
  
}

template<>
const int communication::start_server< communication::Ip_V6 >( const communication::Ip_V6& ip, int listen_size ) {

  int socket = ::socket( AF_INET6, SOCK_STREAM, IPPROTO_TCP );
  if( socket == -1 ) { /* perror( "socket" ); */ return -1; }

  struct sockaddr_in6 hint = {
    
    .sin6_family = AF_INET6,
    .sin6_port = htons( ip.port )

  };

  std::memcpy( hint.sin6_addr.s6_addr, ip.address.data(), 16 );

  const int sts_bind = ::bind( socket, ( sockaddr* ) &hint, sizeof( hint ) );
  if( sts_bind == -1 ) { /* perror( "bind" ); */ close( socket ); return -1; }

  const int sts_listen = ::listen( socket, listen_size );
  if( sts_listen == -1 ) { /* perror( "listen" ); */ close( socket ); return -1; }

  return socket;

}
