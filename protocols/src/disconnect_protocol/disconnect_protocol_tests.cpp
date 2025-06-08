
#include "ip_v4.h"
#include "packet.h"
#include "protocol_ids.h"
#include "server.h"
#include <cassert>
#include <cstdint>
#include <cstring>

void send_packet_between_connections();
communication::Packet get_packet();

int main (int argc, char *argv[]) {

  return 0;
}

void send_packet_between_connections() {

    const communication::Ip_V4 ip_v4( 0x7F000001, 8001 );
    communication::Server< communication::Ip_V4 > server_mut( ip_v4, 10 );
    assert( ! server_mut.is_up() ); assert( server_mut.start() ); assert( server_mut.is_up() );
  
    communication::Connection< communication::Ip_V4 > connection_mut( ip_v4 );
    assert( connection_mut.connect() ); assert( connection_mut.is_connected() );
  
    communication::Connection< communication::Ip_V4 > accepted_connection_mut = server_mut.accept_new_connection_request();
    assert( accepted_connection_mut.is_connected() );

    const communication::Packet packet = get_packet();
    assert( packet.is_valid() );

    const communication::Packet packet_invalid = communication::Packet();
    assert( packet.is_valid() ); assert( ! packet_invalid.is_valid() );

    assert( ! connection_mut.send( packet_invalid ) );
    assert( connection_mut.send( packet ) ); 

    const communication::Packet packet_received = accepted_connection_mut.receive();
    assert( packet_received.is_valid() ); assert( packet == packet_received );

    connection_mut.~Connection();

}

communication::Packet get_packet() {

    const communication::Packet_Headers headers = communication::Packet_Headers( communication::DISCONNECT, 0 );
    assert( headers.is_valid() );

    return communication::Packet( headers, std::unique_ptr< uint8_t[] >() );

}
