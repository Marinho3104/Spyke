use std::net::SocketAddr;

use tokio::{net::TcpStream, sync::mpsc};

use crate::node::{connection_manager::ConnectionId, connection_manager_command::ConnectionManagerCommand};


pub(crate) struct Connection {
    connection_id: ConnectionId,
    stream: TcpStream,
    addr: SocketAddr,
    connection_manager_channel: mpsc::Sender<ConnectionManagerCommand>,
}

impl Connection {

    pub(crate) fn new(
        connection_id: ConnectionId, 
        stream: TcpStream, 
        addr: SocketAddr,
        connection_manager_channel: mpsc::Sender<ConnectionManagerCommand>
    ) -> Connection {
        Self {
            connection_id,
            stream,
            addr,
            connection_manager_channel
        }
    }

}
