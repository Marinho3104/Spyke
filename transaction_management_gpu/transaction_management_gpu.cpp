
/** INCLUDES **/
#include "transaction_management_defines.h"
#include "transaction_management_gpu.h"
#include "transaction_management_gpu_configuration.h"
#include <CL/cl.h>
#include <CL/cl_platform.h>
#include <cstddef>
#include <iostream>
#include <unistd.h>
#include "./../gpu_management/opencl_wrapper.h"
#include "transaction_management_gpu_data.h"

spyke::transaction_management_gpu::Transaction_Management_Gpu::~Transaction_Management_Gpu() {}

void spyke::transaction_management_gpu::Transaction_Management_Gpu::finalize() { gpu_data.finalize(); }

spyke::transaction_management_gpu::Transaction_Management_Gpu::Transaction_Management_Gpu( 
    spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration& config ) 
      : configuration( config ), gpu_data( Transaction_Management_Gpu_Data( configuration.gpu_information.platforms_count ) ) {}

bool spyke::transaction_management_gpu::Transaction_Management_Gpu::set_deep_configuration() {

  std::cout << "*** Starting deep configuration ***\n" << std::endl;

  // Makes a config for all given platforms
  for ( int _ = 0; _ < configuration.gpu_information.platforms_count; _ ++ ) {

    std::cout << "\tPlatform: " << _ << std::endl;

    // Work item per all devices in use
    size_t work_items = 0;

    // Loops to get all compute units sum of all devices in curret platform
    for ( int __ = 0; __ < configuration.gpu_information.devices_count[ _ ]; __ ++ ) {

      // Max number of single computer units in the device
      cl_uint max_compute_units;

      // Number of work items that can be instatiated in a single work group
      size_t max_work_items_per_work_group;

      if (
        ! spyke::gpu_management::opencl_wrapper::get_device_info(
          configuration.gpu_information.device_ids[ _ ][ __ ],
          CL_DEVICE_MAX_COMPUTE_UNITS, 
          sizeof( cl_uint ), 
          &max_compute_units, 
          0
        ) ||
        ! spyke::gpu_management::opencl_wrapper::get_device_info(
          configuration.gpu_information.device_ids[ _ ][ __ ], 
          CL_DEVICE_MAX_WORK_GROUP_SIZE, 
          sizeof( size_t ), 
          &max_work_items_per_work_group, 
          0
        )
      ) return 0;

      // Add the number of work items 
      work_items += max_compute_units * max_work_items_per_work_group;

      std::cout << "\t\tDevice " << __ << ": " << max_compute_units << " " << max_work_items_per_work_group << std::endl;

    }

    // Set the number of work itens to use, which will be 80% percent of the max calculated prior
    configuration.global_work_items_transaction_proccess[ _ ] = work_items * 4 / 5;

  }

  std::cout << "\n*** Deep configuration done ***\n\n" << std::endl;

  return 1;

}

bool spyke::transaction_management_gpu::Transaction_Management_Gpu::setup() {

  std::cout << "Setup" << std::endl;

  // If no deep config were set, it sets it automatic 
  // trying to get the best performance out of it
  if ( ! configuration.deep_config_set && ! set_deep_configuration() ) return 0;

  // Setup Gpu Data
  return gpu_data.setup( configuration );

}

bool spyke::transaction_management_gpu::Transaction_Management_Gpu::confirmed_transaction( void* transaction_data, unsigned int transaction_data_size ) {

  size_t sizes[] = { 3 };

  // Loop throught out each platform to try and start the threads
  for( int _ = 0; _ < configuration.gpu_information.platforms_count; _++ ) {
  
    cl_mem transaction_data_cl_mem;

    if(

      ! spyke::gpu_management::opencl_wrapper::set_buffer(

        transaction_data_cl_mem,
        gpu_data.contexts[ _ ],
        CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
        transaction_data_size,
        transaction_data

      )

    ) return 0;

    if(

      ! spyke::gpu_management::opencl_wrapper::set_kernel_argument(

        gpu_data.kernels[ _ ][ TRANSACTION_MANAGEMENT_KERNELS_INDEX_TRANSACTION_PROCCESSING ].kernel,
        2,
        sizeof( void* ),
        &transaction_data_cl_mem

      ) ||

      ! spyke::gpu_management::opencl_wrapper::set_kernel_argument(

        gpu_data.kernels[ _ ][ TRANSACTION_MANAGEMENT_KERNELS_INDEX_TRANSACTION_PROCCESSING ].kernel,
        3,
        sizeof( transaction_data_size ),
        &transaction_data_size

      )

    ) return 0;
 
    // Transaction Proccessing kernel
    if (
     ! spyke::gpu_management::opencl_wrapper::launch_kernel(

        gpu_data.main_command_queues[ _ ],
        gpu_data.kernels[ _ ][ TRANSACTION_MANAGEMENT_KERNELS_INDEX_TRANSACTION_PROCCESSING ].kernel,
        1,
        0,
        sizes,
        sizes,
        0,
        0,
        0

      )

    ) return 0;   

  }

  return 1;

}

/*
bool start() {

  std::cout << "*** Starting Kernels ***\n" << std::endl;

  size_t sizes[] = { 2 };

  // Loop throught out each platform to start the kernels
  for( int _ = 0; _ < configuration.gpu_information.platforms_count; _++ ) {

    // Transaction Proccessing kernel
    if (
     ! spyke::gpu_management::opencl_wrapper::launch_kernel(

        gpu_data.main_command_queues[ _ ],
        gpu_data.kernels[ _ ][ TRANSACTION_MANAGEMENT_KERNELS_INDEX_TRANSACTION_PROCCESSING ].kernel,
        1,
        0,
        sizes,
        sizes,
        0,
        0,
        0

      )

    ) return 0;

  }

  std::cout << "*** End Kernels ***\n" << std::endl;

  return 1;

}*/
