use thiserror::Error;

#[derive(Debug, Error)]
pub(crate) enum PacketError {
    #[error("Packet payload is too large: {actual} > {max}")]
    PayloadTooLarge {
	actual: usize,
	max: usize
    }
}


#[derive(Debug)]
pub(crate) struct Packet {
    protocol_id: u16,
    payload: Vec<u8>,
}

impl Packet {

    pub(crate) const MAX_PAYLOAD_SIZE: usize = 512;

    pub(crate) fn new(protocol_id: u16, payload: Vec<u8>) -> Result<Packet, PacketError> {
	let payload_length = payload.len();
	if payload_length > Packet::MAX_PAYLOAD_SIZE {
	    return Err(PacketError::PayloadTooLarge { actual: payload_length, max: Packet::MAX_PAYLOAD_SIZE });
	}
	Ok(Self {
	    protocol_id,
	    payload
	})
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
	let protocol_id = 1;
	let payload = vec![0; 128];
	let packet_result = Packet::new(protocol_id, payload.clone());
	let packet = packet_result.unwrap();
	assert_eq!(packet.protocol_id(), protocol_id);
	assert_eq!(packet.payload(), &payload);
    }
 
    #[test]
    fn test_packet_creation_error_payload_too_large() {
	let payload_length = Packet::MAX_PAYLOAD_SIZE + 1;
	let payload = vec![0; payload_length];
	match Packet::new(1, payload.clone()) {
	    Err(PacketError::PayloadTooLarge { actual, max: _ }) => assert_eq!(actual, payload_length),
	    other => panic!("Expecting Err(PacketError::PayloadToLarge), instead got {:?}", other)
	}
    }   
}
