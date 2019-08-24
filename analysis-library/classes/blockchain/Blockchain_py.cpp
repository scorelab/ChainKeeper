#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <boost/python/list.hpp>
#include "../../rocks_db/connection.h"
#include "../../sqlite_db/Block_db.h"
#include "Blockchain_py.h"
#include "Block_py.h"
#include "Tx_py.h"
#include "Input_py.h"
#include "Output_py.h"
#include "../Globals_py.h"

using namespace std;
std::map<int,std::vector<Block>> blockObjectMap;
std::map<int,std::map<int,std::vector<Tx>>> spent_with_outs_Map;
std::map<int,std::vector<Block>> blockRangeObjectMap;
std::map<int,std::vector<Input>> inputObjectMap;
std::map<int,std::vector<Input>> inputRangeObjectMap;
std::map<int,std::vector<Tx>> txFilterObjectMap;
std::mutex mutx;
std::mutex mutx_in;

//all outputs within given range
std::vector<Output> outputObj;

//convert vectors to pythonList
boost::python::list toPythonList(std::vector<Block> vector) {
    typename std::vector<Block>::iterator iter;
    boost::python::list list;
    for (iter = vector.begin(); iter != vector.end(); ++iter) {
        list.append(*iter);
    }
    return list;
}

boost::python::list toPythonListTx(std::vector<Tx> vector) {
    typename std::vector<Tx>::iterator iter;
    boost::python::list list;
    for (iter = vector.begin(); iter != vector.end(); ++iter) {
        list.append(*iter);
    }
    return list;
}

boost::python::list toPythonListInputs(std::vector<Input> vector) {
    typename std::vector<Input>::iterator iter;
    boost::python::list list;
    for (iter = vector.begin(); iter != vector.end(); ++iter) {
        list.append(*iter);
    }
    return list;
}

//slave function
void slaveParallelBlockFinder(int threadId, int chunkSize,bool isLast,int offset){
    int low, high;
    std::vector<Block> block_arr_local;

    if(isLast){
        low = chunkSize * threadId;
        high = chunkSize + low + offset;
    }else{
        low = chunkSize * threadId;
        high = chunkSize + low - 1;
    }

    if(threadId == 0){
        low = 1;
    }

    //load all range data
    BlockData::BlockData blockRange (parserOutputLocation, "blockchain-data", "blocks");
    std::vector <std::map<string,string>>  blockRangeData;
    blockRangeData = blockRange.getBlockDetailsRange(low, high);

    for(int x = 0; x < blockRangeData.size(); x++){
        map<string,string> slaveBlkMap;
        slaveBlkMap = blockRangeData[x];

        Block * blk = new Block(slaveBlkMap);
        block_arr_local.push_back(*blk);
    }

    mutx.lock();
    blockObjectMap[threadId] = block_arr_local;
    mutx.unlock();
}

void slaveParallelBlockRangeFinder(int threadId, int chunkSize,bool isLast,int offset,int fromBlock){
    int low, high = 0;
    std::vector<Block> block_arr_local;

    if(isLast){
        low = chunkSize * threadId + fromBlock;
        high = chunkSize + low + offset;
    }else{
        low = chunkSize * threadId + fromBlock;
        high = chunkSize + low - 1;
    }


    //load all range data
    BlockData::BlockData blockRange (parserOutputLocation, "blockchain-data", "blocks");
    std::vector <std::map<string,string>>  blockRangeData;
    blockRangeData = blockRange.getBlockDetailsRange(low, high);

    for(int x = 0; x < blockRangeData.size(); x++){
        map<string,string> slaveBlkMap;
        slaveBlkMap = blockRangeData[x];

        Block * blk = new Block(slaveBlkMap);
        block_arr_local.push_back(*blk);
    }

    mutx.lock();
    blockRangeObjectMap[threadId] = block_arr_local;
    mutx.unlock();
}

//class methods
Blockchain::Blockchain(std::string url){
    parserOutputLocation = url;
}

int Blockchain::block_count() {
    rocksdb_mapping::connectDB map (parserOutputLocation, "hash-id-mapping", "lastIds");
    string count = map.getValueFromKey("lastBlockId");
    map.close();

    return atoi(count.c_str()) - 1;
}

