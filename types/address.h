
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
  enum Address_Types : unsigned char {

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
    Address_Types type;

    // Address checksum
    uint16_t checksum;

    // Default contructor
    Address();

    // Constructor given the id and type fills the checksum
    Address( unsigned char*, Address_Types );

    // Given a id and type set creates and sets the proper checksum
    void set_checksum();

    // Verifies if the setted checksum if correct for the given id and type set
    bool verify_checksum();

    // Converts the address data into a binary representation
    void binary_representation( char* );

    // Converts the address data into a Hexadecimal string "human representation"
    void hexadecimal_representation( char* );


    // Returns the number of bytes used in a id given a address type
    static unsigned char get_id_bytes( Address_Types& );

    // Returns the number of bytes used in the binary representation given a address type
    static unsigned char get_binary_bytes( Address_Types& );

    // Creates an address of type NORMAL given the public key
    static void create_address_type_NORMAL( unsigned char[ 32 ], Address& );

    // Fills a given address with all information given the binary representation of it
    static bool fill_address( char*, uint16_t&, Address& );

  };

}

#endif

// Normal type
#define NORMAL_TYPE_ADDRESS_ID_SIZE 64
#define NORMAL_TYPE_ADDRESS_BINARY_REPRESENTATION ( 1 + NORMAL_TYPE_ADDRESS_ID_SIZE + 2 ) /* Type - 1 bytes | Checksum - 2 bytes */

// Short type
#define SHORT_TYPE_ADDRESS_ID_SIZE 32
#define SHORT_TYPE_ADDRESS_BINARY_REPRESENTATION ( 1 + SHORT_TYPE_ADDRESS_ID_SIZE + 2 ) /* Type - 1 bytes | Checksum - 2 bytes */

