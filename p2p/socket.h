
/** socket.h - Holds all logic related to the socket connections
 *
 *
**/


#ifndef SPYKE_P2P_SOCKET_H
#define SPYKE_P2P_SOCKET_H

/** INCLUDES **/
#include "open_server_connection.h"
#include "open_connection.h"
#include <cstddef>


namespace spyke::p2p {

  // Tries to make a server from a given IP connection information
  bool make_server( Open_Server_Connection&, int );

  // Tries to establish a connection with a given IP data
  bool establish_connection( Open_Connection& );

  // Close the socket and the connection of a given connection
  bool close_connection( Open_Connection& );

  // Accepts a new connection
  bool accept_new_connection( Open_Server_Connection&, Open_Connection& );

  // Sends a given message to a given socket
  bool send_message( Open_Connection&, void*, size_t );

  // Receives a message from a given socket
  void* receive_message( Open_Connection& );

}

#endif
