
#include "priority_slot.h"
#include <cstdint>


priority_queue::Priority_Slot::Priority_Slot( const uint32_t& queue_size ) noexcept : entries( std::make_unique< Priority_Slot_Entry[] >( queue_size ) ), 
  entries_head( 0 ), entries_tail( 0 ), queue_size( queue_size ) {}

// In the future change to % queue_size, for better performance, make queue_size a power of 2
uint32_t priority_queue::Priority_Slot::get_entry_index() const noexcept {

  uint32_t index;

  do {

    index = entries_tail.fetch_add( 1, std::memory_order_relaxed );

    if( index == queue_size - 1 ) {

      entries_tail.store( 0, std::memory_order_relaxed );

    }

  } while ( index >= queue_size );

  return index;

}

void priority_queue::Priority_Slot::push( std::unique_ptr< Item >&& item ) noexcept {

  const uint32_t index = get_entry_index();

  entries.get()[ index ].item = std::move( item );
  entries.get()[ index ].valid.test_and_set( std::memory_order_relaxed );

}
