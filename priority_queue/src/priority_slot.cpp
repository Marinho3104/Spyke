
#include "priority_slot.h"
#include "item.h"
#include <semaphore.h>
#include <utility>


priority_queue::Priority_Slot::Priority_Slot( sem_t& is_not_empty ) : first_mut(), last_mut( first_mut.get() ), is_not_empty_mut( is_not_empty ), status( INVALID ) {

  const int locker_mut_sts = sem_init( &locker_mut, 0, 1 );
  if( locker_mut_sts != 0 ) {
    return;
  }

  status = VALID;

}

priority_queue::Priority_Slot::Priority_Slot( Priority_Slot&& other ) : first_mut(), last_mut( first_mut.get() ), is_not_empty_mut( other.is_not_empty_mut ), status( INVALID ) {

  if( ! other.is_valid() ) {
    return;
  }

  const int locker_mut_sts = sem_init( &locker_mut, 0, 1 );
  if( locker_mut_sts != 0 ) {
    return;
  }

  sem_wait( &other.locker_mut );

  first_mut = std::move( other.first_mut );
  last_mut = other.last_mut;

  sem_post( &other.locker_mut );

  status = VALID;

}

bool priority_queue::Priority_Slot::is_valid() const { return status == Status::VALID; }

bool priority_queue::Priority_Slot::add_item( std::unique_ptr< Item >&& item ) {

  sem_wait( &locker_mut );

  Item* new_last_mut_value_mut = item.get();
  const bool set_next_sts = last_mut->set_next( std::move( item ) );
  if( set_next_sts ) {
    last_mut = new_last_mut_value_mut;
  }

  sem_post( &locker_mut );

  return set_next_sts;

}

priority_queue::Item priority_queue::Priority_Slot::pop() {}
