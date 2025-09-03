
#include "worker.h"
#include "item.h"
#include "log.h"
#include <optional>

//
// priority_queue::Worker::Worker( Priority_Queue& queue_mut ) noexcept : queue_mut( queue_mut ) {}
//
// void priority_queue::Worker::start() noexcept {
//
//   while( true ) {
//
//     std::optional< Item > item_mut = queue_mut.pop();
//
//     // The queue will only return a null object if it was sealed and no
//     // more Item are inside the queue
//     if( ! item_mut ) {
//       break;
//     }
//
//     handle( item_mut->get_data(), item_mut->data_size );
//
//   }
//
// }
