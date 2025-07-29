
#include "item.h"
#include "priority_queue.h"
#include <cassert>
#include <cstdint>
#include <log.h>
#include <memory>
#include <utility>

void single_thread_normal_test();

int main () {
 
  single_thread_normal_test();

  return 0;

}

void single_thread_normal_test() {

  priority_queue::Priority_Queue queue = priority_queue::Priority_Queue( 10, 1000 );

  for( uint32_t i = 0; i < 10; i++ ) {
    for( uint32_t j = 0; j < 100; j++ ) {
      std::unique_ptr< uint8_t[] > item_content = std::make_unique< uint8_t[] >( 8 );

      reinterpret_cast< uint32_t* >( item_content.get() )[ 0 ] = i;
      reinterpret_cast< uint32_t* >( item_content.get() )[ 1 ] = j;

      std::unique_ptr< priority_queue::Item > item = std::make_unique< priority_queue::Item >( priority_queue::Item( std::move( item_content ), 8 ) );
      assert( queue.add_item( std::move( item ), i ) );

    }
  }

  std::unique_ptr< priority_queue::Item > item = std::make_unique< priority_queue::Item >( priority_queue::Item( std::make_unique< uint8_t[] >( 5 ), 5 ) );
  assert( ! queue.add_item( std::move( item ), 0 ) );

  for( uint32_t i = 0; i < 10; i++ ) {
    for( uint32_t j = 0; j < 100; j++ ) {
      std::unique_ptr< priority_queue::Item > item = queue.pop();
      assert( item->get_data_size() == 8 );
      assert( reinterpret_cast< uint32_t* >( item->get_data().get() )[ 0 ] == i );
      assert( reinterpret_cast< uint32_t* >( item->get_data().get() )[ 1 ] == j );
    }
  }

}
