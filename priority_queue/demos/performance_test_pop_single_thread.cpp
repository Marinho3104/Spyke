
#include "log.h"
#include "priority_queue.h"
#include "item.h"
#include <array>
#include <cstdint>
#include <cstdlib>
#include <vector>

const uint32_t MAX_PRIORITY = 10;
const uint32_t QUEUE_SIZE = 2 << 4;
const uint32_t ITEMS_COUNT = 10;
const uint32_t ITERATIONS = 1;

struct ItemAndPriority {
  std::unique_ptr< priority_queue::Item > item;
  uint32_t priority;
};

int main () {

  LOG_INFO("*** SINGLE THREAD PERFORMANCE TESTS FOR PUSH ***");

  priority_queue::Priority_Queue< MAX_PRIORITY, 1 > priority_queue = priority_queue::Priority_Queue< MAX_PRIORITY >( QUEUE_SIZE );
  std::srand(std::time(nullptr));

  double times_per_iteration[ ITERATIONS ] = { 0 };

  for( uint32_t i = 0; i < ITERATIONS; i++ ) {

    std::vector< ItemAndPriority > payloads;
    for( uint32_t i = 0; i < ITEMS_COUNT; i++ ) {
      priority_queue.push( 0, std::rand() % MAX_PRIORITY, std::make_unique< priority_queue::Item >( std::make_unique< uint8_t[] >( 8 ), 8 ) );
    };

    auto start = std::chrono::high_resolution_clock::now();

    std::array< priority_queue::Item, 1 > pop_queue;
    priority_queue.pop < 1 >( pop_queue );

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration< double > elapsed_seconds = end - start;
    times_per_iteration[ i ] = elapsed_seconds.count();

  }

  double sum = 0;
  for( uint32_t i = 0; i < ITERATIONS; i++ ) {
    sum += times_per_iteration[ i ];
  }

  LOG_INFO( "Average time per iteration: %f seconds to add %u items", sum / ITERATIONS, ITEMS_COUNT );

  return 0;

}
