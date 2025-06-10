
#include "priority_queue.h"
#include "priority_slot.h"
#include "smart_pointers.hpp"
#include <cstdint>
#include <semaphore.h>


priority_queue::Priority_Queue::Priority_Queue( const uint8_t& slots_count ) : slots_count( slots_count ) {

  const int locker_mut_sts = sem_init( &locker_mut, 0, 1 );
  if( locker_mut_sts != 0 ) {
    return;
  }

  const int is_not_empty_mut_sts = sem_init( &is_not_empty_mut, 0, 0 );
  if( is_not_empty_mut_sts != 0 ) {
    return;
  }

  slots_mut = utils::make_unique_array_with_args< Priority_Slot >( slots_count, is_not_empty_mut );

}
