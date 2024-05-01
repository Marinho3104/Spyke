
/** INCLUDES **/
#include "node.h"
#include "./../p2p/socket.h"
#include "node_configuration.h"
#include <bits/types/sigset_t.h>
#include <csignal>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <sys/select.h>
#include <thread>
#include <unistd.h>


spyke::node::Node::Node( spyke::node::Node_Configuration& configuration ) : configuration( configuration ) {

  // Initialize the semaphores
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

void spyke::node::Node::stop() {

  // Send SIGUSR1 signal to stop the execution of manage_file_descriptors
  kill( 0, SIGUSR1 );

}

bool spyke::node::Node::setup() {

  // Tries to create the server
  if ( ! p2p::make_server( server, configuration.max_stable_connections + configuration.max_ordinary_connections ) ) return 0;

  // Set to be whatched in the fd_set
  FD_SET( server.connection.socket, &file_descriptors_manager );

  // Set the SIGINT sifgnal to peacefully exit the node 
  sigset_t mask; sigemptyset( &mask ); sigaddset( &mask, SIGINT ); sigaddset( &mask, SIGUSR1 ); sigprocmask( SIG_SETMASK, &mask, 0 );

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
      .is_connected = 1,

    };

    // Tries to establish a connection with the given Connection IP
    if ( ! p2p::establish_connection( open_connection ) ) { open_connection.finalize(); continue; }

    // If the connection succed adds it into the connections array 
    add_connection( open_connection, Ordinary_Connection );

  }

}

void spyke::node::Node::TUI() {

  char x;

  while( 1 ) {

    std::cout << "[ 0 ] - Exit" << std::endl;
    std::cout << "\n -> ";

    std::cin >> x;

    switch (x) {

      case '0': goto out;
    
    }

  }

  // If this part is reach means that the user wants to exit the node program 
  // so calls the stop function to exit all threads in execution
out: stop();

}

void spyke::node::Node::start() {

  // Tries to establish the given initial connections
  establish_initial_connections();

  // All proccesses arfe executed as a individual thread to make like a barrier where
  // it only go throught when all threads finishes
  std::thread threads[ 2 ];

  threads[ 0 ] = std::thread( &spyke::node::Node::manage_file_descriptors, this );
  threads[ 1 ] = std::thread( &spyke::node::Node::TUI, this );

  for( int _ = 0; _ < 2; _ ++ ) threads[ _ ].join();

  // Only reach point when all threads have finish
  // Hopefully peacefully :)

}

// Empty function to override the SIGUSR1 signal
void SIGUSR1_handler( int ) {}

void spyke::node::Node::manage_file_descriptors() {

  // The signal SIGUSR1 is choosed to act as a stop mechanism for the fd loop
  // So we override the default action of SIGUSR1 to be nothing 
  struct sigaction sa; sa.sa_handler = SIGUSR1_handler; sigemptyset( &sa.sa_mask ); sa.sa_flags = 0; sigaction( SIGUSR1, &sa, NULL );

  // Mask signals to override the previous mask and to accept the signal SIGUSR1
  sigset_t pselect_mask; sigemptyset( &pselect_mask );

  int files_count; fd_set set_sockets = file_descriptors_manager;

  while(

    ( 
      files_count = pselect( FD_SETSIZE, &set_sockets, 0, 0, 0, &pselect_mask )
    ) != -1
  
  ) {

    // Server
    if ( FD_ISSET( server.connection.socket, &set_sockets ) ) {

      p2p::Open_Connection new_connection = { 0 };

      if ( ! spyke::p2p::accept_new_connection( server, new_connection ) ) new_connection.finalize();

      else add_connection( new_connection, Ordinary_Connection );

    }

    sem_wait( &connections_locker );

    for ( int _ = 0; _ < configuration.max_ordinary_connections; _ ++ ) {

      // Check if the connection is up and if so checks if the socket fd were not changed
      if ( 
        ! ordinary_connections[ _ ].is_connected || 
        ! FD_ISSET( ordinary_connections[ _ ].connection.socket, &set_sockets ) 
      ) continue;

      void* message = p2p::receive_message( ordinary_connections[ _ ] );

      // Removes connection if message has an error
      if ( ! message ) { remove_connection( ordinary_connections[ _ ], true ); continue; }

    }

    sem_post( &connections_locker );

    set_sockets = file_descriptors_manager;

  }

}

bool spyke::node::Node::add_connection( p2p::Open_Connection& connection, Connection_Type type ) {

  // sem_wait( &connections_locker );

  bool rtr = 0;

  if ( type == Ordinary_Connection ) {

    for ( int _ = 0; _ < configuration.max_ordinary_connections; _ ++ )

      if ( ! ordinary_connections[ _ ].is_connected ) 

        { FD_SET( connection.connection.socket, &file_descriptors_manager ); ordinary_connections[ _ ] = connection; rtr = 1; break; }

  }

  else if ( type == Stable_Connection ) {

    for ( int _ = 0; _ < configuration.max_ordinary_connections; _ ++ )

      if ( ! stable_connections[ _ ].is_connected ) 

        { FD_SET( connection.connection.socket, &file_descriptors_manager ); stable_connections[ _ ] = connection; rtr = 1; break; }

  }

  // sem_post( &connections_locker );

  return rtr;

}

bool spyke::node::Node::remove_connection( p2p::Open_Connection& connection, bool call_finalize ) {

  // sem_wait( &connections_locker );

  bool rtr = 0;

  for ( int _ = 0; _ < configuration.max_ordinary_connections; _ ++ )

    if ( ordinary_connections[ _ ].connection == connection.connection ) { 

      FD_CLR( ordinary_connections[ _ ].connection.socket, &file_descriptors_manager );

      if ( call_finalize ) ordinary_connections[ _ ].finalize(); 

      else ordinary_connections[ _ ].is_connected = 0;

      rtr = 1; break;

    }

  for ( int _ = 0; _ < configuration.max_stable_connections; _ ++ )

    if ( stable_connections[ _ ].connection == connection.connection ) {

      FD_CLR( stable_connections[ _ ].connection.socket, &file_descriptors_manager );

      if ( call_finalize ) stable_connections[ _ ].finalize();

      else stable_connections[ _ ].is_connected = 0;

      rtr = 1; break;
    
    }

  // sem_post( &connections_locker );

  return rtr;

}

