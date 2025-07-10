
#ifndef INCLUDE_PRIORITY_QUEUE_H_
#define INCLUDE_PRIORITY_QUEUE_H_

#include "priority_slot.h"
#include "smart_pointers.hpp"
#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <semaphore.h>


namespace priority_queue {

  class Priority_Queue {

    private:

      utils::unique_array_with_args_return_type< Priority_Slot > slots_mut;
      mutable std::condition_variable signal_mut;
      mutable std::mutex mutex_mut;
      mutable uint32_t items_count_mut;
      mutable sem_t locker_mut;

    private:

      const uint8_t slots_count;

    private:

      void wait_for_item() const;

    public:

      Priority_Queue() = delete;

      Priority_Queue( const Priority_Queue& ) = delete;

      Priority_Queue( Priority_Queue&& ) = delete;

    public:

      Priority_Queue( const uint8_t&, const uint32_t& ) noexcept;

      bool is_valid() const noexcept;

      bool add_item( std::unique_ptr< Item >&&, const uint8_t& ) noexcept;

      std::unique_ptr< Item > pop() noexcept;

  };

}

#endif
