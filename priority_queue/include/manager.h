
#ifndef INCLUDE_PRIORITY_QUEUE_WORKERS_MANAGER_H_
#define INCLUDE_PRIORITY_QUEUE_WORKERS_MANAGER_H_


#include "priority_queue.h"
#include "worker.h"
#include <array>
#include <cstdint>
#include <thread>
#include <type_traits>
#include <utility>

namespace priority_queue {

  template< typename T, uint8_t N, typename... Args, size_t... I >
  std::array< T, N > helper( std::index_sequence< I... >, Args&&... args ) noexcept {
    static_assert(std::is_nothrow_constructible_v<T, Args...>, "Worker type must be nothrow constructible");
    return { ((void)I, T( std::forward< Args >( args )... ))... };
  }

  template< typename Worker_Type, uint8_t N >
  class Manager {

    static_assert(std::is_base_of<Worker, Worker_Type>::value, "Worker type must derive from Base Worker");

    private:

      Priority_Queue queue_mut;
      std::array< Worker_Type, N > workers_mut;

    public:

      Manager( const Manager& ) = delete;

      Manager() = delete;

    public:

      Manager( Priority_Queue ) noexcept;

      // This function will only return when all the workers have finished
      void start() noexcept;

      void add_item( std::unique_ptr< Item >, const uint32_t& ) noexcept;

      void seal_priority_queue() noexcept;

  };

  template< typename Worker_Type, uint8_t N >
  priority_queue::Manager< Worker_Type, N >::Manager( Priority_Queue queue_mut ) noexcept : queue_mut( std::move( queue_mut ) ),
    workers_mut( helper< Worker_Type, N >( std::make_index_sequence< N >(), this->queue_mut ) ) {}

  template< typename Worker_Type, uint8_t N >
  void priority_queue::Manager< Worker_Type, N >::start() noexcept {

    std::array< std::thread, N > threads_mut;

    queue_mut.activate();

    for( uint8_t i = 0; i < N; i++ ) {
      threads_mut[ i ] = std::thread( &Worker_Type::start, &workers_mut[ i ] );
    }

    for( uint8_t i = 0; i < N; i++ ) {
      threads_mut[ i ].join();
    }

  }

  template< typename Worker_Type, uint8_t N >
  void priority_queue::Manager< Worker_Type, N >::add_item( std::unique_ptr< Item > item, const uint32_t& priority ) noexcept {
    queue_mut.add_item( std::move( item ), priority );
  }

  template< typename Worker_Type, uint8_t N >
  void priority_queue::Manager< Worker_Type, N >::seal_priority_queue() noexcept {
    queue_mut.seal();
  }

}

#endif // INCLUDE_PRIORITY_QUEUE_WORKERS_MANAGER_H_
