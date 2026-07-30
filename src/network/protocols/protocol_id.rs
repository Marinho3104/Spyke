use strum::FromRepr;

#[derive(Debug, FromRepr)]
#[repr(u16)]
pub(crate) enum ProtocolId {
    DisconnectProtocol,
}
