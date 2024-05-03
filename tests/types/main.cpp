
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include "./../../types/address.h"
#include "./../../libs/cipher/cipher/sha512.h"
#include "./../../libs/ed25519/src/ed25519.h"

void create_address_NORMAL() {

  unsigned char seed[32], public_key[32], private_key[64], signature[64];

  if (ed25519_create_seed(seed)) {
      printf("error while generating seed\n");
      exit(1);
  }

  ed25519_create_keypair(public_key, private_key, seed);

  spyke::types::Address_Types type = spyke::types::Address_Types::NORMAL;

  spyke::types::Address address = spyke::types::Address();

  spyke::types::Address::create_address_type_NORMAL( public_key, address );
  
  char repre[ spyke::types::Address::get_hexadecimal_bytes( type ) ];

  address.hexadecimal_representation( repre );

  repre[133] = 0;
    
  std::cout << repre << std::endl;

}

int main ( int argc, char *argv[] ) {

  create_address_NORMAL();

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
