
/** INCLUDES **/
#include "./../libs/cipher/cipher/sha512.h"
#include "address.h"
#include <climits>
#include <cstdint>
#include <cstring>

spyke::types::Address::Address() {}

spyke::types::Address::Address( unsigned char* id, Address_Types type ) : type( type ) { memcpy( this->id, id, get_id_bytes( type ) ); }

void spyke::types::Address::set_checksum() {

  // Checksum algorithm:
  // Performs a sum in 2 bytes sequence for all the id data and adds the type value
  // Than if the sum is greater than USHRT_MAX makes a modulus of it

  int checksum = 0;

  for ( int _ = 0; _ < get_id_bytes( type ) / 2; _ += 2 )

    checksum += *( uint16_t* ) ( id + _ );

  checksum += type;

  if ( checksum >= USHRT_MAX ) checksum %= USHRT_MAX;

}

bool spyke::types::Address::verify_checksum() {

  uint16_t checksum_to_verify = checksum;

  set_checksum(); bool result = checksum_to_verify == checksum;

  // Keeps the original checksum in place
  checksum = checksum_to_verify;

  return result;

}

void spyke::types::Address::binary_representation( char* representation ) {

  memcpy( representation, &type, 2 ); representation += 2;
  memcpy( representation, id, get_id_bytes( type ) ); representation += get_id_bytes( type );
  memcpy( representation, &checksum, 2 );

}

void spyke::types::Address::hexadecimal_representation( char* representation ) {
 
  char const hexadecimal_characters[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

  *( representation ++ ) = hexadecimal_characters[ ( type & 0xF0 ) >> 4 ];
  *( representation ++ ) = hexadecimal_characters[ ( type & 0x0F ) >> 0 ];

  for ( int _ = 0; _ < get_id_bytes( type ); _ ++ ) {

    *( representation ++ ) = hexadecimal_characters[ ( id[ _ ] & 0xF0 ) >> 4 ];
    *( representation ++ ) = hexadecimal_characters[ ( id[ _ ] & 0x0F ) >> 0 ];

  }

  *( representation ++ ) = hexadecimal_characters[ ( checksum & 0xF000 ) >> 12 ];
  *( representation ++ ) = hexadecimal_characters[ ( checksum & 0x0F00 ) >> 8 ];

  *( representation ++ ) = hexadecimal_characters[ ( checksum & 0xF0 ) >> 4 ];
  *( representation ++ ) = hexadecimal_characters[ ( checksum & 0x0F ) >> 0 ];

}



unsigned char spyke::types::Address::get_id_bytes( Address_Types& type ) {

  switch ( type ) {

    case spyke::types::Address_Types::NORMAL: return NORMAL_TYPE_ADDRESS_ID_SIZE;
    case spyke::types::Address_Types::SHORT: return SHORT_TYPE_ADDRESS_ID_SIZE;
  
  }

  return -1;

}

unsigned char spyke::types::Address::get_binary_bytes( Address_Types& type ) {

  switch ( type ) {

    case spyke::types::Address_Types::NORMAL: return NORMAL_TYPE_ADDRESS_BINARY_REPRESENTATION;
    case spyke::types::Address_Types::SHORT: return SHORT_TYPE_ADDRESS_BINARY_REPRESENTATION;
  
  }

  return -1;

}



void spyke::types::Address::create_address_type_NORMAL( unsigned char public_key[ 32 ], Address& address ) {

  // The algorithm to generate the id is simply pass the public_key to the sha512 and then with the 
  // result mak it pass again more 2 times totalling 3 times passing throught the sha512

  unsigned char out0[ 64 ]; SHA512_Simple( public_key, 32, out0 );
  unsigned char out1[ 64 ]; SHA512_Simple( out1, 64, out1 );
  unsigned char out2[ 64 ]; SHA512_Simple( out2, 64, out2 );

  address = Address( out2, Address_Types::NORMAL );

}



