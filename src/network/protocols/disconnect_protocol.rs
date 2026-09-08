use crate::network::{packet::{Packet, PacketHeader}, protocols::{protocol::Protocol, protocol_dispatcher::ProtocolDispatcherError, protocol_id::{self, ProtocolId::{self}}}};

#[derive(Debug)]
pub(crate) struct DisconnectProtocol;

impl Protocol for DisconnectProtocol {
    const PROTOCOL_ID: ProtocolId = ProtocolId::DisconnectProtocol;

    fn max_total_sequence() -> u16 {
        1
    }
}

impl TryFrom<Vec<Packet>> for DisconnectProtocol {

    type Error = ProtocolDispatcherError;

    fn try_from(packets: Vec<Packet>) -> Result<Self, Self::Error> {

        let [packet] = packets.as_slice() else {
            return Err(
                ProtocolDispatcherError::UnexpectedSizeOfVecPackets {  }
            );
        };

        let packet_protocol_id = packet.headers().protocol_id();

        if packet_protocol_id != DisconnectProtocol::PROTOCOL_ID {
            return Err(
                ProtocolDispatcherError::UnexpectedProtocolId { 
                    protocol_id: packet_protocol_id, 
                    expecting_protocol_id: DisconnectProtocol::PROTOCOL_ID
                }
            )
        }

        if !packet.payload().is_empty() {
            return Err(
                ProtocolDispatcherError::UnexpectedPayload {
                    protocol_id: DisconnectProtocol::PROTOCOL_ID,
                    error_message: "Disconnect protocol payload should be empty!".into()
                }
            )
        }

        Ok( DisconnectProtocol {} )
    }
    
}

impl From<DisconnectProtocol> for Vec<Packet> {

    fn from(_protocol: DisconnectProtocol) -> Self {
        let headers = PacketHeader::new(rand::random(), ProtocolId::DisconnectProtocol, 0, 1)
            .expect("Packet header values are hardcoded, should never fail");
        let payload = vec![0; 0];
        let packet = Packet::new(headers, payload)
            .expect("Packet values are harcodedm should never fail");
        vec![packet]
    }
    
}

#[cfg(debug_assertions)]
mod tests {
    use crate::network::packet::PacketHeader;
    use super::*;

    #[test]
    fn test_try_from_success() {
        let headers = PacketHeader::new(rand::random(), ProtocolId::DisconnectProtocol, 0, 1).expect("Expected Ok packet headers");
        let payload = vec![0; 0];
        let packets = vec![Packet::new(headers, payload).expect("Expected Ok packet")];
	let result = DisconnectProtocol::try_from(packets);
        assert!(result.is_ok());
    }

    #[test]
    fn test_try_into_success() {
        let disconnect_protocol = DisconnectProtocol {};
	let result: Vec<Packet> = disconnect_protocol.into();
        let [packet] = result.as_slice() else {
            panic!("Result should be exactly one in lenght");
        };

        assert_eq!(packet.headers().protocol_id(), ProtocolId::DisconnectProtocol);
        assert_eq!(packet.headers().sequence_index(), 0);
        assert_eq!(packet.headers().sequence_total(), 1);
        assert!(packet.payload().is_empty());
    }


	//       #[test]
	//       fn test_try_from_wrong_protocol_id_error() {
	//           let headers = PacketHeader::new(rand::random(), ProtocolId::PlaceHolder, 0, 1).expect("Expected Ok packet headers");
	//           let payload = vec![0; 0];
	//           let packets = Packet::new(headers, payload).expect("Expected Ok packet");
	//    let result = DisconnectProtocol::try_from(packets);
	//    assert!(result.is_err());
	//    assert!(matches!(result.unwrap_err(), ProtocolDispatcherError::UnexpectedProtocolId { .. }))
	// }

    #[test]
    fn test_try_from_unexpected_vec_packets_size_error() {
        let packets = vec![];
        let result = DisconnectProtocol::try_from(packets);
        assert!(
            matches!( result, Err( ProtocolDispatcherError::UnexpectedSizeOfVecPackets { .. }) )
        )
    }

    #[test]
    fn test_try_from_unexpected_payload_error() {
        let headers = PacketHeader::new(rand::random(), ProtocolId::DisconnectProtocol, 0, 1).expect("Expected Ok packet headers");
        let payload = vec![0; 1];
        let packets = vec![Packet::new(headers, payload).expect("Expected Ok packet")];
        let result = DisconnectProtocol::try_from(packets);
        assert!(
            matches!( result, Err( ProtocolDispatcherError::UnexpectedPayload { .. }) )
        )
    }

}
