
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include "./../../types/address.h"
#include "./../../types/transaction.h"
#include "./../../libs/ed25519/src/ed25519.h"

spyke::types::Address create_address_NORMAL() {

  unsigned char seed[32], public_key[32], private_key[64], signature[64];

  if (ed25519_create_seed(seed)) {
      printf("error while generating seed\n");
      exit(1);
  }

  ed25519_create_keypair(public_key, private_key, seed);

  spyke::types::Address_Types type = spyke::types::Address_Types::NORMAL;

  spyke::types::Address address = spyke::types::Address();

  spyke::types::Address::create_address_type_NORMAL( public_key, address );
  
  char repre[ spyke::types::Address::get_binary_bytes( type ) * 2 ];

  address.hexadecimal_representation( repre );

  char bin_repre[ spyke::types::Address::get_binary_bytes( type ) ];

  address.binary_representation( bin_repre );

  spyke::types::Address address2 = spyke::types::Address();

  uint16_t size = sizeof( bin_repre );

  bin_repre[ 5 ] = 123;

  // std::cout << "Bin to struct result:" << spyke::types::Address::fill_address( bin_repre, size, address2 ) << std::endl;

  for ( int _ = 0; _ < address.get_binary_bytes( address.type ); _ ++ ) std::cout << repre[ _ ];
    
  std::cout << std::endl;

  return address;

}

spyke::types::Transaction create_transaction() {

  unsigned char seed[32], public_key[32], private_key[64], signature[64];

  if (ed25519_create_seed(seed)) {
      printf("error while generating seed\n");
      exit(1);
  }
  
  ed25519_create_keypair(public_key, private_key, seed);
  
  spyke::types::Address sender = spyke::types::Address();
  spyke::types::Address::create_address_type_NORMAL( public_key, sender );
  
  spyke::types::Address receiver = create_address_NORMAL();

  spyke::types::Transaction transaction = 
    spyke::types::Transaction( sender, receiver, 1000, 50 );

  unsigned char data_to_sign[ transaction.get_binary_sign_bytes() ];

  transaction.binary_representation_sign( ( char* ) data_to_sign );

  // ed25519_sign(transaction.signature, data_to_sign, transaction.get_binary_sign_bytes(), public_key, private_key);

  std::cout << ed25519_verify( transaction.signature, data_to_sign, transaction.get_binary_sign_bytes(), public_key ) << std::endl;

  return transaction;

}

int main ( int argc, char *argv[] ) {

  create_address_NORMAL();

  // create_transaction();

  return 0;

}


/*
 *
 *
 *
  unsigned char seed[32], public_key[32], private_key[64], signature[64];
  unsigned char other_public_key[32], other_private_key[64], shared_secret[32];
  const unsigned char message[] = "TES";

  if (ed25519_create_seed(seed)) {
      printf("error while generating seed\n");
      exit(1);
  }

  ed25519_create_keypair(public_key, private_key, seed);

  ed25519_sign(signature, message, 3, public_key, private_key);
  
  if (ed25519_verify(signature, message, 3, public_key)) {
      printf("valid signature\n");
  } else {
      printf("invalid signature\n");
  }

 
*/
