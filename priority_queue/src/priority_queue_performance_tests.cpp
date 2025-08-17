
#include <vector>
#include "priority_queue.h"
#include <cstdint>
#include <chrono>
#include <log.h>

void single_thread_test( const uint32_t& );

int main () {

  single_thread_test( 10000 );
  
  return 0;

}


void single_thread_test( const uint32_t& items_count ) {

  const uint32_t iterations_count = 150;
  LOG_INFO( "Performing single thread test with %u items!", items_count );

  priority_queue::Priority_Queue queue = priority_queue::Priority_Queue( 1, items_count );
  double time_taken = 0.;
  double time_taken1 = 0.;

  for( uint32_t i = 0; i < iterations_count; i++ ) {

    std::vector<std::unique_ptr<priority_queue::Item>> payloads;
    for( uint32_t i = 0; i < items_count; i++ ) {
      payloads.push_back( std::make_unique< priority_queue::Item >( priority_queue::Item( std::make_unique< uint8_t[] >( 8 ), 8 ) ) );
    }    

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();   

    for( uint32_t i = 0; i < items_count; i++ ) {
        queue.add_item( std::move( payloads[ i ] ), 0 );
    }

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();   

    std::chrono::duration< double > duration = end - start;
    time_taken += duration.count();

    start = std::chrono::high_resolution_clock::now();   

    for( uint32_t j = 0; j < items_count; j++ ) {
      queue.pop().release();
    }

    end = std::chrono::high_resolution_clock::now();   

    duration = end - start;

    time_taken1 += duration.count();

  }


  LOG_INFO( "Average time it took to add %u items: %f seconds", items_count, time_taken / iterations_count);
  LOG_INFO( "Average time it took to remove %u items: %f seconds", items_count, time_taken1 / iterations_count);

}
