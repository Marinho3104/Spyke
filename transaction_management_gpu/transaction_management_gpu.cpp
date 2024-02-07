
/** INCLUDES **/
#include "transaction_management_gpu.h"
#include "transaction_management_gpu_configuration.h"
#include <CL/cl.h>
#include <CL/cl_platform.h>
#include <cstddef>
#include <iostream>
#include "./../gpu_management/opencl_wrapper.h"

spyke::transaction_management_gpu::Transaction_Management_Gpu::Transaction_Management_Gpu( 
    spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration& config ) : configuration( config ) {}

bool spyke::transaction_management_gpu::Transaction_Management_Gpu::set_deep_configuration() {

  std::cout << "Starting deep configuration:\n" << std::endl;

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

  std::cout << "\nDeep configuration done" << std::endl;

  return 1;

}

bool spyke::transaction_management_gpu::Transaction_Management_Gpu::setup() {

  std::cout << "Setup" << std::endl;

  // If no deep config were set, it sets it automatic 
  // trying to get the best performance out of it
  if ( ! configuration.deep_config_set && set_deep_configuration() ) return 0;

  

  return 1;

}

/*
 *
 *
      cl_uint compute_units, max_work_item_dimensions; 
      size_t max_work_items_per_work_group;

      if (
        ! spyke::gpu_management::opencl_wrapper::get_device_info(
          configuration.gpu_information.device_ids[ _ ][ __ ],
          CL_DEVICE_MAX_COMPUTE_UNITS, 
          sizeof( cl_uint ), 
          &compute_units, 
          0
        ) ||
        ! spyke::gpu_management::opencl_wrapper::get_device_info(
          configuration.gpu_information.device_ids[ _ ][ __ ], 
          CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, 
          sizeof( cl_uint ), 
          &max_work_item_dimensions, 
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

      size_t max_work_item_sizes_per_dimension[ max_work_item_dimensions ];

      if(
        ! spyke::gpu_management::opencl_wrapper::get_device_info(
          configuration.gpu_information.device_ids[ _ ][ __ ], 
          CL_DEVICE_MAX_WORK_ITEM_SIZES, 
          sizeof( size_t ) * max_work_item_dimensions, 
          &max_work_item_sizes_per_dimension,
          0
        )
      ) return 0;

      std::cout << compute_units << " " << max_work_item_dimensions << " " << max_work_items_per_work_group << std::endl;

      for ( int _ = 0; _ < max_work_item_dimensions; _ ++ ) 

        std::cout << max_work_item_sizes_per_dimension[ _ ] << std::endl;
  
      std::cout << "-------" << std::endl;

    }
*/
