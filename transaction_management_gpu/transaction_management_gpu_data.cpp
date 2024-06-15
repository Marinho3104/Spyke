
/** INCLUDES **/
#include "transaction_management_gpu_data.h"
#include "transaction_management_defines.h"
#include "transaction_management_gpu_configuration.h"
#include "./../gpu_management/opencl_wrapper.h"
#include "./../utils/utils.h"
#include <iostream>
#include <CL/cl.h>

spyke::transaction_management_gpu::Transaction_Management_Gpu_Data::~Transaction_Management_Gpu_Data() {}

void spyke::transaction_management_gpu::Transaction_Management_Gpu_Data::finalize() {

  // Loop to free all opencl variables
  for ( int _ = 0; _ < platform_count; _++ ) {

    // Release main command queue
    clReleaseCommandQueue( main_command_queues[ _ ] );

    // Release acquire command queue
    clReleaseCommandQueue( acquire_command_queues[ _ ] );

    // Release the context
    clReleaseContext( contexts[ _ ] );

    // Release the program used
    clReleaseProgram( programs[ _ ] );

    for ( int __ = 0; __ < TRANSACTION_MANAGEMENT_KERNELS_COUNT; __ ++ ) kernels[ _ ][ __ ].~Kernel();

    clReleaseMemObject( transaction_pool[ _ ] ); 
    clReleaseMemObject( balance_pool[ _ ] );
    
    free( kernels[ _ ] );

  }

  free( main_command_queues ); free( acquire_command_queues ); free( contexts ); free( programs ); free( kernels );

  for ( int _ = 0; _ < TRANSACTION_MANAGEMENT_CL_PROGRAMS_FILE_PATH_COUNT; _++ ) free( ( char* ) program_codes[ _ ] );

  free( program_codes ); free( transaction_pool ); free( balance_pool );

}

spyke::transaction_management_gpu::Transaction_Management_Gpu_Data::Transaction_Management_Gpu_Data( size_t platform_count )
  : platform_count( platform_count ), contexts( ( cl_context* ) malloc( sizeof( cl_context ) * platform_count ) ),
    main_command_queues( ( cl_command_queue* ) malloc( sizeof( cl_command_queue ) * platform_count ) ), 
      acquire_command_queues( ( cl_command_queue* ) malloc( sizeof( cl_command_queue ) * platform_count ) ), 
        programs( ( cl_program* ) malloc( sizeof( cl_program ) * platform_count ) ), kernels( ( Kernel** ) malloc( sizeof( Kernel* ) * platform_count ) ), 
          program_codes( ( const char** ) calloc( sizeof( char* ), TRANSACTION_MANAGEMENT_CL_PROGRAMS_FILE_PATH_COUNT ) ),
            transaction_pool( ( cl_mem* ) malloc( sizeof( cl_mem ) * platform_count ) ), balance_pool( ( cl_mem* ) malloc( sizeof( cl_mem ) * platform_count ) ) {

            // Allocate memory for the kernels of each platform
            for ( int _ = 0; _ < platform_count; _++ ) 

              kernels[ _ ] = ( Kernel* ) malloc( sizeof( Kernel ) * TRANSACTION_MANAGEMENT_KERNELS_COUNT);

}

bool spyke::transaction_management_gpu::Transaction_Management_Gpu_Data::setup_global_cl_memory( size_t& transaction_pool_size, size_t& balance_pool_size ) {

  for ( int _ = 0; _ < platform_count; _ ++ ) 
    if( 
      ! gpu_management::opencl_wrapper::set_buffer( transaction_pool[ _ ], contexts[ _ ], CL_MEM_ALLOC_HOST_PTR | CL_MEM_READ_WRITE, transaction_pool_size, 0 ) ||
      ! gpu_management::opencl_wrapper::set_buffer( balance_pool[ _ ], contexts[ _ ], CL_MEM_ALLOC_HOST_PTR | CL_MEM_READ_WRITE, balance_pool_size, 0 ) 
    ) return 0;

  return 1;

}

bool spyke::transaction_management_gpu::Transaction_Management_Gpu_Data::setup_cl_program_code() {

  std::cout << "*** Starting opencl program code setup ***\n" << std::endl;
  
  // File paths to opencl functions
  TRANSACTION_MANAGEMENT_CL_PROGRAMS_FILE_PATH;

  // Obtain the opencl program code
  for ( int _ = 0; _ < TRANSACTION_MANAGEMENT_CL_PROGRAMS_FILE_PATH_COUNT; _++ ) {

    // Try to obtain the code content
    if( ! ( program_codes[ _ ] = utils::get_file_content( transaction_management_cl_programs_file_path[ _ ] ) ) ) return 0;

  }

  std::cout << "*** End opencl program code setup ***\n" << std::endl;
  
  return 1;

}

