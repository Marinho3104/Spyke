
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
#include <semaphore.h>
#include <sys/types.h>


namespace spyke::node {

    // Specifies which type of connection is
    enum Connection_Type {
    
      Ordinary_Connection = 0,
      Stable_Connection = 1,

    };

    // Hold all function and variables about a Node
    struct Node {

      // Initial condifuration given
      Node_Configuration configuration;

      // Server Connection data
      p2p::Open_Server_Connection server;

      // Current open connections 
      p2p::Open_Connection* ordinary_connections, *stable_connections;

      // Locker for the Array connections changes to be sync
      sem_t connections_locker;

      // Locker for the Manage file descriptors loop
      sem_t close_manage_file_descriptors_locker;

      // Manage all file descriptors
      fd_set file_descriptors_manager;


      // Given a Node configuration confiure every thing needed for the execution
      Node( Node_Configuration& );

      // Finalizes and releases all memory used
      void finalize();

      // Stops all threads proccessing in execution to exit the Node peacefully
      void stop();

      // Performs the initial setup when the config file is set
      bool setup();

      // Tries to establish a connection with all given initial connections
      void establish_initial_connections();
      
      // Starts all the proccessing for a normal execution of a Node
      void start();

      // Tui for user inputs
      void TUI();

      // Manage every change in the socket connections
      void manage_file_descriptors();

      // Adds a given connections into the connections array
      bool add_connection( p2p::Open_Connection&, Connection_Type );

      // Removes a given connection from the connections array
      bool remove_connection( p2p::Open_Connection&, bool );

    };


  }

#endif
