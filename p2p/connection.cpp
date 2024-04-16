
/** INCLUDES **/
#include "connection.h"
#include <cstdlib>


void spyke::p2p::Connection::finalize() { free( hint ); free( ip_connection ); hint = 0; ip_connection = 0; }

bool spyke::p2p::Connection::operator==( Connection& comp ) { return socket == comp.socket; }
