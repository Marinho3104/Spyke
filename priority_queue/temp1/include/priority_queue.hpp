
#ifndef INCLUDE_PRIORITY_QUEUE_PRIORITY_QUEUE_H_
#define INCLUDE_PRIORITY_QUEUE_PRIORITY_QUEUE_H_

#include "priority_slot.h"
#include <array>
#include <cstdint>
#include <mutex>
#include <atomic>
#include <shared_mutex>
#include "validation.h"

namespace priority_queue {

  template< typename T, uint8_t N, typename... Args, size_t... I >
  std::array< T, N > helper( std::index_sequence< I... >, Args&&... args ) noexcept {
    static_assert(std::is_nothrow_constructible_v<T, Args...>, "Worker type must be nothrow constructible");
    return { ((void)I, T( std::forward< Args >( args )... ))... };
  }

  template< uint32_t MAX_ITEMS >
  struct Batched_Slot {

    public:

      std::array< Item, MAX_ITEMS > batched_pool_mut;
      std::atomic< uint32_t > index = 0;
      std::shared_mutex mutex_mut;

      Batched_Slot() noexcept {}

  };

  template< uint8_t SLOTS_COUNT, uint32_t MAX_ITEMS >
  class Priority_Queue {

    private:

      enum State: uint8_t {
        ACTIVE = 0,
        INACTIVE = 1,
        SEALED = 2
      };

    private:

      std::array< Batched_Slot< MAX_ITEMS >, SLOTS_COUNT > batched_slots_mut;
      std::array< Priority_Slot, SLOTS_COUNT > slots_mut;
      std::atomic< uint32_t > items_count_mut; // This count envolves items already in queue or items that are about to be added ( a.k.a with a reserved spot )
      std::atomic< State > state_mut;
      
    public:

      Priority_Queue( const Priority_Queue& ) = delete;

    public:

      Priority_Queue() noexcept;

      void activate() noexcept;

      void seal() noexcept;

      bool add_item( Item, const uint32_t& ) noexcept;

  };

  template< uint8_t SLOTS_COUNT, uint32_t MAX_ITEMS >
  Priority_Queue< SLOTS_COUNT, MAX_ITEMS >::Priority_Queue() noexcept : 
    slots_mut( helper< Priority_Slot, SLOTS_COUNT >( std::make_index_sequence< SLOTS_COUNT >(), MAX_ITEMS ) ), items_count_mut( 0 ), state_mut( INACTIVE ) {}

  template< uint8_t SLOTS_COUNT, uint32_t MAX_ITEMS >
  void Priority_Queue< SLOTS_COUNT, MAX_ITEMS >::activate() noexcept {
    state_mut.store( ACTIVE );
  }

  template< uint8_t SLOTS_COUNT, uint32_t MAX_ITEMS >
  void Priority_Queue< SLOTS_COUNT, MAX_ITEMS >::seal() noexcept {
    state_mut.store( SEALED );
  }

  template< uint8_t SLOTS_COUNT, uint32_t MAX_ITEMS >
  bool Priority_Queue< SLOTS_COUNT, MAX_ITEMS >::add_item( Item item, const uint32_t& priority ) noexcept {

    const uint32_t reserved_index = items_count_mut.fetch_add( 1 );

    if( reserved_index >= MAX_ITEMS ) {
      items_count_mut.fetch_sub( 1 );
      return false;
    }

    std::shared_lock lock( batched_slots_mut[ priority ].mutex_mut );

    const uint32_t batched_pool_index = batched_slots_mut[ priority ].index.fetch_add( 1 );
    new( &batched_slots_mut[ priority ].batched_pool_mut[ batched_pool_index ] ) Item( std::move( item ) );

    return true;

  }

}

#endif // INCLUDE_PRIORITY_QUEUE_PRIORITY_QUEUE_H_
