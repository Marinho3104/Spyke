
struct Node {

  unsigned long long balance, nonce;
  unsigned char address[ 28 ], height;

  struct Node* previous, *left, *right;

};

void update_height_after_added_node( struct Node* );


void copy_node_data( struct Node* dst, struct Node* src, char cpy_AVL_data ) {

  dst->balance = src->balance;
  dst->nonce = src->nonce;

  for( int _ = 0; _ < sizeof( dst->address ); _ ++ ) 

    dst->address[ _ ] = src->address[ _ ];

  if( cpy_AVL_data ) {

    dst->left = src->left;
    dst->right = src->right;
    dst->previous = src->previous;
    dst->height = src->height;

  }

}

// Compares 2 given address to get the which one is the greater difference between them
// If return is:
//  -1 address1 is greater
//  0 they are equal
//  1 address2 is greater
char compare_addresses( unsigned char address1[ 28 ], unsigned char address2[ 28 ] ) {

  for( int _ = 0; _ < sizeof( unsigned char [ 28 ] ); _ ++ ) 

    if ( address1[ _ ] > address2[ _ ] ) return -1;

    else if( address1[ _ ] < address2[ _ ] ) return 1;

  return 0;

}

// Given an specific address returns the node which holds that value
struct Node* get_node( struct Node* current, unsigned char address[ 28 ] ) {

  // Beacuse the memory needed for the AVL is already all "allocated" the root node
  // already exists, which make the base case condition to be if the balance is 0,
  // instead of current == 0
  if( ! current->balance ) return 0;

  // Loops until it reatches the end of the tree
  while( current )

    switch ( compare_addresses( address, current->address ) ) {

      // If is -1 means that the current node is not greater than
      // the address which is wanted so go to the right
      case -1:

        current = current->right;

        break;

      // If is 1 means that the current node is greater than
      // the address which is wanted so go to the left
      case 1:

        current = current->left;

        break;

      // If is 0 means this node is the wanted node
      case 0:

        return current;

        break;
    
    }

  // If it ever reatches here means that the end of the tree was reatched 
  // and there is no node with given address
  return 0;

}

// Adds a new node into the AVL and rebalances everything
void add_node( struct Node* current, struct Node* new ) {

  // Beacuse the memory needed for the AVL is already all "allocated" the root node
  // already exists, which make the base case condition to be if the balance is 0,
  // instead of current == 0
  if( ! current->balance ) { copy_node_data( current, new, 1 ); return; }

  // Loops until it reatches the end of the tree
  while( current )

    switch ( compare_addresses( new->address, current->address ) ) {

      // If is -1 means that the current node is not greater than
      // the address which is wanted so go to the right
      case -1:

        if( current->right ) { current = current->right; break; }

        current->right = new; new->previous = current;

        update_height_after_added_node( new );

        return; break;

      // If is 1 means that the current node is greater than
      // the address which is wanted so go to the left
      case 1:

        if( current->left ) { current = current->left; break; }

        current->left = new; new->previous = current;

        update_height_after_added_node( new );

        return; break;

      // If is 0 means this node is the wanted node
      case 0: return; break;
    
    }

}

void remove_node( struct Node* to_delete ) {

  struct Node* previous_node = to_delete->previous;

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

    struct Node* replacement_node = to_delete->left;

    while( replacement_node->right ) replacement_node = replacement_node->right;

    copy_node_data( to_delete, replacement_node, 0 ); remove_node( replacement_node );

  }

}

void update_height_after_added_node( struct Node* added_node ) {

  char current_height = added_node->height + 1;
  
  added_node = added_node->previous;

  while( added_node && added_node->height < current_height ) {

    added_node->height = current_height;

    current_height ++;

    added_node = added_node->previous;

  }

}

void rebalance_AVL( struct Node* rebalance_node ) {

  char bf_rebalance_node = 
    ( rebalance_node->left ? rebalance_node->left->height : 0 ) -
    ( rebalance_node->right ? rebalance_node->right->height : 0 );

  if( bf_rebalance_node > -2 && bf_rebalance_node < 2 ) return;

  /*
  char bf_next_node = 
    ( next_node->left ? next_node->left->height : 0 ) -
    ( next_node->right ? next_node->right->height : 0 );
*/

  // Right-Right rotation
  if( bf_rebalance_node >= 0 && bf_next_node >= 0 ) {

    

  }
  
  // Left-Left rotation
  else if( bf_rebalance_node < 0 && bf_rebalance_node < 0 ) {}

}

int main() {


  return 0;

}
