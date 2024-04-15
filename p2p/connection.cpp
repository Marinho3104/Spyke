
/** INCLUDES **/
#include "connection.h"
#include <cstdlib>


void spyke::p2p::Connection::finalize() { free( hint ); free( ip_connection ); }
