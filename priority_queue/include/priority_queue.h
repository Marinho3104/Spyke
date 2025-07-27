
#ifndef INCLUDE_PRIORITY_QUEUE_PRIORITY_QUEUE_H_
#define INCLUDE_PRIORITY_QUEUE_PRIORITY_QUEUE_H_

#include "item.h"
#include "priority_slot.h"
#include <atomic>
#include <condition_variable>
#include <cstdint>
namespace priority_queue {

  class Priority_Queue {

    private:

      std::unique_ptr< Priority_Slot[] > slots_mut;
      mutable std::atomic< uint32_t > items_count;
      mutable std::condition_variable signal_mut;
      mutable std::mutex mutex_mut;

    private:

      const uint32_t max_items_count;
      const uint32_t slots_count;

    private:

      void wait_for_item() const noexcept;

    public:

      Priority_Queue() = delete;

      Priority_Queue( const Priority_Queue& ) = delete;

    public:

      Priority_Queue( const uint32_t&, const uint32_t& ) noexcept;

      bool is_priority_value_valid( const uint32_t& ) const noexcept;

      bool add_item( Item&&, const uint32_t& ) noexcept;

      std::unique_ptr< Item > pop() noexcept;

  };

}

#endif // INCLUDE_PRIORITY_QUEUE_PRIORITY_QUEUE_H_
