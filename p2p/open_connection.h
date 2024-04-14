
/** open_connecction.h - Represents an open connection all the possible logic to 
 * interact with the connection as well as all variables related to
 *
**/


#ifndef SPYKE_P2P_OPEN_CONNECTION_H
#define SPYKE_P2P_OPEN_CONNECTION_H

/** INCLUDES **/
#include "connection.h"


namespace spyke::p2p {

  struct Open_Connection {

    // Connection information
    Connection connection;

    // Connected
    bool is_connected;

  };

}

#endif
