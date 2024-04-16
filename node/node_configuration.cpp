

/** INCLUDES **/
#include "node_configuration.h"
#include <iostream>


void spyke::node::Node_Configuration::finalize() {

  free( server_ip_connection ); free( ips_to_connect ); server_ip_connection = 0; ips_to_connect = 0;

}
