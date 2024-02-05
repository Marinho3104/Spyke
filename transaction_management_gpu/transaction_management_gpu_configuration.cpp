

/** INCLUDES **/
#include "transaction_management_gpu_configuration.h"

spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration::Transaction_Management_Gpu_Configuration(
    spyke::gpu_management::Gpu_Information& gpu_information ) : gpu_information( gpu_information ), deep_config_set( 0 ) {}
