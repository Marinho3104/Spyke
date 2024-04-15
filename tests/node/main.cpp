
#include "./../../node/node.h"
#include "./../../node/node_configuration.h"
#include "./../../p2p/connection.h"
#include <iostream>

spyke::p2p::Connection* get_connect_to() {

  // Ip connection information
  spyke::p2p::IP_V4 ip_v4 = {

    .address = 0x7f000001,
    .port = 3002

  };

  spyke::p2p::IP_V4* ip_v4_ptr = ( spyke::p2p::IP_V4* ) malloc( sizeof( spyke::p2p::IP_V4 ) );
  *ip_v4_ptr = ip_v4;

  // Server connection
  spyke::p2p::Connection connection = {

    .ip_connection_type = spyke::p2p::IP_Connection_Type::V4,
    .ip_connection = ip_v4_ptr

  };
  spyke::p2p::Connection* connect_to = ( spyke::p2p::Connection* ) malloc( sizeof( spyke::p2p::Connection ) * 1 );

  connect_to[ 0 ] = connection;

  return connect_to;

}


int main (int argc, char *argv[]) {

  // Ip connection information
  spyke::p2p::IP_V4 ip_v4_server = {

    .address = 0x7f000001,
    .port = 3002

  };

  spyke::p2p::IP_V4* ip_v4_ptr = ( spyke::p2p::IP_V4* ) malloc( sizeof( spyke::p2p::IP_V4 ) );
  *ip_v4_ptr = ip_v4_server;

  // Server connection
  spyke::p2p::Connection server_connection = {

    .ip_connection_type = spyke::p2p::IP_Connection_Type::V4,
    .ip_connection = ip_v4_ptr

  };

  spyke::node::Node_Configuration config = {

    .server_connection = server_connection,
    .to_connect = get_connect_to(),
    .to_connect_count = 1,
    .max_ordinary_connections = 5,
    .max_stable_connections = 5,

  };

  spyke::node::Node node = spyke::node::Node( config );

  std::cout << node.setup() << std::endl;

  node.start();

  node.finalize();

  return 0;
}
