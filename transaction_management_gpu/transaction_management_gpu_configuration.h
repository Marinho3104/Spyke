
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

    /** DEEP CONFIG **/

    // Sinalize if the user have already set the deep configuration
    bool deep_config_set;

    /** FUNCTIONS **/

    // Copies parameters 
    Transaction_Management_Gpu_Configuration( gpu_management::Gpu_Information& );

    

  };

}

#endif
