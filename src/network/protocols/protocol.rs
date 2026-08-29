use crate::network::protocols::protocol_id::ProtocolId;

pub(crate) trait Protocol {
    const PROTOCOL_ID: ProtocolId;
}
