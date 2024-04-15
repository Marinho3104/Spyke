
/** open_connecction.h - Represents an open server connection all the possible logic to 
 * interact with the connection as well as all variables related to
 *
**/


#ifndef SPYKE_P2P_OPEN_SERVER_CONNECTION_H
#define SPYKE_P2P_OPEN_SERVER_CONNECTION_H

/** INCLUDES **/
#include "connection.h"


namespace spyke::p2p {

  struct Open_Server_Connection {

    // Connection information
    Connection connection;

    // Is the server up
    bool is_up;
 
    // Finalizes and releases all memory used
    void finalize();   

  };

}

#endif
