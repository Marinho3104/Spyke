
#ifndef INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_
#define INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_

#include "item.h"
#include <cstdint>
#include <memory>
#include <mutex>
#include <optional>

namespace priority_queue {

  class Priority_Slot {

    private:

      std::unique_ptr< Item[] > pool_mut;
      uint32_t pop_index_mut, add_index_mut;
      std::mutex& mutex_mut;
      
    private:

      const uint32_t& pool_size;

    public:

      Priority_Slot( const Priority_Slot& ) = delete;

      Priority_Slot() noexcept = delete;

    public:

      Priority_Slot( const uint32_t&, std::mutex& ) noexcept;

      void add_item( Item&& ) noexcept;

      std::optional< Item > pop() noexcept;

  };

}

#endif // INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_
