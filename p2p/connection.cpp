
/** INCLUDES **/
#include "connection.h"
#include "IP_connection.h"
#include <arpa/inet.h>
#include <cstdint>
#include <cstdlib>
#include <netinet/in.h>
#include <sys/socket.h>


void spyke::p2p::Connection::finalize() { free( hint ); free( ip_connection ); hint = 0; ip_connection = 0; }

bool spyke::p2p::Connection::operator==( Connection& comp ) { return socket == comp.socket; }
