use std::{collections::HashMap, net::SocketAddr};
use thiserror::Error;
use tokio::{net::{TcpListener, TcpStream}, sync::mpsc};

use crate::node::{connection::Connection, connection_manager_command::ConnectionManagerCommand, connection_manager_handle::ConnectionManagerHandle};


pub(crate) type ConnectionId = u64;

#[derive(PartialEq)]
enum ConnectionType {
    TEMPORARY,
    STABLE
}

#[derive(Debug, Error)]
pub(crate) enum ConnectionManagerError {
    #[error("Not able to connect with address: {err}")]
    NotAbleToConnectWithAddress {
        err: String
    },

    #[error("Not able to bind given address: {err}")]
    NotAbletoBindGivenAddress {
        err: String
    },

    #[error("Error fatal on accept() call in server: {err}")]
    ServerFatalAccept {
        err: String
    },

    #[error("There is no more space left to add a new connection (Max space: {max_space})")]
    NoSpaceLeftToAddNewConnection {
        max_space: u8
    }
}

pub(crate) struct ConnectionManager {
    max_stable_connections: u8,
    max_temporary_connections: u8,

    server_stream: Option<TcpListener>,

    stable_connections: HashMap<ConnectionId, ConnectionMetadata>,
    temporary_connections: HashMap<ConnectionId, ConnectionMetadata>,

    tx: mpsc::Sender<ConnectionManagerCommand>,
    rx: mpsc::Receiver<ConnectionManagerCommand>,

    next_connection_id: ConnectionId,
}

impl ConnectionManager {

    fn new(
        max_stable_connections: u8, 
        max_temporary_connections: u8, 
        server_stream: Option<TcpListener>,
        tx: mpsc::Sender<ConnectionManagerCommand>, 
        rx: mpsc::Receiver<ConnectionManagerCommand>
    ) -> ConnectionManager {
        ConnectionManager { 
            max_stable_connections, 
            max_temporary_connections,
            server_stream,
            tx,
            rx,
            stable_connections: HashMap::new(),
            temporary_connections: HashMap::new(),
            next_connection_id: 0
        }
    }

    pub(crate) async fn spawn(
        max_stable_connections: u8, 
        max_temporary_connections: u8, 
        server_addr: Option<SocketAddr>
    ) -> Result<ConnectionManagerHandle, ConnectionManagerError> {
    
        let server_stream = match server_addr {
            Some(addr) => Some(
                TcpListener::bind(addr)
                .await
                .map_err(|err| ConnectionManagerError::NotAbletoBindGivenAddress { err: err.to_string() })?
            ),
            None => None
        };

        let (tx, rx) = mpsc::channel::<ConnectionManagerCommand>(32);

        let connection_manager = ConnectionManager::new(max_stable_connections, max_temporary_connections, server_stream, tx.clone(), rx);

        tokio::spawn(connection_manager.run());

        Ok(ConnectionManagerHandle::new(tx))
    
    }

    async fn run(mut self) {

        if self.server_stream.is_some() {
            tokio::select! {
                _ = self.accept_connections() => {}
            }
        }
        else {}
    }

    pub(crate) async fn add_new_connection(&mut self, addr: SocketAddr) -> Result<ConnectionId, ConnectionManagerError> {

        if self.temporary_connections.len() == self.max_temporary_connections as usize {
            return Err(
                ConnectionManagerError::NoSpaceLeftToAddNewConnection { max_space: self.max_temporary_connections }
            );
        }

        let connection_id: u64 = self.next_available_connection_id();

        let stream = TcpStream::connect(addr)
            .await
            .map_err(|err| ConnectionManagerError::NotAbleToConnectWithAddress { err: err.to_string() })?;

        let _connection: Connection = Connection::new(connection_id, stream, addr, self.tx.clone());

        let connection_metadata = ConnectionMetadata::new();

        self.add_connection_metadata(connection_id, connection_metadata, ConnectionType::TEMPORARY);

        Ok(connection_id)
    }

    fn next_available_connection_id(&mut self) -> u64 {
        loop {
            let connection_id = self.next_connection_id;

            self.next_connection_id = self.next_connection_id
                .checked_add(1)
                .unwrap_or(0);

            let exist_in_temporary_connections = self.temporary_connections.contains_key(&connection_id); 
            let exist_in_stable_connections = self.stable_connections.contains_key(&connection_id); 

            if !exist_in_stable_connections && !exist_in_temporary_connections {
                return connection_id;
            }
        }
    }

    async fn accept_connections(&mut self) -> Result<(), ConnectionManagerError> {

        // This is safe because the only function using this validates if server_stream is Some first
        let server_stream = self.server_stream.as_ref().unwrap();

        let (new_connection_stream, new_connection_addr) = match server_stream.accept().await {
            Ok(new_connection) => new_connection,
            Err(e) => match e.kind() {
                std::io::ErrorKind::Interrupted |
                    std::io::ErrorKind::ConnectionAborted => return Ok(()),
                _ => return Err(ConnectionManagerError::ServerFatalAccept { err: e.to_string() })

            }
        };

        let connection_id: u64 = self.next_available_connection_id();

        let _connection = Connection::new(connection_id, new_connection_stream, new_connection_addr, self.tx.clone());

        let connection_metadata = ConnectionMetadata::new();

        self.add_connection_metadata(connection_id, connection_metadata, ConnectionType::TEMPORARY);

        Ok(())
    }

    fn add_connection_metadata(
        &mut self, 
        connection_id: ConnectionId, 
        connection_metadata: ConnectionMetadata, 
        connection_type: ConnectionType
    ) {

        let (target, target_max_size) = match connection_type {
            ConnectionType::TEMPORARY => (&mut self.temporary_connections, self.max_temporary_connections),
            ConnectionType::STABLE => (&mut self.stable_connections, self.max_stable_connections),
        };
        
        if target.len() == target_max_size as usize {
            panic!("The target max size was exceeded, this should never happen at this point! CHECK LOGIC")
        } else if target.contains_key(&connection_id) {
            panic!("The connection id already exists in target, this should never happen at this point! CHECK LOGIC")
        }

        target.insert(connection_id, connection_metadata);
    }

}

struct ConnectionMetadata {}

impl ConnectionMetadata {

    fn new() -> ConnectionMetadata {
        Self {}
    }
}
