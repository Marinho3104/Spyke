
/** node.h - Responsible to connect and communicate with other nodes inside the network
 *
 *
**/

#ifndef NODE_NODE_H
#define NODE_NODE_H

/** INCLUDES **/
#include "./../p2p/open_server_connection.h"
#include "node_configuration.h"
#include "./../p2p/open_connection.h"
#include <sys/select.h>


namespace spyke::node {

    // Hold all function and variables about a Node
    struct Node {

      // Initial condifuration given
      Node_Configuration configuration;

      // Server Connection data
      p2p::Open_Server_Connection server;

      // Current open connections 
      p2p::Open_Connection* ordinary_connections, *stable_connections;

      // Manage all file descriptors
      fd_set file_descriptors_manager;


      // Given a Node configuration confiure every thing needed for the execution
      Node( Node_Configuration& );

      // Finalizes and releases all memory used
      void finalize();

      // Performs the initial setup when the config file is set
      bool setup();

      // Tries to establish a connection with all given initial connections
      void establish_initial_connections();
      
      // Starts all the proccessing for a normal execution of a Node
      void start();

      // Manage every change in the socket connections
      void manage_file_descriptors();

    };


  }

#endif
