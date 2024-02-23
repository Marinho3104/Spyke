
/** transaction_management_gpu_data.h - Holds all opencl cl variables related to the Transaction Manafement gpu stuff
 *
**/

#ifndef SPYKE_TRANSACTION_MANAGEMENT_GPU_DATA_H
#define SPYKE_TRANSACTION_MANAGEMENT_GPU_DATA_H

/** INCLUDES **/
#include "transaction_management_gpu_configuration.h"
#include <CL/cl.h>

namespace spyke::transaction_management_gpu {

  struct Transaction_Management_Gpu_Data {

    // Platform count
    size_t platform_count;

    // Context in use
    cl_context* contexts;

    // Main command queue to be used
    cl_command_queue* main_command_queues;

    /** FUNCTIONS **/

    ~Transaction_Management_Gpu_Data();

    Transaction_Management_Gpu_Data( size_t );

    bool setup( Transaction_Management_Gpu_Configuration& );

    

  };

}

#endif
