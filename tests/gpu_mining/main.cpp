
/** INCLUDES **/

#include <unistd.h>
#include <iostream>

#include "transaction_management_defines.h"
#include "transaction_management.h"
#include "gpu.h"


int main() {

    // GPU Setup
    if ( ! spyke::gpu::setup() ) return 0;

    // User settings

    size_t __threads_per_device_id[ 1 ] = { 32 }; 

    spyke::transaction_management::user_settings.type = 
        TRANSACTION_MANAGEMENT_TRANSACTION_MANAGEMENT_DEFINES_H_MINER_SETUP;

    spyke::transaction_management::user_settings.platforms_count = 2;
    spyke::transaction_management::user_settings.platforms = 
        ( spyke::transaction_management::User_Settings_Platform_Only* ) malloc( sizeof( spyke::transaction_management::User_Settings_Platform_Only ) * spyke::transaction_management::user_settings.platforms_count );

    spyke::transaction_management::user_settings.platforms[ 0 ].device_ids_count = spyke::gpu::gpu_data.platform_datas[ 0 ].device_ids_count;
    spyke::transaction_management::user_settings.platforms[ 0 ].device_ids = spyke::gpu::gpu_data.platform_datas[ 0 ].device_ids;

    spyke::transaction_management::user_settings.platforms[ 0 ].device_ids_transaction_request_proccess_count = spyke::gpu::gpu_data.platform_datas[ 0 ].device_ids_count;
    spyke::transaction_management::user_settings.platforms[ 0 ].device_ids_transaction_request_proccess = spyke::gpu::gpu_data.platform_datas[ 0 ].device_ids;
    spyke::transaction_management::user_settings.platforms[ 0 ].transaction_request_proccess_threads_count = __threads_per_device_id;
    spyke::transaction_management::user_settings.platforms[ 0 ].transaction_request_proccesseds_count = 10;

    spyke::transaction_management::user_settings.platforms[ 0 ].device_id_acquire_thread = spyke::gpu::gpu_data.platform_datas[ 0 ].device_ids[ 0 ];


    spyke::transaction_management::user_settings.platforms[ 1 ].device_ids_count = spyke::gpu::gpu_data.platform_datas[ 1 ].device_ids_count;
    spyke::transaction_management::user_settings.platforms[ 1 ].device_ids = spyke::gpu::gpu_data.platform_datas[ 1 ].device_ids;
    
    spyke::transaction_management::user_settings.platforms[ 1 ].device_ids_transaction_request_proccess_count = spyke::gpu::gpu_data.platform_datas[ 1 ].device_ids_count;
    spyke::transaction_management::user_settings.platforms[ 1 ].device_ids_transaction_request_proccess = spyke::gpu::gpu_data.platform_datas[ 1 ].device_ids;
    spyke::transaction_management::user_settings.platforms[ 1 ].transaction_request_proccess_threads_count = __threads_per_device_id;
    spyke::transaction_management::user_settings.platforms[ 1 ].transaction_request_proccesseds_count = 10;

    spyke::transaction_management::user_settings.platforms[ 1 ].device_id_acquire_thread = spyke::gpu::gpu_data.platform_datas[ 1 ].device_ids[ 0 ];

    // Transaction Management Setup
    if ( ! spyke::transaction_management::setup() ) return 0;

    // std::cout << "Setup done" << std::endl;

    if ( ! spyke::transaction_management::start_kernels() ) return 0;

    // // std::cout << "Start done" << std::endl;
    sleep( 3 );

    int p = 1011;

    spyke::transaction_management::add_new_transaction_request( &p, 4 );

    // if ( ! spyke::transaction_management::start_kernels() ) return 0;

    return 1;

}


    // // Thread count for each Transaction Request Proccess Kernel device id
    // size_t threads_count_transaction_request_proccess[ 1 ] = { 128 };

    // // User setup
    // spyke::transaction_management::user_data_transaction_management_setup.context_device_ids = spyke::gpu::gpu_data.platform_datas[ 0 ].device_ids;
    // spyke::transaction_management::user_data_transaction_management_setup.context_device_ids_count = 1;
    // spyke::transaction_management::user_data_transaction_management_setup.type = 1;

    // spyke::transaction_management::user_data_transaction_management_setup.device_ids_transaction_request_proccess_kernel = spyke::gpu::gpu_data.platform_datas[ 0 ].device_ids;
    // spyke::transaction_management::user_data_transaction_management_setup.device_ids_transaction_request_proccess_kernel_count = 1;
    // spyke::transaction_management::user_data_transaction_management_setup.threads_number_device_id_transaction_request_proccess_kernel = threads_count_transaction_request_proccess;
    // spyke::transaction_management::user_data_transaction_management_setup.threads_number_combined_device_id_transaction_request_proccess_kernel = threads_count_transaction_request_proccess[ 0 ];

    // spyke::transaction_management::user_data_transaction_management_setup.device_id_transaction_request_acquire_new_thread_kernel = 0;
    // spyke::transaction_management::user_data_transaction_management_setup.device_ids_transaction_pool_get_transaction_kernel = 0;

    // spyke::transaction_management::user_data_transaction_management_setup.transactions_count_transaction_pool = 11;

    // // Transaction Management Setup
    // if ( ! spyke::transaction_management::setup() ) return 0;

    // // Start all kernels for Transaction Management
    // if ( ! spyke::transaction_management::start_kernels() ) return 0;

    // // std::cout << "Waiting ..." << std::endl;

    // // spyke::transaction_management::add_new_transaction_request( 0 );

    // sleep( 5 );

    // spyke::transaction_management::transaction_pool::get_ready_transaction();

    // return 0;

    // // std::cout << "Sending ..." << std::endl;

    // // spyke::transaction_management::add_new_transaction_request( 0 );

    // // std::cout << "Done" << std::endl;