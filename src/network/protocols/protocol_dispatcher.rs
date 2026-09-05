use crate::network::{packet::Packet, protocols::{disconnect_protocol::DisconnectProtocol, protocol_id::ProtocolId::{self}}};
use std::convert::TryFrom;
use thiserror::Error;

#[derive(Debug, Error)]
pub(crate) enum ProtocolDispatcherError {
    
    // USED BY EACH PROTOCOL TRY FROM //
    #[error("Unexpected payload for protocol id: {protocol_id}. Error: {error_message}")]
    UnexpectedPayload {
        protocol_id: ProtocolId,
        error_message: String
    },
    #[error("Unexpected protocol id: {protocol_id}, expecting {expecting_protocol_id:?}")]
    UnexpectedProtocolId {
        protocol_id: ProtocolId,
        expecting_protocol_id: ProtocolId
    }

}

pub(crate) enum ProtocolDispatcher {
    DisconnectProtocol(DisconnectProtocol)
}

impl TryFrom<Packet> for ProtocolDispatcher {

    type Error = ProtocolDispatcherError;

    fn try_from(packet: Packet) -> Result<Self, Self::Error> {
        match packet.headers().protocol_id() {
            ProtocolId::DisconnectProtocol => 
                DisconnectProtocol::try_from(packet).map(ProtocolDispatcher::DisconnectProtocol),
        }
    }

}

#[cfg(debug_assertions)]
mod tests {
    use crate::network::{packet::PacketHeader, protocols::protocol::Protocol};
    use super::*;

    #[test]
    fn test_try_from_success() {
        let headers = PacketHeader::new(rand::random(), ProtocolId::DisconnectProtocol, 0, 1).expect("Expected Ok packet headers");
	let payload = vec![0; 0];
	let packet = Packet::new(headers, payload).expect("Expected Ok packet");
        let result = ProtocolDispatcher::try_from(packet).expect("Expected Ok Protocol Dispatcher");
        assert!(matches!(result, ProtocolDispatcher::DisconnectProtocol(_)));
    }

}
