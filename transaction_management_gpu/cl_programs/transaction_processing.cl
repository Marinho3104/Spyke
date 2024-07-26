
#include "./../transaction_management_gpu/cl_programs/BST.cl"

// Holds all Transaction data decomposed
struct Transaction {

  unsigned char from[ 32 ], to[ 32 ], previous_hash[ 32 ];
  unsigned long long balance, nonce;

};

// Forward
bool decompose_transaction_data( __global void*, __local struct Transaction*, unsigned int );
bool check_addresses_integrity( __local unsigned char[ 32 ], __local unsigned char[ 32 ] );
bool check_balance_previous_hash( __global int*, __local struct Node* __local*, __local unsigned char[ 32 ], __local unsigned char[ 32 ], unsigned long long );
void check_signature();


kernel void transaction_processing(
    // Balance pool related variables
    __local void* balance_pool, __global int* balance_pool_locker,
    // Transaction data to confirmed
    __global void* transaction_data, unsigned int transaction_data_size
  ) {

    // Decompose the given transaction data
    __local struct Transaction transaction_decomposed;

    // Local variables used to verify if all checks were succefull
    __local bool check0, check1, check2;

    // Get the thread id 2 to decompose the transaction
    if( get_local_id( 0 ) == 2 ) check2 = decompose_transaction_data( transaction_data, &transaction_decomposed, transaction_data_size );

    // Fence
    barrier(CLK_LOCAL_MEM_FENCE);

    // Check if transaction decomposition were succefull
    if( ! check2 ) return;

    switch( get_local_id( 0 ) ) {
  
      case 0: check0 = check_addresses_integrity( transaction_decomposed.from, transaction_decomposed.to ); break;
      case 1: check1 = check_balance_previous_hash( balance_pool_locker, ( __local struct Node* __local* ) balance_pool, transaction_decomposed.from, transaction_decomposed.previous_hash, transaction_decomposed.balance); break;
      default: break;

    }

    // Fence
    barrier(CLK_LOCAL_MEM_FENCE);

    // Checks if all previous operations were succefull
    if( ! check0 || ! check1 ) return;

    // for( int _ = 0; _ < 32; _ ++ ) printf("%d ", ( int ) transaction_decomposed.from[ _ ]);
    for( int _ = 0; _ < 32; _ ++ ) printf("%d ", ( int ) transaction_decomposed.previous_hash[ _ ]);
    printf("%d ", ( int ) transaction_decomposed.balance );
    // printf("Hey\n");

}

// Decompose a given transaction data into a struct with
// all the elements
bool decompose_transaction_data( __global void* transaction_data, __local struct Transaction* transaction_decomposed, unsigned int transaction_data_size ) {

  __global unsigned char* addresses = transaction_data;
  
  for( int _ = 0; _ < 32; _ ++ ) transaction_decomposed->from[ _ ] = *( addresses ++ );
  for( int _ = 0; _ < 32; _ ++ ) transaction_decomposed->to[ _ ] = *( addresses ++ );

  transaction_decomposed->balance = *( ( __global unsigned long long* ) addresses );

  return 1;

}

// Given an address id, type and checksum verifies if the given checksum
// is correct
bool verify_checksum( unsigned short type, unsigned short checksum, __local unsigned char id[ 28 ] ) {

  unsigned int cal_checksum = 0;

  for( int _ = 0; _ < 28; _ += 2 )

    cal_checksum += *( ( __local unsigned short* ) ( id + _ ) );

  cal_checksum += type; cal_checksum %= 0xffff;

  return cal_checksum == checksum;

}

// Checks if the address to and from are correctly formed
bool check_addresses_integrity( __local unsigned char address1[ 32 ], __local unsigned char address2[ 32 ] ) { 

  unsigned short address1_type = *( __local unsigned short* ) address1, address1_checksum = *( __local unsigned short* ) ( address1 + 30 );
  unsigned short address2_type = *( __local unsigned short* ) address2, address2_checksum = *( __local unsigned short* ) ( address2 + 30 );

  return verify_checksum( address1_type, address1_checksum, address1 + 2 ) && verify_checksum( address2_type, address2_checksum, address2 + 2 ); 

}

// Checks if the address from has enough balance and the nonce
// of the signature is correct
bool check_balance_previous_hash( __global int* balance_pool_locker, __local struct Node* __local* root, __local unsigned char address[ 32 ], __local unsigned char previous_hash[ 32 ], unsigned long long balance_to_spend ) {

  // Test
  __local struct Node* new_node = create_new_node( address, 1000, previous_hash, *( root + 1 ) ); add_node( *root, new_node );

  // Wait until it locks to safely use/modify the balance pool
  while( atomic_cmpxchg( balance_pool_locker, 0, 1 ) );

  // Gets the node with given address
  __local struct Node* node; node = get_node( *root, address );

  // If no node were found means given address has no balance
  // Or if the node information are already being in use
  if ( ! node || node->in_use ) return 0;

  // If a node were found checks if current balance is enough to the amount the transaction will spend
  if( node->balance < balance_to_spend ) return 0;

  // If it was enough just copies the previous hash used 
  // to further be used in the signature confirmation
  for( int _ = 0; _ < 32; _ ++ ) previous_hash[ _ ] = node->previous_hash[ _ ];

  // Sinalize to other threads that this node information
  // will be changed if the signature check is succefull
  node->in_use = 1;

  // Releases the locker for other threads to use
  atomic_xchg( balance_pool_locker, 0 );

  return 1;

}

// Checks if the signature is correct given the type of address
void check_signature() {}
