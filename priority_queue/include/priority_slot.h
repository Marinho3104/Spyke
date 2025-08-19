
#ifndef INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_
#define INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_

#include "item.h"
#include <cstdint>
#include <memory>
#include <atomic>

namespace priority_queue {

  class Priority_Slot {

    private:

      std::unique_ptr< Item[] > pool_mut;
      std::atomic< uint32_t > add_index_mut, pop_index_mut, pop_max_index_mut;
      std::atomic< uint32_t >& actual_counter;

    private:

      const uint32_t& pool_size;

    private:

      uint32_t increment_index( const uint32_t& ) const noexcept;

    public:

      Priority_Slot( const Priority_Slot& ) = delete;

      Priority_Slot() noexcept = delete;

    public:

      Priority_Slot( const uint32_t&, std::atomic< uint32_t >& ) noexcept;

      void add_item( Item&& ) noexcept;

      Item pop() noexcept;

  };

}

#endif // INCLUDE_PRIORITY_QUEUE_PRIORITY_SLOT_H_
