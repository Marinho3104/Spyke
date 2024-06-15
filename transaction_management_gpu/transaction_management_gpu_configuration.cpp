

/** INCLUDES **/
#include "transaction_management_gpu_configuration.h"
#include <cstddef>

spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration::~Transaction_Management_Gpu_Configuration() {}

void spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration::finalize()
  { free( global_work_items_transaction_proccess ); }

spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration::Transaction_Management_Gpu_Configuration(
    spyke::gpu_management::Gpu_Information& gpu_information, size_t& transactions_pool_size, size_t& balance_pool_size ) 
      : gpu_information( gpu_information ), deep_config_set( 0 ), 
        global_work_items_transaction_proccess( ( size_t* ) malloc( sizeof( size_t ) * gpu_information.platforms_count ) ),
          transactions_pool_size( transactions_pool_size ), balance_pool_size( balance_pool_size ) {}
