
/** block.h - Represents a block with all the needed information
 *
 *
**/

#ifndef SPYKE_TYPES_BLOCK_H
#define SPYKE_TYPES_BLOCK_H

/** INCLUDES **/
#include <cstdint>


namespace spyke::types {

  struct Block {

    // Block's miner public key
    unsigned char miner_public_key[ 32 ];

    // Miner's signature
    unsigned char miner_signature[ 64 ];

    // Bytes size objects inside this block data
    uint32_t size;

    // Block data
    void* data;

    // Constructor to receive a not sign block
    Block( unsigned char[ 32 ], uint32_t, void* );

    // Constructor to received a already sign block
    Block( unsigned char[ 32 ], unsigned char[ 64 ], uint32_t, void* );

    // Finalizes and releases all memory used
    // Calling this function on a Transaction Not Confirmed converts it into a Transaction Confirmed
    void finalize();

    // Verifies if the signature set is correct given the rest of information set
    bool verify_signature();

    // Returns the number of bytes used in the binary representation to be sign
    uint32_t get_binary_sign_bytes();

    // Returns the number of bytes used in the binary representation
    uint32_t get_binary_bytes();

    // Sets the raw block representation to sign the transaction into a given variable
    void binary_representation_sign( char* );

    // Sets the raw block representation into a given variable
    void binary_representation( char* );


    // Fills a given transaction with all information given the binary representation of it ( Transaction not Confirmed )
    static bool fill_block( char*, uint32_t&, Block& );

  };

}

#endif
