
#ifndef INCLUDE_PRIORITY_QUEUE_PRIORITY_QUEUE_H_
#define INCLUDE_PRIORITY_QUEUE_PRIORITY_QUEUE_H_

#include "item.h"
#include "priority_slot.h"
#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <optional>
#include "smart_pointers.hpp"

namespace priority_queue {

  class Priority_Queue {

    private:

      enum State: uint8_t {
        ACTIVE = 0,
        INACTIVE = 1,
        SEALED = 2
      };

    private:

      utils::unique_array_with_args_return_type< Priority_Slot > slots;
      mutable std::atomic< uint32_t > items_count;
      mutable std::atomic< uint32_t > reserved_count;
      mutable std::condition_variable signal_mut, signal_empty_mut;
      mutable std::mutex mutex_mut, is_empty_mutex_mut;
      std::atomic< State > state_mut;

    private:

      const uint32_t max_items_count;
      const uint32_t slots_count;

    private:

      void wait_for_item() const noexcept;

      bool is_priority_value_valid( const uint32_t& ) const noexcept;

      bool is_active() const noexcept;
      
      bool is_sealed() const noexcept;

    public:

      Priority_Queue() = delete;

      Priority_Queue( const Priority_Queue& ) = delete;

    public:

      Priority_Queue( const uint32_t&, const uint32_t& ) noexcept;

      Priority_Queue( Priority_Queue&& ) noexcept;

      void activate() noexcept;

      void seal() noexcept;

      void wait_until_empty() const noexcept;

      bool add_item( Item, const uint32_t& ) noexcept;

      std::optional< Item > pop() noexcept;

  };

}

#endif // INCLUDE_PRIORITY_QUEUE_PRIORITY_QUEUE_H_
