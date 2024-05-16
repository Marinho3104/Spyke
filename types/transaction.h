
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
    uint64_t balance_after = 0;

    // Signature of the sender
    unsigned char signature[ 64 ];

    // Extra data used to carry extra information to the transaction confirmation fase
    void* extra_data = 0; uint16_t extra_data_size = 0;

    // Default
    Transaction();

    // Constructor to initiate a transaction that is still not complete ( not accepted in the blockchain )
    // which means the parameter balance_after is still unknown
    Transaction( Address&, uint64_t, uint64_t, void*, uint16_t );

    // Constructor to initiate a transaction that is complete 
    Transaction( Address&, Address&, uint64_t&, uint64_t&, uint64_t& );

    // Finalizes and releases all memory used
    // Calling this function on a Transaction Not Confirmed converts it into a Transaction Confirmed
    void finalize();

    // Converts the extra data information into the from Address
    bool set_from_address();

    // Converts the extra data information into the from address ( Address type NORMAL )
    bool set_from_address_type_NORMAL();


    // Verifies if the signature set is correct given the rest of information set
    bool verify_signature();

    // Verifies if the signature is correct for a NORMAL address signature
    bool verify_signature_type_NORMAL( unsigned char* );

    // Returns the number of bytes used in the binary representation to be sign
    uint32_t get_binary_sign_bytes();

    // Returns the number of bytes used in the binary representation
    uint32_t get_binary_bytes();

    // Sets the raw transaction representation to sign the transaction into a given variable
    void binary_representation_sign( char* );

    // Sets the raw transaction representation into a given variable
    void binary_representation( char* );


    // Fills a given transaction with all information given the binary representation of it ( Transaction not Confirmed )
    static bool fill_transaction_not_confirmed( char*, uint32_t&, Transaction& );

    // Fills a given transaction with all information given the binary representation of it ( Transaction Confirmed )
    static bool fill_transaction_confirmed( char*, uint32_t&, Transaction& );

  };

}

#endif

// Extra data size for Address from type NORMAL
#define EXTRA_DATA_SIZE_TYPE_NORMAL 33


