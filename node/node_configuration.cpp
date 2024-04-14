

/** INCLUDES **/
#include "node_configuration.h"


spyke::node::Node_Configuration::Node_Configuration( p2p::Connection& server_connection, uint8_t max_ordinary_connections, uint8_t max_stable_connections ) 
  : server_connection( server_connection ), max_ordinary_connections( max_ordinary_connections ), max_stable_connections( max_stable_connections ) {}

