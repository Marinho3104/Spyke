
#include <CL/cl.h>
#include "./../../gpu_management/gpu_information.h"
#include "./../../transaction_management_gpu/transaction_management_gpu_configuration.h"
#include "./../../transaction_management_gpu/transaction_management_gpu.h"
#include <cstddef>
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>

int main (int argc, char *argv[]) {

  spyke::gpu_management::Gpu_Information gpu_information = spyke::gpu_management::Gpu_Information();

  if ( ! spyke::gpu_management::Gpu_Information::set_available_information( gpu_information ) ) return 1; 

  spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration config = 
    spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration( gpu_information );

  spyke::transaction_management_gpu::Transaction_Management_Gpu transaction_management_gpu =
    spyke::transaction_management_gpu::Transaction_Management_Gpu( config );

  if( ! transaction_management_gpu.setup() ) return 1;

  unsigned char transaction_data[ 7 ] = { 101, 2, 3, 4, 5, 6, 7 };
  unsigned int transaction_data_size = 7;

  transaction_management_gpu.confirmed_transaction( transaction_data, transaction_data_size );

  transaction_management_gpu.finalize();

  config.finalize();

  return 0;

}
