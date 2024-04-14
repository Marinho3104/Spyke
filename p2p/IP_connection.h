
/** IP_connection_type.h - Holds the IP information about a connection  either IPV$ or IPV6
 *
 *
**/

#ifndef SPYKE_P2P_IP_CONNECTION_TYPE_H
#define SPYKE_P2P_IP_CONNECTION_TYPE_H

/** INCLUDES **/
#include <cstdint>


namespace spyke::p2p {

  // Hold a IP connection type 
  // the ideia is to be extended by the IPV6 and IPV4 structures
  struct IP_Connection {};

  // Holds all variables used in a IPV4 connection
  struct IP_V4 : IP_Connection {

    uint32_t address; uint16_t port;

  };

  // Holds all variables used in a IPV6 connection
  struct IP_V6 : IP_Connection {

  };

}

#endif
