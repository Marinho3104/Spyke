
#include "smart_pointers.hpp"
#include <cassert>
#include <cstdint>


class Test {

  private:

    uint16_t& counter;

  public:

    ~Test() {
      counter--;
    }

    Test( uint16_t& counter ): counter( counter ) {}

};

int main () {
  
  uint16_t counter = 10;
  utils::unique_array_with_args_return_type< Test > rtr = utils::make_unique_array_with_args< Test >( 10, counter );
  rtr.reset();
  assert( counter == 0 );
  
  uint16_t counter2 = 10;
  utils::unique_array_with_args_return_type< Test > rtr2 = utils::make_unique_array_with_args< Test >( 10, counter2 );
  utils::unique_array_with_args_return_type< Test > rtr3 = std::move( rtr2 );
  assert( counter2 == 10 );
  rtr3.reset();
  assert( counter2 == 0 );


  return 0;

}
