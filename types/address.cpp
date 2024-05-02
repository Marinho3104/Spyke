
/** INCLUDES **/
#include "address.h"
#include <cstring>


spyke::types::Address::Address( unsigned char*& id, Address_Types type ) : type( type ) {

  if ( type == Address_Types::NORMAL ) memcpy( this->id, id, NORMAL_TYPE_ADDRESS_ID_SIZE );

  else if ( type == Address_Types::SHORT ) memcpy( this->id, id, SHORT_TYPE_ADDRESS_ID_SIZE );

}

void spyke::types::Address::set_checksum() {

  // Checksum algorithm:
  // Performs a sum in 2 bytes sequence for all the id data and after adds the type value
  // Than shifts it until all '1's are in the first 16 bits making it a 2 bytes value



}

bool spyke::types::Address::verify_checksum() { return 1; }
