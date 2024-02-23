
/** INCLUDES **/
#include "transaction_management_gpu_data.h"
#include "transaction_management_gpu_configuration.h"
#include "./../gpu_management/opencl_wrapper.h"
#include <iostream>
#include <CL/cl.h>

spyke::transaction_management_gpu::Transaction_Management_Gpu_Data::~Transaction_Management_Gpu_Data() { 

  for ( int _ = 0; _ < platform_count; _++ ) {

    // Release main command queue
    clReleaseCommandQueue( main_command_queues[ _ ] );

    // Release the context
    clReleaseContext( contexts[ _ ] );

  }

  free( main_command_queues );

  free( contexts ); 

}

spyke::transaction_management_gpu::Transaction_Management_Gpu_Data::Transaction_Management_Gpu_Data( size_t platform_count )
  : platform_count( platform_count ), contexts( ( cl_context* ) malloc( sizeof( cl_context ) * platform_count ) ),
    main_command_queues( ( cl_command_queue* ) malloc( sizeof( cl_command_queue ) * platform_count ) ){}

bool spyke::transaction_management_gpu::Transaction_Management_Gpu_Data::setup( spyke::transaction_management_gpu::Transaction_Management_Gpu_Configuration& configuration ) {
  
  std::cout << "Starting gpu setup calls:\n" << std::endl;

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

      )

    ) return 0;

  }

  std::cout << "\nEnding gpu setup calls" << std::endl;

  return 1;  

}
