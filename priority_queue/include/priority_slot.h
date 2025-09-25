
#ifndef PRIORITY_QUEUE_INCLUDE_PRIORITY_SLOT_H
#define PRIORITY_QUEUE_INCLUDE_PRIORITY_SLOT_H

#include "item.h"
#include <atomic>
#include <cstdint>
#include <memory>


namespace priority_queue {

  class Priority_Slot {

    private:

      std::unique_ptr< Item[] > entries;
      std::atomic< Item* > queue_tail_address, queue_head_address;
      const Item* queue_limit;
      const uint32_t queue_size;

    public:

      Priority_Slot() = delete;

      Priority_Slot( const Priority_Slot& ) = delete;

      explicit Priority_Slot( const uint32_t& ) noexcept;

      bool push( std::unique_ptr< Item >&& ) noexcept;

      template< uint32_t POP_QUEUE_SIZE >
      uint32_t pop( std::array< Item, POP_QUEUE_SIZE >&, const uint32_t& ) noexcept;

  };
  
} // namespace priority_queue

#endif // PRIORITY_QUEUE_INCLUDE_PRIORITY_SLOT_H
