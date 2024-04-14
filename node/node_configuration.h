
/** node_configuration.h - Holds all configuration fields for the initial Node instatiation
 *
 *
**/

#ifndef NODE_NODE_CONFIGURATION_H
#define NODE_NODE_CONFIGURATION_H


/** INCLUDES **/
#include "./../p2p/connection.h"
#include <cstdint>


namespace spyke::node {

  struct Node_Configuration {

    // Server Connection information
    p2p::Connection server_connection;

    // Number of connections that will be maintain in Node
    uint8_t max_ordinary_connections, max_stable_connections;

    // Default
    Node_Configuration( p2p::Connection&, uint8_t, uint8_t );

  };

}

#endif
