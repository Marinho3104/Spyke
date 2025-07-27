
#include "priority_queue.h"
#include "validation.h"
#include <cstdint>


priority_queue::Priority_Queue::Priority_Queue( const uint32_t& slots_count, const uint32_t& max_items ) noexcept : slots_mut( std::make_unique< Priority_Slot[] >( slots_count ) ),
  items_count( 0 ), max_items_count( max_items ), slots_count( slots_count ) {}

void priority_queue::Priority_Queue::wait_for_item() const noexcept {

  std::unique_lock< std::mutex > lock( mutex_mut );

  auto decrement_items_count = [ this ]() {
    
    uint32_t current_count = items_count.load();

    while( current_count != 0 ) {

      if( items_count.compare_exchange_weak( current_count, current_count - 1 ) ) {
        return true;
      }

    }

    return false;

  };

  signal_mut.wait( lock, decrement_items_count );

}

bool priority_queue::Priority_Queue::is_priority_value_valid( const uint32_t& priority_value ) const noexcept {
  return priority_value < slots_count;
}

bool priority_queue::Priority_Queue::add_item( Item&& item, const uint32_t& priority ) noexcept {

  CHECK( is_priority_value_valid( priority ), "Priority value is not valid" )

  // To maintain performance, we perform a loose check.
  // If multiple threads reach this point concurrently, it's possible
  // that the queue may temporarily exceed the user-specified capacity.
  if( items_count.load() >= max_items_count ) {
    return false;
  }

  slots_mut[ priority ].add_item( std::move( item ) );
  items_count.fetch_add( 1 );
  signal_mut.notify_one();

  return true;

}

std::unique_ptr< priority_queue::Item > priority_queue::Priority_Queue::pop() noexcept {

  wait_for_item();

  for( uint32_t i = 0; i < slots_count; i++ ) {

    std::unique_ptr< Item > item = slots_mut[ i ].pop();

    if( item ) {
      return item;
    }
    
  }

  ENSURE( false, "This point should never been reached" )

}
