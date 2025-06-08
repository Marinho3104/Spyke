
#ifndef INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_
#define INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_

#include "item.h"
#include <semaphore.h>

namespace priority_queue {

  class Priority_Slot {

    private:

      sem_t& is_not_empty;
      sem_t locker;

    public:

      Priority_Slot() = delete;

      Priority_Slot( const Priority_Slot& ) = delete;

    public:

      Priority_Slot( sem_t& );

      void add_item( Item );

      Item pop();

  };

}

#endif
