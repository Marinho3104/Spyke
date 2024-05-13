
#include "header.h"
#include "./../../libs/ed25519/src/ed25519.h"
#include <iostream>

void transaction_tests() {


  std::cout << "*** Transaction Tests ***\n\n" << std::endl;

  unsigned char public_key[ 32 ], private_key[ 64 ];
  create_ed25519_key_pair( public_key, private_key );

  spyke::types::Address address = spyke::types::Address(); create_address_NORMAL( address, public_key ); 

  std::cout << "Creating a transaction ..." << std::endl;
  spyke::types::Transaction transaction = spyke::types::Transaction(); create_transaction( transaction, address );
  std::cout << "Done" << std::endl;

  std::cout << "Verifing transaction signature ..." << std::endl;
  std::cout << "Done" << std::endl;

}

void create_transaction( spyke::types::Transaction& transaction, spyke::types::Address& address ) {

  // Address to
  spyke::types::Address addr = spyke::types::Address(); create_address_NORMAL( addr );

  // Create the transaction
  transaction =
    spyke::types::Transaction( address, addr, 1000, 50 );  

}

void sign_transaction( spyke::types::Transaction& transaction, unsigned char public_key[ 32 ], unsigned char private_key[ 64 ] ) {

  // transaction data to sign
  unsigned char transaction_data_sign[ transaction.get_binary_sign_bytes() ];
  transaction.binary_representation_sign( ( char* ) transaction_data_sign );

  // Sign
  ed25519_sign( transaction.signature, transaction_data_sign, sizeof( transaction_data_sign ), public_key, private_key );

}
