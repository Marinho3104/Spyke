
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
      std::unique_ptr< sem_t > is_not_empty_mut, locker_mut;

    private:

      const uint8_t slots_count;

    public:

      Priority_Queue() = delete;

      Priority_Queue( const Priority_Queue& ) = delete;

    public:

      Priority_Queue( const uint8_t& );

      Priority_Queue( Priority_Queue&& );

      bool is_valid() const;

  };

}

#endif
