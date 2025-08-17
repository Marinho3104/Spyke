
#include "validation.h"
#include <semaphore.h>


diagnostics::Log_Context::Log_Context() {

  const int sem_init_sts = sem_init( &log_locker, 0, 1 );
  ENSURE( sem_init_sts == 0, "Error in diagnostics log init" );

}
