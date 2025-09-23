
#include "log.h"
#include "priority_queue.h"
#include "item.h"
#include <cstdint>
#include <cstdlib>
#include <thread>
#include <vector>

const uint32_t MAX_PRIORITY = 20;
const uint32_t QUEUE_SIZE = 2 << 20;
const uint32_t ITEMS_COUNT = 1000000;
const uint32_t ITERATIONS = 5;
const uint32_t THREAD_COUNT = 20;

struct ItemAndPriority {
  std::unique_ptr< priority_queue::Item > item;
  uint32_t priority;
};

int main () {

  LOG_INFO("*** MULTI THREAD PERFORMANCE TESTS FOR PUSH ***");

  std::srand(std::time(nullptr));

  double times_per_iteration[ ITERATIONS ] = { 0 };
  double max_time_per_iteration[ ITERATIONS ] = { 0 };

  for( uint32_t i = 0; i < ITERATIONS; i++ ) {

    priority_queue::Priority_Queue< MAX_PRIORITY, THREAD_COUNT > queue = priority_queue::Priority_Queue< MAX_PRIORITY, THREAD_COUNT >( QUEUE_SIZE );

    double times_per_thread[ THREAD_COUNT ] = { 0 };

    auto add_items_fun = [ &queue, &times_per_thread ]( uint32_t thread_index ) {

      std::vector< ItemAndPriority > payloads;
      for( uint32_t i = 0; i < ITEMS_COUNT / THREAD_COUNT; i++ ) {
          payloads.push_back( 
              { 
                .item = std::make_unique< priority_queue::Item >( std::make_unique< uint8_t[] >( 8 ), 8 ), 
                .priority = thread_index
              }
            );
      };

      auto start = std::chrono::high_resolution_clock::now();

      for( auto& payload : payloads ) {
        queue.push( thread_index, payload.priority, std::move( payload.item ) );
      }

      auto end = std::chrono::high_resolution_clock::now();

      std::chrono::duration< double > elapsed_seconds = end - start;
      times_per_thread[ thread_index ] = elapsed_seconds.count();

    }; 

    std::thread add_threads[ THREAD_COUNT ];
    for( uint32_t i = 0; i < THREAD_COUNT; i++ ) {
      add_threads[ i ] = std::thread( add_items_fun, i );
    }

    for( uint32_t i = 0; i < THREAD_COUNT; i++ ) {
      add_threads[ i ].join();
    }

    double sum = 0;
    double max = 0;
    for( uint32_t i = 0; i < THREAD_COUNT; i++ ) {
      sum += times_per_thread[ i ];
      max = std::max( max, times_per_thread[ i ] );
    }

    times_per_iteration[ i ] = sum / THREAD_COUNT;
    max_time_per_iteration[ i ] = max;

  }

  double sum = 0;
  for( uint32_t i = 0; i < ITERATIONS; i++ ) {
    sum += times_per_iteration[ i ];
  }

  double sum_max = 0;
  for( uint32_t i = 0; i < ITERATIONS; i++ ) {
    sum_max += max_time_per_iteration[ i ];
  }



  LOG_INFO( "Average time per iteration: %f seconds to add %u items", sum / ITERATIONS, ITEMS_COUNT );
  LOG_INFO( "Average max time it took per iteration: %f seconds to add %u items", sum_max / ITERATIONS, ITEMS_COUNT );

  return 0;

}
