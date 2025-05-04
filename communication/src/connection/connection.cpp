
#include "connection.h"
#include "connection_socket_helper.h"
#include "ip_v4.h"
#include "ip_v6.h"
#include "socket_context.h"
#include <algorithm>
#include <cstdlib>


template< typename IP_TYPE >
communication::Connection< IP_TYPE >::~Connection( void ) {

  if( ! is_connected() ) return;

  socket_context_mut.close_socket();

}

template< typename IP_TYPE >
communication::Connection< IP_TYPE >::Connection( void ): ip(), socket_context_mut() {}

template< typename IP_TYPE >
communication::Connection< IP_TYPE >::Connection( const IP_TYPE& ip ): ip( std::move( ip ) ), socket_context_mut() {}

template< typename IP_TYPE >
communication::Connection< IP_TYPE >::Connection( Socket_Context& socket_context_mut )
  : ip( std::move( socket_context_mut.get_ip< IP_TYPE >() ) ), socket_context_mut( std::move( socket_context_mut ) ) {

    if( ! this->ip.is_valid() ) {
      this->socket_context_mut.close_socket();
    }

}

template< typename IP_TYPE >
communication::Connection< IP_TYPE >::Connection( Connection&& other ) : ip( std::move( other.ip ) ), socket_context_mut( std::move( other.socket_context_mut ) ) {}

template< typename IP_TYPE >
const bool communication::Connection< IP_TYPE >::operator==( const Connection& other ) const { 
  return ip == other.ip && socket_context_mut == other.socket_context_mut; 
}

template< typename IP_TYPE >
const bool communication::Connection< IP_TYPE >::operator!=( const Connection& other ) const { 
  return ip != other.ip || socket_context_mut != other.socket_context_mut; 
}

template< typename IP_TYPE >
const bool communication::Connection< IP_TYPE >::is_connected( void ) const { return socket_context_mut.is_socket_context_valid(); }

template< typename IP_TYPE >
const bool communication::Connection< IP_TYPE >::connect( void ) {
  
  if( is_connected() || ! ip.is_valid() ) { 
    return 0;
  }

  Socket_Context socket_context_mut = communication::connect( ip );
  if( ! socket_context_mut.is_socket_context_valid() ) return 0;

  this->socket_context_mut.~Socket_Context();
  new( &this->socket_context_mut ) Socket_Context( std::move( socket_context_mut ) );
  return 1;

}

template< typename IP_TYPE >
bool communication::Connection< IP_TYPE >::send( const Packet& packet ) {

  if( ! is_connected() ) { 
    return 0; 
  }

  const std::unique_ptr< uint8_t[] > packet_serialized = packet.serialize();
  
  return communication::send( 
    this->socket_context_mut.get_socket(), 
    packet_serialized.get(),
    packet.serialized_length()
  );

}

template< typename IP_TYPE >
communication::Packet communication::Connection< IP_TYPE >::receive() {

  if( ! is_connected() ) {
    return Packet();
  }

  

}


template class communication::Connection< communication::Ip_V4 >;
template class communication::Connection< communication::Ip_V6 >;
