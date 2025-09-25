
#ifndef PRIORITY_QUEUE_INCLUDE_PUSH_WORKER_H
#define PRIORITY_QUEUE_INCLUDE_PUSH_WORKER_H

#include "priority_slot.h"
#include <array>
#include <cstdint>


namespace priority_queue {

  template< uint8_t MAX_PRIORITY >
  class Push_Worker {

    private:

      std::array< Priority_Slot, MAX_PRIORITY > queue;

      template< uint8_t MAX_PRIORITY_PRIORITY_QUEUE, uint8_t PUSH_THREADS_COUNT >
      friend class Priority_Queue;

    private:

      Push_Worker() = delete;

      Push_Worker( const Push_Worker& ) = delete;

      bool push( const uint8_t&, std::unique_ptr< Item >&& ) noexcept;

      template< uint32_t POP_QUEUE_SIZE >
      uint32_t pop( std::array< Item, POP_QUEUE_SIZE >&, const uint32_t& ) noexcept;

    public:

      explicit Push_Worker( const uint32_t& ) noexcept;

  };

}

#ifdef ENABLE_TEMPLATE_COMPILATION
  #include "push_worker.hpp"
#endif

#endif // PRIORITY_QUEUE_INCLUDE_PUSH_WORKER_H
