
#include "stack_array.h"
#include <atomic>
#include <cstdint>
#ifndef ENABLE_TEMPLATE_COMPILATION
  #include "push_worker.h"
#endif

template< uint8_t MAX_PRIORITY >
priority_queue::Push_Worker< MAX_PRIORITY >::Push_Worker( const uint32_t& queue_size ) noexcept : queue( utils::make_stack_array< Priority_Slot, MAX_PRIORITY >( queue_size ) ) {}

template< uint8_t MAX_PRIORITY >
bool priority_queue::Push_Worker< MAX_PRIORITY >::push( const uint8_t& priority, std::unique_ptr< Item >&& item ) noexcept {
  return queue.at( priority ).push( std::move( item ) );
}

template< uint8_t MAX_PRIORITY >
template< uint32_t POP_QUEUE_SIZE >
uint32_t priority_queue::Push_Worker< MAX_PRIORITY >::pop( std::array< Item, POP_QUEUE_SIZE >& pop_queue, const uint32_t& offset ) noexcept {
  return queue.at( offset ).template pop< POP_QUEUE_SIZE >( pop_queue, offset );
}

#ifndef ENABLE_TEMPLATE_COMPILATION
  template class priority_queue::Push_Worker< 0 >;
  template uint32_t priority_queue::Push_Worker< 0 >::pop< 0 >( std::array< priority_queue::Item, 0 >&, const uint32_t& );
#endif