bool spyke::transaction_management_gpu::Transaction_Management_Gpu_Data::setup_transaction_proccessing_kernel() {

  std::cout << "*** Starting opencl Transaction_Proccessing kernel setup ***\n" << std::endl;

  TRANSACTION_MANAGEMENT_KERNELS_NAME;
  
  // Loop throught out all available platforms
  for ( int _ = 0; _ < platform_count; _ ++ ) {

    // Tries to create the kernel
    if(

      ! spyke::gpu_management::opencl_wrapper::set_kernel(

        kernels[ _ ][ TRANSACTION_MANAGEMENT_KERNELS_INDEX_TRANSACTION_PROCCESSING ].kernel,
        programs[ _ ],
        transaction_management_kernels_name[ TRANSACTION_MANAGEMENT_KERNELS_INDEX_TRANSACTION_PROCCESSING ]

      )
          
    ) return 0;

  }

  std::cout << "*** End opencl Transaction_Proccessing kernel setup ***\n" << std::endl;

  return 1;

}

bool spyke::transaction_management_gpu::Transaction_Management_Gpu_Data::setup_acquire_thread_kernel() {

  std::cout << "*** Starting opencl Acquire_Thread kernel setup ***\n" << std::endl;

  TRANSACTION_MANAGEMENT_KERNELS_NAME;
  
  // Loop throught out all available platforms
  for ( int _ = 0; _ < platform_count; _ ++ ) {

    // Tries to create the kernel
    if(

      ! spyke::gpu_management::opencl_wrapper::set_kernel(

        kernels[ _ ][ TRANSACTION_MANAGEMENT_KERNELS_INDEX_ACQUIRE_THREAD  ].kernel,
        programs[ _ ],
        transaction_management_kernels_name[ TRANSACTION_MANAGEMENT_KERNELS_INDEX_ACQUIRE_THREAD ]

      )
          
    ) return 0;

  }

  std::cout << "*** End opencl Acquire_Thread kernel setup ***\n" << std::endl;

  return 1;

}

bool spyke::transaction_management_gpu::Transaction_Management_Gpu_Data::setup_kernels() {

  return (

    setup_transaction_proccessing_kernel() &&
    setup_acquire_thread_kernel()

  );

}

bool spyke::transaction_management_gpu::Transaction_Management_Gpu_Data::setup( spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration& configuration ) {
  
  // Setup gpu opencl functions that will be used
  if( ! setup_cl_program_code() ) return 0;

  std::cout << "*** Starting gpu setup calls ***\n" << std::endl;

  for ( int _ = 0; _ < platform_count; _ ++ ) {

    std::cout << "\tPlatform: " << _ << std::endl;

    cl_context_properties context_properties[] = {
        
      // Platform where it will be used
      CL_CONTEXT_PLATFORM, ( cl_context_properties ) configuration.gpu_information.platform_ids[ _ ],
      
      // End
      0

    };

    cl_command_queue_properties command_queue_properties[] = {

      // Queue properties
      CL_QUEUE_PROPERTIES, ( cl_command_queue_properties ) CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE,

      // End
      0

    };

    // Variabkes for the opencl calls
    cl_uint programs_file_path_count = TRANSACTION_MANAGEMENT_CL_PROGRAMS_FILE_PATH_COUNT;
    const size_t* program_lengths = 0;

    // Verify if any gpu operation failed, if so return error
    if(

      // Create context
      ! spyke::gpu_management::opencl_wrapper::set_context(

        contexts[ _ ],
        context_properties,
        configuration.gpu_information.devices_count[ _ ],
        configuration.gpu_information.device_ids[ _ ],
        0, 0

      ) ||

      // Create the main command queue
      ! spyke::gpu_management::opencl_wrapper::set_command_queue(

        main_command_queues[ _ ],
        contexts[ _ ],
        configuration.gpu_information.device_ids[ _ ][ 0 ],
        command_queue_properties

      ) ||

      // Create the acquire command queue
      ! spyke::gpu_management::opencl_wrapper::set_command_queue(

        acquire_command_queues[ _ ],
        contexts[ _ ],
        configuration.gpu_information.device_ids[ _ ][ 0 ],
        command_queue_properties

      ) ||

      // Create the program for the kernel executions
      ! spyke::gpu_management::opencl_wrapper::set_program_with_source(

        programs[ _ ],
        contexts[ _ ],
        programs_file_path_count,
        program_codes,
        program_lengths

      ) ||

      // Build the program 
      ! spyke::gpu_management::opencl_wrapper::build_program(

          programs[ _ ],
          configuration.gpu_information.devices_count[ _ ],
          configuration.gpu_information.device_ids[ _ ],
          0, 0, 0

      )

    ) return 0;

  }

  if ( ! setup_global_cl_memory( configuration.transactions_pool_size, configuration.balance_pool_size ) ) return 0;

  if ( ! setup_kernels() ) return 0;

  std::cout << "\n*** Ending gpu setup calls ***\n\n" << std::endl;

  return 1;  

}


spyke::transaction_management_gpu::Kernel::~Kernel() { clReleaseKernel( kernel ); }

spyke::transaction_management_gpu::Kernel::Kernel() {}
