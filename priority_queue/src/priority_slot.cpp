
#include "priority_slot.h"
#include "item.h"
#include <cstdint>
#include <memory>


priority_queue::Priority_Slot::Priority_Slot( const uint32_t& pool_size ) noexcept : 
  pool_mut( new Item[ pool_size ] ), pop_index_mut( 0 ), add_index_mut( 0 ), pool_size( pool_size ) {}

void priority_queue::Priority_Slot::add_items( Item* items, const uint32_t& items_count ) noexcept {

  std::lock_guard< std::mutex > lock( mutex_mut );

  for( uint32_t i = 0; i < items_count; i++ ) {
    new( &pool_mut[ add_index_mut++ ] ) Item( std::move( items[ i ] ) );
  }

}
