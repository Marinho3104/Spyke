
#include "server.h"
#include "ip_v4.h"
#include "ip_v6.h"
#include "server_socket_helper.h"
#include "socket_helper.h"


template< typename IP_TYPE >
communication::Server< IP_TYPE >::~Server() {
  
  if( ! is_up() ) return;

  communication::close_socket( socket );

}

template< typename IP_TYPE >
communication::Server< IP_TYPE >::Server( const IP_TYPE& ip, const int listen_size ) : ip( std::move( ip ) ), listen_size( std::move( listen_size ) ), socket( -1 ) {}

template< typename IP_TYPE >
communication::Server< IP_TYPE >::Server::Server( Server&& other ) : ip( std::move( other.ip ) ), listen_size( std::move( other.listen_size ) ), socket( std::move( other.socket ) ) {

  other.socket = -1;

}

template< typename IP_TYPE >
const bool communication::Server< IP_TYPE >::Server::operator==( const Server& other ) const { return ip == other.ip && socket == other.socket; }

template< typename IP_TYPE >
const bool communication::Server< IP_TYPE >::Server::operator!=( const Server& other ) const { return ip != other.ip || socket != other.socket; }

template< typename IP_TYPE >
const bool communication::Server< IP_TYPE >::Server::is_up() const { return socket != -1; }

template< typename IP_TYPE >
const bool communication::Server< IP_TYPE >::Server::start() {

  if( is_up() ) return 0;

  int listen_size = ( int ) this->listen_size;
  int socket = communication::start_server< IP_TYPE >( ip, listen_size );
  if( socket == -1 ) return -1;

  this->socket = socket;

  return 1;

}


template class communication::Server< communication::Ip_V4 >;
template class communication::Server< communication::Ip_V6 >;
