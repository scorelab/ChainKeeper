#include "Block_py.h"
#include "Tx_py.h"
#include "../../rocks_db/connection.h"
#include "../../sqlite_db/Block_db.h"
#include "../Globals_py.h"
#include <boost/python/list.hpp>
#include <boost/python/dict.hpp>

template <class K, class V>
boost::python::dict toPythonDict(std::map<K, V> map) {
    typename std::map<K, V>::iterator iter;
    boost::python::dict dictionary;
    for (iter = map.begin(); iter != map.end(); ++iter) {
        dictionary[iter->first] = iter->second;
    }
    return dictionary;
}

Block::Block() {}

Block::Block(std::map<string, string> blockData) {
    hash = blockData.find("HASH")->second;
    prev_block_hash = blockData.find("PREV_HASH")->second;
    next_block_hash = blockData.find("NEXT_HASH")->second;
    height = atoi(blockData.find("HEIGHT")->second.c_str());
    timestamp = blockData.find("TIMESTAMP")->second;
    size = atoi(blockData.find("SIZE")->second.c_str());
    tx_count = atoi(blockData.find("TX_COUNT")->second.c_str());
    block_index = atoi(blockData.find("HEIGHT")->second.c_str());
    nonce = atoi(blockData.find("NONCE")->second.c_str());
}

Block::Block(int index) {
    block_index = index;
    BlockData::BlockData blockIndex (parserOutputLocation, "blockchain-data", "blocks");
    map<string, string> blk_map = blockIndex.getBlockDetails(index);

    height = atoi(blk_map.find("HEIGHT")->second.c_str());
    hash = blk_map.find("HASH")->second;
    prev_block_hash = blk_map.find("PREV_HASH")->second;
    next_block_hash = blk_map.find("NEXT_HASH")->second;
    timestamp = blk_map.find("TIMESTAMP")->second;
    size = atoi(blk_map.find("SIZE")->second.c_str());
    tx_count = atoi(blk_map.find("TX_COUNT")->second.c_str());
    nonce = atoi(blk_map.find("NONCE")->second.c_str());
}

Block::Block(string hashVal) {
    rocksdb_mapping::connectDB blockHashMap (parserOutputLocation, "hash-id-mapping", "blocks");
    string hashID = blockHashMap.getValueFromKey(hashVal);
    block_index = atoi(hashID.c_str());
    blockHashMap.close();

    if(hashID != "null"){
        int index = atoi(hashID.c_str());
        BlockData::BlockData blockIndex (parserOutputLocation, "blockchain-data", "blocks");
        map<string, string> blk_map = blockIndex.getBlockDetails(index);

        height = atoi(blk_map.find("HEIGHT")->second.c_str());
        hash = blk_map.find("HASH")->second;
        prev_block_hash = blk_map.find("PREV_HASH")->second;
        next_block_hash = blk_map.find("NEXT_HASH")->second;
        timestamp = blk_map.find("TIMESTAMP")->second;
        size = atoi(blk_map.find("SIZE")->second.c_str());
        tx_count = atoi(blk_map.find("TX_COUNT")->second.c_str());
        nonce = atoi(blk_map.find("NONCE")->second.c_str());
    }
}

//methods
string Block::str() {
    return "Block (numTxes="+ to_string(tx_count) +", height="+ to_string(height)+", header_hash="+hash+", timestamp="+timestamp+", bits="+to_string(size)+")";
}

Block Block::next_block() {
    int thisBlock = block_index;
    int nextBlock = thisBlock + 1;

    BlockData::BlockData blockIndex (parserOutputLocation, "blockchain-data", "blocks");
    map<string, string> next_blk_map = blockIndex.getBlockDetails(nextBlock);

    Block *blk = new Block(next_blk_map);
    return *blk;
}

Block Block::prev_block() {
    int thisBlock = block_index;
    int prevBlock = thisBlock - 1;
    Block *blk = new Block();

    if(prevBlock >= 1){
        BlockData::BlockData blockIndex (parserOutputLocation, "blockchain-data", "blocks");
        map<string, string> prev_blk_map = blockIndex.getBlockDetails(prevBlock);
        Block *blkObj = new Block(prev_blk_map);
        return *blkObj;
    }

    return *blk;
}

boost::python::list Block::coinbase_tx() {
    BlockData::BlockData blockTxIndex (parserOutputLocation, "blockchain-data", "tx");
    boost::python::list tx_id = blockTxIndex.getTxOfBlock(block_index);

    BlockData::BlockData blockTxCoinbase (parserOutputLocation, "blockchain-data", "tx");
    std::vector <std::map<string,string>> coinbaseTxHashList = blockTxCoinbase.getCoinbaseTxFromIndex(tx_id);

    boost::python::list txObject;

    for(int x=0; x < coinbaseTxHashList.size(); x++ ){
        std::map<string, string> txMap;
        txMap = coinbaseTxHashList[x];

        Tx * coinbase = new Tx(txMap);
        txObject.append(*coinbase);
    }

    return txObject;
}

long double Block::fee() {
    BlockData::BlockData blockTxIndex (parserOutputLocation, "blockchain-data", "tx");
    boost::python::list tx_id = blockTxIndex.getTxOfBlock(block_index);

    BlockData::BlockData blkFee (parserOutputLocation, "blokchain-data", "tx");
    long double amount = blkFee.getFeeOfBlock(tx_id);

    return amount;
}

boost::python::list Block::txes() {
    BlockData::BlockData blockTxData (parserOutputLocation, "blockchain-data", "tx");
    std::vector <std::map<string,string>> blockTxList = blockTxData.getBlockTxData(height);

    boost::python::list txObject;

    for(int x=0; x < blockTxList.size(); x++ ){
        std::map<string, string> txMap;
        txMap = blockTxList[x];

        Tx * blk = new Tx(txMap);
        txObject.append(*blk);
    }

    return txObject;
}