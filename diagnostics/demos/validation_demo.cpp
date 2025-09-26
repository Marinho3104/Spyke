
#include "validation.h"

int main () {
 
  ENSURE( 1 == 1, "1 == 1" );
  ENSURE( 1 == 2, "1 == 2" );

  return 0;
}
