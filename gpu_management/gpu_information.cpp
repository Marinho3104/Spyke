

/** INCLUDES **/
#include "gpu_information.h"
#include "opencl_wrapper.h"
#include <CL/cl.h>

spyke::gpu_management::Gpu_Information::~Gpu_Information() {

  free( platform_ids );

  for ( int _ = 0; _ < platforms_count; _ ++ ) free( device_ids[ _ ] );

  free( device_ids ); free( devices_count );

}

spyke::gpu_management::Gpu_Information::Gpu_Information() : platform_ids( 0 ), platforms_count( 0 ), device_ids( 0 ), devices_count( 0 ) {}

spyke::gpu_management::Gpu_Information::Gpu_Information( cl_platform_id*& platform_ids, cl_uint& platforms_count, cl_device_id**& device_ids, cl_uint*& devices_count ) 
  : platform_ids( platform_ids ), platforms_count( platforms_count ), device_ids( device_ids ), devices_count( devices_count ) {}

bool spyke::gpu_management::Gpu_Information::set_available_information( Gpu_Information& gpu_information ) {

  // Get platforms count
  if ( ! spyke::gpu_management::opencl_wrapper::get_platforms_count( &gpu_information.platforms_count ) ) return 0;
  
  // Allocate memery for all platform ids
  gpu_information.platform_ids = 
    ( cl_platform_id* ) malloc( sizeof( cl_platform_id ) * gpu_information.platforms_count );

  // Get platform ids
  if ( ! spyke::gpu_management::opencl_wrapper::get_platform_ids( gpu_information.platform_ids, gpu_information.platforms_count ) ) goto error_platform_ids;

  // Allocate memory for all device ids array
  gpu_information.device_ids = 
    ( cl_device_id** ) calloc( sizeof( cl_device_id* ), gpu_information.platforms_count );
  
  // Allocate space to store the number if devices of each platform
  gpu_information.devices_count = 
    ( cl_uint* ) malloc( sizeof( cl_uint ) * gpu_information.platforms_count );

  for ( int _ = 0; _ < gpu_information.platforms_count; _++ ) {

    // Get devices count for current platform
    if ( ! spyke::gpu_management::opencl_wrapper::get_devices_count( gpu_information.platform_ids[ _ ], CL_DEVICE_TYPE_GPU, gpu_information.devices_count + _ ) ) goto error_devices;

    // Allocate space for all devices available in current platform
    gpu_information.device_ids[ _ ] = 
      ( cl_device_id* ) malloc( sizeof( cl_device_id ) * gpu_information.devices_count[ _ ] );

    if ( ! spyke::gpu_management::opencl_wrapper::get_device_ids( gpu_information.platform_ids[ _ ], CL_DEVICE_TYPE_GPU, gpu_information.devices_count[ _ ], gpu_information.device_ids[ _ ] ) ) 
      goto error_devices;

  }

  return 1;

error_devices:

  for ( int _ = 0; _ < gpu_information.platforms_count; _ ++ ) 

    // If memory were allocated frees it
    if ( gpu_information.device_ids[ _ ] ) free( gpu_information.device_ids[ _ ] ); 

    // If is null means no more allocations were made so can exit the loop
    else break;

  free( gpu_information.device_ids); free( gpu_information.devices_count );

error_platform_ids: 

  free( gpu_information.platform_ids );

  return 0;

}

