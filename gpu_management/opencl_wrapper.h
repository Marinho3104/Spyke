
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
  bool check_opencl_status( cl_int, const char*&& );

  // Sets the given argument with the device information  requested
  // returns true if all successed, or false otherwise
  bool get_device_info( cl_device_id&, cl_device_info&&, size_t&&, void*, size_t* );

  // Sets the given argument with the number of platforms available to use,
  // returns true if all successed, or false ortherwise
  bool get_platforms_count( cl_uint* );

  // Sets the given argument with the platforms IDs specific from each one available
  // returns true if all successed, or false ortherwise
  bool get_platform_ids( cl_platform_id*, const cl_uint& );

  // Sets the given argument with the number of devices in a given platform
  // returns true if all successed, or false otherwise
  bool get_devices_count( cl_platform_id&, cl_device_type&&, cl_uint* );
 
  // Sets the given argument with the device IDs specific from the given platform
  // returns true if all successed, or false ortherwise
  bool get_device_ids( cl_platform_id&, cl_device_type&&, const cl_uint&, cl_device_id* );

  // Sets the given argument with a new created context for the given device ids
  // returns true if all successed, or false ortherwise
  bool set_context( cl_context&, const cl_context_properties*, cl_uint&, const cl_device_id*, void ( CL_CALLBACK* )( const char*, const void*, size_t, void* ), void* );

  // Sets the given argument with a new created command queue for a given device id
  // returns true if all successed, or false ortherwise
  bool set_command_queue( cl_command_queue&, cl_context&, cl_device_id&, const cl_command_queue_properties* );

  // Sets the given argument with a new created program from a given source
  // returns true if all successed, or false otherwise
  bool set_program_with_source( cl_program&, cl_context&, cl_uint&, const char**&, const size_t*& );
  
  // Builds a given successful program
  // returns true if all successed, or false otherwise
  bool build_program( cl_program&, cl_uint&, const cl_device_id*, const char*, void ( CL_CALLBACK* )(cl_program, void* ), void* );

  //  Sets the given argument with a new created kernel with the given program in innit
  // returns true if all successed, or false otherwise
  bool set_kernel( cl_kernel&, cl_program&, const char*& );

  // Sets the given argument with a new created buffer for the given context and with the given value
  // returns true if all successed, or false otherwise
  bool set_buffer( cl_mem&, cl_context&, const cl_mem_flags&&, size_t, void* );

  // Sets a new argument for the given kernel
  // returns true if all successed, or false otherwise
  bool set_kernel_argument( cl_kernel&, cl_uint, size_t, const void* );

  // Launches a given kernel with specification given
  // returns true if all successed, or false otherwise
  bool launch_kernel( cl_command_queue&, cl_kernel&, cl_uint, const size_t*, const size_t*, const size_t*, cl_uint, const cl_event*, cl_event* );

  // Launches a single thread of a given kernel
  // returns true if all successed, or false otherwise
  bool launch_kernel_single_thread( cl_command_queue&, cl_kernel&, cl_uint, const cl_event*, cl_event* );

}

#endif
