

#include "connection.h"
#include "ip_v4.h"
#include <cassert>

int main (int argc, char *argv[]) {

  communication::Ip_V4 ip( 0x7F000001, 1234 );

  communication::Connection< communication::Ip_V4 > connection( ip );
  assert( ! connection.is_connected() );
  assert( ! connection.connect() );

  return 0;

}
