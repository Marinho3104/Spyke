
#include "log.h"

int main () {
  
  LOG_INFO( "Hello %d %s", 12345, "Marinho" );
  LOG_SUCCESS( "Hello %d %s", 12345, "Marinho" );
  LOG_ERROR( "Hello %d %s", 12345, "Marinho" );

  return 0;
}
