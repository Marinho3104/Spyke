
#define TRANSACTION_MANAGEMENT_CL_PROGRAMS_FILE_PATH_COUNT 2

#define TRANSACTION_MANAGEMENT_CL_PROGRAMS_FILE_PATH \
  const char* transaction_management_cl_programs_file_path[] = \
    { \
      "./../transaction_management_gpu/cl_programs/transaction_proccessing.cl", \
      "./../transaction_management_gpu/cl_programs/acquire_thread.cl" \
    };

#define TRANSACTION_MANAGEMENT_KERNELS_COUNT 2

#define TRANSACTION_MANAGEMENT_KERNELS_NAME \
  const char* transaction_management_kernels_name[] = \
    { \
      "transaction_proccessing", \
      "acquire_thread" \
    };

#define TRANSACTION_MANAGEMENT_KERNELS_INDEX_TRANSACTION_PROCCESSING 0
#define TRANSACTION_MANAGEMENT_KERNELS_INDEX_ACQUIRE_THREAD 1


/** USER OPTIONS **/

#define BALANCE_POOL_SIZE 4096
