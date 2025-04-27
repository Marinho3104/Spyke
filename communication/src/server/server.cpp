
#include "server.h"
#include "ip_v4.h"
#include "ip_v6.h"
#include "server_socket_helper.h"
#include "socket_context.h"
#include <algorithm>


template< typename IP_TYPE >
communication::Server< IP_TYPE >::~Server() {
  
  if( ! is_up() ) return;

  socket_context_mut.close_socket();

}

template< typename IP_TYPE >
communication::Server< IP_TYPE >::Server( const IP_TYPE& ip, const int& listen_size ) : ip( std::move( ip ) ), listen_size( std::move( listen_size ) ), socket_context_mut() {}

template< typename IP_TYPE >
communication::Server< IP_TYPE >::Server::Server( Server&& other ) 
  : ip( std::move( other.ip ) ), listen_size( std::move( other.listen_size ) ), socket_context_mut( std::move( other.socket_context_mut ) ) {}

template< typename IP_TYPE >
const bool communication::Server< IP_TYPE >::Server::operator==( const Server& other ) const { return ip == other.ip && socket_context_mut == other.socket_context_mut; }

template< typename IP_TYPE >
const bool communication::Server< IP_TYPE >::Server::operator!=( const Server& other ) const { return ip != other.ip || socket_context_mut != other.socket_context_mut; }

template< typename IP_TYPE >
const bool communication::Server< IP_TYPE >::Server::is_up() const { return socket_context_mut.is_socket_context_valid(); }

template< typename IP_TYPE >
const bool communication::Server< IP_TYPE >::Server::start() {

  if( is_up() ) return 0;

  Socket_Context socket_context_mut = communication::start_server< IP_TYPE >( ip, listen_size );
  if( ! socket_context_mut.is_socket_context_valid() ) return 0;

  this->socket_context_mut.~Socket_Context();
  new ( &this->socket_context_mut ) Socket_Context( std::move( socket_context_mut ) );
  return 1;

}


template class communication::Server< communication::Ip_V4 >;
template class communication::Server< communication::Ip_V6 >;
