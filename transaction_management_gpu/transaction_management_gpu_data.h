
/** transaction_management_gpu_data.h - Holds all opencl cl variables related to the Transaction Manafement gpu stuff
 *
**/

#ifndef SPYKE_TRANSACTION_MANAGEMENT_GPU_DATA_H
#define SPYKE_TRANSACTION_MANAGEMENT_GPU_DATA_H

/** INCLUDES **/
#include "transaction_management_gpu_configuration.h"
#include <CL/cl.h>

namespace spyke::transaction_management_gpu {

  // Forward
  struct Kernel;

  struct Transaction_Management_Gpu_Data {

    // Platform count
    size_t platform_count;

    // Context in use
    cl_context* contexts;

    // Main command queue to be used
    cl_command_queue* main_command_queues;
 
    // Acquire command queue to be used for try acquire new thread for new Transaction proccessing
    cl_command_queue* acquire_command_queues;
       
    // Opencl program codes of each part
    const char** program_codes;

    // Opencl programs used for the Transaction Management
    cl_program* programs;

    // Kernels used by the platforms
    // Is a double array cause that is more than one kernel per platform so,
    // the first array is the platform kernels and then each individual kernel inside it is a usable kernel for the 
    // specific platform
    Kernel** kernels;

    /** FUNCTIONS **/
    
    ~Transaction_Management_Gpu_Data();

    // Allocates all memory needed and setups up cl programs codes into variables
    Transaction_Management_Gpu_Data( size_t );

    // Setup all cl programs code
    bool setup_cl_program_code();

    // Setup transaction_proccessing kernel
    bool setup_transaction_proccessing_kernel();

    // Setup acquire_thread kernel
    bool setup_acquire_thread_kernel();

    // Setup all kernels
    bool setup_kernels();

    // Setups up all gpu variables needed for the gpu execution of Transaction Management
    bool setup( Transaction_Management_Gpu_Configuration& );

  };

  // Structure to holds all data refereing a kernel 
  // For a more easy manipulation of the kernel variables
  struct Kernel {

    // Kernel variable
    cl_kernel kernel;

    /** FUNCTIONS **/

    // Destructor
    ~Kernel();

    // Constructor intiates the variables needed given the information provided
    Kernel();

  };

}

#endif
