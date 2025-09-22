
#ifndef PRIORITY_QUEUE_INCLUDE_PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_INCLUDE_PRIORITY_QUEUE_H

#include <array>
#include <cstdint>
#include "priority_slot.h"


namespace priority_queue {

  template< uint8_t MAX_PRIORITY >
  class Priority_Queue {

    private:

      std::array< Priority_Slot, MAX_PRIORITY > queue;

    public:

      Priority_Queue() = delete;

      Priority_Queue( const Priority_Queue& ) = delete;

      explicit Priority_Queue( const uint32_t& ) noexcept;

  };

} // namespace priority_queue

#ifdef ENABLE_TEMPLATE_COMPILATION
  #include "priority_queue.hpp"
#endif

#endif // PRIORITY_QUEUE_INCLUDE_PRIORITY_QUEUE_H

