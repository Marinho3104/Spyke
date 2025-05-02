
#include "ip_v4.h"
#include "server.h"
#include <cassert>
#include <utility>

void general_tests( void );
void server_connection_test( void );

int main (int argc, char *argv[]) {

  general_tests();
  server_connection_test();

  return 0;

}

void general_tests( void ) {
  
  communication::Ip_V4 ip_v4( 0x7F000001, 8000 );
  communication::Server< communication::Ip_V4 > server( ip_v4, 10 );
  communication::Server< communication::Ip_V4 > server3( ip_v4, 10 );
  assert( server == server3 ); assert( ! server.is_up() ); assert( ! server3.is_up() );

  assert( server.start() ); assert( server.is_up() );

  communication::Server< communication::Ip_V4 > server2( std::move( server ) );
  assert( ! server.is_up() ); assert( server2.is_up() );

}

void server_connection_test( void ) {
  
  const communication::Ip_V4 ip_v4( 0x7F000001, 8001 );
  communication::Server< communication::Ip_V4 > server_mut( ip_v4, 10 );
  assert( ! server_mut.is_up() ); assert( server_mut.start() ); assert( server_mut.is_up() );

  communication::Connection< communication::Ip_V4 > connection_mut( ip_v4 );
  assert( connection_mut.connect() ); assert( connection_mut.is_connected() );

  communication::Connection< communication::Ip_V4 > accepted_connection_mut = server_mut.accept_new_connection_request();
  assert( accepted_connection_mut.is_connected() );

  connection_mut.~Connection();

}