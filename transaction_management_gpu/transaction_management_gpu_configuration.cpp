

/** INCLUDES **/
#include "transaction_management_gpu_configuration.h"
#include <cstddef>
#include <sys/mman.h>
#include "./transaction_management_defines.h"
#include <string.h>

spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration::~Transaction_Management_Gpu_Configuration() {}

void spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration::finalize() { 

  free( global_work_items_transaction_process ); 
  munmap( balance_pool_ptr, BALANCE_POOL_SIZE ); 

}

spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration::Transaction_Management_Gpu_Configuration( spyke::gpu_management::Gpu_Information& gpu_information ) 
  : gpu_information( gpu_information ), deep_config_set( 0 ), global_work_items_transaction_process( ( size_t* ) malloc( sizeof( size_t ) * gpu_information.platforms_count ) ) {

    balance_pool_ptr = mmap(NULL, BALANCE_POOL_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    memset( balance_pool_ptr, 0, 8 );

    balance_pool_locker = 0;

}
