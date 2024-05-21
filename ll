Scenario 2: Deferred Allocation
Lazy Allocation: If you use MAP_ANONYMOUS with mmap, the memory is typically allocated lazily. This means physical memory pages (RAM or swap space) are not allocated until the memory is actually accessed (e.g., written to). This is also known as demand paging.

