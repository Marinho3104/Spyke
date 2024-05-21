
/** INCLUDES **/
#include "./../libs/ed25519/src/ed25519.h"
#include <iostream>
#include "block.h"
#include <cstdint>
#include <cstring>


spyke::types::Block::Block( unsigned char miner_public_key[ 32 ], uint32_t size, void* data )
  : size( size ), data( malloc( size ) ) { memcpy( this->miner_public_key, miner_public_key, 32 ); memcpy( this->data, data, size ); }

spyke::types::Block::Block( unsigned char miner_public_key[ 32 ], unsigned char signature[ 64 ], uint32_t size, void* data ) 
  : size( size ), data( malloc( size ) ) { memcpy( this->miner_public_key, miner_public_key, 32 ); memcpy( this->miner_signature, signature, 64 ); memcpy( this->data, data, size ); }

void spyke::types::Block::finalize() { free( data ); data = 0; size = 0; }

bool spyke::types::Block::verify_signature() {

  unsigned char data_to_sign[ get_binary_sign_bytes() ]; binary_representation_sign( ( char* ) data_to_sign );

  return 
    ed25519_verify( miner_signature, data_to_sign, get_binary_sign_bytes(), miner_public_key );

}

uint32_t spyke::types::Block::get_binary_sign_bytes() { return sizeof( miner_public_key ) + sizeof( size ) + size; }

uint32_t spyke::types::Block::get_binary_bytes() {  return sizeof( miner_public_key ) + sizeof( miner_signature ) + sizeof( size ) + size; }

void spyke::types::Block::binary_representation_sign( char* representation ) {

  memcpy( representation, miner_public_key, sizeof( miner_public_key ) ); representation += sizeof( miner_public_key ); 
  memcpy( representation, &size, sizeof( size ) ); representation += sizeof( size ); 
  memcpy( representation, data, size );

}

void spyke::types::Block::binary_representation( char* representation ) {

  memcpy( representation, miner_public_key, sizeof( miner_public_key ) ); representation += sizeof( miner_public_key ); 
  memcpy( representation, miner_signature, sizeof( miner_signature ) ); representation += sizeof( miner_signature ); 
  memcpy( representation, &size, sizeof( size ) ); representation += sizeof( size ); 
  memcpy( representation, data, size );

}

bool spyke::types::Block::fill_block( char* data, uint32_t& size, Block& block ) {

  // Check if have enought space for public key signature and size 
  if ( size < sizeof( block.miner_public_key ) + sizeof( block.miner_signature ) + sizeof( block.size ) ) return 0; 
  size -= sizeof( block.miner_public_key ) + sizeof( block.miner_signature ) + sizeof( block.size );
    
  unsigned char* public_key = ( unsigned char* ) data; data += sizeof( block.miner_public_key );
  unsigned char* signature = ( unsigned char* ) data; data += sizeof( block.miner_signature );
  uint32_t block_size = *( uint32_t* ) data; data += sizeof( block.size );

  // Check if have enought space for the block data
  if ( size < block_size ) return 0;

  void* block_data = data;

  block = Block( public_key, signature, block_size, block_data );
  
  return 1;

}


