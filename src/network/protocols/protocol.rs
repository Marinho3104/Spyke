use crate::network::{packet::Packet, protocols::{protocol_dispatcher::ProtocolDispatcher, protocol_id::ProtocolId}};

pub(crate) trait Protocol: TryFrom<Vec<Packet>> {
    const PROTOCOL_ID: ProtocolId;

    fn max_total_sequence() -> u16;
}
