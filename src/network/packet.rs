use std::time::Duration;

use serde::{ Deserialize, Serialize };
use thiserror::Error;
use tokio::{io::AsyncReadExt, net::TcpStream, time::timeout};

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

    #[error("Deserialization timeout on read size")]
    DeserializationTimeoutOnReadSize {},

    #[error("Deserialization timeout on read data")]
    DeserializationTimeoutOnReadData {},

    #[error("Packet deserialization error: {error_message}")]
    PacketDeserializationError {
        error_message: String
    }

}

pub(crate) struct ReadPacketTimeouts {
    read_size_timeout: u64,
    read_data_timeout: u64
}

impl ReadPacketTimeouts {
    
    fn new(read_size_timeout: u64, read_data_timeout: u64) -> Self {
        Self {
            read_size_timeout,
            read_data_timeout
        }
    }


    fn default() -> Self {
        Self {
            read_size_timeout: 60000,
            read_data_timeout: 5000
        }
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

    pub(crate) async fn read_packet(stream: &mut TcpStream, timeouts: Option<ReadPacketTimeouts>) -> Result<Packet, PacketError> {
        let timeouts = timeouts.unwrap_or(ReadPacketTimeouts::default());

        let packet_size = timeout(
                Duration::from_millis(timeouts.read_size_timeout),
                stream.read_u16_le()
            )
            .await
            .map_err(|_| PacketError::DeserializationTimeoutOnReadSize {  } )?
            .map_err(|err| PacketError::StreamReadIssue { error_message: err.to_string() })?
            as usize;

        let mut packet_data = vec![0u8; packet_size];

        timeout(
                Duration::from_millis(timeouts.read_data_timeout),
                stream.read_exact(&mut packet_data)
        )
            .await
            .map_err(|_| PacketError::DeserializationTimeoutOnReadData {  })?
            .map_err(|err| PacketError::StreamReadIssue { error_message: err.to_string() })?;

        let packet: Packet = postcard::from_bytes(&packet_data)
            .map_err(|err| PacketError::PacketDeserializationError { error_message: err.to_string() })?;

        Ok(packet)
    }

}

#[cfg(debug_assertions)]
mod tests {
    use tokio::{io::AsyncWriteExt, net::TcpListener};

use super::*;

    #[test]
    fn test_packet_headers_creation_success() {
        let packet_id = rand::random();
        let protocol_id = ProtocolId::DisconnectProtocol;
        let sequence_index = 0;
        let sequence_total = 1;
        let headers_result = PacketHeader::new(packet_id, protocol_id, sequence_index, sequence_total);
        assert!(headers_result.is_ok());
        let headers = headers_result.unwrap();
        assert_eq!(headers.id(), packet_id);
        assert_eq!(headers.protocol_id(), protocol_id);
        assert_eq!(headers.sequence_total(), sequence_total);
        assert_eq!(headers.sequence_index(), sequence_index);
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

    #[tokio::test]
    async fn test_read_packet_success() {
        let listener = TcpListener::bind("127.0.0.1:0")
            .await
            .expect("Expected Ok: Server bind");

        let addr = listener
            .local_addr()
            .expect("Expected Ok: Get server address");

        let server = tokio::spawn(async move {
            let (stream, _) = listener
                .accept()
                .await
                .expect("Expected Ok: Server accept connection");

            stream
        });

        let mut client_stream = TcpStream::connect(addr)
            .await
            .expect("Expected Ok: Client connect to server");

        let mut server_stream = server
            .await
            .expect("Expected Ok: Server task");

        let packet_id = rand::random();
        let protocol_id = ProtocolId::DisconnectProtocol;
        let sequence_index = 1;
        let sequence_total = 10;
        let headers = PacketHeader::new(packet_id, protocol_id, sequence_index, sequence_total).expect("Expected Ok Headers");
        let payload = vec![0; 0];
	let packet = Packet::new(headers, payload).expect("Expected Ok packet");
        let serialized_data = packet.serialized().expect("Expected Ok serialized data");

        server_stream
            .write_all(&serialized_data)
            .await
            .expect("Expected Ok Write All");

        let packet_result = Packet::read_packet(&mut client_stream, None).await;

        assert!(packet_result.is_ok());

        let packet = packet_result.unwrap();
        let headers = packet.headers();

        assert_eq!(headers.id(), packet_id);
        assert_eq!(headers.protocol_id(), protocol_id);
        assert_eq!(headers.sequence_total(), sequence_total);
        assert_eq!(headers.sequence_index(), sequence_index);

        assert_eq!(packet.payload().len(), 0);
    }

    #[tokio::test]
    async fn test_read_packet_stream_read_error() {
        let listener = TcpListener::bind("127.0.0.1:0")
            .await
            .expect("Expected Ok: Server bind");

        let addr = listener
            .local_addr()
            .expect("Expected Ok: Get server address");

        tokio::spawn(async move {
            let (stream, _) = listener
                .accept()
                .await
                .expect("Expected Ok: Server accept connection");

            stream
        });

        let mut client_stream = TcpStream::connect(addr)
            .await
            .expect("Expected Ok: Client connect to server");

        let packet_result = Packet::read_packet(
                &mut client_stream, 
                None
            )
            .await;

        assert!(packet_result.is_err());
        assert!(matches!(packet_result.unwrap_err(), PacketError::StreamReadIssue { .. }))
    }

    #[tokio::test]
    async fn test_read_packet_timeout_error() {
        let listener = TcpListener::bind("127.0.0.1:0")
            .await
            .expect("Expected Ok: Server bind");

        let addr = listener
            .local_addr()
            .expect("Expected Ok: Get server address");

        let server = tokio::spawn(async move {
            let (stream, _) = listener
                .accept()
                .await
                .expect("Expected Ok: Server accept connection");

            stream
        });

        let mut client_stream = TcpStream::connect(addr)
            .await
            .expect("Expected Ok: Client connect to server");

        let mut server_stream = server
            .await
            .expect("Expected Ok: Server task");

        let packet_result = Packet::read_packet(
                &mut client_stream, 
                Some(ReadPacketTimeouts::new(500, 500))
            )
            .await;

        assert!(packet_result.is_err());
        assert!(matches!(packet_result.unwrap_err(), PacketError::DeserializationTimeoutOnReadSize {  }))
    }
}
