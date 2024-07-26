struct Node {

  unsigned long long balance;
  unsigned char previous_hash[ 32 ], address[ 32 ];
  unsigned int in_use;

  __local struct Node* left, *right, *previous;

};


void copy_node_data( __local struct Node* dst, __local struct Node* src, char cpy_AVL_data ) {

  dst->balance = src->balance;
  dst->in_use = src->in_use;

  for( int _ = 0; _ < sizeof( dst->previous_hash ); _ ++ ) 

    dst->previous_hash[ _ ] = src->previous_hash[ _ ];

  for( int _ = 0; _ < sizeof( dst->address ); _ ++ ) 

    dst->address[ _ ] = src->address[ _ ];

  if( cpy_AVL_data ) {

    dst->left = src->left;
    dst->right = src->right;
    dst->previous = src->previous;

  }

}

// Compares 2 given address to get the which one is the greater difference between them
// If return is:
//  -1 address1 is greater
//  0 they are equal
//  1 address2 is greater
char compare_addresses( __local unsigned char address1[ 32 ], __local unsigned char address2[ 32 ] ) {

  for( int _ = 0; _ < sizeof( __local unsigned char [ 32 ] ); _ ++ ) 

    if ( address1[ _ ] > address2[ _ ] ) return -1;

    else if( address1[ _ ] < address2[ _ ] ) return 1;

  return 0;

}

// Given an specific address returns the node which holds that value
__local struct Node* get_node( __local struct Node* current, __local unsigned char address[ 32 ] ) {

  // Because the memory needed for the AVL is already all "allocated" the root node
  // already exists, which make the base case condition to be if the balance is 0,
  // instead of current == 0
  if( ! current ) return 0;

  // Loops until it reatches the end of the tree
  while( current )

    switch ( compare_addresses( address, current->address ) ) {

      // If is -1 means that the current node is not greater than
      // the address which is wanted so go to the right
      case -1: current = current->right; break;

      // If is 1 means that the current node is greater than
      // the address which is wanted so go to the left
      case 1: current = current->left; break;

      // If is 0 means this node is the wanted node
      case 0: return current; break;
    
    }

  // If it ever reatches here means that the end of the tree was reatched 
  // and there is no node with given address
  return 0;

}

// Cause all memory is already initiated we need a double pointer to 
// change the address of the root
void start_BST( __local struct Node** current, __local struct Node* new ) { *current = new; }

// Adds a new node into the AVL and rebalances everything
void add_node( __local struct Node* current, __local struct Node* new ) {

  // Loops until it reatches the end of the tree
  while( current )

    switch ( compare_addresses( new->address, current->address ) ) {

      // If is -1 means that the current node is not greater than
      // the address which is wanted so go to the right
      case -1:

        if( current->right ) { current = current->right; break; }

        current->right = new; new->previous = current;

        return; break;

      // If is 1 means that the current node is greater than
      // the address which is wanted so go to the left
      case 1:

        if( current->left ) { current = current->left; break; }

        current->left = new; new->previous = current;

        return; break;

      // If is 0 means this node is the wanted node
      case 0: return; break;
    
    }

}

void remove_node( __local struct Node* to_delete ) {

  __local struct Node* previous_node = to_delete->previous;

  // Its a base case, leaf node
  if( ! to_delete->left && ! to_delete->right ) {

    if ( previous_node->right == to_delete ) previous_node->right = 0;
    else previous_node->left = 0;

  }

  // There is only node to the left side 
  else if( ! to_delete->left ) {

    // Change previous node address
    to_delete->right = previous_node;

    // Copy only the node data
    copy_node_data( to_delete, to_delete->right, 1 );

  }

  else if( ! to_delete->right ) {

    // Change previous node address
    to_delete->left = previous_node;

    // Copy only the node data
    copy_node_data( to_delete, to_delete->left, 1 );

  }

  else {

    __local struct Node* replacement_node = to_delete->left;

    while( replacement_node->right ) replacement_node = replacement_node->right;

    copy_node_data( to_delete, replacement_node, 0 ); remove_node( replacement_node );

  }

}

__local struct Node* create_new_node( __local unsigned char address[ 32 ], unsigned long long balance, __local unsigned char previous_hash[ 32 ], __local struct Node* BST_data ) {

  while( BST_data->balance ) BST_data ++;

  BST_data->balance = balance;
  BST_data->in_use = 0;

  BST_data->left = 0;
  BST_data->right = 0;
  BST_data->previous = 0;

  for( int _ = 0; _ < sizeof( BST_data->address ); _ ++ ) BST_data->address[ _ ] = address[ _ ];
  for( int _ = 0; _ < sizeof( BST_data->previous_hash ); _ ++ ) BST_data->previous_hash[ _ ] = previous_hash[ _ ];

  return BST_data; 

}
