
/** transaction.h - Representation of a transaction data either before and after state
 *
 *
**/

#ifndef SPYKE_TYPES_TRANSACTION_H
#define SPYKE_TYPES_TRANSACTION_H

/** INCLUDES **/
#include "address.h"
#include <cstdint>


namespace spyke::types {

  struct Transaction {

    // Address of the one send and the one receiving the transaction
    Address from, to;

    // Amount that were spent and the fee payed
    uint64_t amount, fee;

    // After the transaction is accepted and insert into the blockchain
    // The balance_after correspond to the amount of balance that the
    // sender have after the transaction
    uint64_t balance_after;

    // Signature of the sender
    unsigned char signature[ 64 ];

    // The transaction is complete or not
    bool complete;


    // Constructor to initiate a transaction that is still not complete ( not accepted in the blockchain )
    // which means the parameter balance_after is still unknown
    Transaction( Address&, Address&, uint64_t, uint64_t );

    // Constructor to initiate a transaction that is complete 
    Transaction( Address&, Address&, uint64_t&, uint64_t&, uint64_t&, unsigned char* );

    // Returns the number of bytes used in the binary representation
    uint32_t get_binary_bytes();

    // Sets the raw transaction representation into a given variable
    void binary_representation( char* );

  };

}

#endif
