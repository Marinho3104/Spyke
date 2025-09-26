
#include <cassert>
#include "smart_pointers.hpp"

int main() {

  utils::unique_array_with_args_return_type< int > arr = utils::make_unique_array_with_args< int >( 100000, 101 );
  for( int i = 0; i < 100000; ++i ) {
    assert( arr[ i ] == 101 );
  }

  return 0;

}
