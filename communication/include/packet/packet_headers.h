
#ifndef INCLUDE_COMMUNICATION_PACKET_PACKET_HEADERS_H_
#define INCLUDE_COMMUNICATION_PACKET_PACKET_HEADERS_H_

#include "protocol_ids.h"
#include <cstdint>
#include <memory>
#include <array>

#define PACKET_HEADERS_ID_SIZE sizeof( communication::PROTOCOL_ID )
#define PACKET_HEADERS_PAYLOAD_LENGTH_SIZE sizeof( uint32_t )
#define PACKET_HEADERS_FULL_SIZE PACKET_HEADERS_ID_SIZE + PACKET_HEADERS_PAYLOAD_LENGTH_SIZE

namespace communication {

    class Packet_Headers {

        private:

            const PROTOCOL_ID id;
            const uint32_t payload_length;

        public:

            Packet_Headers();

            Packet_Headers( const PROTOCOL_ID&, const uint32_t& );

            Packet_Headers( const std::array< uint8_t, PACKET_HEADERS_FULL_SIZE > );

            bool operator==( const Packet_Headers& ) const;

            bool operator!=( const Packet_Headers& ) const;

            bool is_valid() const;

            const PROTOCOL_ID& get_id() const;

            const uint32_t& get_payload_length() const;

            std::array< uint8_t, PACKET_HEADERS_FULL_SIZE > serialize() const;

    };

}   

#endif