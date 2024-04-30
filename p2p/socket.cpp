
/** INCLUDES **/
#include <cstddef>
#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <semaphore.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <iostream>
#include "socket.h"
#include "IP_connection.h"
#include "connection.h"
#include "open_connection.h"
#include "open_server_connection.h"


bool spyke::p2p::make_server( Open_Server_Connection &server, int max_queue_pending_connections_length ) {

  // All variables that will depend on the IP type ( IPV4 / IPV6 ) will be defined here and set next
  // To avoid making the condition in every function that need it
  int socket_type, sizeof_hint;

  // IPV4
  if ( server.connection.ip_connection->type == IP_Connection_Type::V4 ) {

    IP_V4* ipv4 = ( IP_V4* ) server.connection.ip_connection;

    socket_type = AF_INET;
    
    sockaddr_in* sockaddr = 
      ( sockaddr_in* ) malloc( sizeof( sockaddr_in ) );
    sockaddr->sin_family = AF_INET;
    sockaddr->sin_addr.s_addr = htonl( ipv4->address );
    sockaddr->sin_port = ipv4->port;
    server.connection.hint = sockaddr;

    sizeof_hint = sizeof( sockaddr_in );


  }

  // IPV6
  else {

    socket_type = AF_INET6; throw -1;

  }

  // Tries to create a socket for the server
  if ( 
      
      ( server.connection.socket = 
        socket( socket_type, SOCK_STREAM, IPPROTO_TCP ) 
      ) == -1

    ) return 0;

  // Tries to bind the server
  if (

    bind(

      server.connection.socket,
      ( sockaddr* ) server.connection.hint,
      sizeof_hint

    ) == -1

  ) return 0;

  // Set queue max length
  if (

    listen(

      server.connection.socket,
      max_queue_pending_connections_length

    ) == -1

  ) return 0;

  return 1;

}


bool spyke::p2p::establish_connection( spyke::p2p::Open_Connection& connection ) {

  // All variables that will depend on the IP type ( IPV4 / IPV6 ) will be defined here and set next
  // To avoid making the condition in every function that need it
  int socket_type, sizeof_hint;

  // IPV4
  if ( connection.connection.ip_connection->type == IP_Connection_Type::V4 ) {

    IP_V4* ipv4 = ( IP_V4* ) connection.connection.ip_connection;

    socket_type = AF_INET;
    
    sockaddr_in* sockaddr = 
      ( sockaddr_in* ) malloc( sizeof( sockaddr_in ) );
    sockaddr->sin_family = AF_INET;
    sockaddr->sin_addr.s_addr = htonl( ipv4->address );
    sockaddr->sin_port = ipv4->port;
    connection.connection.hint = sockaddr;

    sizeof_hint = sizeof( sockaddr_in );


  }

  // IPV6
  else {

    socket_type = AF_INET6; throw -1;

  }

  // Tries to create a socket for the server
  if ( 
      
      ( connection.connection.socket = 
        socket( socket_type, SOCK_STREAM, IPPROTO_TCP ) 
      ) == -1

    ) return 0;

  // Tries to establish connection
  if (

    connect(

      connection.connection.socket,
      ( sockaddr* ) connection.connection.hint,
      sizeof_hint

    ) == -1

  ) return 0;

  return 1;

}

bool spyke::p2p::close_connection( spyke::p2p::Open_Connection& connection ) {

  if ( connection.connection.socket == -1 ) return 0;

  // Tries to close the socket file descriptor
  return close( connection.connection.socket ) != -1;

}

bool spyke::p2p::accept_new_connection( Open_Server_Connection& server, Open_Connection& new_connection ) {

  void* hint; socklen_t hint_size;

  // Check the server ip connection type
  // Cause if it is IPV4 for easier implementation
  // it will only accept IPV4 connections as well
  // But if it is IPV6 it accept either IPV4 or IPV6 
  // but the hint will always sockaddr_in6 cause it can
  // represent IPV$ and IPV6
  if ( server.connection.ip_connection->type == V4 ) 
  
    { new_connection.connection.hint = malloc( sizeof( sockaddr_in ) ); hint_size = sizeof( sockaddr_in ); }
  
  else 
    
    { new_connection.connection.hint = malloc( sizeof( sockaddr_in6 ) ); hint_size = sizeof( sockaddr_in6 ); }


  // Check for error
  if (

    (

      new_connection.connection.socket = accept( 

        server.connection.socket, 
        ( sockaddr* ) new_connection.connection.hint, 
        &hint_size 
      
      ) 
    
    ) == -1

  ) return 0;

  new_connection.is_connected = 1;

  return 1;

}

bool spyke::p2p::send_message( Open_Connection& connection, void* data, size_t data_size ) {

  int status = send(

    connection.connection.socket,
    data, data_size,
    0

  );
    
  return status != -1;

}

void* spyke::p2p::receive_message( Open_Connection& connection ) { 

  char data[4];

  int status =
    recv(

      connection.connection.socket,
      data,
      3,
      0

    );

  data[ 3 ] = 0;

  std::cout << data << std::endl;

  return 0;

}

