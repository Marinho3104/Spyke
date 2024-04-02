
#include <CL/cl.h>
#include "./../../gpu_management/gpu_information.h"
#include "./../../transaction_management_gpu/transaction_management_gpu_configuration.h"
#include "./../../transaction_management_gpu/transaction_management_gpu.h"

int main (int argc, char *argv[]) {

  spyke::gpu_management::Gpu_Information gpu_information = spyke::gpu_management::Gpu_Information();

  if ( ! spyke::gpu_management::Gpu_Information::set_available_information( gpu_information ) ) return 1; 

  size_t number_transactions_pool = 128;

  spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration config = 
    spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration( gpu_information, number_transactions_pool );

  spyke::transaction_management_gpu::Transaction_Management_Gpu transaction_management_gpu =
    spyke::transaction_management_gpu::Transaction_Management_Gpu( config );

  if( ! transaction_management_gpu.setup() ) return 1;

  if ( ! transaction_management_gpu.start() ) return 1;

  while( 1 );

  return 0;

}