int Blockchain::tx_count() {
    rocksdb_mapping::connectDB map (parserOutputLocation, "hash-id-mapping", "lastIds");
    string count = map.getValueFromKey("lastTransactionId");
    map.close();

    return atoi(count.c_str()) -1;
}

boost::python::list Blockchain::blocks() {
    blockObjectMap.clear();
    unsigned concurentThreadsSupported;
    int blkCount;
    boost::python::list blockRangeArray;

    //check number of cors available
    concurentThreadsSupported = std::thread::hardware_concurrency() - 1;

    //check full blockchain length
    rocksdb_mapping::connectDB map (parserOutputLocation, "hash-id-mapping", "lastIds");
    blkCount = atoi(map.getValueFromKey("lastBlockId").c_str()) - 1;
    map.close();

    //devide blockRange for threads
    int chunkSize = blkCount / concurentThreadsSupported;
    int offset = blkCount % concurentThreadsSupported;


    std::thread t[concurentThreadsSupported];
    for(int i = 0; i<concurentThreadsSupported; i++){

        if(i == (concurentThreadsSupported -1)){
            t[i]= std::thread(slaveParallelBlockFinder,i,chunkSize,true, offset);
        }else{
            t[i]= std::thread(slaveParallelBlockFinder,i,chunkSize,false,offset);
        }
    }

    for(int i = 0; i<concurentThreadsSupported; i++){
        t[i].join();
    }

    for(int x=0; x < blockObjectMap.size();x++){
        std::vector<Block> bubSlaveArray = blockObjectMap.find(x)->second;
        boost::python::list arr = toPythonList(bubSlaveArray);
        blockRangeArray.extend(arr);
    }

    return blockRangeArray;
}

boost::python::list Blockchain::block_range(int fromBlock, int toBlock) {
    blockRangeObjectMap.clear();
    unsigned concurentThreadsSupported;
    int blkCount;
    boost::python::list blockRangeArray;

    //check number of cors available
    concurentThreadsSupported = std::thread::hardware_concurrency();

    //check full blockchain length
    rocksdb_mapping::connectDB map (parserOutputLocation, "hash-id-mapping", "lastIds");
    blkCount = atoi(map.getValueFromKey("lastBlockId").c_str()) - 1;
    map.close();

    //check given block range is valid range
    if(blkCount>fromBlock && blkCount >= toBlock){
        int lowBlock = fromBlock;
        int highBlock = toBlock;

        int blockRangeDif = toBlock - fromBlock + 1;
        if(blockRangeDif < 0){
            return blockRangeArray;
        }

        //devide blockRange for threads
        int chunkSize = blockRangeDif / concurentThreadsSupported;
        int offset = blockRangeDif % concurentThreadsSupported;

        std::thread t[concurentThreadsSupported];
        for(int i = 0; i<concurentThreadsSupported; i++){

            if(i == (concurentThreadsSupported -1)){
                t[i]= std::thread(slaveParallelBlockRangeFinder,i,chunkSize,true, offset,fromBlock);
            }else{
                t[i]= std::thread(slaveParallelBlockRangeFinder,i,chunkSize,false,offset,fromBlock);
            }
        }

        for(int i = 0; i<concurentThreadsSupported; i++){
            t[i].join();
        }

        for(int x=0; x < blockRangeObjectMap.size();x++){
            std::vector<Block> bubSlaveArray = blockRangeObjectMap.find(x)->second;
            boost::python::list arr = toPythonList(bubSlaveArray);
            blockRangeArray.extend(arr);
        }
    }

    return blockRangeArray;
}

Tx Blockchain::tx_with_hash(string hash) {
    Tx blk_tx;
    rocksdb_mapping::connectDB txHashMap (parserOutputLocation, "hash-id-mapping", "tx");
    string hashID = txHashMap.getValueFromKey(hash);
    txHashMap.close();

    if(hashID != "null"){
        Tx * txObj = new Tx(hash);
        return *txObj;
    }

    return blk_tx;
}

Tx Blockchain::tx_with_index(int index) {
    Tx * txObj = new Tx(index);
    return *txObj;
}