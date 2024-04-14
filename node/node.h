
/** node.h - Responsible to connect and communicate with other nodes inside the network
 *
 *
**/

#ifndef NODE_NODE_H
#define NODE_NODE_H

  #include "node_configuration.h"
namespace spyke::node {

    // Hold all function and variables about a Node
    struct Node {

      // Initial condifuration given
      Node_Configuration configuration;

      // Given a Node configuration confiure every thing needed for the execution
      Node( Node_Configuration& );

      // Performs the initial setup when the config file is set
      bool setup();


    };


  }

#endif
