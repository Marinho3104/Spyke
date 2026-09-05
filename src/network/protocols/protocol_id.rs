use std::fmt;

use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize, Copy, Clone, PartialEq)]
#[repr(u16)]
pub(crate) enum ProtocolId {
    DisconnectProtocol,
}

impl fmt::Display for ProtocolId {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            ProtocolId::DisconnectProtocol => write!(f, "Disconnect Protocol"),
        }
    }
}

mod tests {
    use crate::network::protocols::protocol_id::ProtocolId;


    #[test]
    fn test_protocol_id_display() {
        let protocol_id = ProtocolId::DisconnectProtocol;
        assert_eq!(format!("{}", protocol_id), "Disconnect Protocol");
    }

}
