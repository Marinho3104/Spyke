
#[derive(Debug)]
pub(crate) struct Packet {

    protocol_id: u16,
    payload: Vec<u8>,
    
}

impl Packet {

    pub(crate) const MAX_PAYLOAD_SIZE: usize = 512;

    pub(crate) fn new(protocol_id: u16, payload: Vec<u8>) -> Packet {
	Self {
	    protocol_id,
	    payload
	}
    }

}
