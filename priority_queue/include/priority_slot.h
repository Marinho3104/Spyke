
#ifndef INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_
#define INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_

#include "item.h"
#include <cstdint>
#include <memory>
#include <mutex>
#include <atomic>

namespace priority_queue {

  class Priority_Slot {

    private:

      mutable std::atomic< uint32_t > items_count;
      std::unique_ptr< Item > first_mut;
      std::unique_ptr< Item >* next;
      mutable std::mutex mutex_mut;

    private:

      bool try_reserve() const noexcept;

    public:

      Priority_Slot( const Priority_Slot& ) = delete;

    public:

      Priority_Slot() noexcept;

      void add_item( Item&& ) noexcept;

      std::unique_ptr< Item > pop() noexcept;

  };

}

#endif // INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_
