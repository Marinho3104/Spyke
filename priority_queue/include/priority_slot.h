
#ifndef INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_
#define INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_

#include "item.h"
#include <mutex>

namespace priority_queue {

  class Priority_Slot {

    private:

      mutable std::mutex mutex_mut;
      std::unique_ptr< Item > first_mut;
      Item *last_mut;

    public:

      Priority_Slot( const Priority_Slot& ) = delete;

    public:

      Priority_Slot() noexcept;

      void add_item( std::unique_ptr< Item >&& ) noexcept;

      std::unique_ptr<Item> pop() noexcept;

  };

}

#endif // INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_
