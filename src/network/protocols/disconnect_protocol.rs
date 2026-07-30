use crate::network::{packet::Packet, protocols::{protocol::Protocol, protocol_dispatcher::ProtocolDispatcherError, protocol_id::ProtocolId::{self}}};

pub(crate) struct DisconnectProtocol;

impl Protocol for DisconnectProtocol {
    const PROTOCOL_ID: ProtocolId = ProtocolId::DisconnectProtocol;
}

impl TryFrom<Packet> for DisconnectProtocol {

    type Error = ProtocolDispatcherError;

    fn try_from(packet: Packet) -> Result<Self, Self::Error> {

        if packet.protocol_id() != DisconnectProtocol::PROTOCOL_ID_CODE {
            return Err(
                ProtocolDispatcherError::UnexpectedProtocolId { 
                    protocol_id: packet.protocol_id(), 
                    expecting_protocol_id: DisconnectProtocol::PROTOCOL_ID
                }
            )
        }

        if packet.payload().len() != 0 {
            return Err(
                ProtocolDispatcherError::UnexpectedPayload {
                    protocol_id: ProtocolId::DisconnectProtocol as u16,
                    error_message: "Disconnect protocol payload should be empty!".into()
                }
            )
        }

        Ok( DisconnectProtocol {} )
    }
    
}

#[cfg(debug_assertions)]
mod tests {
    use super::*;

    #[test]
    fn test_try_from_success() {
	let protocol_id: u16 = DisconnectProtocol::PROTOCOL_ID_CODE;
	let payload = vec![0; 0];
	let packet = Packet::new(protocol_id, payload).expect("Expected Ok packet");
        let result = DisconnectProtocol::try_from(packet);
        assert!(result.is_ok());
    }

    #[test]
    fn test_try_from_unexpected_payload_error() {
	let protocol_id: u16 = DisconnectProtocol::PROTOCOL_ID_CODE;
	let payload = vec![0; 1];
	let packet = Packet::new(protocol_id, payload).expect("Expected Ok packet");
        let result = DisconnectProtocol::try_from(packet);
        assert!(result.is_err());
    }

    #[test]
    fn test_try_from_unexpected_protocol_id_error() {
	let protocol_id: u16 = 999;
	let payload = vec![0; 0];
	let packet = Packet::new(protocol_id, payload).expect("Expected Ok packet");
        let result = DisconnectProtocol::try_from(packet);
        assert!(result.is_err());
    }

}
