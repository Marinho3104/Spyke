

// #include "./../../gpu_management/gpu_management.h"
#include <CL/cl.h>
#include <CL/cl_platform.h>
#include "./../../gpu_management/opencl_wrapper.h"
#include <iostream>


void opencl_wrapper();

int main (int argc, char *argv[]) {

  opencl_wrapper();

  return 0;

}

void opencl_wrapper() {

  // Get count of platforms number
  cl_uint platforms_count; spyke::gpu_management::opencl_wrapper::get_platforms_count( &platforms_count );

  // Platforms Ids
  cl_platform_id platform_ids[ platforms_count ]; spyke::gpu_management::opencl_wrapper::get_platform_ids( platform_ids, platforms_count );

  // Loop throught each platform
  for ( int _ = 0; _ < platforms_count; _++ ) {

    // Device Ids count
    cl_uint count_devices; spyke::gpu_management::opencl_wrapper::get_devices_count(platform_ids[ _ ], CL_DEVICE_TYPE_GPU, &count_devices );

    std::cout << count_devices << std::endl;

  }

}
