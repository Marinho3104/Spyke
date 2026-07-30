use crate::network::{packet::Packet, protocols::{disconnect_protocol::DisconnectProtocol, protocol_id::ProtocolId::{self}}};
use std::convert::TryFrom;
use thiserror::Error;

#[derive(Debug, Error)]
pub(crate) enum ProtocolDispatcherError {

    // USED BY PROTOCOL DISPATCHER TRY FROM //
    #[error("Unknown protocol id: {protocol_id}")]
    UnknownProtocolId {
        protocol_id: u16,
    },

    // USED BY EACH PROTOCOL TRY FROM //
    #[error("Unexpected payload for protocol id: {protocol_id}. Error: {error_message}")]
    UnexpectedPayload {
        protocol_id: u16,
        error_message: String
    },
    #[error("Unexpected protocol id: {protocol_id}, expecting {expecting_protocol_id:?}")]
    UnexpectedProtocolId {
        protocol_id: u16,
        expecting_protocol_id: ProtocolId
    }

}

pub(crate) enum ProtocolDispatcher {
    DisconnectProtocol(DisconnectProtocol)
}

impl TryFrom<Packet> for ProtocolDispatcher {

    type Error = ProtocolDispatcherError;

    fn try_from(packet: Packet) -> Result<Self, Self::Error> {
        let protocol_id = ProtocolId::from_repr(packet.protocol_id());
    
        match protocol_id {
            Some(ProtocolId::DisconnectProtocol) => 
                DisconnectProtocol::try_from(packet).map(ProtocolDispatcher::DisconnectProtocol),
            None => Err(
                ProtocolDispatcherError::UnknownProtocolId { 
                    protocol_id: packet.protocol_id() 
                }
            )
        }
    }

}

#[cfg(debug_assertions)]
mod tests {
    use crate::network::protocols::protocol::Protocol;
    use super::*;

    #[test]
    fn test_try_from_success() {
	let protocol_id_code: u16 = DisconnectProtocol::PROTOCOL_ID_CODE;
	let payload = vec![0; 0];
	let packet = Packet::new(protocol_id_code, payload).expect("Expected Ok packet");
        let result = ProtocolDispatcher::try_from(packet).expect("Expected Ok Protocol Dispatcher");
        assert!(matches!(result, ProtocolDispatcher::DisconnectProtocol(_)));
    }

    #[test]
    fn test_try_from_error() {
	let protocol_id: u16 = 999;
	let payload = vec![0; 0];
	let packet = Packet::new(protocol_id, payload).expect("Expected Ok packet");
        let result = ProtocolDispatcher::try_from(packet);
        assert!(result.is_err());
    }

}
