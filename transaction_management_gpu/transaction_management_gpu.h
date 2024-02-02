
/** transaction_management_gpu.h -
 *
**/


#ifndef TRNASACTION_MANAGEMENT_GPU_H
#define TRNASACTION_MANAGEMENT_GPU_H


/** INCLUDES **/
#include "transaction_management_gpu_user_configuration.h"


namespace spyke::transaction_management_gpu {

  struct Transaction_Management_Gpu {

    /** VARIABLES **/


    /** FUNCTIONS **/

    // Setups all everything about the gpu, with the given data that the user wants to use 
    Transaction_Management_Gpu( Transaction_Management_Gpu_User_Configuration& );

  };

}

#endif
