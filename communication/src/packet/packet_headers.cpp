
#include "packet_headers.h"
#include "string.h"

communication::Packet_Headers::Packet_Headers(): id( communication::PROTOCOL_ID::INVALID ), payload_length( 0 ) {}

communication::Packet_Headers::Packet_Headers( const PROTOCOL_ID& id, const uint32_t& payload_length )
    : id( std::move( id ) ), payload_length( std::move( payload_length ) ) {}

communication::Packet_Headers::Packet_Headers( const std::array< uint8_t, PACKET_HEADERS_FULL_SIZE > headers )
    : id( *reinterpret_cast< const communication::PROTOCOL_ID* >( headers.data() ) ), 
        payload_length( *reinterpret_cast< const uint32_t* >( headers.data() + PACKET_HEADERS_ID_SIZE ) ) {}

bool communication::Packet_Headers::operator==( const Packet_Headers& other ) const {
    return id == other.id && payload_length == other.payload_length;
}

bool communication::Packet_Headers::operator!=( const Packet_Headers& other ) const {
    return id != other.id || payload_length != other.payload_length;
}

bool communication::Packet_Headers::is_valid() const { return id != communication::PROTOCOL_ID::INVALID; }

const communication::PROTOCOL_ID& communication::Packet_Headers::get_id() const {
    return id;
}

const uint32_t& communication::Packet_Headers::get_payload_length() const {
    return payload_length;
}

std::array< uint8_t, PACKET_HEADERS_FULL_SIZE > communication::Packet_Headers::serialize() const {
    
    std::array< uint8_t, PACKET_HEADERS_FULL_SIZE > serialized_packet_headers_mut = { 0 };

    ::memcpy( 
        serialized_packet_headers_mut.data(),
        &this->id,
        PACKET_HEADERS_ID_SIZE
    );

    ::memcpy(
        serialized_packet_headers_mut.data() + PACKET_HEADERS_ID_SIZE,
        &this->payload_length,
        PACKET_HEADERS_PAYLOAD_LENGTH_SIZE
    );

    return serialized_packet_headers_mut;
    
}