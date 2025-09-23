
#ifndef ENABLE_TEMPLATE_COMPILATION
  #include "priority_queue.h"
#endif

#include "push_worker.h"
#include "stack_array.h"
#include "validation.h"
#include "log.h"


template< uint8_t MAX_PRIORITY, uint8_t PUSH_THREADS_COUNT >
priority_queue::Priority_Queue< MAX_PRIORITY, PUSH_THREADS_COUNT >::Priority_Queue( const uint32_t& queue_size ) noexcept : 
  push_workers( utils::make_stack_array< Push_Worker< MAX_PRIORITY >, PUSH_THREADS_COUNT >( queue_size ) ) {
    CHECK( ( queue_size & ( queue_size - 1 ) ) == 0, "Queue size must be a power of 2" );
}

template< uint8_t MAX_PRIORITY, uint8_t PUSH_THREADS_COUNT >
bool priority_queue::Priority_Queue< MAX_PRIORITY, PUSH_THREADS_COUNT >::is_priority_valid( const uint8_t& priority ) const noexcept {
  return MAX_PRIORITY > priority;
}

template< uint8_t MAX_PRIORITY, uint8_t PUSH_THREADS_COUNT >
bool priority_queue::Priority_Queue< MAX_PRIORITY, PUSH_THREADS_COUNT >::push( const uint8_t& push_worker_id, const uint8_t& priority, std::unique_ptr< Item >&& item ) noexcept {
  CHECK( is_priority_valid( priority ), "Invalid priority value provided" );
  return push_workers.at( push_worker_id ).push( priority, std::move( item ) );
}

#ifndef ENABLE_TEMPLATE_COMPILATION
  template class priority_queue::Priority_Queue< 0, 0 >;
#endif
