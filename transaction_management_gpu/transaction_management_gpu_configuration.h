
/** transaction_management_gpu_configuration.h -  
 *
**/

#ifndef SPYKE_TRANSACTION_MANAGEMENT_GPU_CONFIGURATION_H
#define SPYKE_TRANSACTION_MANAGEMENT_GPU_CONFIGURATION_H

/** INCLUDES **/
#include "./../gpu_management/gpu_information.h"


namespace spyke::transaction_management_gpu {

  struct Transaction_Management_Gpu_Configuration {

    /** USER CONFIG **/

    // Gpu resources to be used
    gpu_management::Gpu_Information& gpu_information;

    // Transactions pool byte size
    size_t transactions_pool_size;

    // Balance pool byte size
    size_t balance_pool_size;





    /** DEEP CONFIG **/

    // Sinalize if the user have already set the deep configuration
    bool deep_config_set;
  
     // Number of global work items used in the execution of the Transaction Proccess kernel
    size_t* global_work_items_transaction_proccess;  


    /** FUNCTIONS **/

    // Destructor default
    ~Transaction_Management_Gpu_Configuration();
 
    // Frees all memory used
    void finalize();   

    // Copies parameters 
    Transaction_Management_Gpu_Configuration( gpu_management::Gpu_Information&, size_t&, size_t& );

    

  };

}

#endif
