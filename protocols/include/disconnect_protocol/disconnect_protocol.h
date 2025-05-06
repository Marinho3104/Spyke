

#ifndef INCLUDE_COMMUNICATION_PROTOCOLS_DISCONNECT_PROTOCOL_DISCONNECT_PROTOCOL_H_
#define INCLUDE_COMMUNICATION_PROTOCOLS_DISCONNECT_PROTOCOL_DISCONNECT_PROTOCOL_H_

#include "base_protocol.h"

namespace communication {

    class Disconnect_Protocol: Base_Protocol {

        public:

            Disconnect_Protocol();

            Disconnect_Protocol( std::unique_ptr< uint8_t[] >, const uint32_t& );

            template< typename NODE_TYPE >
            void handle() const;

    };

}

#endif