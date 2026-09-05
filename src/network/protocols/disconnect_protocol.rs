use crate::network::{packet::Packet, protocols::{protocol::Protocol, protocol_dispatcher::ProtocolDispatcherError, protocol_id::{self, ProtocolId::{self}}}};

#[derive(Debug)]
pub(crate) struct DisconnectProtocol;

impl Protocol for DisconnectProtocol {
    const PROTOCOL_ID: ProtocolId = ProtocolId::DisconnectProtocol;
}

impl TryFrom<Packet> for DisconnectProtocol {

    type Error = ProtocolDispatcherError;

    fn try_from(packet: Packet) -> Result<Self, Self::Error> {
        let packet_protocol_id = packet.headers().protocol_id();

        if packet_protocol_id != DisconnectProtocol::PROTOCOL_ID {
            return Err(
                ProtocolDispatcherError::UnexpectedProtocolId { 
                    protocol_id: packet_protocol_id, 
                    expecting_protocol_id: DisconnectProtocol::PROTOCOL_ID
                }
            )
        }

        if packet.payload().len() != 0 {
            return Err(
                ProtocolDispatcherError::UnexpectedPayload {
                    protocol_id: DisconnectProtocol::PROTOCOL_ID,
                    error_message: "Disconnect protocol payload should be empty!".into()
                }
            )
        }

        Ok( DisconnectProtocol {} )
    }
    
}

#[cfg(debug_assertions)]
mod tests {
    use crate::network::packet::PacketHeader;
    use super::*;

    #[test]
    fn test_try_from_success() {
        let headers = PacketHeader::new(rand::random(), ProtocolId::DisconnectProtocol, 0, 1).expect("Expected Ok packet headers");
	let payload = vec![0; 0];
	let packet = Packet::new(headers, payload).expect("Expected Ok packet");
        let result = DisconnectProtocol::try_from(packet);
        assert!(result.is_ok());
    }

	//    #[test]
	//    fn test_try_from_wrong_protocol_id_error() {
	//        let headers = PacketHeader::new(rand::random(), ProtocolId::PlaceHolder, 0, 1).expect("Expected Ok packet headers");
	// let payload = vec![0; 0];
	// let packet = Packet::new(headers, payload).expect("Expected Ok packet");
	//        let result = DisconnectProtocol::try_from(packet);
	//        assert!(result.is_err());
	//        assert!(matches!(result.unwrap_err(), ProtocolDispatcherError::UnexpectedProtocolId { .. }))
	//    }

    #[test]
    fn test_try_from_unexpected_payload_error() {
        let headers = PacketHeader::new(rand::random(), ProtocolId::DisconnectProtocol, 0, 1).expect("Expected Ok packet headers");
	let payload = vec![0; 1];
	let packet = Packet::new(headers, payload).expect("Expected Ok packet");
        let result = DisconnectProtocol::try_from(packet);
        assert!(result.is_err());
    }

}
