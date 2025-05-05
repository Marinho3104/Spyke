
#include "connection.h"
#include "connection_socket_helper.h"
#include "ip_v4.h"
#include "ip_v6.h"
#include "socket_context.h"
#include "packet_headers.h"
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
bool communication::Connection< IP_TYPE >::send( const Packet& packet ) const {

  if( ! is_connected() ) { 
    return 0; 
  }

  std::unique_ptr< uint8_t[] > packet_serialized = packet.serialize();
  const uint8_t* packet_serialized_raw_pointer = packet_serialized.get();
  
  return communication::send(
    this->socket_context_mut.get_socket(), 
    packet_serialized_raw_pointer,
    packet.serialized_length()
  );

}

template< typename IP_TYPE >
communication::Packet communication::Connection< IP_TYPE >::receive() const {

  if( ! is_connected() ) {
    return Packet();
  }

  std::array< uint8_t, PACKET_HEADERS_FULL_SIZE > headers_mut;
  if(
    communication::receive_until( 
      socket_context_mut.get_socket(), 
      headers_mut.data(), 
      headers_mut.size() 
    )
  ) { return Packet(); }

  const Packet_Headers packet_headers = Packet_Headers( headers_mut );

  std::unique_ptr< uint8_t[] > packet_payload_mut = 
    std::make_unique< uint8_t[] >( packet_headers.get_payload_length() );
  if(
    communication::receive_until( 
      socket_context_mut.get_socket(), 
      packet_payload_mut.get(), 
      packet_headers.get_payload_length()
    )
  ) { return Packet(); }

  return Packet(
    packet_headers,
    std::move( packet_payload_mut )
  );

}


template class communication::Connection< communication::Ip_V4 >;
template class communication::Connection< communication::Ip_V6 >;
