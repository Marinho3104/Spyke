
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sys/types.h>

#include "./../../libs/cipher/cipher/sha512.h"
#include "./../../libs/ed25519/src/ed25519.h"

int main ( int argc, char *argv[] ) {

  unsigned char seed[32], public_key[32], private_key[64], signature[64];
  unsigned char other_public_key[32], other_private_key[64], shared_secret[32];
  const unsigned char message[] = "TES";

  /* create a random seed, and a key pair out of that seed */
  if (ed25519_create_seed(seed)) {
      printf("error while generating seed\n");
      exit(1);
  }

  ed25519_create_keypair(public_key, private_key, seed);

  /* create signature on the message with the key pair */
  ed25519_sign(signature, message, 3, public_key, private_key);
  
  /* verify the signature */
  if (ed25519_verify(signature, message, 3, public_key)) {
      printf("valid signature\n");
  } else {
      printf("invalid signature\n");
  }

  std::cout << "POP" << std::endl;

  return 0;

}

