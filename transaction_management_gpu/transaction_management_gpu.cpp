
/** INCLUDES **/
#include "transaction_management_defines.h"
#include "transaction_management_gpu.h"
#include "transaction_management_gpu_configuration.h"
#include <CL/cl.h>
#include <CL/cl_platform.h>
#include <cstddef>
#include <iostream>
#include "./../gpu_management/opencl_wrapper.h"
#include "transaction_management_gpu_data.h"

spyke::transaction_management_gpu::Transaction_Management_Gpu::~Transaction_Management_Gpu() {}

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

bool spyke::transaction_management_gpu::Transaction_Management_Gpu::start() {

  std::cout << "*** Starting Kernels ***\n" << std::endl;

  size_t sizes[] = { 1 };

  // Loop throught out each platform to start the kernels
  for( int _ = 0; _ < configuration.gpu_information.platforms_count; _++ ) {

    // Transaction Proccessing kernel
    if (

      ! spyke::gpu_management::opencl_wrapper::launch_kernel(

        gpu_data.main_command_queues[ _ ],
        gpu_data.kernels[ _ ][ TRANSACTION_MANAGEMENT_KERNELS_INDEX_TRANSACTION_PROCCESSING ].kernel,
        1,
        0,
        configuration.global_work_items_transaction_proccess,
        sizes,
        0,
        0,
        0

      ) 

    ) return 0;

  }

  std::cout << "*** End Kernels ***\n" << std::endl;

  return 1;

}
