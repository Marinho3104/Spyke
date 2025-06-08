
#ifndef INCLUDE_PRIORITY_QUEUE_H_
#define INCLUDE_PRIORITY_QUEUE_H_

#include <cstdint>
#include <semaphore.h>


namespace priority_queue {

  class Priority_Queue {

    private:

      sem_t is_not_empty_mut;
      sem_t locker_mut;

    public:

      Priority_Queue() = delete;

    public:

      Priority_Queue( const uint16_t& );

  };

}

#endif
