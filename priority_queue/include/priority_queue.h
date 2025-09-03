
#ifndef INCLUDE_PRIORITY_QUEUE_PRIORITY_QUEUE_H_
#define INCLUDE_PRIORITY_QUEUE_PRIORITY_QUEUE_H_

#include "item.h"
#include "priority_slot.h"
#include "smart_pointers.hpp"
#include <cstdint>
#include <atomic>
#include <memory>
#include <shared_mutex>

namespace priority_queue {

  class Batched_Slot {

    private:

      struct Object {

        public:

          Item item;
          std::atomic_flag valid;

          Object() noexcept;

      };

    public:

      std::unique_ptr< Object[] > batched_pool;
      std::atomic< uint32_t > index, actual;
      std::shared_mutex mutex;
      const uint32_t pool_size;

      Batched_Slot( const uint32_t& ) noexcept;

      uint32_t reserve_spot() noexcept;

  };

  class Priority_Queue {

    private:

      enum State: uint8_t {
        ACTIVE = 0,
        INACTIVE = 1,
        SEALED = 2,
        DEACTIVATED = 3
      };

    private:

      const uint8_t max_priority;
      const uint32_t pool_size;

    private:

      utils::unique_array_with_args_return_type< Batched_Slot > batched_slots;
      utils::unique_array_with_args_return_type< Priority_Slot > slots;
      std::unique_ptr< std::atomic< uint32_t >[] > global_items; // Number of items already inside the queue or with a reserved spot 
      std::atomic< State > state = INACTIVE;

    private:

      bool is_active() const noexcept;
      
      bool is_sealed() const noexcept;

      bool is_deactivated() const noexcept;

      void add_batched_items() noexcept;

    public:

      Priority_Queue() = delete;

      Priority_Queue( const Priority_Queue& ) = delete;

    public:

      ~Priority_Queue() noexcept;

      Priority_Queue( const uint8_t&, const uint32_t& ) noexcept;

      void activate() noexcept;

      void seal() noexcept;

      void deactivate() noexcept;

      bool add_item( Item, const uint32_t& ) noexcept;

  };

}

#endif // INCLUDE_PRIORITY_QUEUE_PRIORITY_QUEUE_H_
