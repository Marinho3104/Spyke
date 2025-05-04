
#ifndef INCLUDE_COMMUNICATION_PACKET_PACKET_H_
#define INCLUDE_COMMUNICATION_PACKET_PACKET_H_

#include "protocol_ids.h"
#include <memory>

namespace communication {

    class Packet {

        private:
        
            const uint32_t payload_length;
            const PROTOCOL_ID id;

        private:

            std::unique_ptr< uint8_t[] > payload_mut;

        public:

            Packet( const Packet& ) = delete;

        public:

            Packet();

            Packet( const PROTOCOL_ID&, std::unique_ptr< uint8_t[] >, const uint32_t& );

            bool is_valid() const;

            inline uint32_t serialized_length() const;

            std::unique_ptr< uint8_t[] > serialize() const;

        public: 

            static Packet deserialize( const std::unique_ptr< uint8_t[] >&, const uint32_t& );

    };

}

#define PACKET_ID_SIZE sizeof( communication::PROTOCOL_ID )
#define PACKET_PAYLOAD_LENGTH_SIZE sizeof( uint32_t )
#define PACKET_HEADERS_SIZE PACKET_ID_SIZE + PACKET_PAYLOAD_LENGTH_SIZE

#endif