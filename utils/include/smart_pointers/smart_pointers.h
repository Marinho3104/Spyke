
#ifndef INCLUDE_UTILS_SMART_POINTERS_H_
#define INCLUDE_UTILS_SMART_POINTERS_H_

#include <memory>

namespace utils {

  template< typename T, typename... CONSTRUCTOR_ARGS >
  std::unique_ptr< T[] > create_unique_ptr_array_with_arguments( const uint16_t& );

}

#include "smart_pointers.hpp"

#endif
