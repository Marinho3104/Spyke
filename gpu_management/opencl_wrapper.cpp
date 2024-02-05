
/** INCLUDES **/
#include "opencl_wrapper.h"
#include <CL/cl.h>
#include <CL/cl_platform.h>
#include <iostream>


bool spyke::gpu_management::opencl_wrapper::check_opencl_status( cl_int&& status, const char*&& function_name ) {

  if ( status != CL_SUCCESS ) {
  
    std::cout << function_name << " opencl error with code: " << status << std::endl;
    
    return 0;

  }

  return 1; 

}

bool spyke::gpu_management::opencl_wrapper::get_device_info( cl_device_id& device_id, cl_device_info&& device_info, size_t&& parameter_size, void* parameter_value, size_t* parameter_size_ret ) {

  return
    check_opencl_status(
      
        clGetDeviceInfo(
    
          device_id, 
          device_info, 
          parameter_size,
          parameter_value,
          parameter_size_ret

        ),

        "clGetDeviceInfo"
    );

}

bool spyke::gpu_management::opencl_wrapper::get_platforms_count( cl_uint* count ) {

  return
    check_opencl_status( 
    
      clGetPlatformIDs(
        0, 
        nullptr,
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

