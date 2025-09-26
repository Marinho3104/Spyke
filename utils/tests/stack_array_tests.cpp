
#include <cassert>
#include "stack_array.hpp"

int main() {

  std::array< int, 5 > arr = utils::make_stack_array< int, 5 >( 101 );
  for( int i = 0; i < 5; ++i ) {
    assert( arr[ i ] == 101 );
  }

  return 0;

}
