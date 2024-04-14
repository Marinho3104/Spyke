

/** INCLUDES **/
#include "node.h"
#include "node_configuration.h"
#include <iostream>

spyke::node::Node::Node( spyke::node::Node_Configuration& configuration ) : configuration( configuration ) {

    std::cout << "Node constructor" << std::endl;

}

bool spyke::node::Node::setup() {

  

  // Everything works fine
  return 1;

}
