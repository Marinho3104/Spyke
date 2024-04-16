
/** connection.h - Responsible to hold all information about a specific connection
 *
 *
**/

#ifndef SPYKE_P2P_CONNECTION_H
#define SPYKE_P2P_CONNECTION_H

/** INCLUDES **/
#include "IP_connection.h"
#include <netinet/in.h>


namespace spyke::p2p {

  // Connection Structure
  struct Connection {

    // Ip connection information
    IP_Connection *ip_connection;

    // Socket Connection hint
    int socket; void* hint;

    // Finalizes and releases all memory used
    void finalize();

    // Compares if the socket id is the same with a given one
    bool operator==( Connection& );

  };

}

#endif

