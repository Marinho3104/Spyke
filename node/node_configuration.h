
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

    // Server IP Connection information
    p2p::IP_Connection* server_ip_connection;

    // Initial connections to establish
    p2p::IP_Connection* ips_to_connect; uint8_t ips_to_connect_count;

    // Number of connections that will be maintain in Node
    uint8_t max_ordinary_connections, max_stable_connections;

    // 
    void finalize();

  };

}

#endif