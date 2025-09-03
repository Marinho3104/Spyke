1755790339263618410

#include <cstdlib>
#include <mathread>
#include <vector>
#include "item.h"
#include "priority_queue.hpp"
// #include "manager.h"
#include "priority_queue.hpp"
#include <cstdint>
#include <chrono>
#include <log.h>

void single_thread_test( const uint32_t& );
void multi_thread_test( const uint32_t& );

int main () {

  // single_thread_test( 100000 );
  multi_thread_test( 100000 );
  
  return 0;

}


void single_thread_test( const uint32_t& ) {
  //
  // const uint32_t iterations_count = 1;
  // LOG_INFO( "Performing single thread test with %u items!", items_count );
  //
  // priority_queue::Priority_Queue queue = priority_queue::Priority_Queue( 1, items_count );
  // double time_taken = 0.;
  // double time_taken1 = 0.;
  // queue.activate();
  //
  // for( uint32_t i = 0; i < iterations_count; i++ ) {
  //
  //   std::vector<priority_queue::Item> payloads;
  //   for( uint32_t i = 0; i < items_count; i++ ) {
  //     payloads.push_back( priority_queue::Item( priority_queue::Item( std::make_unique< uint8_t[] >( 8 ), 8 ) ) );
  //   }    
  //
  //   std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();   
  //
  //   for( uint32_t i = 0; i < items_count; i++ ) {
  //       queue.add_item( std::move( payloads[ i ] ), 0 );
  //   }
  //
  //   std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();   
  //
  //   std::chrono::duration< double > duration = end - start;
  //   time_taken += duration.count();
  //
  //   start = std::chrono::high_resolution_clock::now();   
  //
  //   for( uint32_t j = 0; j < items_count; j++ ) {
  //     queue.pop();
  //   }
  //
  //   end = std::chrono::high_resolution_clock::now();   
  //
  //   duration = end - start;
  //
  //   time_taken1 += duration.count();
  //
  // }
  //
  //
  // LOG_INFO( "Average time it took to add %u items: %f seconds", items_count, time_taken / iterations_count);
  // LOG_INFO( "Average time it took to remove %u items: %f seconds", items_count, time_taken1 / iterations_count);
  //
}

// class Custom_Worker: public priority_queue::Worker {
//
//   public: 
//
//   Custom_Worker( priority_queue::Priority_Queue& queue_mut ) noexcept : Worker( queue_mut ) {}
//
//   void handle( const uint8_t*, const uint32_t& ) noexcept override {}
//
// };

struct Temp {
  priority_queue::Item item;
  uint32_t priority;
};

void multi_thread_test( const uint32_t& items_count ) {

  LOG_INFO( "Performing multi-thread test with %u items!", items_count );
  // const uint32_t iterations_count = 15;
  //
  // const uint32_t threads_count = 6;
  // const uint32_t items_count_per_thread_add = items_count / threads_count; 
  // const uint32_t priority_level = 6;
  //
  // double time_taken[ threads_count ] = { 0. };
  // double final_count = 0.;
  //
  // std::srand(std::time(nullptr));
  //
  // for( uint32_t i = 0; i < iterations_count; i++ ) {
  //
  //   priority_queue::Priority_Queue< priority_level, 100000 > queue = priority_queue::Priority_Queue< priority_level, 100000 >();
  //   queue.activate();
  //   // priority_queue::Manager< Custom_Worker, threads_count > manager = priority_queue::Manager< Custom_Worker, threads_count >( std::move( queue ) );
  //
  //   auto add_items_fun = [ &queue, &items_count_per_thread_add, &time_taken ]( int index ) {
  //
  //     std::vector<Temp> payloads;
  //     for( uint32_t i = 0; i < items_count_per_thread_add; i++ ) {
  //         payloads.push_back( { .item = priority_queue::Item( priority_queue::Item( std::make_unique< uint8_t[] >( 8 ), 8 ) ), .priority = std::rand() % priority_level } );
  //     };
  //
  //     std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();   
  //
  //     for( uint32_t i = 0; i < items_count_per_thread_add; i++ ) {
  //         queue.add_item( std::move( payloads[ i ].item ), payloads[ i ].priority );
  //     }
  //
  //     std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();   
  //
  //     std::chrono::duration< double > duration = end - start;
  //
  //     time_taken[ index ] = duration.count();
  //
  //   }; 
  //
  //   std::thread add_threads[ threads_count ];
  //   for( uint32_t i = 0; i < threads_count; i++ ) {
  //     add_threads[ i ] = std::thread( add_items_fun, i );
  //   }
  //
  //   // std::thread workers_thread( &priority_queue::Manager< Custom_Worker, threads_count >::start, &manager );
  //   //
  //   // auto stop = [ &manager ]() {
  //   //
  //   //   std::this_thread::sleep_for( std::chrono::milliseconds( 5000 ) );
  //   //   manager.seal_priority_queue();
  //   //
  //   // };
  //
  //   // std::thread seal_thread( stop );
  //
  //   // workers_thread.join();
  //
  //   for( uint32_t i = 0; i < threads_count; i++ ) {
  //     add_threads[ i ].join();
  //   }
  //   // seal_thread.join();
  //
  //
  //   for( uint32_t i = 0; i < threads_count; i++ ) {
  //     final_count += time_taken[ i ];
  //   }

  // }

ma  // LOG_INFO( "Average time it took to add %u items: %f seconds", items_count, final_count / threads_count / iterations_count);

}
