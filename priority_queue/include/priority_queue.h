
#ifndef PRIORITY_QUEUE_INCLUDE_PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_INCLUDE_PRIORITY_QUEUE_H

#include <array>
#include <cstdint>
#include "push_worker.h"


namespace priority_queue {

  template< uint8_t MAX_PRIORITY, uint8_t PUSH_THREADS_COUNT = 1 >
  class Priority_Queue {

    private:

      std::array< Push_Worker< MAX_PRIORITY >, PUSH_THREADS_COUNT > push_workers;

    private:

      bool is_priority_valid( const uint8_t& ) const noexcept;

    public:

      Priority_Queue() = delete;

      Priority_Queue( const Priority_Queue& ) = delete;

      explicit Priority_Queue( const uint32_t& ) noexcept;

      bool push( const uint8_t&, const uint8_t&, std::unique_ptr< Item >&& ) noexcept;

  };

} // namespace priority_queue

#ifdef ENABLE_TEMPLATE_COMPILATION
  #include "priority_queue.hpp"
#endif

#endif // PRIORITY_QUEUE_INCLUDE_PRIORITY_QUEUE_H

