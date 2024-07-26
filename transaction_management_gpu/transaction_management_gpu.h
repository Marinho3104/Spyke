
/** transaction_management_gpu.h - Responsible for making the setup and cpu control over the gpu processing in Transaction Management
 *
**/

#ifndef SPYKE_TRANSACTION_MANAGEMENT_GPU_H
#define SPYKE_TRANSACTION_MANAGEMENT_GPU_H

/** INCLUDES **/
#include "transaction_management_gpu_configuration.h"
#include "transaction_management_gpu_data.h"


namespace spyke::transaction_management_gpu {

  /* About gpu the configuration will be:
   * Kernel for Processing a transaction
   * Kernel to sinalize to the processing transactions that a new transaction is there to be processed
   * Kernel to get all processed transactions and return them
  */

  struct Transaction_Management_Gpu {

    // Config used for the gpu setup
    Transaction_Management_Gpu_Configuration& configuration;

    // Opencl variables in use
    Transaction_Management_Gpu_Data gpu_data;

    /** FUNCTIONS **/

    // Destructor default
    ~Transaction_Management_Gpu();

    // Frees all memory used
    void finalize();

    // Receives and copy the config for the setup
    Transaction_Management_Gpu( Transaction_Management_Gpu_Configuration& );

    // Makes the deep configuration automatically
    bool set_deep_configuration();

    // Performs the gpu setup according to the given config
    bool setup();

    // Sets up the Processing Transaction Kernel
    bool setup_processing_transaction();

    // Launches the threads used to confirmed a given transaction
    bool confirmed_transaction( void*, unsigned int );

  };

}

#endif
