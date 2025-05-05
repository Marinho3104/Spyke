
#ifndef INCLUDE_COMMUNICATION_PACKET_PACKET_H_
#define INCLUDE_COMMUNICATION_PACKET_PACKET_H_

#include "packet_headers.h"
#include "protocol_ids.h"
#include <memory>

#define PACKET_ID_SIZE sizeof( communication::PROTOCOL_ID )
#define PACKET_PAYLOAD_LENGTH_SIZE sizeof( uint32_t )
#define PACKET_HEADERS_SIZE PACKET_ID_SIZE + PACKET_PAYLOAD_LENGTH_SIZE

namespace communication {

    class Packet {

        private:
        
            const Packet_Headers headers;

        private:

            std::unique_ptr< uint8_t[] > payload_mut;

        public:

            Packet( const Packet& ) = delete;

        public:

            Packet();

            Packet( const Packet_Headers&, std::unique_ptr< uint8_t[] > );

            bool operator==( const Packet& ) const;

            bool operator!=( const Packet& ) const;

            bool is_valid() const;

            uint32_t serialized_length() const;

            std::unique_ptr< uint8_t[] > serialize() const;

    };

}

#endif