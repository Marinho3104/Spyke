
#ifndef INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_
#define INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_

#include "item.h"
#include <cstdint>
#include <memory>
#include <semaphore.h>
#include <atomic>

namespace priority_queue {

  class Priority_Slot {

    private:

      enum Status: uint8_t {
        VALID = 0,
        INVALID = 1
      };

    private:

      std::atomic< uint32_t > items_count;
      std::unique_ptr< Item > first_mut;
      Item* last_mut;
      sem_t locker_mut;
      Status status_mut;

    private:

      bool try_reserve_item();

    public:

      Priority_Slot( const Priority_Slot& ) = delete;

    public:

      Priority_Slot();

      Priority_Slot( Priority_Slot&& );

      bool is_valid() const;

      void add_item( std::unique_ptr< Item >&& );

      std::unique_ptr< Item > pop();

  };

}

#endif
