
#include "priority_slot.h"
#include <cstdint>
#include <memory>


priority_queue::Priority_Slot::Priority_Slot( const uint32_t& pool_size ) noexcept : 
  pool_mut( new Item[ pool_size ] ), pool_size( pool_size ) {}

// void priority_queue::Priority_Slot::add_item( Item&& item ) noexcept {
//
//   reserved_index_mut = ( reserved_index_mut + 1 ) % pool_size;
//
//   std::lock_guard< std::mutex > lock( mutex_mut );
//
//   new( &pool_mut[ reserved_index_mut ] ) Item( std::move( item ) );
//   pop_max_index_mut ++;
//
// }
//
// std::optional< priority_queue::Item > priority_queue::Priority_Slot::pop() noexcept {
//
//   std::lock_guard< std::mutex > lock( mutex_mut );
//
//   if( pop_index_mut == pop_max_index_mut ) {
//     return std::nullopt;
//   }
//
//   pop_index_mut = ( pop_index_mut + 1 ) % pool_size;
//   const uint32_t pop_index = pop_index_mut;
//
//   return std::move( pool_mut[ pop_index ] );
//
// }
