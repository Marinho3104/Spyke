
#ifndef ENABLE_TEMPLATE_COMPILATION
  #include "priority_queue.h"
  priority_queue::Priority_Queue< 10 > ignored = priority_queue::Priority_Queue< 10 >( 100 );
#endif

#include "stack_array.h"


template< uint8_t MAX_PRIORITY >
priority_queue::Priority_Queue< MAX_PRIORITY >::Priority_Queue( const uint32_t& queue_size ) noexcept : queue( utils::make_stack_array< Priority_Slot, MAX_PRIORITY >( queue_size ) ) {}
