
#include "ip_v4.h"
#include "server.h"
#include <cassert>
#include <utility>


int main (int argc, char *argv[]) {

  communication::Ip_V4 ip_v4( 0x7F000001, 8000 );
  communication::Server< communication::Ip_V4 > server( ip_v4, 10 );
  assert( ! server.is_up() );

  assert( server.start() ); assert( server.is_up() );

  communication::Server< communication::Ip_V4 > server2( std::move( server ) );
  assert( ! server.is_up() ); assert( server2.is_up() );
  
  return 0;

}
