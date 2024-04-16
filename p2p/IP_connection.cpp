

/** INCLUDES **/
#include "IP_connection.h"
#include <cstring>
#include <iostream>
#include <cstdint>

spyke::p2p::IP_Connection::IP_Connection( spyke::p2p::IP_Connection_Type type ) : type( type ) {}

spyke::p2p::IP_Connection* spyke::p2p::IP_Connection::copy() {

  void* copy = 
    malloc( type == V4 ? sizeof( IP_V4 ) : sizeof( IP_V6 ) );

  memcpy( copy, ( void* ) this, type == V4 ? sizeof( IP_V4 ) : sizeof( IP_V6 ) );

  return ( IP_Connection* ) copy;

}


spyke::p2p::IP_V4::IP_V4( uint32_t address, uint16_t port ) : IP_Connection( V4 ), address( address ), port( port ) {}

