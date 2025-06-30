
#include "log.h"
#include "validation.h"
#include <iostream>

int main (int argc, char *argv[]) {
  
  LOG_INFO( "Hello %d %s", 12345, "Marinho" );
  LOG_SUCCESS( "Hello %d %s", 12345, "Marinho" );
  LOG_ERROR( "Hello %d %s", 12345, "Marinho" );

  ENSURE( 1 );
  VALIDATE( 0 );

  return 0;
}
