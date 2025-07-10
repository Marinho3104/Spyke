
#include "priority_queue.h"
#include "item.h"
#include "priority_slot.h"
#include "smart_pointers.hpp"
#include <cstdint>
#include <memory>
#include <mutex>
#include <semaphore.h>


priority_queue::Priority_Queue::Priority_Queue( const uint8_t& slots_count, const uint32_t& max_items_per_slot ) noexcept : slots_count( slots_count ), items_count_mut( 0 ) {

  const int locker_mut_sts = sem_init( &locker_mut, 0, 1 );
  if( locker_mut_sts != 0 ) {
    return;
  }

  slots_mut = utils::make_unique_array_with_args< Priority_Slot >( slots_count, max_items_per_slot );

}

void priority_queue::Priority_Queue::wait_for_item() const {

  std::unique_lock< std::mutex > lock( mutex_mut );

  if( items_count_mut != 0 ) {

    items_count_mut--;
    return;

  }

  signal_mut.wait( lock );

}

bool priority_queue::Priority_Queue::is_valid() const noexcept { return !! slots_mut; }

bool priority_queue::Priority_Queue::add_item( std::unique_ptr< Item >&& item, const uint8_t& priority ) noexcept {

  uint8_t current_slot_priority_mut = priority;
  bool add_item_rslt_mut;

  do {

    add_item_rslt_mut = slots_mut.get()[ current_slot_priority_mut ].add_item( std::move( item ) );
    current_slot_priority_mut ++;

  } while( ! add_item_rslt_mut && current_slot_priority_mut < slots_count );

  if( add_item_rslt_mut ) {

    std::unique_lock< std::mutex > lock( mutex_mut );
    items_count_mut ++;

  }

  return add_item_rslt_mut;

}

std::unique_ptr< priority_queue::Item > priority_queue::Priority_Queue::pop() noexcept {

  wait_for_item();

  for( uint8_t _ = 0; _ < slots_count; _ ++ ) {

    std::unique_ptr< Item > popped_item = slots_mut.get()[ _ ].pop();

    if( popped_item ) {
      return popped_item;
    }

  }

  return std::unique_ptr< Item >();

}
