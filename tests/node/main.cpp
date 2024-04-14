
#include "./../../node/node.h"
#include "./../../node/node_configuration.h"
#include "./../../p2p/connection.h"

int main (int argc, char *argv[]) {

  // Ip connection information
  spyke::p2p::IP_V4 ip_v4_server = {

    .address = 0x7f000001,
    .port = 3001

  };

  // Server connection
  spyke::p2p::Connection server_connection = {

    .ip_connection_type = spyke::p2p::IP_Connection_Type::V4,
    .ip_connection = &ip_v4_server

  };

  spyke::node::Node_Configuration config = 
    spyke::node::Node_Configuration( server_connection, 5, 5 );

  spyke::node::Node node = spyke::node::Node( config );

  return 0;
}
