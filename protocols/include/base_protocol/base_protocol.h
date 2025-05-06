
#ifndef INCLUDE_COMMUNICATION_PROTOCOLS_BASE_PROTOCOL_H_
#define INCLUDE_COMMUNICATION_PROTOCOLS_BASE_PROTOCOL_H_

#include "packet.h"
#include <memory>

namespace communication {

    class Base_Protocol {

        private:

            std::unique_ptr< uint8_t[] > payload_mut; 
            uint32_t payload_length_mut;

        public:

            Base_Protocol( const Base_Protocol& ) = delete;

        public:

            Base_Protocol();

            Base_Protocol( std::unique_ptr< uint8_t[] >, const uint32_t& );

            bool is_valid() const;

            virtual communication::Packet to_packet() const = 0;

    };

}

#endif