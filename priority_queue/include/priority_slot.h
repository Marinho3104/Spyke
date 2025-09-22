
#ifndef PRIORITY_QUEUE_INCLUDE_PRIORITY_SLOT_H
#define PRIORITY_QUEUE_INCLUDE_PRIORITY_SLOT_H

#include "item.h"
#include <atomic>
#include <cstdint>
#include <memory>


namespace priority_queue {

  class Priority_Slot {

    private:

      struct Priority_Slot_Entry {

        public:

          std::unique_ptr< Item > item = nullptr;
          std::atomic_flag valid = ATOMIC_FLAG_INIT;

      };

    private:

      std::unique_ptr< Priority_Slot_Entry[] > entries;
      mutable std::atomic_uint_fast32_t entries_head, entries_tail;
      const uint32_t queue_size;

    private:

      uint32_t get_entry_index() const noexcept;

    public:

      Priority_Slot() = delete;

      Priority_Slot( const Priority_Slot& ) = delete;

      explicit Priority_Slot( const uint32_t& ) noexcept;

      bool push( std::unique_ptr< Item >&& ) noexcept;


  };
  
} // namespace priority_queue

#endif // PRIORITY_QUEUE_INCLUDE_PRIORITY_SLOT_H
