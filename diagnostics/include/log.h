
#ifndef DIAGNOSTICS_INCLUDE_LOG_H
#define DIAGNOSTICS_INCLUDE_LOG_H

#include <mutex>
#include <cstdio>


namespace diagnostics {

  inline std::mutex log_mutex;


  #define LOG( type, fmt, ... ) \
    do { \
      std::unique_lock lock( diagnostics::log_mutex ); \
      printf( type ": [%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__ ); \
    } while( 0 ); \

  #define LOG_INFO( fmt, ... ) LOG( "INFO", fmt, ##__VA_ARGS__ )

  #define LOG_SUCCESS( fmt, ... ) LOG( "SUCCESS", fmt, ##__VA_ARGS__ )

  #define LOG_ERROR( fmt, ... ) LOG( "ERROR", fmt, ##__VA_ARGS__ )

} // namespace diagnostics

#endif // DIAGNOSTICS_INCLUDE_LOG_H
