
#ifndef INCLUDE_DIAGNOSTICS_LOG_H_
#define INCLUDE_DIAGNOSTICS_LOG_H_

#include <semaphore.h>
#include <cstdio>

namespace diagnostics {

  struct Log_Context {

    sem_t log_locker;

    public:

      Log_Context();

  };

  static diagnostics::Log_Context log_context;

}

#define LOG( type, fmt, ... ) \
  do { \
    sem_wait( &diagnostics::log_context.log_locker ); \
    printf( type ": [%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__ ); \
    sem_post( &diagnostics::log_context.log_locker ); \
  } while( 0 ); \


#define LOG_INFO( fmt, ... ) LOG( "INFO", fmt, ##__VA_ARGS__ )

#define LOG_SUCCESS( fmt, ... ) LOG( "SUCCESS", fmt, ##__VA_ARGS__ )

#define LOG_ERROR( fmt, ... ) LOG( "ERROR", fmt, ##__VA_ARGS__ )

#endif // INCLUDE_DIAGNOSTICS_LOG_H_
