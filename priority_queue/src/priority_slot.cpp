
#include "priority_slot.h"
#include <memory>


priority_queue::Priority_Slot::Priority_Slot() noexcept : items_count( 0 ), first_mut(), next( nullptr ) {}

bool priority_queue::Priority_Slot::try_reserve() const noexcept {
  
  uint32_t current_count = items_count.load();

  while( current_count != 0 ) {

    if( items_count.compare_exchange_weak( current_count, current_count - 1 ) ) {
      return true;
    }

  }

  return false;

}

void priority_queue::Priority_Slot::add_item( std::unique_ptr< Item >&& item ) noexcept {

  std::lock_guard< std::mutex > lock( mutex_mut );

  if( ! first_mut ) {

    first_mut = std::move( item );
    next = &first_mut->get_next();

  }

  else {

    *next = std::move( item );
    next = &(*next)->get_next();

  }

  items_count.fetch_add( 1 );

}

std::unique_ptr< priority_queue::Item > priority_queue::Priority_Slot::pop() noexcept {

  if( ! try_reserve() ) {
    return nullptr;
  }

  std::lock_guard< std::mutex > lock( mutex_mut );

  std::unique_ptr< Item > rtr = std::move( first_mut );
  first_mut = std::move( rtr->get_next() );
  return rtr;

}
