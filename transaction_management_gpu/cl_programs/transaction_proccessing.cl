
#include "./../transaction_management_gpu/cl_programs/BST.cl"

// Holds all Transaction data decomposed
struct Transaction {

    

};

struct Transaction decompose_transaction_data( __global void*, unsigned int );
void check_addresses_integrity();
void check_balance_nonce();
void check_signature();


kernel void transaction_proccessing(
    // Balance pool related variables
    __global void* balance_pool, __global char* balance_pool_locker,
    // Transaction data to confirmed
    __global void* transaction_data, unsigned int transaction_data_size
  ) {

    // Decompose the given transaction data
    struct Transaction transaction_decompose = decompose_transaction_data( transaction_data, transaction_data_size );
    

    switch( get_local_id( 0 ) ) {
  
      case 0: check_addresses_integrity(); break;
      case 1: check_balance_nonce(); break;
      case 2: check_signature(); break;

    }

    printf("Hey\n");

}

// Decompose a given transaction data into a struct with
// all the elements
struct Transaction decompose_transaction_data( __global void* transaction_data, unsigned int transaction_data_size ) {

  struct Transaction transaction_decomposed;

  return transaction_decomposed;

}

// Checks if the address to and from have correctly formed
void check_addresses_integrity() {}

// Checks if the address from has enought balance and the nonce
// of the signature is correct
void check_balance_nonce() {}

// Checks if the signature is correct given the type of address
void check_signature() {}
