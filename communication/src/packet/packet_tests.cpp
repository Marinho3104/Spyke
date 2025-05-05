
#include "packet.h"
#include "packet_headers.h"
#include <assert.h>
#include <string.h>

void general_tests();

int main( int argc, char const *argv[] ) {
    
    general_tests();

    return 0;
}

void general_tests() {

    const communication::Packet_Headers headers = communication::Packet_Headers();
    assert( ! headers.is_valid() );

    const communication::Packet_Headers headers_1 = communication::Packet_Headers( communication::TEST, 5 );
    const communication::Packet_Headers headers_2 = communication::Packet_Headers( communication::TEST, 5 );
    assert( headers_1.is_valid() ); assert( headers_2.is_valid() );
    assert( headers_1 == headers_2 ); assert( headers_1 != headers );

    const communication::Packet packet = communication::Packet();
    assert( ! packet.is_valid() );

    const char* payload_data = "Mario";
    std::unique_ptr< uint8_t[] > payload_1 = std::make_unique< uint8_t[] >( headers_1.get_payload_length() );
    std::unique_ptr< uint8_t[] > payload_2 = std::make_unique< uint8_t[] >( headers_2.get_payload_length() );
    ::memcpy( payload_1.get(), payload_data, headers_1.get_payload_length() );
    ::memcpy( payload_2.get(), payload_data, headers_2.get_payload_length() );
    const communication::Packet packet_1 = communication::Packet( headers_1, std::move( payload_1 ) );
    const communication::Packet packet_2 = communication::Packet( headers_2, std::move( payload_2 ) );
    assert( packet_1.is_valid() ); assert( packet_2.is_valid() );
    assert( packet_1 == packet_2 ); assert( packet_1 != packet );

}
