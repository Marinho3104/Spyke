
kernel void transaction_proccessing(
    __global void* balance_pool
  ) {

    int local_id = get_local_id(0);

    printf("%d\n", local_id);

}


