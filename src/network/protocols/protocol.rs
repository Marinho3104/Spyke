use crate::network::protocols::protocol_id::ProtocolId;

pub(crate) trait Protocol {
    const PROTOCOL_ID: ProtocolId;
    const PROTOCOL_ID_CODE: u16 = Self::PROTOCOL_ID as u16;
}
