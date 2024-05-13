
/** INCLUDES **/
#include "transaction.h"
#include "./../libs/ed25519/src/ed25519.h"
#include <cstdint>
#include <iostream>
#include <cstring>


spyke::types::Transaction::Transaction() {}

spyke::types::Transaction::Transaction( Address& from, Address& to, uint64_t amount, uint64_t fee, void* extra_data, uint16_t extra_data_size )
  : from( from ), to( to ), amount( amount ), fee( fee ), extra_data( malloc( extra_data_size ) ), extra_data_size( extra_data_size ) { memcpy( this->extra_data, extra_data, extra_data_size ); }

spyke::types::Transaction::Transaction( Address& from, Address& to, uint64_t& amount, uint64_t& fee, uint64_t& balance_after, unsigned char* signature )
  : from( from ), to( to ), amount( amount ), fee( fee ), balance_after( balance_after ) { memcpy( this->signature, signature, 64 ); }

void spyke::types::Transaction::finalize() { free( extra_data ); extra_data = 0; extra_data_size = 0; }

bool spyke::types::Transaction::verify_signature() {

  // Data to sign
  unsigned char data_to_sign[ get_binary_sign_bytes() ]; binary_representation_sign( ( char* ) data_to_sign );

  return 1; // ed25519_verify( signature, data_to_sign, sizeof( data_to_sign ),  )

}

uint32_t spyke::types::Transaction::get_binary_sign_bytes() {

  return 
    from.get_binary_bytes( from.type ) + to.get_binary_bytes( to.type ) + sizeof( amount ) * 2;

}

uint32_t spyke::types::Transaction::get_binary_bytes() {

  // To the binary representation we have 2 options:
  //  Transaction Not Confirmed - Which includes the extra data and dont include the from address 
  //  Transaction Confirmed - Which includes the from address and dont include the extra data

  // If extra data is set, means is a not confirmed transaction
  if ( extra_data_size )

    return to.get_binary_bytes( to.type ) + sizeof( amount ) * 3 + sizeof( signature ) + sizeof( extra_data_size ) + extra_data_size;

  // If not, means is a confirmed transaction
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

  // Only if is a confirmed transaction we include the from address information
  if ( ! extra_data_size ) { from.binary_representation( representation ); representation += from.get_binary_bytes( from.type ); }
  
  to.binary_representation( representation ); representation += to.get_binary_bytes( to.type ); 
  memcpy( representation, &amount, sizeof( amount ) ); representation += sizeof( amount );
  memcpy( representation, &fee, sizeof( fee ) ); representation += sizeof( fee );
  memcpy( representation, &balance_after, sizeof( balance_after ) ); representation += sizeof( balance_after );
  memcpy( representation, signature, sizeof( signature ) ); 

  // Only if is a not confirmed transaction we include the extra data
  if ( extra_data_size ) {

    representation += sizeof( signature );
    memcpy( representation, &extra_data_size, sizeof( extra_data_size ) ); representation += sizeof( extra_data_size );
    memcpy( representation, extra_data, extra_data_size );

  }

}
