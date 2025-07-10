
#include "priority_slot.h"
#include "item.h"
#include <cstdint>
#include <semaphore.h>
#include <utility>
#include "validation.h"
#include <iostream>


priority_queue::Priority_Slot::Priority_Slot() noexcept : first_mut(), last_mut( first_mut.get() ), items_count( 50 ), max_items( 0 ), status_mut( INVALID ) {

  const int locker_mut_sts = sem_init( &locker_mut, 0, 1 );
  if( locker_mut_sts != 0 ) {
    return;
  }

  status_mut = VALID;

}

priority_queue::Priority_Slot::Priority_Slot( const uint32_t& max_items ) noexcept : first_mut(), last_mut( first_mut.get() ), items_count( 0 ), max_items( max_items ), status_mut( INVALID ) {

  const int locker_mut_sts = sem_init( &locker_mut, 0, 1 );
  if( locker_mut_sts != 0 ) {
    return;
  }

  status_mut = VALID;

}

bool priority_queue::Priority_Slot::try_reserve_item() {
  
  uint32_t current_count = items_count.load();

  while( current_count != 0 ) {

    if( items_count.compare_exchange_strong( current_count, current_count - 1 ) ) {
      return 1;
    }

  }

  return 0;

}

bool priority_queue::Priority_Slot::is_valid() const noexcept { return status_mut == Status::VALID; }

void priority_queue::Priority_Slot::add_item( std::unique_ptr< Item >&& item ) noexcept {

  if( items_count.load() == max_items ) {
    return;
  }

  sem_wait( &locker_mut );

  Item* new_last_mut_value_mut = item.get();

  if( ! first_mut ) {

    first_mut = std::move( item );
    last_mut = new_last_mut_value_mut;

  }

  else {

    std::unique_ptr< Item >& last_item_next_ref_mut = last_mut->get_next();
    ENSURE( ! last_item_next_ref_mut );
    
    last_item_next_ref_mut.swap( item );
    last_mut = new_last_mut_value_mut;

  }

  items_count.fetch_add( 1 );

  sem_post( &locker_mut );

}

std::unique_ptr< priority_queue::Item > priority_queue::Priority_Slot::pop() noexcept {

  if( ! try_reserve_item() ) {
    return std::unique_ptr< Item >();
  }

  sem_wait( &locker_mut );

  std::unique_ptr< Item > popped_item = std::move( first_mut );
  first_mut = std::move( popped_item->get_next() );

  sem_post( &locker_mut );

  return popped_item;

}
