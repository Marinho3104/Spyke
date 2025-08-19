
#include "priority_slot.h"
#include "log.h"
#include <cstdint>
#include <memory>


priority_queue::Priority_Slot::Priority_Slot( const uint32_t& pool_size, std::atomic< uint32_t >& actual_counter ) noexcept : 
  pool_mut( new Item[ pool_size ] ), actual_counter( actual_counter ), pool_size( pool_size ) {}

uint32_t priority_queue::Priority_Slot::increment_index( const uint32_t& index ) const noexcept {
  return ( index + 1 ) % pool_size;
}

void priority_queue::Priority_Slot::add_item( Item&& item ) noexcept {

  uint32_t index_mut = add_index_mut.load();

  while( true ) {

    if( add_index_mut.compare_exchange_weak( index_mut, increment_index( index_mut ) ) ) {
      break;
    }

  }

  new( &pool_mut[ index_mut ] ) Item( std::move( item ) );
  pop_max_index_mut.fetch_add( 1 );
  actual_counter.fetch_add( 1 );

}

priority_queue::Item priority_queue::Priority_Slot::pop() noexcept {

  uint32_t index_mut = pop_index_mut.load();

  while( true ) {

    if( pop_index_mut.compare_exchange_weak( index_mut, increment_index( pop_index_mut ) ) ) {
      break;
    }

    if( index_mut == pop_max_index_mut.load() ) {
      return Item();
    }

  }

  return std::move( pool_mut[ index_mut ] );

}
