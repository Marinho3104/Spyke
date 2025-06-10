
#include <cstdint>
#include <cstdlib>
#include <memory>


namespace utils {


  template< typename T, typename... CONSTRUCTOR_ARGS >
  std::unique_ptr< T > create_unique_ptr_array_with_arguments( const uint16_t& array_size, const CONSTRUCTOR_ARGS&... constructor_args ) {

    const auto unique_ptr_delete = []( T* t ) {
      delete t;
    };

    void* ptr_raw_mut = malloc( sizeof( T ) * array_size );
    T* ptr_mut = static_cast< T* >( ptr_raw_mut );

    for( int _ = 0; _ < array_size; _++ ) {
      new( &ptr_mut[ _ ] ) T( constructor_args... );
    }


    return std::unique_ptr< T[], decltype( unique_ptr_delete ) >( ptr_mut,unique_ptr_delete );

  }

}
