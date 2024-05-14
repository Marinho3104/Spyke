
#include "header.h"
#include "./../../libs/ed25519/src/ed25519.h"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>

void transaction_tests() {


  std::cout << "*** Transaction Tests ***\n\n" << std::endl;

  unsigned char public_key[ 32 ], private_key[ 64 ];
  create_ed25519_key_pair( public_key, private_key );

  spyke::types::Address address = spyke::types::Address(); create_address_NORMAL( address, public_key ); 

  std::cout << "Creating a transaction ..." << std::endl;
  spyke::types::Transaction transaction = spyke::types::Transaction(); create_transaction( transaction, address, public_key );
  std::cout << "Done\n" << std::endl;

  std::cout << "Verifing transaction signature ..." << std::endl;
  sign_transaction( transaction, public_key, private_key );
  std::cout << "Done\n" << std::endl;

  std::cout << "Checking conversion between Struct and Binary and vice versa ..." << std::endl;
  check_conversion( transaction );
  std::cout << "Done\n" << std::endl;

  transaction.finalize();

}

void create_transaction( spyke::types::Transaction& transaction, spyke::types::Address& address, unsigned char public_key[ 32 ] ) {

  // Address to
  spyke::types::Address addr = spyke::types::Address(); create_address_NORMAL( addr );

  // Extra data
  unsigned char extra_data[ 33 ]; extra_data[ 0 ] = 0; memcpy( extra_data + 1, public_key, 32 );
  
  // Create the transaction
  transaction =
    spyke::types::Transaction( addr, 1000, 50, extra_data, 33 );  

  transaction.set_from_address();

}

void sign_transaction( spyke::types::Transaction& transaction, unsigned char public_key[ 32 ], unsigned char private_key[ 64 ] ) {

  // transaction data to sign
  unsigned char transaction_data_sign[ transaction.get_binary_sign_bytes() ];
  transaction.binary_representation_sign( ( char* ) transaction_data_sign );

  // Sign
  ed25519_sign( transaction.signature, transaction_data_sign, sizeof( transaction_data_sign ), public_key, private_key );

  // Verify if signature is correct
  assert( transaction.verify_signature() == 1 );

  // transaction.signature[ 0 ] = 0;

  // Verify is wrong signature gives error
  // assert( transaction.verify_signature() == 0 );

}


void check_conversion( spyke::types::Transaction& transaction ) {

  char bin_representation[ transaction.get_binary_bytes() ]; transaction.binary_representation( bin_representation );

  std::cout << "Original binary representation: ";

  for ( int _ = 0; _ < transaction.get_binary_bytes(); _ ++ ) std::cout << ( int ) bin_representation[ _ ] << " ";

  std::cout << std::endl;

  spyke::types::Transaction transaction_copy; uint32_t sizetranscopy = sizeof( bin_representation );
  
  assert( spyke::types::Transaction::fill_transaction_not_confirmed( bin_representation, sizetranscopy, transaction_copy ) == 1 );

  assert( transaction_copy.set_from_address() == 1 );

  char bin_representation_copy[ transaction_copy.get_binary_bytes() ]; transaction_copy.binary_representation( bin_representation_copy );

  std::cout << "Copied binary representation: ";

  for ( int _ = 0; _ < transaction_copy.get_binary_bytes(); _ ++ ) std::cout << ( int ) bin_representation_copy[ _ ] << " ";

  std::cout << std::endl;

  assert( transaction_copy.verify_signature() == 1 );

  transaction_copy.finalize();

}
