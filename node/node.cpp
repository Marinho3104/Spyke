
/** INCLUDES **/
#include "node.h"
#include "./../p2p/socket.h"
#include "node_configuration.h"
#include <bits/types/sigset_t.h>
#include <csignal>
#include <iostream>
#include <sys/select.h>
#include <thread>
#include <unistd.h>


spyke::node::Node::Node( spyke::node::Node_Configuration& configuration ) : configuration( configuration ) {

  // Set the server connection into the open server connection for the "make_server" function
  server.connection = configuration.server_connection;

  // Clean the file descriptor management
  FD_ZERO( &file_descriptors_manager );

}

void spyke::node::Node::finalize() { server.finalize(); }

bool spyke::node::Node::setup() {

  // Tries to create the server
  if ( ! p2p::make_server( server, configuration.max_stable_connections + configuration.max_ordinary_connections ) ) return 0;

  // Memory for the connections
  ordinary_connections = ( spyke::p2p::Open_Connection* ) malloc( sizeof( spyke::p2p::Open_Connection ) * configuration.max_ordinary_connections );
  stable_connections = ( spyke::p2p::Open_Connection* ) malloc( sizeof( spyke::p2p::Open_Connection ) * configuration.max_stable_connections );

  // Everything works fine
  return 1;

}

void spyke::node::Node::establish_initial_connections() {

  for ( int _ = 0; _ < configuration.to_connect_count; _ ++ ) {



  }

}

void spyke::node::Node::start() {

  establish_initial_connections();

  manage_file_descriptors();

}

// Empty function to override the SIGUSR1 signal
void SIGUSR1_handler( int ) {}

void spyke::node::Node::manage_file_descriptors() {

  // Set the handler for the SIGUSR1
  struct sigaction sa; sa.sa_handler = SIGUSR1_handler; sigemptyset( &sa.sa_mask ); sa.sa_flags = 0; 

  // Set the signal up 
  sigaction( SIGUSR1, &sa, NULL );

  int files_count;

  while(
    ( 
      files_count = pselect( FD_SETSIZE, &file_descriptors_manager, 0, 0, 0, NULL ) 
    ) != -1
  ) {

    std::cout << "Hey hey" << std::endl;

  }

}


