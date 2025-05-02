
#include "socket_helper.h"
#include <unistd.h>

const bool communication::close_socket( const int& file_descriptor ) {
  return close( file_descriptor ) == 0;
}
