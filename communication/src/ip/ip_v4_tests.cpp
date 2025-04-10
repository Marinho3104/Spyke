
#include "ip_v4.h"
#include <cassert>


int main( int argc, char *argv[] ) {
 
  const communication::Ip_V4 ip;
  assert( ! ip.is_valid() );

  const communication::Ip_V4 ip1( 0xFC000001, 8000 );
  const communication::Ip_V4 ip2( 0xFC000001, 8000 );
  assert( ip1.is_valid() && ip2.is_valid() );
  assert( ip1 == ip2 );

  const communication::Ip_V4 ip3( 0xFC000001, 8000 );
  const communication::Ip_V4 ip4( 0xabcdef01, 8001 );
  assert( ip3.is_valid() && ip4.is_valid() );
  assert( ip3 != ip4 );

  return 0;

}
