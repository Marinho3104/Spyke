
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

  // Enumeration to the type of IP connection used
  enum IP_Connection_Type {

    V4 = 0,
    V6 = 1

  };

  // Connection Structure
  struct Connection {

    // Type of the IP connection in use
    IP_Connection_Type ip_connection_type;

    // Ip connection information
    IP_Connection *ip_connection;

    // Socket Connection hint
    int socket; void* hint;

    // Finalizes and releases all memory used
    void finalize();

  };

}

#endif

