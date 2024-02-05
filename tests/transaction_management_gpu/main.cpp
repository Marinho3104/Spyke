
#include <CL/cl.h>
#include "./../../gpu_management/gpu_information.h"
#include "./../../transaction_management_gpu/transaction_management_gpu_configuration.h"
#include "./../../transaction_management_gpu/transaction_management_gpu.h"
#include <iostream>
#include "./../../gpu_management/opencl_wrapper.h"

int main (int argc, char *argv[]) {

  cl_uint t;

  spyke::gpu_management::opencl_wrapper::get_platforms_count( &t );

  std::cout << t << std::endl;

  return 0;

  spyke::gpu_management::Gpu_Information gpu_information = spyke::gpu_management::Gpu_Information();

  if ( ! spyke::gpu_management::Gpu_Information::set_available_information( gpu_information ) ) return 1; 
  spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration config = 
    spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration( gpu_information );

  spyke::transaction_management_gpu::Transaction_Management_Gpu transaction_management_gpu =
    spyke::transaction_management_gpu::Transaction_Management_Gpu( config );

  transaction_management_gpu.setup();

  return 0;

}
