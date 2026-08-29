use serde::{ Deserialize, Serialize };
use thiserror::Error;
use tokio::{io::AsyncReadExt, net::TcpStream};

use crate::network::protocols::protocol_id::ProtocolId;


pub(crate) const MAX_PAYLOAD_SIZE: usize = 512;
pub(crate) type PacketId = u64;

#[derive(Debug, Error)]
pub(crate) enum PacketError {

    #[error("Packet sequence index must be less than sequence total: {sequence_index} >= {sequence_total}")]
    SequenceIndexShouldBeLessThanSequenceTotal {
        sequence_index: u16,
        sequence_total: u16
    },

    #[error("Payload is too big: {actual_payload_size} > {MAX_PAYLOAD_SIZE}")]
    PayloadTooBig {
        actual_payload_size: usize,
    },

    #[error("Packet serialization error: {error_message}")]
    PacketSerializationError {
        error_message: String
    },

    #[error("Stream read issue: {error_message}")]
    StreamReadIssue {
        error_message: String
    },

    #[error("Packet deserialization error: {error_message}")]
    PacketDeserializationError {
        error_message: String
    }

}

#[derive(Serialize, Deserialize, Debug, Clone, Copy, PartialEq)]
pub(crate) struct PacketHeader {
    id: PacketId,
    protocol_id: ProtocolId,
    sequence_index: u16,
    sequence_total: u16, 
}

impl PacketHeader {

    pub(crate) fn new(id: PacketId, protocol_id: ProtocolId, sequence_index: u16, sequence_total: u16) -> Result<PacketHeader, PacketError> {
        if sequence_index >= sequence_total {
            return Err(
                PacketError::SequenceIndexShouldBeLessThanSequenceTotal { sequence_index, sequence_total }
            );
        }

        Ok(
            Self {
                id,
                protocol_id,
                sequence_index, 
                sequence_total
            }
        )
    }
    
    pub(crate) fn id(&self) -> PacketId {
        self.id
    }

    pub(crate) fn protocol_id(&self) -> ProtocolId {
        self.protocol_id
    }
    
    pub(crate) fn sequence_index(&self) -> u16 {
        self.sequence_index
    }

    pub(crate) fn sequence_total(&self) -> u16 {
        self.sequence_total
    }

}

#[derive(Serialize, Deserialize, Debug, Clone)]
pub(crate) struct Packet {
    headers: PacketHeader,
    payload: Vec<u8>
}

impl Packet {

    pub(crate) fn new(headers: PacketHeader, payload: Vec<u8>) -> Result<Packet, PacketError> {

        if payload.len() > MAX_PAYLOAD_SIZE {
            return Err(
                PacketError::PayloadTooBig { actual_payload_size: payload.len() }
            )
        }

	Ok(
            Self {
	        headers,
	        payload: payload
	    }
        )
    }

    pub(crate) fn headers(&self) -> &PacketHeader {
	&self.headers
    }

    pub(crate) fn payload(&self) -> &Vec<u8> {
	&self.payload
    }

    pub(crate) fn serialized(&self) -> Result<Vec<u8>, PacketError> {
        let serialized_packet = postcard::to_allocvec(self)
            .map_err(|err| PacketError::PacketSerializationError { error_message: err.to_string() })?;

        // This is safe as long as the payload max size stays 512 MAX
        let serialized_packet_size: u16 = u16::try_from(serialized_packet.len()).unwrap();        

        let mut serialized_data = serialized_packet_size.to_le_bytes().to_vec();

        serialized_data.extend(serialized_packet);

        Ok(serialized_data)
    }

    pub(crate) async fn read_packet(stream: &mut TcpStream) -> Result<Packet, PacketError> {
        let packet_size = stream.read_u16_le()
            .await
            .map_err(|err| PacketError::StreamReadIssue { error_message: err.to_string() })?
            as usize;

        let mut packet_data = vec![0u8; packet_size];

        stream.read_exact(&mut packet_data)
            .await
            .map_err(|err| PacketError::StreamReadIssue { error_message: err.to_string() })?;

        let packet: Packet = postcard::from_bytes(&packet_data)
            .map_err(|err| PacketError::PacketDeserializationError { error_message: err.to_string() })?;

        Ok(packet)
    }

}

#[cfg(debug_assertions)]
mod tests {
    use super::*;

    #[test]
    fn test_packet_headers_creation_success() {
        let headers = PacketHeader::new(rand::random(), ProtocolId::DisconnectProtocol, 0, 1);
        assert!(headers.is_ok());
    }

    #[test]
    fn test_packet_headers_creation_error() {
        let headers = PacketHeader::new(rand::random(), ProtocolId::DisconnectProtocol, 1, 1);
        assert!(headers.is_err());
    }

    #[test]
    fn test_packet_creation_success() {
        let headers = PacketHeader::new(rand::random(), ProtocolId::DisconnectProtocol, 0, 1).expect("Expected Ok packet headers");
        let payload = vec![0];
        let headers_copy = headers.clone();
        let payload_copy = payload.clone();
	let packet = Packet::new(headers, payload).expect("Expected Ok packet");
	assert_eq!(*packet.headers(), headers_copy);
	assert_eq!(*packet.payload(), payload_copy);
    }

    #[test]
    fn test_packet_creation_payload_too_big_error() {
        let headers = PacketHeader::new(rand::random(), ProtocolId::DisconnectProtocol, 0, 1).expect("Expected Ok packet headers");
        let payload = vec![0; MAX_PAYLOAD_SIZE + 1];
	let packet = Packet::new(headers, payload);
        assert!(packet.is_err());
    }

    #[test]
    fn test_packet_serialization_success() {
        let headers = PacketHeader::new(rand::random(), ProtocolId::DisconnectProtocol, 0, 1).expect("Expected Ok packet headers");
        let payload = vec![0];
	let packet = Packet::new(headers, payload).expect("Expected Ok packet");
        let serialized_data = packet.serialized();
        assert!(serialized_data.is_ok());
    }

    fn test_packet_deserialization_success() {
        let headers = PacketHeader::new(rand::random(), ProtocolId::DisconnectProtocol, 0, 1).expect("Expected Ok packet headers");
        let headers_copy = headers.clone();
        let payload = vec![0];
	let packet = Packet::new(headers, payload).expect("Expected Ok packet");
	let packet_copy = packet.clone();
        let serialized_data = packet.serialized().expect("Expected Ok serialized data");
    }

}
