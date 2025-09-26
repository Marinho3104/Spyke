
#ifndef UTILS_INCLUDE_SMART_POINTERS_H_
#define UTILS_INCLUDE_SMART_POINTERS_H_

#include <cstdint>
#include <memory>


namespace utils {

  template< typename T >
  struct Unique_Array_Deleter {

    private:

      uint64_t array_size_mut;

    public:

      Unique_Array_Deleter() : array_size_mut( 0 ) {}

      Unique_Array_Deleter( const uint64_t& array_size ) : array_size_mut( array_size ) {}

      Unique_Array_Deleter( const Unique_Array_Deleter& ) = default;

      Unique_Array_Deleter& operator=( Unique_Array_Deleter&& other ) = default;

      void operator()( T* ptr_mut ) {
      
        for( uint64_t _ = 0; _ < array_size_mut; _++ ) {
          ptr_mut[ _ ].~T();
        }

        ::operator delete[]( ptr_mut );

      }

  };

  template< typename T, typename... CONSTRUCTOR_ARGS >
  std::unique_ptr< T[], Unique_Array_Deleter< T > > make_unique_array_with_args( const uint64_t& array_size, CONSTRUCTOR_ARGS&&... constructor_args ) {

    void* ptr_raw_mut = ::operator new[]( sizeof( T ) * array_size );
    T* ptr_mut = static_cast< T* >( ptr_raw_mut );

    for( uint64_t _ = 0; _ < array_size; _++ ) {
      new( &ptr_mut[ _ ] ) T( std::forward< CONSTRUCTOR_ARGS >( constructor_args )... );
    }

    return std::unique_ptr< T[], Unique_Array_Deleter< T > >( ptr_mut, Unique_Array_Deleter< T >( array_size ) );

  }

  template< typename T >
  using unique_array_with_args_return_type = std::unique_ptr< T[], Unique_Array_Deleter< T > >;

}; // namespace utils

#endif // UTILS_INCLUDE_SMART_POINTERS_H_
