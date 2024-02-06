
#include <CL/cl.h>
#include "./../../gpu_management/gpu_information.h"
#include "./../../transaction_management_gpu/transaction_management_gpu_configuration.h"
#include "./../../transaction_management_gpu/transaction_management_gpu.h"

int main (int argc, char *argv[]) {

  spyke::gpu_management::Gpu_Information gpu_information = spyke::gpu_management::Gpu_Information();

  if ( ! spyke::gpu_management::Gpu_Information::set_available_information( gpu_information ) ) return 1; 
  spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration config = 
    spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration( gpu_information );

  spyke::transaction_management_gpu::Transaction_Management_Gpu transaction_management_gpu =
    spyke::transaction_management_gpu::Transaction_Management_Gpu( config );

  transaction_management_gpu.setup();

  return 0;

}
