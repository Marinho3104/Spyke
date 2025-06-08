
#include "disconnect_protocol.h"
#include "base_protocol.h"
#include "protocol_ids.h"


communication::Disconnect_Protocol::Disconnect_Protocol(): Base_Protocol() {}

bool communication::Disconnect_Protocol::is_valid() const { return 1; }

communication::Packet communication::Disconnect_Protocol::to_packet() const {

  const communication::Packet_Headers headers = communication::Packet_Headers( communication::PROTOCOL_ID::DISCONNECT, 0 );
  return communication::Packet( headers, std::unique_ptr< uint8_t[] >() );

}
