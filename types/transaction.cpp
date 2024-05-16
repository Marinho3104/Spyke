
/** INCLUDES **/
#include "transaction.h"
#include "./../libs/ed25519/src/ed25519.h"
#include "address.h"
#include <cstdint>
#include <iostream>
#include <cstring>


spyke::types::Transaction::Transaction() {}

spyke::types::Transaction::Transaction( Address& to, uint64_t amount, uint64_t fee, void* extra_data, uint16_t extra_data_size )
  : from( Address() ), to( to ), amount( amount ), fee( fee ), extra_data( malloc( extra_data_size ) ), extra_data_size( extra_data_size ) { memcpy( this->extra_data, extra_data, extra_data_size ); }

spyke::types::Transaction::Transaction( Address& from, Address& to, uint64_t& amount, uint64_t& fee, uint64_t& balance_after )
  : from( from ), to( to ), amount( amount ), fee( fee ), balance_after( balance_after ) {}

void spyke::types::Transaction::finalize() { free( extra_data ); extra_data = 0; extra_data_size = 0; }

bool spyke::types::Transaction::set_from_address() {

  if ( extra_data_size < 1 ) return 0;

  switch ( *( Address_Types* ) extra_data ) {
  
    case Address_Types::NORMAL: return set_from_address_type_NORMAL();

  }

  return 0;

}

bool spyke::types::Transaction::set_from_address_type_NORMAL() {
  
  // Checks if available space is the correct for type NORMAL
  if ( EXTRA_DATA_SIZE_TYPE_NORMAL != extra_data_size ) return 0;

  unsigned char public_key[ 32 ]; memcpy( public_key, ( char* ) extra_data + 1, 32 );

  // Generates the address from the public key
  Address::create_address_type_NORMAL( public_key, from );

  return 1;

}

bool spyke::types::Transaction::verify_signature() {

  // Data to sign
  unsigned char data_to_sign[ get_binary_sign_bytes() ]; binary_representation_sign( ( char* ) data_to_sign );

  // Select type for the signature confirmation
  switch ( from.type ) {

    case spyke::types::Address_Types::NORMAL: return verify_signature_type_NORMAL( data_to_sign );
  
  }

  return 0;

}

bool spyke::types::Transaction::verify_signature_type_NORMAL( unsigned char* data_to_sign ) {

  if ( extra_data_size != EXTRA_DATA_SIZE_TYPE_NORMAL ) return 0;

  // Extra data only contains the address from public key 

  return ed25519_verify( signature, data_to_sign, get_binary_sign_bytes(), ( unsigned char* ) extra_data + 1 );

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

    return to.get_binary_bytes( to.type ) + sizeof( amount ) * 2 + sizeof( signature ) + sizeof( extra_data_size ) + extra_data_size;

  // If not, means is a confirmed transaction
  return 
    from.get_binary_bytes( from.type ) + to.get_binary_bytes( to.type ) +
      sizeof( amount ) * 3;

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

  if ( ! extra_data_size ) { memcpy( representation, &balance_after, sizeof( balance_after ) ); representation += sizeof( balance_after ); }

  // Only if is a not confirmed transaction we include the extra data
  else { 

    memcpy( representation, signature, sizeof( signature ) ); representation += sizeof( signature );
    memcpy( representation, &extra_data_size, sizeof( extra_data_size ) ); representation += sizeof( extra_data_size );
    memcpy( representation, extra_data, extra_data_size );

  }

}

bool spyke::types::Transaction::fill_transaction_not_confirmed( char* data, uint32_t& data_size, Transaction& transaction ) {

  // From and to addresses
  spyke::types::Address to; 

  if ( ! spyke::types::Address::fill_address( data, data_size, to ) ) return 0;
  data += to.get_binary_bytes( to.type ); data_size -= to.get_binary_bytes( to.type );

  // Check if there is still space for the rest of the information
  if ( data_size < sizeof( amount ) * 2 + sizeof( signature ) ) return 0;

  data_size -= sizeof( amount ) * 2 + sizeof( signature );

  // Get fields
  uint64_t amount, fee; unsigned char signature[ 64 ];

  memcpy( &amount, data, sizeof( amount ) ); data += sizeof( amount );
  memcpy( &fee, data, sizeof( fee ) ); data += sizeof( fee );
  memcpy( signature, data, sizeof( signature ) ); data += sizeof( signature );

  // Check if is still space for the extra data size field
  if ( data_size < 2 ) return 0;

  // Get the extra data size
  uint16_t extra_data_size; 

  memcpy( &extra_data_size, data, sizeof( extra_data_size ) ); data += sizeof( extra_data_size ); data_size -= sizeof( extra_data_size );

  if ( data_size < extra_data_size ) return 0;

  void* extra_data = malloc( extra_data_size ); memcpy( extra_data, data, extra_data_size );

  transaction = Transaction( to, amount, fee, extra_data, extra_data_size );

  free( extra_data );
  
  // Copy the signature as it is the only thing left that the constructor dont accept
  memcpy( transaction.signature, signature, 64 ); 

  return 1;

}

bool spyke::types::Transaction::fill_transaction_confirmed( char* data, uint32_t& data_size, Transaction& transaction ) {

  // From and to addresses
  spyke::types::Address from, to; 
  
  // Get the addresses
  if ( ! spyke::types::Address::fill_address( data, data_size, from ) ) return 0;
  data += from.get_binary_bytes( from.type ); data_size -= from.get_binary_bytes( from.type );

  if ( ! spyke::types::Address::fill_address( data, data_size, to ) ) return 0;
  data += to.get_binary_bytes( to.type ); data_size -= to.get_binary_bytes( to.type );

  // Check if there is still space for the rest of the information
  if ( data_size < sizeof( amount ) * 3 ) return 0;

  // Get the rest of the fields
  uint64_t amount, fee, balance_after;

  memcpy( &amount, data, sizeof( amount ) ); data += sizeof( amount );
  memcpy( &fee, data, sizeof( fee ) ); data += sizeof( fee );
  memcpy( &balance_after, data, sizeof( balance_after ) ); data += sizeof( balance_after );

  transaction = Transaction( from, to, amount, fee, balance_after );

  return 1;

}

