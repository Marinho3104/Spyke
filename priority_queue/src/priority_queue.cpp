
#include "priority_queue.h"
#include "priority_slot.h"
#include "smart_pointers.hpp"
#include <cstdint>
#include <memory>
#include <semaphore.h>


priority_queue::Priority_Queue::Priority_Queue( const uint8_t& slots_count ) : slots_count( slots_count ) {

  // TODO: Handle throws of make_unique
  locker_mut = std::make_unique< sem_t >();
  const int locker_mut_sts = sem_init( locker_mut.get(), 0, 1 );
  if( locker_mut_sts != 0 ) {
    return;
  }

  is_not_empty_mut = std::make_unique< sem_t >();
  const int is_not_empty_mut_sts = sem_init( is_not_empty_mut.get(), 0, 0 );
  if( is_not_empty_mut_sts != 0 ) {
    return;
  }

  slots_mut = utils::make_unique_array_with_args< Priority_Slot >( slots_count, *is_not_empty_mut );

}

priority_queue::Priority_Queue::Priority_Queue( Priority_Queue&& other ) : slots_count( other.slots_count ) {

  if( ! other.is_valid() ) {
    return;
  }

  sem_wait( other.locker_mut.get() );

  locker_mut = std::move( other.locker_mut );
  is_not_empty_mut = std::move( other.is_not_empty_mut );
  slots_mut = std::move( other.slots_mut );

  sem_post( locker_mut.get() );

}

bool priority_queue::Priority_Queue::is_valid() const { return !! slots_mut; }
