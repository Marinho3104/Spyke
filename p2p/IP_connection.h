
/** IP_connection_type.h - Holds the IP information about a connection  either IPV$ or IPV6
 *
 *
**/

#ifndef SPYKE_P2P_IP_CONNECTION_H
#define SPYKE_P2P_IP_CONNECTION_H

/** INCLUDES **/
#include <cstdint>


namespace spyke::p2p {

  // Enumeration to the type of IP connection used
  enum IP_Connection_Type {

    V4 = 0,
    V6 = 1,

  };

  // Hold a IP connection type 
  // the ideia is to be extended by the IPV6 and IPV4 structures
  struct IP_Connection {

    // Type of the IP 
    IP_Connection_Type type;

    IP_Connection( IP_Connection_Type );

    // Returns a pointer to a copy of this Structure
    IP_Connection* copy();

  };

  // Holds all variables used in a IPV4 connection
  struct IP_V4 : IP_Connection {

    uint32_t address; uint16_t port;

   IP_V4( uint32_t, uint16_t );

  };

  // Holds all variables used in a IPV6 connection
  struct IP_V6 : IP_Connection {

  };

}

#endif
