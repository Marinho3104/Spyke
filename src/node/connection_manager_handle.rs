use crate::node::connection_manager_command::ConnectionManagerCommand;
use tokio::sync::mpsc;

pub(crate) struct ConnectionManagerHandle {
    connection_manager_channel: mpsc::Sender<ConnectionManagerCommand>,
}

impl ConnectionManagerHandle {

    pub(crate) fn new(connection_manager_channel: mpsc::Sender<ConnectionManagerCommand>) -> ConnectionManagerHandle {
        Self {
            connection_manager_channel
        }
    }
        
}
