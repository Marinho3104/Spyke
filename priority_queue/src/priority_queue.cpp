
#include "priority_queue.h"
#include "priority_slot.h"
#include <cstdint>
#include <memory>
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

  // slots_mut = std::make_unique< Priority_Slot[] >( slots_count );

}
