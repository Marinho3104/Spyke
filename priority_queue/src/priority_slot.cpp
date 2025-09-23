
#include "priority_slot.h"
#include <cstdint>


priority_queue::Priority_Slot::Priority_Slot( const uint32_t& queue_size ) noexcept : entries( std::make_unique< Item[] >( queue_size ) ), 
  entries_head( 0 ), entries_tail( 0 ), queue_size( queue_size ) {}

uint32_t priority_queue::Priority_Slot::get_entry_index() const noexcept {
  const uint32_t index = entries_tail;
  if( index == entries_head ) {
    return queue_size;
  }
  entries_tail = ( index + 1 ) & ( queue_size - 1 );
  return index;
}

bool priority_queue::Priority_Slot::push( std::unique_ptr< Item >&& item ) noexcept {
  const uint32_t index = get_entry_index();
  if( index == queue_size ) {
    return false;
  }
  new ( &entries.get()[ index ] ) Item( std::move( *item ) );
  return true;
}
