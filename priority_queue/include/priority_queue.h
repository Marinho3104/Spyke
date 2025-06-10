
#ifndef INCLUDE_PRIORITY_QUEUE_H_
#define INCLUDE_PRIORITY_QUEUE_H_

#include "priority_slot.h"
#include <cstdint>
#include <memory>
#include <semaphore.h>


namespace priority_queue {

  class Priority_Queue {

    private:

      std::unique_ptr< Priority_Slot[] > slots_mut;
      sem_t is_not_empty_mut;
      sem_t locker_mut;

    private:

      const uint8_t slots_count;

    public:

      Priority_Queue() = delete;

    public:

      Priority_Queue( const uint8_t& );

  };

}

#endif
