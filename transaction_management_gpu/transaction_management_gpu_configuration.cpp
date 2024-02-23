

/** INCLUDES **/
#include "transaction_management_gpu_configuration.h"

spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration::~Transaction_Management_Gpu_Configuration() 
  { free( global_work_items_transaction_proccess ); }

spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration::Transaction_Management_Gpu_Configuration(
    spyke::gpu_management::Gpu_Information& gpu_information, size_t& number_transactions_pool ) 
      : gpu_information( gpu_information ), deep_config_set( 0 ), 
        global_work_items_transaction_proccess( ( size_t* ) malloc( sizeof( size_t ) * gpu_information.platforms_count ) ),
          number_transactions_pool( number_transactions_pool ) {}
