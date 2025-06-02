
#include "packet.h"
#include "packet_headers.h"
#include <assert.h>
#include <string.h>
#include "ip_v4.h"
#include "connection.h"
#include "server.h"

void general_tests();
void send_packet_between_connections();

communication::Packet get_packet();


int main( int argc, char const *argv[] ) {
    
    general_tests();
    send_packet_between_connections();

    return 0;
}

void general_tests() {

    const communication::Packet_Headers headers = communication::Packet_Headers();
    assert( ! headers.is_valid() );

    const communication::Packet_Headers headers_1 = communication::Packet_Headers( communication::TEST, 6 );
    const communication::Packet_Headers headers_2 = communication::Packet_Headers( communication::TEST, 6 );
    assert( headers_1.is_valid() ); assert( headers_2.is_valid() );
    assert( headers_1 == headers_2 ); assert( headers_1 != headers );

    const communication::Packet packet = communication::Packet();
    assert( ! packet.is_valid() );
    
    const communication::Packet packet_1 = get_packet();
    const communication::Packet packet_2 = get_packet();
    assert( packet_1.is_valid() ); assert( packet_2.is_valid() );
    assert( packet_1 == packet_2 ); assert( packet_1 != packet );

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

    const communication::Packet_Headers headers = communication::Packet_Headers( communication::TEST, 6 );
    assert( headers.is_valid() );

    const char* payload_data = "Mario";
    std::unique_ptr< uint8_t[] > payload = std::make_unique< uint8_t[] >( headers.get_payload_length() );
    ::memcpy( payload.get(), payload_data, headers.get_payload_length() );
    
    return communication::Packet( headers, std::move( payload ) );

}
