
/** INCLUDES **/
#include "opencl_wrapper.h"
#include <CL/cl.h>
#include <CL/cl_platform.h>
#include <iostream>


bool spyke::gpu_management::opencl_wrapper::check_opencl_status( cl_int status, const char*&& function_name ) {

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

bool spyke::gpu_management::opencl_wrapper::set_context(
  cl_context& context,
  const cl_context_properties* properties, 
  cl_uint& number_devices, 
  const cl_device_id* device_ids,
  void ( CL_CALLBACK* callback )(const char *, const void *, size_t, void *), 
  void* user_data
) {

  // Status
  cl_int status;

  context = 
    clCreateContext(
      
      properties,
      number_devices,
      device_ids,
      callback,
      user_data,
      &status

    );

  return check_opencl_status( status, "clCreateContext" );

}


bool spyke::gpu_management::opencl_wrapper::set_command_queue(
  cl_command_queue& command_queue, 
  cl_context& context, 
  cl_device_id& device, 
  const cl_command_queue_properties* properties 
) {

  // Status
  cl_int status;

  command_queue = 
    clCreateCommandQueueWithProperties(
    
      context,
      device,
      properties,
      &status

    );

  return check_opencl_status( status, "clCreateCommandQueueWithProperties" );
    
}

bool spyke::gpu_management::opencl_wrapper::set_program_with_source(
  cl_program& program, 
  cl_context& context, 
  cl_uint& count, 
  const char**& code, 
  const size_t*& code_lenghts
) {

  // Status
  cl_int status;

  program = 
    clCreateProgramWithSource(

      context,
      count,
      code,
      code_lenghts,
      &status

    );

  return check_opencl_status( status, "clCreateCommandQueueWithProperties" );

}

bool spyke::gpu_management::opencl_wrapper::set_kernel(cl_kernel& kernel, cl_program& program, const char*& name ) {

  // Status
  cl_int status;

  kernel =
    clCreateKernel(

      program,
      name,
      &status

    );

  return check_opencl_status( status, "clCreateKernel" );

}

bool spyke::gpu_management::opencl_wrapper::set_buffer(cl_mem& memory, cl_context& context, const cl_mem_flags&& flags, size_t& size, void* host_pointer ) {

  // Status
  cl_int status;

  memory =
    clCreateBuffer(

      context,
      flags,
      size,
      host_pointer,
      &status

    );

  return check_opencl_status( status, "clCreateBuffer" );  

}

bool spyke::gpu_management::opencl_wrapper::set_kernel_argument(cl_kernel& kernel, cl_uint& index, size_t& size, const void* value ) {
  
  return
    check_opencl_status(
      clSetKernelArg(
      
        kernel,
        index,
        size,
        value

      ),

      "clSetKernelArg"

    );

}

bool spyke::gpu_management::opencl_wrapper::launch_kernel(
  cl_command_queue& command_queue, 
  cl_kernel& kernel, 
  cl_uint work_dimension,
  const size_t* global_work_offset, 
  const size_t * global_work_size, 
  const size_t * local_work_size,
  cl_uint number_events_wait_list,
  const cl_event * events_wait_list,
  cl_event * event
) {

  return
    check_opencl_status(

      clEnqueueNDRangeKernel(
  
        command_queue,
        kernel,
        work_dimension,
        global_work_offset,
        global_work_size,
        local_work_size,
        number_events_wait_list,
        events_wait_list,
        event

      ),

      "clEnqueueNDRangeKernel"

    );

}

bool spyke::gpu_management::opencl_wrapper::launch_kernel_single_thread(
  cl_command_queue& command_queue, 
  cl_kernel& kernel, 
  cl_uint number_events_wait_list,
  const cl_event* events_wait_list,
  cl_event* event
) {

  size_t global_work_size[ 1 ] = { 1 }, local_work_size[ 1 ] = { 1 };

  return 
    check_opencl_status(

      clEnqueueNDRangeKernel(

        command_queue,
        kernel,
        1,
        0,
        global_work_size,
        local_work_size,
        number_events_wait_list,
        events_wait_list,
        event

      ),

      "clEnqueueNDRangeKernel-Single"

    );

}

