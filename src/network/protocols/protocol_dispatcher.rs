use crate::network::{packet::Packet, protocols::{disconnect_protocol::DisconnectProtocol, protocol::Protocol, protocol_id::ProtocolId::{self}}};
use std::convert::TryFrom;
use thiserror::Error;

#[derive(Debug, Error)]
pub(crate) enum ProtocolDispatcherError {

    #[error("Received empty vec of packets")]
    EmptyPacketsVec {},

    #[error("Unexpected size of vec packets")]
    UnexpectedSizeOfVecPackets {},
    
    #[error("Unexpected payload for protocol id: {protocol_id}. Error: {error_message}")]
    UnexpectedPayload {
        protocol_id: ProtocolId,
        error_message: String
    },

    #[error("Unexpected protocol id: {protocol_id}, expecting {expecting_protocol_id}")]
    UnexpectedProtocolId {
        protocol_id: ProtocolId,
        expecting_protocol_id: ProtocolId
    },

    #[error("Issue when generating the packets from protocol: {error_message}")]
    IssueWhenGeneratingPacketsFromProtocol {
        error_message: String
    }

}

pub(crate) enum ProtocolDispatcher {
    DisconnectProtocol(DisconnectProtocol)
}

impl ProtocolDispatcher {

    pub(crate) fn max_sequence_total(protocol_id: ProtocolId) -> u16 {
        match protocol_id {
            ProtocolId::DisconnectProtocol => DisconnectProtocol::max_total_sequence()
        }
    }

}

impl TryFrom<Vec<Packet>> for ProtocolDispatcher {

    type Error = ProtocolDispatcherError;

    fn try_from(packets: Vec<Packet>) -> Result<Self, Self::Error> {
        let protocol_id = packets.first()
            .ok_or(ProtocolDispatcherError::EmptyPacketsVec {  })?
            .headers().protocol_id();

        match protocol_id {
            ProtocolId::DisconnectProtocol => 
                DisconnectProtocol::try_from(packets).map(ProtocolDispatcher::DisconnectProtocol),
        }
    }

}

impl TryFrom<ProtocolDispatcher> for Vec<Packet> {

    type Error = ProtocolDispatcherError;

    fn try_from(protocol_dispatcher: ProtocolDispatcher) -> Result<Self, Self::Error> {
        match protocol_dispatcher {
            ProtocolDispatcher::DisconnectProtocol(protocol) => Ok(protocol.into()),
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
	let packets = vec![Packet::new(headers, payload).expect("Expected Ok packet")];
        let result = ProtocolDispatcher::try_from(packets).expect("Expected Ok Protocol Dispatcher");
        assert!(matches!(result, ProtocolDispatcher::DisconnectProtocol(_)));
    }

    #[test]
    fn test_try_into_success() {
        let disconnect_protocol = DisconnectProtocol {};
        let protocol = ProtocolDispatcher::DisconnectProtocol(disconnect_protocol);
        let result: Result<Vec<Packet>, ProtocolDispatcherError> = protocol.try_into();
        assert!(result.is_ok());
    }


    #[test]
    fn test_try_from_empty_vec_error() {
	let packets = vec![];
        let result = ProtocolDispatcher::try_from(packets);
        assert!(matches!(result, Err(ProtocolDispatcherError::EmptyPacketsVec { .. })));
    }

    #[test]
    fn test_max_sequence_total_success() {
        let cases = [
            (ProtocolId::DisconnectProtocol, 1),
        ];

        for (protocol_id, expected) in cases {
            assert_eq!(ProtocolDispatcher::max_sequence_total(protocol_id), expected);
        }
    }

}
