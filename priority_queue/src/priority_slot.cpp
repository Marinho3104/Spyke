
#include "priority_slot.h"
#include "log.h"
#include <atomic>
#include <cstdint>


priority_queue::Priority_Slot::Priority_Slot( const uint32_t& queue_size ) noexcept : entries( std::make_unique< Item[] >( queue_size ) ), 
  queue_tail_address( entries.get() ), queue_head_address( entries.get() ), queue_limit( entries.get() + queue_size ), queue_size( queue_size ) {}

bool priority_queue::Priority_Slot::push( std::unique_ptr< Item >&& item ) noexcept {
  Item* target_address = queue_tail_address.load();
  Item* next_tail_address = target_address + 1;

  if( next_tail_address > queue_limit ) {
    next_tail_address = entries.get();
  }
  if( next_tail_address == queue_head_address ) {
    return false;
  }

  new ( target_address ) Item( std::move( *item ) );
  queue_tail_address.store( next_tail_address );
  
  return true;
}

template< uint32_t POP_QUEUE_SIZE >
uint32_t priority_queue::Priority_Slot::pop( std::array< Item, POP_QUEUE_SIZE >&, const uint32_t& ) noexcept {

  const Item* current_tail_address = queue_tail_address.load();
  Item* current_head_address = queue_head_address.load();
  int64_t current_head_offset = current_tail_address - current_head_address;

  if( current_head_offset == 0 ) {
    return 0;
  }

  if( current_head_offset < 0 ) {
    current_head_offset += queue_size;
  }

  LOG_INFO( "current_head_offset = %lld", current_head_offset );

  // while( 1 ) {
  //
  //
  //
  // }

}
