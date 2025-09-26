

#ifndef DIAGNOSTICS_INCLUDE_VALIDATION_H_
#define DIAGNOSTICS_INCLUDE_VALIDATION_H_

#include "cstdlib"
#include "log.h"


// If the condition fails it will stop the execution of the program
#define ENSURE( condition, fmt, ... ) \
  if( ! ( condition ) ) { \
    LOG_ERROR( fmt, ##__VA_ARGS__ ); \
    exit( -1 ); \
  } \

// Used to verify code executes in the expected order; 
// aborts in debug builds, ignored in release.
#ifndef RELEASE

  #define CHECK( condition, fmt, ... ) \
    if( ! ( condition ) ) { \
      LOG_ERROR( fmt, ##__VA_ARGS__ ); \
      exit( -1 ); \
    } \

#else

  #define CHECK( condition, fmt, ... ) \

#endif

#endif // DIAGNOSTICS_INCLUDE_VALIDATION_H_
