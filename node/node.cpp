
/** INCLUDES **/
#include "node.h"
#include "./../p2p/socket.h"
#include "node_configuration.h"
#include <bits/types/sigset_t.h>
#include <csignal>
#include <iostream>
#include <semaphore.h>
#include <sys/select.h>
#include <thread>
#include <unistd.h>


spyke::node::Node::Node( spyke::node::Node_Configuration& configuration ) : configuration( configuration ) {

  // Initialize semaphore for the connections
  sem_init( &connections_locker, 0, 1 );

  // Set the server connection into the open server connection for the "make_server" function
  server.connection = {

    .ip_connection = configuration.server_ip_connection->copy(),
    .socket = -1,
    .hint = 0,

  };

  // Clean the file descriptor management
  FD_ZERO( &file_descriptors_manager );

}

void spyke::node::Node::finalize() { 

  for ( int _ = 0; _ < configuration.max_ordinary_connections; _ ++ ) ordinary_connections[ _ ].finalize();
  for ( int _ = 0; _ < configuration.max_stable_connections; _ ++ ) stable_connections[ _ ].finalize();

  free( ordinary_connections ); free( stable_connections ); ordinary_connections = 0; stable_connections = 0;

  server.finalize(); configuration.finalize();

}

void SIGINT_handler( int ) {

  // Send the signal to all proccess in this gpid
  // stops the manage file descriptors loop
  kill( 0, SIGUSR1 );

  exit( 1 );

}

bool spyke::node::Node::setup() {

  // Tries to create the server
  if ( ! p2p::make_server( server, configuration.max_stable_connections + configuration.max_ordinary_connections ) ) return 0;

  // Set to be whatched in the fd_set
  FD_SET( server.connection.socket, &file_descriptors_manager );

  // Set the SIGINT sifgnal to peacefully exit the node 
  struct sigaction sa; sa.sa_handler = SIGINT_handler; sigemptyset( &sa.sa_mask ); sigaddset( &sa.sa_mask, SIGUSR1 ); sa.sa_flags = 0; 
  sigaction( SIGINT, &sa, NULL );

  // Memory for the connections
  ordinary_connections = ( spyke::p2p::Open_Connection* ) malloc( sizeof( spyke::p2p::Open_Connection ) * configuration.max_ordinary_connections );
  stable_connections = ( spyke::p2p::Open_Connection* ) malloc( sizeof( spyke::p2p::Open_Connection ) * configuration.max_stable_connections );

  for ( int _ = 0; _ < configuration.max_ordinary_connections; _ ++ ) { 

    ordinary_connections[ _ ].connection = { 0 }; ordinary_connections[ _ ].is_connected = 0; 

  }

  for ( int _ = 0; _ < configuration.max_stable_connections;_ ++ ) { 

    stable_connections[ _ ].connection = { 0 }; stable_connections[ _ ].is_connected = 0; 

  }

  // Everything works fine
  return 1;

}

void spyke::node::Node::establish_initial_connections() {

  for ( int _ = 0; _ < configuration.ips_to_connect_count; _ ++ ) {

    spyke::p2p::Open_Connection open_connection = {

      .connection = {

        .ip_connection = configuration.ips_to_connect[ _ ].copy(),
        .socket = -1,
        .hint = 0,

      },
      .is_connected = 0,

    };

    if ( ! p2p::establish_connection( open_connection ) ) { open_connection.finalize(); continue; }

    add_connection( open_connection, Ordinary_Connection );

  }

}

void spyke::node::Node::start() {

  establish_initial_connections();

  std::thread( &spyke::node::Node::manage_file_descriptors, this ).detach();

}

// Empty function to override the SIGUSR1 signal
void SIGUSR1_handler( int ) {}

void spyke::node::Node::manage_file_descriptors() {

  // Set the handler for the SIGUSR1
  struct sigaction sa; sa.sa_handler = SIGUSR1_handler; sigemptyset( &sa.sa_mask ); sa.sa_flags = 0; 

  // Set the signal up 
  sigaction( SIGUSR1, &sa, NULL );

  // Pselect mask to ignore other signals used in the code
  sigset_t pselect_mask; sigemptyset( &pselect_mask ); sigaddset( &pselect_mask, SIGINT );

  int files_count;

  while(
    ( 
      files_count = pselect( FD_SETSIZE, &file_descriptors_manager, 0, 0, 0, &pselect_mask )
    ) != -1
  ) {

    std::cout << "Hey hey" << std::endl;

  }

  std::cout << "out" << std::endl;

}


bool spyke::node::Node::add_connection( p2p::Open_Connection& connection, Connection_Type type ) {

  sem_wait( &connections_locker );

  bool rtr = 0;

  if ( type == Ordinary_Connection ) {

    for ( int _ = 0; _ < configuration.max_ordinary_connections; _ ++ )

      if ( ! ordinary_connections[ _ ].is_connected ) { ordinary_connections[ _ ] = connection; rtr = 1; break; }

  }

  else if ( type == Stable_Connection ) {

    for ( int _ = 0; _ < configuration.max_ordinary_connections; _ ++ )

      if ( ! stable_connections[ _ ].is_connected ) { stable_connections[ _ ] = connection; rtr = 1; break; }

  }

  sem_post( &connections_locker );

  return rtr;

}

bool spyke::node::Node::remove_connection( p2p::Open_Connection& connection, bool call_finalize ) {

  sem_wait( &connections_locker );

  bool rtr = 0;

  for ( int _ = 0; _ < configuration.max_ordinary_connections; _ ++ )

    if ( ordinary_connections[ _ ].connection == connection.connection ) { 

      if ( call_finalize ) ordinary_connections[ _ ].finalize(); 

      else ordinary_connections[ _ ].is_connected = 0;

      rtr = 1; break;

    }

  for ( int _ = 0; _ < configuration.max_ordinary_connections; _ ++ )

    if ( stable_connections[ _ ].connection == connection.connection ) {

      if ( call_finalize ) stable_connections[ _ ].finalize();

      else stable_connections[ _ ].is_connected = 0;

      rtr = 1; break;
    
    }

  sem_post( &connections_locker );

  return rtr;

}


