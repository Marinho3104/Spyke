
#include "packet.h"
#include <cstring>

communication::Packet::Packet(): headers(), payload_mut() {}

communication::Packet::Packet( const Packet_Headers& headers, std::unique_ptr< uint8_t[] > payload_mut )
    : headers( std::move( headers ) ), payload_mut( std::move( payload_mut ) ) {}

bool communication::Packet::operator==( const Packet& other ) const {
    return headers == other.headers && 
        ( ::memcmp( payload_mut.get(), other.payload_mut.get(), headers.get_payload_length() ) == 0 );
}

bool communication::Packet::operator!=( const Packet& other ) const {
    return headers != other.headers ||
        ( ::memcmp( payload_mut.get(), other.payload_mut.get(), headers.get_payload_length() ) != 0 );
}

bool communication::Packet::is_valid() const { return !! this->payload_mut; }

uint32_t communication::Packet::serialized_length() const {
    return PACKET_HEADERS_SIZE + this->headers.get_payload_length();
}

std::unique_ptr< uint8_t[] > communication::Packet::serialize() const {

    const std::array< uint8_t, PACKET_HEADERS_FULL_SIZE > serialized_packet_headers = this->headers.serialize();

    std::unique_ptr< uint8_t[] > serialized_packet_mut = std::make_unique< uint8_t[] >( serialized_length() );
    uint8_t *serialized_packet_raw_pointer_mut = serialized_packet_mut.get();

    ::memcpy(
        serialized_packet_raw_pointer_mut,
        serialized_packet_headers.data(),
        PACKET_HEADERS_FULL_SIZE
    );
    
    ::memcpy( 
        serialized_packet_raw_pointer_mut + PACKET_HEADERS_SIZE,
        this->payload_mut.get(),
        this->headers.get_payload_length()
    );
    
    return std::move( serialized_packet_mut );

}