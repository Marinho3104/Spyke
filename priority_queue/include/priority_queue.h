
#ifndef INCLUDE_PRIORITY_QUEUE_H_
#define INCLUDE_PRIORITY_QUEUE_H_

#include "priority_slot.h"
#include "smart_pointers.hpp"
#include <cstdint>
#include <semaphore.h>


namespace priority_queue {


  class Priority_Queue {

    private:

      utils::unique_array_with_args_return_type< Priority_Slot > slots_mut;
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
