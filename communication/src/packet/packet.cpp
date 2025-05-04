
#include "packet.h"
#include <cstring>

communication::Packet::Packet(): payload_length( 0 ), id( PROTOCOL_ID::INVALID ), payload_mut() {}

communication::Packet::Packet( const PROTOCOL_ID& id, std::unique_ptr< uint8_t[] > payload_mut, const uint32_t& payload_length )
    : payload_length( std::move( payload_length ) ), id( std::move( id ) ), payload_mut( std::move( payload_mut ) ) {}

bool communication::Packet::is_valid() const { return !! this->payload_mut; }

inline uint32_t communication::Packet::serialized_length() const {
    return PACKET_HEADERS_SIZE + this->payload_length;
}

std::unique_ptr< uint8_t[] > communication::Packet::serialize() const {

    std::unique_ptr< uint8_t[] > serialized_packet_data_mut = std::make_unique< uint8_t[] >( serialized_length() );
    uint8_t *serialized_packet_data_raw_pointer_mut = serialized_packet_data_mut.get();

    ::memcpy( 
        serialized_packet_data_raw_pointer_mut,
        &this->id,
        PACKET_ID_SIZE
    );

    ::memcpy( 
        serialized_packet_data_raw_pointer_mut + PACKET_ID_SIZE,
        &this->payload_length,
        PACKET_PAYLOAD_LENGTH_SIZE
    );
    
    ::memcpy( 
        serialized_packet_data_raw_pointer_mut + PACKET_HEADERS_SIZE,
        this->payload_mut.get(),
        this->payload_length
    );
    
    return std::move( serialized_packet_data_mut );

}


communication::Packet communication::Packet::deserialize( const std::unique_ptr< uint8_t[] >& serialized_packet, const uint32_t& serialized_packet_length ) {

    if( PACKET_HEADERS_SIZE >= serialized_packet_length ) {
        return Packet();
    }

    const uint8_t* serialized_packet_data_raw_pointer = serialized_packet.get();

    const PROTOCOL_ID& id = *reinterpret_cast< const communication::PROTOCOL_ID* >( serialized_packet_data_raw_pointer );
    const uint32_t& payload_length = *reinterpret_cast< const uint32_t* >( serialized_packet_data_raw_pointer );

    if( payload_length != serialized_packet_length - PACKET_HEADERS_SIZE ) {
        return Packet();
    }

    std::unique_ptr< uint8_t[] > data_mut = std::make_unique< uint8_t[] >( payload_length );
    ::memcpy( data_mut.get(), serialized_packet_data_raw_pointer + PACKET_HEADERS_SIZE, payload_length );

    return Packet( id, std::move( data_mut ), payload_length );

}