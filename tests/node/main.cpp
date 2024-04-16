
#include "./../../node/node.h"
#include "./../../node/node_configuration.h"
#include "./../../p2p/connection.h"
#include <unistd.h>
#include <iostream>

spyke::p2p::IP_Connection* get_connect_to() {

  // Ip connection information
  spyke::p2p::IP_V4 ip_v4 = spyke::p2p::IP_V4( 0x7f000001, 3003 );

  spyke::p2p::IP_V4* ip_v4_ptr = ( spyke::p2p::IP_V4* ) malloc( sizeof( spyke::p2p::IP_V4 ) );
  *ip_v4_ptr = ip_v4;

  return ip_v4_ptr;

}


int main (int argc, char *argv[]) {

  // Ip connection information
  spyke::p2p::IP_V4 ip_v4_server = spyke::p2p::IP_V4( 0x7f000001, 3010 );

  spyke::p2p::IP_Connection p = ip_v4_server;

  spyke::p2p::IP_V4* ip_v4_ptr = ( spyke::p2p::IP_V4* ) malloc( sizeof( spyke::p2p::IP_V4 ) );
  *ip_v4_ptr = ip_v4_server;

  spyke::node::Node_Configuration config = {

    .server_ip_connection = ip_v4_ptr,
    .ips_to_connect = get_connect_to(),
    .ips_to_connect_count = 1,
    .max_ordinary_connections = 5,
    .max_stable_connections = 5,

  };

  spyke::node::Node node = spyke::node::Node( config );

  if ( ! node.setup() ) return 1;

  // node.start();

  sleep( 100 );

  while( 1 );

  node.finalize();

  return 0;
}