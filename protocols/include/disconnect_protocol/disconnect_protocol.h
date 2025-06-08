

#ifndef INCLUDE_COMMUNICATION_PROTOCOLS_DISCONNECT_PROTOCOL_DISCONNECT_PROTOCOL_H_
#define INCLUDE_COMMUNICATION_PROTOCOLS_DISCONNECT_PROTOCOL_DISCONNECT_PROTOCOL_H_

#include "base_protocol.h"

namespace communication {

    class Disconnect_Protocol: Base_Protocol {

        public:

            Disconnect_Protocol();

            bool is_valid() const override;

            communication::Packet to_packet() const override;

    };

}

#endif
