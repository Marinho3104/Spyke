
#include "connection.h"
#include "connection_socket_helper.h"
#include "ip_v4.h"
#include "ip_v6.h"
#include "socket_helper.h"
#include <algorithm>
#include <cstdlib>


template< typename IP_TYPE >
communication::Connection< IP_TYPE >::~Connection() {

  if( ! is_connected() ) return;

  communication::close_socket( socket );

}

template< typename IP_TYPE >
communication::Connection< IP_TYPE >::Connection( const IP_TYPE& ip ) : ip( ip ), socket( -1 ) {}

template< typename IP_TYPE >
communication::Connection< IP_TYPE >::Connection( Connection&& other ) : ip( std::move( other.ip ) ), socket( std::move( other.socket ) ) {

    other.socket = -1;

}

template< typename IP_TYPE >
const bool communication::Connection< IP_TYPE >::operator==( const Connection& other ) const { return ip == other.ip && socket == other.socket; }

template< typename IP_TYPE >
const bool communication::Connection< IP_TYPE >::operator!=( const Connection& other ) const { return ip != other.ip || socket != other.socket; }

template< typename IP_TYPE >
const bool communication::Connection< IP_TYPE >::is_connected() const { return socket != -1; }

template< typename IP_TYPE >
const bool communication::Connection< IP_TYPE >::connect() {
  
  if( is_connected() ) return 0;

  const int socket = communication::connect( ip );
  if( socket == -1 ) return 0;

  this->socket = socket;
  return 0;

}


template class communication::Connection< communication::Ip_V4 >;
template class communication::Connection< communication::Ip_V6 >;
