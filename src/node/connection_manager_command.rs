use std::net::SocketAddr;

pub(crate) enum ConnectionManagerCommand {
    AddConnection {
        addr: SocketAddr
    },
    Add
}
