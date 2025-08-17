
#ifndef INCLUDE_DIAGNOSTICS_VALIDATION_H_
#define INCLUDE_DIAGNOSTICS_VALIDATION_H_

#include "cstdlib"
#include "log.h"

// If the condition fails it will stop the execution of the program
#define ENSURE( condition, fmt, ... ) \
  if( ! ( condition ) ) { \
    LOG_ERROR( fmt, ##__VA_ARGS__ ); \
    exit( -1 ); \
  } \

// If the condition fails, the program will terminate unless it's a release build.
// this function is only used to confirm code flow
#ifdef RELEASE

  #define CHECK( condition, fmt, ... )

#else

  #define CHECK( condition, fmt, ... ) \
    if( ! ( condition ) ) { \
      LOG_ERROR( fmt, ##__VA_ARGS__ ); \
      exit( -1 ); \
    }
  #endif

#endif
