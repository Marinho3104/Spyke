
#include "log.h"
#include "test.h"

int main () {
  
  LOG_INFO( "Just information!" );
  LOG_SUCCESS( "Success!" );
  LOG_ERROR( "Error!" );

  LOG_INFO("Value: %u", test::test1())

  return 0;
}
