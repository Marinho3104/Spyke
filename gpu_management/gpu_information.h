
/** gpu_information.h - A struct to hold general information about gpu, this struct ideal to represent the amount of gpu power a user wants to use in a specific setup. ( e.g. Transaction Management )
 * The platforms available
 * Repective device ids of each platform
**/

#ifndef SPYKE_GPU_MANAGEMENT_GPU_INFORMATION_H
#define SPYKE_GPU_MANAGEMENT_GPU_INFORMATION_H

/** INCLUDES **/
#include <CL/cl.h>


namespace spyke::gpu_management {

  struct Gpu_Information {

    // Platforms //
    
    cl_platform_id* platform_ids;
    cl_uint platforms_count;

    // Devices //

    // The holds an array of device ids of the same size of the amount of platforms_count 
    // Inside each array there is another array with the ids of each device in each platform where the size of that array is in devices_count
    cl_device_id** device_ids;
    cl_uint* devices_count;


    /** FUNCTIONS **/

    // Frees all memory
    ~Gpu_Information();

    // Initializes all data at zero
    Gpu_Information();

    // Receives all data an copies it into the structure arguments
    Gpu_Information( cl_platform_id*&, cl_uint&, cl_device_id**&, cl_uint*& );


    /** STATIC **/

    // Sets the given Gpu_Information with all available gpu platforms and devices information
    static bool set_available_information( Gpu_Information& );

  };

}

#endif
