use serde::{ Deserialize, Serialize };

pub(crate) const MAX_PAYLOAD_SIZE: usize = 512;

use thiserror::Error;

#[derive(Debug, Error)]
pub(crate) enum PacketError {

    #[error("Payload is too big: {actual_payload_size} > {MAX_PAYLOAD_SIZE}")]
    PayloadTooBig {
        actual_payload_size: usize,
    },

}

#[derive(Serialize, Deserialize, Debug)]
pub(crate) struct Packet {
    protocol_id: u16,
    payload: Vec<u8>
}

impl Packet {

    pub(crate) fn new(protocol_id: u16, payload: Vec<u8>) -> Result<Packet, PacketError> {

        if payload.len() > MAX_PAYLOAD_SIZE {
            return Err(
                PacketError::PayloadTooBig { actual_payload_size: payload.len() }
            )
        }

	Ok(
            Self {
	        protocol_id,
	        payload: payload
	    }
        )
    }

    pub(crate) fn protocol_id(&self) -> u16 {
	self.protocol_id
    }

    pub(crate) fn payload(&self) -> &Vec<u8> {
	&self.payload
    }

}

#[cfg(debug_assertions)]
mod tests {
    use super::*;

    #[test]
    fn test_packet_creation_success() {
	let protocol_id: u16 = 1;
        let payload = vec![0];
        let payload_copy = payload.clone();
	let packet = Packet::new(protocol_id, payload).expect("Expected Ok packet");
	assert_eq!(packet.protocol_id(), protocol_id);
	assert_eq!(*packet.payload(), payload_copy);
    }

    #[test]
    fn test_packet_creation_payload_too_big_error() {
	let protocol_id: u16 = 1;
        let payload = vec![0; MAX_PAYLOAD_SIZE + 1];
	let packet = Packet::new(protocol_id, payload);
        assert!(packet.is_err());
    }
}
