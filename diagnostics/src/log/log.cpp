
#include "log.h"
#include <cstdlib>
#include <semaphore.h>
#include <iostream>


diagnostics::Log_Context::Log_Context() {

  const int sem_init_sts = sem_init( &log_locker, 0, 1 );
  if( sem_init_sts != 0 ) {
    std::cout << "Error in diagnostics log init" << std::endl;
    exit( -1 );
  }

}
