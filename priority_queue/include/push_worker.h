
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
      mutable std::atomic_flag lock;

    private:

      void wait() const noexcept;

      void release() const noexcept;

    public:

      Push_Worker() = delete;

      Push_Worker( const Push_Worker& ) = delete;

      explicit Push_Worker( const uint32_t& ) noexcept;

      bool push( const uint8_t&, std::unique_ptr< Item >&& ) noexcept;


  };

}

#ifdef ENABLE_TEMPLATE_COMPILATION
  #include "push_worker.hpp"
#endif

#endif // PRIORITY_QUEUE_INCLUDE_PUSH_WORKER_H
