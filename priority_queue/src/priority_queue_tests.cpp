
#include "item.h"
#include "priority_queue.h"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <assert.h>

std::unique_ptr< priority_queue::Item > get_item( const char*, const uint32_t& );
void add_pop_simple_test();
void add_pop_complex_test();

int main (int argc, char *argv[]) {

  add_pop_simple_test();
  add_pop_complex_test();
 
  return 0;

}

void add_pop_simple_test() {

  priority_queue::Priority_Queue priority_queue = priority_queue::Priority_Queue( 1, 1 );
  assert( priority_queue.add_item( get_item( "Marinho", 7 ), 0 ) );
  assert( ! priority_queue.add_item( get_item( "Marinho", 7 ), 0 ) );

  std::unique_ptr< priority_queue::Item > popped_item = priority_queue.pop();
  assert( popped_item ); assert( popped_item->get_data_size() == 7 );

  const char* popped_data = ( const char* ) popped_item->get_data().get();
  assert( strncmp( popped_data, "Marinho", 7 ) == 0 );
 
}

void add_pop_complex_test() {

  priority_queue::Priority_Queue priority_queue = priority_queue::Priority_Queue( 5, 3 );
  assert( priority_queue.add_item( get_item( "Marinho", 7 ), 1 ) );
  assert( priority_queue.add_item( get_item( "Mari123", 7 ), 0 ) );

  std::unique_ptr< priority_queue::Item > popped_item = priority_queue.pop();
  assert( popped_item ); assert( popped_item->get_data_size() == 7 );

  const char* popped_data = ( const char* ) popped_item->get_data().get();
  assert( strncmp( popped_data, "Mari123", 7 ) == 0 );
 
  std::unique_ptr< priority_queue::Item > popped_item1 = priority_queue.pop();
  assert( popped_item1 ); assert( popped_item1->get_data_size() == 7 );

  const char* popped_data1 = ( const char* ) popped_item1->get_data().get();
  assert( strncmp( popped_data1, "Marinho", 7 ) == 0 );

}

std::unique_ptr< priority_queue::Item > get_item( const char* item_data, const uint32_t& item_data_size ) {
  std::unique_ptr< uint8_t[] > data_mut = std::make_unique< uint8_t[] >( item_data_size );
  strncpy( ( char* ) data_mut.get(), item_data, item_data_size );
  return std::make_unique< priority_queue::Item >( std::move( data_mut ), item_data_size );
}
