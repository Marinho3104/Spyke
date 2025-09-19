
#include "item.h"


priority_queue::Item::Item( std::unique_ptr< uint8_t[] >&& data, const uint64_t& size ) noexcept : data( std::move( data ) ), size( size ) {}

priority_queue::Item::Item( Item&& other ) noexcept : data( std::move( other.data ) ), size( other.size ) {}

const uint8_t* priority_queue::Item::get_data() const noexcept { return data.get(); }

const uint64_t& priority_queue::Item::get_size() const noexcept { return size; }
