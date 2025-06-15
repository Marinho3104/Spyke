
#include "item.h"


priority_queue::Item::Item( std::unique_ptr< uint8_t[] >&& data_mut, const uint32_t& data_size ) noexcept : data_mut( std::move( data_mut ) ), data_size( data_size ) {}

priority_queue::Item::Item( Item&& other ) noexcept : data_mut( std::move( other.data_mut ) ), data_size( other.data_size ) {}

bool priority_queue::Item::is_valid() const noexcept { return !! data_mut; }

void priority_queue::Item::set_next( std::unique_ptr< Item >&& next_value ) noexcept {
  next_mut = std::move( next_value );
}
