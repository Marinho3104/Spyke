
/** INCLUDES **/
#include "transaction_management_gpu.h"
#include "transaction_management_gpu_configuration.h"
#include <CL/cl.h>
#include <CL/cl_platform.h>
#include <iostream>
#include "./../gpu_management/opencl_wrapper.h"

spyke::transaction_management_gpu::Transaction_Management_Gpu::Transaction_Management_Gpu( 
    spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration& config ) : configuration( config ) {}

bool spyke::transaction_management_gpu::Transaction_Management_Gpu::setup() {

  std::cout << "Setup" << std::endl;

  // If no deep config were set, it sets it automatic 
  // trying to get the best performance out of it
  if ( ! configuration.deep_config_set ) {

    // Makes a config for all given platforms
    for ( int _ = 0; _ < configuration.gpu_information.platforms_count; _ ++ ) {

      // Loops to get all compute units sum of all devices in curret platform
      for ( int __ = 0; __ < configuration.gpu_information.devices_count[ _ ]; __ ++ ) {

        cl_uint compute_units;

        if (
          ! spyke::gpu_management::opencl_wrapper::get_device_info(
            configuration.gpu_information.device_ids[ _ ][ __ ], 
            CL_DEVICE_MAX_COMPUTE_UNITS, 
            sizeof( cl_uint ), 
            &compute_units, 
            0
          )
        ) return 0;

        std::cout << compute_units << std::endl;

      }

    }

  }

  return 1;

}
