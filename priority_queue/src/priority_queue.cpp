
#include "priority_queue.h"
#include "validation.h"
#include <cstdint>


priority_queue::Priority_Queue::Priority_Queue( const uint32_t& slots_count, const uint32_t& max_items ) noexcept : slots_mut( std::make_unique< Priority_Slot[] >( slots_count ) ),
  items_count( 0 ), state_mut( State::INACTIVE ), max_items_count( max_items ), slots_count( slots_count ) {}

priority_queue::Priority_Queue::Priority_Queue( Priority_Queue&& other ) noexcept : items_count( other.items_count ), state_mut( State::INACTIVE ), max_items_count( other.max_items_count ), 
  slots_count( other.slots_count ) {
    
    CHECK( ! other.is_active(), "Cannot move an active priority queue" )
    slots_mut = std::move( other.slots_mut );

}

void priority_queue::Priority_Queue::activate() noexcept { 

  CHECK( ! is_active(), "Priority queue is already active")

  state_mut.store( State::ACTIVE ); 

}

void priority_queue::Priority_Queue::seal() noexcept { 

  CHECK( ! is_sealed(), "Priority queue is already sealed" )

  state_mut.store( State::SEALED );

  signal_mut.notify_all();

}

void priority_queue::Priority_Queue::wait_until_empty() const noexcept {
  
  CHECK( is_sealed(), "Priority queue is not sealed" )

  std::unique_lock< std::mutex > lock( is_empty_mutex_mut );

  auto is_empty = [ this ]() {
    return items_count == 0;
  };

  signal_mut.wait( lock, is_empty );

}

void priority_queue::Priority_Queue::wait_for_item() const noexcept {

  std::unique_lock< std::mutex > lock( mutex_mut );

  auto decrement_items_count = [ this ]() {
    
    uint32_t current_count = items_count;

    if( current_count == 0 ) {
      return is_sealed();
    }

    if( current_count == 1 ) {
      signal_empty_mut.notify_all();
    }

    items_count --;

    return true;

  };

  signal_mut.wait( lock, decrement_items_count );

}

bool priority_queue::Priority_Queue::is_priority_value_valid( const uint32_t& priority_value ) const noexcept {
  return priority_value < slots_count;
}

bool priority_queue::Priority_Queue::is_active() const noexcept { return state_mut == State::ACTIVE; }

bool priority_queue::Priority_Queue::is_sealed() const noexcept { return state_mut == State::SEALED; }

bool priority_queue::Priority_Queue::add_item( std::unique_ptr< Item > item, const uint32_t& priority ) noexcept {

  CHECK( is_priority_value_valid( priority ), "Priority value is not valid" )
  CHECK( is_active(), "Priority queue is not active" )

  // To maintain performance, we perform a loose check.
  // If multiple threads reach this point concurrently, it's possible
  // that the queue may temporarily exceed the user-specified capacity.
  if( items_count >= max_items_count ) {
    return false;
  }

  slots_mut[ priority ].add_item( std::move( item ) );

  {
    std::unique_lock< std::mutex > lock( mutex_mut );
    items_count ++;
  }

  signal_mut.notify_one();

  return true;

}

std::unique_ptr< priority_queue::Item > priority_queue::Priority_Queue::pop() noexcept {

  CHECK( is_active() || is_sealed(), "Priority queue is not active nor sealed" )

  // This function will only  return in one of the following cases:
  //  1. There is at least one item in the queue, which was succesfully reserved
  //  2. The queue is sealed and there are no more items in the queue
  wait_for_item();

  for( uint32_t i = 0; i < slots_count; i++ ) {

    std::unique_ptr< Item > item_mut = slots_mut[ i ].pop();

    if( item_mut ) {
      return  item_mut;
    }
    
  }

  return std::unique_ptr< Item >();

}
