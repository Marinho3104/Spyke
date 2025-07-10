
#include "priority_slot.h"
#include "item.h"
#include <cstdint>
#include <semaphore.h>
#include <utility>


priority_queue::Priority_Slot::Priority_Slot() : first_mut(), last_mut( first_mut.get() ), items_count( 0 ), status_mut( INVALID ) {

  const int locker_mut_sts = sem_init( &locker_mut, 0, 1 );
  if( locker_mut_sts != 0 ) {
    return;
  }

  status_mut = VALID;

}

priority_queue::Priority_Slot::Priority_Slot( Priority_Slot&& other ) : first_mut(), last_mut( first_mut.get() ), items_count( 0 ), status_mut( INVALID ) {

  if( ! other.is_valid() ) {
    return;
  }

  const int locker_mut_sts = sem_init( &locker_mut, 0, 1 );
  if( locker_mut_sts != 0 ) {
    return;
  }

  sem_wait( &other.locker_mut );

  items_count = other.items_count.load();
  first_mut = std::move( other.first_mut );
  last_mut = other.last_mut;

  sem_post( &other.locker_mut );

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

bool priority_queue::Priority_Slot::is_valid() const { return status_mut == Status::VALID; }

void priority_queue::Priority_Slot::add_item( std::unique_ptr< Item >&& item ) {

  sem_wait( &locker_mut );

  Item* new_last_mut_value_mut = item.get();

  if( ! first_mut ) {

    first_mut = std::move( item );
    last_mut = new_last_mut_value_mut;

  }

  else {

    last_mut->set_next( std::move( item ) );
    last_mut = new_last_mut_value_mut;

  }

  items_count.fetch_add( 1 );

  sem_post( &locker_mut );

}

std::unique_ptr< priority_queue::Item > priority_queue::Priority_Slot::pop() {

  if( ! try_reserve_item() ) {
    return std::unique_ptr< Item >();
  }

  sem_wait( &locker_mut );

  std::unique_ptr< Item > popped_item = std::move( first_mut );
  first_mut = std::move( popped_item->get_next() );

  sem_post( &locker_mut );

  return popped_item;

}
