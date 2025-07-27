
#include "item.h"
#include "validation.h"
#include <cstdint>


priority_queue::Item::Item( std::unique_ptr< uint8_t[] >&& data_mut, const uint32_t& data_size ) noexcept : data_mut( std::move( data_mut ) ), data_size( data_size ) {}

priority_queue::Item::Item( Item&& other ) noexcept : data_mut( std::move( other.data_mut ) ), next_mut( std::move( other.next_mut ) ), data_size( other.data_size ) {}

bool priority_queue::Item::is_valid() const noexcept { return !! data_mut; }

const std::unique_ptr< uint8_t[] >& priority_queue::Item::get_data() const noexcept {
  CHECK( is_valid(), "Item is not valid" )
  return data_mut;
}

const uint32_t& priority_queue::Item::get_data_size() const noexcept {
  CHECK( is_valid(), "Item is not valid" )
  return data_size;
}

std::unique_ptr< priority_queue::Item >& priority_queue::Item::get_next() noexcept {
  CHECK( is_valid(), "Item is not valid" )
  return next_mut;
}

void priority_queue::Item::set_next( std::unique_ptr< Item >&& next ) noexcept {
  CHECK( is_valid(), "Item is not valid" )
  next_mut = std::move( next );
}
