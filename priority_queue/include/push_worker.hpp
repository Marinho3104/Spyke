
#include "stack_array.h"
#ifndef ENABLE_TEMPLATE_COMPILATION
  #include "push_worker.h"
#endif

template< uint8_t MAX_PRIORITY >
priority_queue::Push_Worker< MAX_PRIORITY >::Push_Worker( const uint32_t& queue_size ) noexcept : queue( utils::make_stack_array< Priority_Slot, MAX_PRIORITY >( queue_size ) ), lock( ATOMIC_FLAG_INIT ) {}

template< uint8_t MAX_PRIORITY >
void priority_queue::Push_Worker< MAX_PRIORITY >::wait() const noexcept {
  while( lock.test_and_set() );
}

template< uint8_t MAX_PRIORITY >
void priority_queue::Push_Worker< MAX_PRIORITY >::release() const noexcept {
  lock.clear();
}

template< uint8_t MAX_PRIORITY >
bool priority_queue::Push_Worker< MAX_PRIORITY >::push( const uint8_t& priority, std::unique_ptr< Item >&& item ) noexcept {
  wait();
  const bool result = queue.at( priority ).push( std::move( item ) );
  release();
  return result;
}

#ifndef ENABLE_TEMPLATE_COMPILATION
  template class priority_queue::Push_Worker< 0 >;
#endif
