
#ifndef ENABLE_TEMPLATE_COMPILATION
  #include "priority_queue.h"
#endif

#include "stack_array.h"
#include "validation.h"
#include "log.h"


template< uint8_t MAX_PRIORITY >
priority_queue::Priority_Queue< MAX_PRIORITY >::Priority_Queue( const uint32_t& queue_size ) noexcept : queue( utils::make_stack_array< Priority_Slot, MAX_PRIORITY >( queue_size ) ) {}

template< uint8_t MAX_PRIORITY >
bool priority_queue::Priority_Queue< MAX_PRIORITY >::is_priority_valid( const uint8_t& priority ) const noexcept {
  return queue.size() >= priority;
}

template< uint8_t MAX_PRIORITY >
bool priority_queue::Priority_Queue< MAX_PRIORITY >::push( const uint8_t& priority, std::unique_ptr< Item >&& item ) noexcept {
  CHECK( is_priority_valid( priority ), "Invalid priority value provided" );
  return queue.at( priority ).push( std::move( item ) );
}

#ifndef ENABLE_TEMPLATE_COMPILATION
  template class priority_queue::Priority_Queue< 0 >;
#endif
