
#include "priority_queue.h"
#include "smart_pointers.hpp"
#include <cstdint>
#include <thread>
#include <chrono>

priority_queue::Batched_Slot::Object::Object() noexcept : item(), valid( ATOMIC_FLAG_INIT ) {}


priority_queue::Batched_Slot::Batched_Slot( const uint32_t& pool_size ) noexcept : batched_pool( std::make_unique< Object[] >( pool_size ) ), index( 0 ), actual( 0 ), pool_size( pool_size ) {}

uint32_t priority_queue::Batched_Slot::reserve_spot() noexcept {

  const uint32_t reserved_spot_index = index.fetch_add( 1 );

  if( reserved_spot_index >= pool_size ) {
    index.fetch_sub( 1 );
    return pool_size;
  }

  return reserved_spot_index;

}


priority_queue::Priority_Queue::~Priority_Queue() noexcept {

  while( ! is_deactivated() ) {
    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
  }

}

priority_queue::Priority_Queue::Priority_Queue( const uint8_t& max_priority, const uint32_t& pool_size ) noexcept : 
  max_priority( max_priority ), pool_size( pool_size ), batched_slots( utils::make_unique_array_with_args< Batched_Slot >( max_priority, pool_size ) ), slots( utils::make_unique_array_with_args< Priority_Slot >( max_priority, pool_size ) ) {}

bool priority_queue::Priority_Queue::is_active() const noexcept { return state == ACTIVE; }

bool priority_queue::Priority_Queue::is_sealed() const noexcept { return state == SEALED; }

bool priority_queue::Priority_Queue::is_deactivated() const noexcept { return state == DEACTIVATED; }

void priority_queue::Priority_Queue::add_batched_items() noexcept {

  while( ! is_sealed() ) {

    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

    for( uint8_t i = 0; i < max_priority; i++ ) {

      batched_slots[ i ].actual.store( batched_slots[ i ].index.load() );

      //
      // if( batched_slots[ i ].index.load() == 0 ) {
      //   continue;
      // }
      //
      // slots[ i ].add_items( batched_slots[ i ].batched_pool.get(), batched_slots[ i ].index.load() );
      //
    }

  }

  state = DEACTIVATED;

}

void priority_queue::Priority_Queue::activate() noexcept {
  std::thread add_batched_items_thread = std::thread( &Priority_Queue::add_batched_items, this );
  add_batched_items_thread.detach();
  state = ACTIVE;
}

void priority_queue::Priority_Queue::seal() noexcept {
  state = SEALED;
}

void priority_queue::Priority_Queue::deactivate() noexcept {
  state = INACTIVE;
}

bool priority_queue::Priority_Queue::add_item( Item item, const uint32_t& priority ) noexcept {

  const uint32_t reserved_spot_index = batched_slots[ priority ].reserve_spot();

  if( reserved_spot_index == pool_size ) {
    return false;
  }

  new( &batched_slots[ priority ].batched_pool[ reserved_spot_index ].item ) Item( std::move( item ) );

  return true;

}
