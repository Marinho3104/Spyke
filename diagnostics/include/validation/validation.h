
#ifndef INCLUDE_DIAGNOSTICS_VALIDATION_H_
#define INCLUDE_DIAGNOSTICS_VALIDATION_H_

// If the condition fails it will stop the execution of the program
#define ENSURE( condition ) \
  if( ! condition ) { \
    LOG_ERROR( "Error" ); \
    exit( -1 ); \
  } \

// If the condition fails, the program will terminate unless it's a release build.
// In release mode, the error will be signaled through the output file descriptor.
#ifdef RELEASE

  #define VALIDATE( condition ) \
    if( ! condition ) { \
      LOG_ERROR( "ERROR" ); \
    }

#else

  #define VALIDATE( condition ) \
    if( ! condition ) { \
      LOG_ERROR( "Error" ); \
      exit( -1 ); \
    }
  #endif

#endif
