
#include "item.h"


priority_queue::Item::Item( std::unique_ptr< uint8_t[] >&& data_mut, const uint32_t& data_size ) noexcept : data_mut( std::move( data_mut ) ), data_size( data_size ) {}

bool priority_queue::Item::is_valid() const noexcept { return !! data_mut; }

std::unique_ptr< priority_queue::Item >& priority_queue::Item::get_next() noexcept {
  return next_mut;
}
