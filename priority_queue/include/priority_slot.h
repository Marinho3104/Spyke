
#ifndef INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_
#define INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_

#include "item.h"
#include <cstdint>
#include <memory>
#include <semaphore.h>

namespace priority_queue {

  class Priority_Slot {

    private:

      enum Status: uint8_t {
        VALID = 0,
        INVALID = 1
      };

    private:

      std::unique_ptr< Item > first_mut;
      Item* last_mut;
      sem_t& is_not_empty_mut;
      sem_t locker_mut;
      Status status;

    public:

      Priority_Slot() = delete;

      Priority_Slot( const Priority_Slot& ) = delete;

    public:

      Priority_Slot( sem_t& );

      Priority_Slot( Priority_Slot&& );

      bool is_valid() const;

      bool add_item( std::unique_ptr< Item >&& );

      Item pop();

  };

}

#endif
