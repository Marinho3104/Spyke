
#include <cassert>
#include <cstdint>
#include <iostream>
#include "./../../libs/ed25519/src/ed25519.h"
#include "./../../types/address.h"
#include "header.h"

// Perform the tests 
void address_tests() {

  std::cout << "*** Address Tests ***\n\n" << std::endl;

  std::cout << "Creating a address type NORMAL ..." << std::endl;
  spyke::types::Address addr = spyke::types::Address(); create_address_NORMAL( addr );
  std::cout << "Done\n" << std::endl;

  std::cout << "Checking conversion between Struct and Binary and vice versa ..." << std::endl;
  check_conversion( addr );
  std::cout << "Done\n" << std::endl;

}

bool create_ed25519_key_pair( unsigned char public_key[ 32 ], unsigned char private_key[ 64 ] ) {

  unsigned char seed[32];

  if ( ed25519_create_seed( seed ) ) {
      printf("error while generating seed\n");
      return 0;
  }

  ed25519_create_keypair( public_key, private_key, seed);

  return 1;

}


void create_address_NORMAL( spyke::types::Address& address ) {

  // Generate a key pair for the address generation
  unsigned char public_key[ 32 ], private_key[ 64 ]; create_ed25519_key_pair( public_key, private_key );

  // Creates the address
  spyke::types::Address::create_address_type_NORMAL( public_key, address );

}

void create_address_NORMAL( spyke::types::Address& address, unsigned char public_key[ 32 ] ) {

  // Creates the address
  spyke::types::Address::create_address_type_NORMAL( public_key, address );

}

void check_conversion( spyke::types::Address& address ) {

  char hex_representation[ address.get_binary_bytes( address.type ) * 2 + 1 ]; hex_representation[ address.get_binary_bytes( address.type ) * 2 ] = 0;
  address.hexadecimal_representation( hex_representation );

  std::cout << "Original hexadecimal representation: " << hex_representation << std::endl;

  char bin_representation[ address.get_binary_bytes( address.type ) ]; 
  address.binary_representation( bin_representation );

  std::cout << "Original binary representation: ";
  for ( int _ = 0; _ < address.get_binary_bytes( address.type ); _ ++ ) 
    std::cout << ( int ) bin_representation[ _ ] << " ";

  std::cout << std::endl;

  spyke::types::Address addr2 = spyke::types::Address();
  uint32_t size_addrbin = sizeof( bin_representation );

  // Check if conversion is successful
  assert( spyke::types::Address::fill_address( bin_representation, size_addrbin, addr2 ) == 1 );

  // Check if given the wrong information gives false
  bin_representation[ 1 ] = 1;
  assert( spyke::types::Address::fill_address( bin_representation, size_addrbin, addr2 ) == 0 );

}
