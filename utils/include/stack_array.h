
#ifndef UTILS_INCLUDE_STACK_ARRAY_H_
#define UTILS_INCLUDE_STACK_ARRAY_H_

#include <array>
#include <cstddef>
#include <cstdint>


namespace utils {

  namespace {
  
    template< typename T, uint8_t N, typename... Args, size_t... I >
    std::array< T, N > make_stack_array_helper( std::index_sequence< I... >, Args&&... args ) noexcept {
      return { ((void)I, T( std::forward< Args >( args )... ))... };
    }

  }

  template< typename T, uint8_t N, typename... Args, size_t... I >
  std::array< T, N > make_stack_array( Args&&... args ) noexcept {
    return make_stack_array_helper< T, N >( std::make_index_sequence< N >(), std::forward< Args >( args )... );
  }

} // namespace utils

#endif
