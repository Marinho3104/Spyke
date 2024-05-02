
/** address.h - Holds a Address information as address type, checksum etc
 * Defines used for all addresses and types
 *
**/


#ifndef SPYKE_TYPES_ADDRESS_H
#define SPYKE_TYPES_ADDRESS_H

/** INCLUDES **/
#include <cstdint>


namespace spyke::types {

  // Enum for all types of transaction
  enum Address_Types {

    NORMAL = 0,
    SHORT = 1,

  };

  // Address
  struct Address {

    // Address id
    // Always takes the max possible size for id of all types 
    // so it always have space
    unsigned char id[ 64 ];

    // Address type
    unsigned char type;

    // Address checksum
    uint16_t checksum;

    // Constructor given the id and type fills the checksum
    Address( unsigned char*&, Address_Types );

    // Given a id and type set creates and sets the proper checksum
    void set_checksum();

    // Verifies if the setted checksum if correct for the given id and type set
    bool verify_checksum();

  };

}

#endif

// Normal type
#define NORMAL_TYPE_ADDRESS_ID_SIZE 64

// Short type
#define SHORT_TYPE_ADDRESS_ID_SIZE 32
