
/** INCLUDES **/
#include "opencl_wrapper.h"
#include <CL/cl.h>
#include <CL/cl_platform.h>
#include <iostream>


bool spyke::gpu_management::opencl_wrapper::check_opencl_status( int32_t&& status, const char*&& function_name ) {

  if ( status != CL_SUCCESS ) {
  
    std::cout << function_name << " opencl error with code: " << status << std::endl;

    return 1;

  }

  return 0; 

}

bool spyke::gpu_management::opencl_wrapper::get_platforms_count( cl_uint* count ) {

  return
    check_opencl_status( 
    
      clGetPlatformIDs(
        0, 
        0,
        count
      ), 

      "clGetPlatformIDs" 
  
    );

}

bool spyke::gpu_management::opencl_wrapper::get_platform_ids( cl_platform_id* platform_ids, const cl_uint& platforms_count ) {

  return 
    check_opencl_status(

      clGetPlatformIDs(

        platforms_count,
        platform_ids,
        NULL

      ),

      "clGetPlatformIDs"

    );

}

bool spyke::gpu_management::opencl_wrapper::get_devices_count( cl_platform_id& platform_id, cl_device_type&& device_type, cl_uint* count ) {

  return
    check_opencl_status(

      clGetDeviceIDs(
      
        platform_id,
        device_type,
        0, 0,
        count

      ),

      "clGetDeviceIDs"

    );

}

bool spyke::gpu_management::opencl_wrapper::get_device_ids( cl_platform_id& platform_id, cl_device_type&& device_type, const cl_uint& count, cl_device_id* device_ids ) {

  return 
    check_opencl_status(

      clGetDeviceIDs(
      
        platform_id,
        device_type,
        count,
        device_ids,
        NULL

      ),

      "clGetDeviceIDs"

    );
  
}

