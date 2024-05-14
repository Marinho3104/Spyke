
#include "./../../types/address.h"
#include "./../../types/transaction.h"

/** ADDRESSES TESTS **/

// Creates and sets a ed25519 public and private key
bool create_ed25519_key_pair( unsigned char[ 32 ], unsigned char[ 64 ] );

// Create a address type NORMAL by the static function
void create_address_NORMAL( spyke::types::Address& );
void create_address_NORMAL( spyke::types::Address&, unsigned char[ 32 ] );

// Checks Address conversion between Struct Object type and Binary
void check_conversion( spyke::types::Address& );

// Perform the tests 
void address_tests();

/** TRANSACTION TESTS **/

// Perform the tests
void transaction_tests();

// Create a transaction 
void create_transaction( spyke::types::Transaction&, spyke::types::Address&, unsigned char[ 32 ] );

void sign_transaction( spyke::types::Transaction&, unsigned char[ 32 ], unsigned char[ 64 ] );

// Checks Transaction conversion between Struct Object type and Binary
void check_conversion( spyke::types::Transaction& );
