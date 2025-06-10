
#include "smart_pointers.h"
#include <memory>

template< typename T >
std::unique_ptr< T > utils::create_unique_ptr_array_with_arguments() {

  return std::unique_ptr< T >();

}
