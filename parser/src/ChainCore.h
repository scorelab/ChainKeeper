#ifndef CHAINCORE_H
#define CHAINCORE_H

#include <iostream>

#include "chain_headers.h"
#include "tools.h"

namespace core
{
    using namespace cryptonote;
    using namespace crypto;
    using namespace std;

    class ChainCore {

        string blockchain_path;

        tx_memory_pool m_mempool;
        Blockchain m_blockchain_storage;

        hw::device* m_device;

        network_type nettype;

    public:
        ChainCore();

        bool
        init(const string& _blockchain_path, network_type nt);

        Blockchain&
        get_core();

        bool
        get_block_by_height(const uint64_t& height, block& blk);

        bool
        get_tx(const crypto::hash& tx_hash, transaction& tx);

        bool
        get_tx(const string& tx_hash, transaction& tx);

        bool
        find_output_in_tx(const transaction& tx,
                          const public_key& output_pubkey,
                          tx_out& out,
                          size_t& output_index);

        bool
        get_tx_hash_from_output_pubkey(const public_key& output_pubkey,
                                       const uint64_t& block_height,
                                       crypto::hash& tx_hash,
                                       transaction& tx_found);

        uint64_t
        get_blk_timestamp(uint64_t blk_height);

        string
        get_blkchain_path();

        hw::device* const
        get_device() const;

        virtual ~ChainCore();
    };



    bool
    init_blockchain(const string& path,
                    MicroCore& mcore,
                    Blockchain*& core_storage,
                    network_type nt);


}



#endif //CHAINCORE_H