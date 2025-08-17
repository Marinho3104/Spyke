
#include "priority_slot.h"


priority_queue::Priority_Slot::Priority_Slot() noexcept : first_mut( nullptr ), last_mut( nullptr ) {}

void priority_queue::Priority_Slot::add_item( std::unique_ptr< Item >&& item ) noexcept {

  std::lock_guard< std::mutex > lock( mutex_mut );

  if( ! first_mut ) {

    first_mut = std::move( item );
    last_mut = first_mut.get();

  }

  else {

    last_mut->next_mut = std::move( item );
    last_mut = last_mut->next_mut.get();

  }

}

std::unique_ptr< priority_queue::Item > priority_queue::Priority_Slot::pop() noexcept {

  std::lock_guard< std::mutex > lock( mutex_mut );

  if( ! first_mut ) {
    return std::unique_ptr< Item >();
  }

  // Even when we are popping the last item on the queue, there is no need
  // to set the last_mut to nullptr. Because this action is performed in a thread safe space
  // and the last_mut is only used if the first_mut is not nullptr. And we set the first_mut
  // to nullptr when we pop the last item.
  std::unique_ptr< Item > rtr = std::move( first_mut );
  first_mut = std::move( rtr->next_mut );

  return rtr;

}
