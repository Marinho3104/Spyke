
/** opencl_wrapper.h - A simple wrapper for all opencl api functions to more easily interact with the api and GPU hardware
 * Always confirm if any errors occur during the function execution
**/

#ifndef SPYKE_GPU_MANAGEMENT_OPENCL_WRAPPER_H
#define SPYKE_GPU_MANAGEMENT_OPENCL_WRAPPER_H

/** INCLUDES **/
#include <CL/cl.h>
#include <CL/cl_platform.h>
#include <cstdint>

namespace spyke::gpu_management::opencl_wrapper {
  
  // Only function that dont interact with the api directly, and its duty is to confirm if the 
  // opencl function status as any error and if so handle it
  bool check_opencl_status( int32_t&&, const char*&& );

  // Sets the given argument with the number of platforms available to use,
  // returns true if all successed, or false ortherwise
  bool get_platforms_count( cl_uint* );

  // Sets the given argument with the platforms IDs specific from each one available
  // returns true if all successed, or false ortherwise
  bool get_platform_ids( cl_platform_id*, const cl_uint& );

  // Sets the given argument with the number of devices in a given platform
  // returns true if all successed, or false otherwise
  bool get_devices_count( cl_platform_id&, cl_device_type&&, cl_uint* );
  
}

#endif
