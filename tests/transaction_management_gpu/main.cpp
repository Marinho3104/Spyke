
#include "./../../transaction_management_gpu/transaction_management_gpu.h"
#include "./../../transaction_management_gpu/transaction_management_gpu_user_configuration.h"


int main (int argc, char *argv[]) {

  // Config used for the transaction management setup
  spyke::transaction_management_gpu::Transaction_Management_Gpu_User_Configuration config = 
    spyke::transaction_management_gpu::Transaction_Management_Gpu_User_Configuration();

  // Gpu config for transactions management
  spyke::transaction_management_gpu::Transaction_Management_Gpu transaction_management_gpu =
    spyke::transaction_management_gpu::Transaction_Management_Gpu( config );

  return 0;

}
