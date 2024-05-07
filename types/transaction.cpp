
/** INCLUDES **/
#include "transaction.h"
#include <cstring>


spyke::types::Transaction::Transaction( Address& from, Address& to, uint64_t amount, uint64_t fee )
  : from( from ), to( to ), amount( amount ), fee( fee ) {}

spyke::types::Transaction::Transaction( Address& from, Address& to, uint64_t& amount, uint64_t& fee, uint64_t& balance_after, unsigned char* signature )
  : from( from ), to( to ), amount( amount ), fee( fee ), balance_after( balance_after ) { memcpy( this->signature, signature, 64 ); }

uint32_t spyke::types::Transaction::get_binary_sign_bytes() {

  return 
    from.get_binary_bytes( from.type ) + to.get_binary_bytes( to.type ) + sizeof( amount ) * 2;

}

uint32_t spyke::types::Transaction::get_binary_bytes() {

  return 
    from.get_binary_bytes( from.type ) + to.get_binary_bytes( to.type ) +
      sizeof( amount ) * 3 + sizeof( signature );

}

void spyke::types::Transaction::binary_representation_sign( char* representation ) {

  from.binary_representation( representation ); representation += from.get_binary_bytes( from.type ); 
  to.binary_representation( representation ); representation += to.get_binary_bytes( to.type ); 

  memcpy( representation, &amount, sizeof( amount ) ); representation += sizeof( amount );
  memcpy( representation, &fee, sizeof( fee ) ); representation += sizeof( fee );

}

void spyke::types::Transaction::binary_representation( char* representation ) {

  from.binary_representation( representation ); representation += from.get_binary_bytes( from.type ); 
  to.binary_representation( representation ); representation += to.get_binary_bytes( to.type ); 

  memcpy( representation, &amount, sizeof( amount ) ); representation += sizeof( amount );
  memcpy( representation, &fee, sizeof( fee ) ); representation += sizeof( fee );
  
  memcpy( representation, &balance_after, sizeof( balance_after ) ); representation += sizeof( balance_after );

  memcpy( representation, signature, sizeof( signature ) );

}
