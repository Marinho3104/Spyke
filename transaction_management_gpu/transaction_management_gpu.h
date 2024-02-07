
/** transaction_management_gpu.h - Responsible for making the setup and cpu control over the gpu proccessing in Transaction Management
 *
**/

#ifndef SPYKE_TRANSACTION_MANAGEMENT_GPU_H
#define SPYKE_TRANSACTION_MANAGEMENT_GPU_H

/** INCLUDES **/
#include "transaction_management_gpu_configuration.h"


namespace spyke::transaction_management_gpu {

  /* About gpu the configuration will be:
   * Kernel for Proccessing a transaction
   * Kernel to sinalize to the proccessing transactions that a new transaction is there to be proccessed
   * Kernel to get all proccessed transactions and return them
  */

  struct Transaction_Management_Gpu {

    // Config used for the gpu setup
    Transaction_Management_Gpu_Configuration& configuration;

    /** FUNCTIONS **/

    // Receives and copy the config for the setup
    Transaction_Management_Gpu( Transaction_Management_Gpu_Configuration& );

    // Makes the deep configuration automaticly
    bool set_deep_configuration();

    // Performs the gpu setup according to the given config
    bool setup();

    // Sets up the Proccessing Transaction Kernel
    bool setup_proccessing_transaction();

  };

}

#endif
