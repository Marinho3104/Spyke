
#include "item.h"
#include "priority_queue.h"
#include <cassert>
#include <cstdint>
#include <log.h>
#include <thread>
#include "worker.h"
#include "manager.h"

void single_thread_normal_test();
void multi_thread_normal_test();

int main () {
 
  single_thread_normal_test();
  multi_thread_normal_test();

  return 0;

}

void single_thread_normal_test() {

  priority_queue::Priority_Queue queue = priority_queue::Priority_Queue( 10, 1000 );
  queue.activate();

  for( uint32_t i = 0; i < 10; i++ ) {
    for( uint32_t j = 0; j < 100; j++ ) {
      std::unique_ptr< uint8_t[] > item_content = std::make_unique< uint8_t[] >( 8 );

      reinterpret_cast< uint32_t* >( item_content.get() )[ 0 ] = i;
      reinterpret_cast< uint32_t* >( item_content.get() )[ 1 ] = j;

      std::unique_ptr< priority_queue::Item > item = std::make_unique< priority_queue::Item >( std::move( item_content ), 8 );
      assert( queue.add_item( std::move( item ), i ) );

    }
  }

  // std::unique_ptr< uint8_t[] > item_content = std::make_unique< uint8_t[] >( 5 );
  // std::unique_ptr< priority_queue::Item > item = std::make_unique< priority_queue::Item >( std::move( item_content ), 5 );
  // assert( ! queue.add_item( std::move( item ), 0 ) );
  //
  // for( uint32_t i = 0; i < 10; i++ ) {
  //   for( uint32_t j = 0; j < 100; j++ ) {
  //     std::unique_ptr< priority_queue::Item > item = queue.pop();
  //     assert( item->data_size == 8 );
  //     assert( reinterpret_cast< const uint32_t* >( item->get_data() )[ 0 ] == i );
  //     assert( reinterpret_cast< const uint32_t* >( item->get_data() )[ 1 ] == j );
  //   }
  // }

}


class Custom_Worker: public priority_queue::Worker {

  public: 

  Custom_Worker( priority_queue::Priority_Queue& queue_mut ) noexcept : Worker( queue_mut ) {}
  
  void handle( const uint8_t*, const uint32_t& ) noexcept override {}

};

void multi_thread_normal_test() {

  priority_queue::Priority_Queue queue = priority_queue::Priority_Queue( 10, 1000 );
  priority_queue::Manager< Custom_Worker, 10 > workers = priority_queue::Manager< Custom_Worker, 10 >( std::move( queue ) );
  std::thread( &priority_queue::Manager< Custom_Worker, 10 >::start, &workers ).detach();

  std::this_thread::sleep_for( std::chrono::seconds( 5 ) );

  while(1) {

    std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
    workers.seal_priority_queue();
    LOG_INFO("Priority queue sealed...")
    break;

  }

}
