
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



  };

} // namespace priority_queue

#endif // PRIORITY_QUEUE_INCLUDE_PRIORITY_QUEUE_H
