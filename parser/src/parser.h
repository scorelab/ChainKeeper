#ifndef CHAIN_PARSER_H
#define CHAIN_PARSER_H

#endif

#include "mstch/mstch.hpp"

#include "monero_headers.h"

#include "MicroCore.h"
#include "tools.h"
#include "rpccalls.h"

#include "CurrentBlockchainStatus.h"
#include "MempoolStatus.h"

#include "../ext/crow/crow.h"

#include "../ext/vpetrigocaches/cache.hpp"
#include "../ext/vpetrigocaches/lru_cache_policy.hpp"
#include "../ext/vpetrigocaches/fifo_cache_policy.hpp"

#include <algorithm>
#include <limits>
#include <ctime>
#include <future>
#include <regex>

#include "idhashmapper.h"
#include "indexmapper.h"
#include "query.h"
#include "bloomFilter.h"
#include <mutex>
#include <ctime>
#include "sys/types.h"
#include "sys/sysinfo.h"

namespace parse {
    using namespace core;
    using json = nlohmann::json;
    using std::fstream;

    bool isAllBlockDone = false;
    int lastBlockId;
    int lastTransactionId;
    int lastKeyImageId;
    int lastStealthAddressId;
    int lastOutputId;
    int lastInputId;
    int lastRingMemberId;
    bool isFromBegining = false;

    BloomFilter bloomFilter; //instance of bloom-filter

    std::mutex mtx;           // mutex for critical section
    std::mutex mtx2;           // mutex for critical section
    std::mutex mtx3;           // mutex for critical section
    std::mutex mtx4;           // mutex for critical section

    std::mutex mtxh1;          //mutex for id-hash vectors
    std::mutex mtxh2;          //mutex for id-hash vectors
    std::mutex mtxh3;          //mutex for id-hash vectors
    std::mutex mtxh4;          //mutex for id-hash vectors
    std::mutex mtxh5;          //mutex for id-hash vectors

    std::mutex mtxb1;          //mutex for blockData vectors
    std::mutex mtxb2;          //mutex for blockIndex vectors

    std::mutex mtxt1;          //mutex for txData vectors
    std::mutex mtxt2;          //mutex for txIndex vectors

    std::mutex mtxk;          //mutex for KIdata vectors

    std::mutex checker;       //mutex for access isBegining boolean

    //global performance points (RAM, VRAM, CPU, TIME)
    std::vector<double> timeMarker;
    std::vector<long> vRamMarker;
    std::vector<long> pRamMarker;
    std::vector<double> cpuMarker;
    long vRamTotalSize = 0;
    long pRamTotalSize = 0;

    //global data store in memory as vectors for HASH-ID MAPPING
    std::vector<std::vector<string>> blockHashIdVector;         //store block hash-id
    std::vector<std::vector<string>> txHashIdVector;            //store tx hash-id
    std::vector<std::vector<string>> saHashIdVector;            //store stealth-address hash-id

    //global data store in memory as vector for INDEX and DETAILS
    std::vector<json> outputOfBlock;
    std::vector<std::vector<int>> outputIndexOfBlock;            //store block details & indexes

    std::vector<json> outputOfStealthAddresses;
    std::vector<std::vector<int>> outputIndexOfStealthAddresses; //store Stealth-Addresses details & indexes

    std::vector<std::vector<string>> outputOfKeyImages;          //store KeyImages details & indexes

    std::vector<json> outputOfRingMembers;
    std::vector<std::vector<int>> outputIndexOfRingMembers;      //store RingMembers details & indexes

    std::vector<json> outputOfTx;
    std::vector<std::vector<int>> outputIndexOfTx;               //store Tx details & indexes

    void storeLastBlockId(int lastBlockId){
        hashmapper::idHashMapperDB map ("blockchain-core", "hash-id-mapping", "lastIds");
        map.insertKey("lastBlockId",to_string(lastBlockId));
        map.close();
    }

    void storeLastTransactionId(int lastTransactionId){
        hashmapper::idHashMapperDB map ("blockchain-core", "hash-id-mapping", "lastIds");
        map.insertKey("lastTransactionId",to_string(lastTransactionId));
        map.close();
    }

    void storeLastKeyImageId(int lastKeyImageId){
        hashmapper::idHashMapperDB map ("blockchain-core", "hash-id-mapping", "lastIds");
        map.insertKey("lastKeyImageId",to_string(lastKeyImageId));
        map.close();
    }

    void storeLastStealthAddressId(int lastStealthAddressId){
        hashmapper::idHashMapperDB map ("blockchain-core", "hash-id-mapping", "lastIds");
        map.insertKey("lastStealthAddressId",to_string(lastStealthAddressId));
        map.close();
    }

    void storeLastRingMemberId(int lastRingMemberId){
        hashmapper::idHashMapperDB map ("blockchain-core", "hash-id-mapping", "lastIds");
        map.insertKey("lastRingMemberId",to_string(lastRingMemberId));
        map.close();
    }

    void storeLastOutputId(int lastOutputId){
        hashmapper::idHashMapperDB map ("blockchain-core", "hash-id-mapping", "lastIds");
        map.insertKey("lastOutputId",to_string(lastOutputId));
        map.close();
    }

    void storeLastInputId(int lastInputId){
        hashmapper::idHashMapperDB map ("blockchain-core", "hash-id-mapping", "lastIds");
        map.insertKey("lastInputId",to_string(lastInputId));
        map.close();
    }

    void storeLastSavedBlockHeight(int blk_height){
        hashmapper::idHashMapperDB map ("blockchain-core", "hash-id-mapping", "lastIds");
        map.insertKey("lastBlockHeight",to_string(blk_height));
        map.close();
    }

    string getLastBlockId(){
        hashmapper::idHashMapperDB map ("blockchain-core", "hash-id-mapping", "lastIds");
        string val = map.getValueFromKey("lastBlockId");
        map.close();
        return val;
    }

    string getLastTransactionId(){
        hashmapper::idHashMapperDB map ("blockchain-core", "hash-id-mapping", "lastIds");
        string val = map.getValueFromKey("lastTransactionId");
        map.close();
        return val;
    }

    string getLastKeyImageId(){
        hashmapper::idHashMapperDB map ("blockchain-core", "hash-id-mapping", "lastIds");
        string val = map.getValueFromKey("lastKeyImageId");
        map.close();
        return val;
    }

    string getLastStealthAddressId(){
        hashmapper::idHashMapperDB map ("blockchain-core", "hash-id-mapping", "lastIds");
        string val = map.getValueFromKey("lastStealthAddressId");
        map.close();
        return val;
    }

    string getLastRingMemberId(){
        hashmapper::idHashMapperDB map ("blockchain-core", "hash-id-mapping", "lastIds");
        string val = map.getValueFromKey("lastRingMemberId");
        map.close();
        return val;
    }

    string getLastOutputId(){
        hashmapper::idHashMapperDB map ("blockchain-core", "hash-id-mapping", "lastIds");
        string val = map.getValueFromKey("lastOutputId");
        map.close();
        return val;
    }

    string getLastInputId(){
        hashmapper::idHashMapperDB map ("blockchain-core", "hash-id-mapping", "lastIds");
        string val = map.getValueFromKey("lastInputId");
        map.close();
        return val;
    }

    string getLastSavedBlockHeight(){
        hashmapper::idHashMapperDB map ("blockchain-core", "hash-id-mapping", "lastIds");
        string last_saved_blk_height = map.getValueFromKey("lastBlockHeight");
        map.close();

        if(last_saved_blk_height == "null"){
            checker.lock();
            isFromBegining = true;
            checker.unlock();
            last_saved_blk_height = "0";
        }

        return last_saved_blk_height;
    }

    json blockDetails(page& monerosci, string blk_height) {
        json jsonResponse  = monerosci.json_block(blk_height);

        return jsonResponse;

    }

    json transactionDetails(page& monerosci, string curTx){
        json jsonResponse  = monerosci.json_detailedtransaction(curTx);

        return jsonResponse;
    }

    void getLastIdList(){
        //get last block id
        string last_blk_id = getLastBlockId();
        if(last_blk_id == "null"){
            lastBlockId = 1;
        }else{
            lastBlockId = atoi(last_blk_id.c_str());
        }

        string last_tx_id = getLastTransactionId();
        if(last_tx_id == "null"){
            lastTransactionId = 1;
        }else{
            lastTransactionId = atoi(last_tx_id.c_str());
        }

        string last_sa_id = getLastStealthAddressId();
        if(last_sa_id == "null"){
            lastStealthAddressId = 1;
        }else{
            lastStealthAddressId = atoi(last_sa_id.c_str());
        }

        string last_output_id = getLastOutputId();
        if(last_output_id == "null"){
            lastOutputId = 1;
        }else{
            lastOutputId = atoi(last_output_id.c_str());
        }

        string last_input_id = getLastInputId();
        if(last_input_id == "null"){
            lastInputId = 1;
        }else{
            lastInputId = atoi(last_input_id.c_str());
        }

        string last_ki_id = getLastKeyImageId();
        if(last_ki_id == "null"){
            lastKeyImageId = 1;
        }else{
            lastKeyImageId = atoi(last_ki_id.c_str());
        }

        string last_rm_id = getLastRingMemberId();
        if(last_rm_id == "null"){
            lastRingMemberId = 1;
        }else{
            lastRingMemberId = atoi(last_rm_id.c_str());
        }
    }

    void storeLastIdList(){
        //store last block id
        storeLastBlockId(lastBlockId);
        storeLastTransactionId(lastTransactionId);
        storeLastStealthAddressId(lastStealthAddressId);
        storeLastOutputId(lastOutputId);
        storeLastKeyImageId(lastKeyImageId);
        storeLastRingMemberId(lastRingMemberId);
        storeLastInputId(lastInputId);
    }

    #pragma warning(disable:4700)
    void coreProcessor(page& monerosci,string blk_height){
        //get block details
        json blockData= blockDetails(monerosci,blk_height);
        string blk_hash = blockData.at("hash");

        //store block map of hash-id in vector
        std::vector<string> blockVector = {blk_hash,to_string(lastBlockId)};
        mtxh2.lock();
        blockHashIdVector.push_back(blockVector);
        mtxh2.unlock();

        //store data on block detail vector
        blockData["lastBlockId"] = lastBlockId;
        mtxb1.lock();
        outputOfBlock.push_back(blockData);
        mtxb1.unlock();

        //insert data into the indexes table
        std::vector<int> blockId = {lastBlockId};
        mtxb2.lock();
        outputIndexOfBlock.push_back(blockId);
        mtxb2.unlock();

        int txCount =  blockData.at("txCount");
        json txs = blockData.at("txs");

//        cout << "Include Transaction Count - "<< txCount<<endl;
        for(int x=0;x<txCount;x++){
            string curTx = txs[x]["tx_hash"];
            json transactionData = transactionDetails(monerosci, curTx);

            string txHash = transactionData.at("tx_hash")[0];

//          store tx map of hash-id in vector
            std::vector<string> txVector = {txHash,to_string(lastTransactionId)};
            mtxh3.lock();
            txHashIdVector.push_back(txVector);
            mtxh3.unlock();

            /*
                 ###################### TRANSACTION STEALTH-ADDRESSES ###########################
                 First store hash-id mapping of SA
                 Second store details of SA
                 Third store indexes of SA
            */
            json outputs = transactionData.at("outputs");

            for(int y=0; y < outputs.size(); y++){
                //output public-key
                string sa_hash = outputs[y]["out_pub_key"][0];

                //store tx map of hash-id in vector
                std::vector<string> saVector = {sa_hash,to_string(lastStealthAddressId)};
                mtxh1.lock();
                saHashIdVector.push_back(saVector);
                mtxh1.unlock();

                //store SA data in SA detail table
                outputs[y]["lastSAId"] = lastOutputId;
                mtx.lock();
                outputOfStealthAddresses.push_back(outputs[y]);
                mtx.unlock();

                //insert data into the indexes table
                std::vector<int> tempIndexData = {lastTransactionId,lastStealthAddressId,lastOutputId,lastBlockId};
                mtx2.lock();
                outputIndexOfStealthAddresses.push_back(tempIndexData);
                mtx2.unlock();

                //increment stealth-address id
                lastStealthAddressId += 1;
                lastOutputId += 1;
            }

            json inputs = transactionData.at("inputs");

            //store data on block detail table
            transactionData["lastTxId"] = lastTransactionId;

            mtxt1.lock();
            outputOfTx.push_back(transactionData);
            mtxt1.unlock();

            //insert data into the indexes table
            std::vector<int> txId = {lastTransactionId,lastBlockId,lastTransactionId};
            mtxt2.lock();
            outputIndexOfTx.push_back(txId);
            mtxt2.unlock();

            lastTransactionId += 1;
        }

        lastBlockId += 1;
    }

    //BLOCK-DATA-STORE
    void runBlockMainThread(){
        //create id-hash map connection
        hashmapper::idHashMapperDB mapCon ("blockchain-core", "hash-id-mapping", "blocks");
        bool is_begining = false;

        checker.lock();
        if(isFromBegining){
            is_begining = true;
        }
        checker.unlock();

        //create database connection for blocks
        indexMapper::indexes dbConnectionBlock ("blockchain-core", "blocks" ,is_begining);

        if(isFromBegining){
            //create block data table and index table
            dbConnectionBlock.createTable(blockDetailsTable);
            dbConnectionBlock.createTable(blockIndexTable);
        }

        int blockHash,blockData,blockIndex = 0;
        std::vector<json> bData;
        std::vector<std::vector<int>> bIndex;

        while (true){
            //chech hash-id map
            if(!blockHashIdVector.empty()){
                std::vector<std::vector<string>> h2;

                mtxh2.lock();
                h2.push_back(blockHashIdVector[0]);
                blockHashIdVector.erase (blockHashIdVector.begin());
                mtxh2.unlock();

                string blk_hash = h2[0][0];
                string lastBlockId = h2[0][1];

                mapCon.insertKey(blk_hash,lastBlockId);
                h2.erase (h2.begin());
                blockHash++;

            }

            //check block-data store
            mtxb1.lock();
            if(outputOfBlock.size() >= 1000){
                long currentSize = outputOfBlock.size();
                bData = outputOfBlock;
                blockData += currentSize;

                outputOfBlock.erase(outputOfBlock.begin(),outputOfBlock.begin()+currentSize);
            }else if(outputOfBlock.size() < 1000 & isAllBlockDone){
                long currentSize = outputOfBlock.size();
                bData = outputOfBlock;
                blockData += currentSize;

                outputOfBlock.erase(outputOfBlock.begin(),outputOfBlock.begin()+currentSize);
            }
            mtxb1.unlock();

            if(!bData.empty()){
                dbConnectionBlock.insertBlockData(bData);
                bData.clear();
            }

            //chech block-index store
            mtxb2.lock();
            if(outputIndexOfBlock.size() >= 1000){
                long currentSize = outputIndexOfBlock.size();
                bIndex = outputIndexOfBlock;
                blockIndex += currentSize;

                outputIndexOfBlock.erase(outputIndexOfBlock.begin(),outputIndexOfBlock.begin()+currentSize);

            }else if(outputIndexOfBlock.size() < 1000 & isAllBlockDone){
                long currentSize = outputIndexOfBlock.size();
                bIndex = outputIndexOfBlock;
                blockIndex += currentSize;

                outputIndexOfBlock.erase(outputIndexOfBlock.begin(),outputIndexOfBlock.begin()+currentSize);
            }
            mtxb2.unlock();

            if(!bIndex.empty()){
                dbConnectionBlock.insertBlockIndex(bIndex);
                bIndex.clear();
            }

            if(isAllBlockDone && blockHashIdVector.empty() && outputOfBlock.empty() && outputIndexOfBlock.empty()){
                break;
            }
        }

        mapCon.close();
        dbConnectionBlock.close();
        cout <<"BLOCK ID-HASH STORING THREAD COMPLETED. STORED " << blockHash << " BLOCK HASHES" << endl;
        cout <<"BLOCK DATA STORING THREAD COMPLETED. STORED " << blockData << " BLOCK DETAILS" << endl;
        cout <<"BLOCK INDEX STORING THREAD COMPLETED. STORED " << blockIndex << " BLOCK INDEXES" << endl;
    }

    //TX-DATA-STORE
    void runTxMainThread(){
        //create id-hash connection
        hashmapper::idHashMapperDB map2 ("blockchain-core", "hash-id-mapping", "tx");
        bool is_begining = false;

        checker.lock();
        if(isFromBegining){
            is_begining = true;
        }
        checker.unlock();

        //create database connection
        indexMapper::indexes dbConnectionTx ("blockchain-core", "tx",is_begining);

        if(is_begining){
            //create tx-data table and index table
            dbConnectionTx.createTable(txDetailsTable);
            dbConnectionTx.createTable(txIndexTable);
        }

        int txHash,txData,txIndex = 0;
        std::vector<json> tData;
        std::vector<std::vector<int>> tIndex;

        while (true){
            //check id-hash map
            if(!txHashIdVector.empty()){
                std::vector<std::vector<string>> h3;

                mtxh3.lock();
                h3.push_back(txHashIdVector[0]);
                txHashIdVector.erase (txHashIdVector.begin());
                mtxh3.unlock();

                string tx_hash = h3[0][0];
                string lastTransactionId = h3[0][1];

                map2.insertKey(tx_hash,lastTransactionId);
                h3.erase (h3.begin());
                txHash++;
            }

            //check tx-data store
            mtxt1.lock();
            if(outputOfTx.size() >= 1000){
                long currentSize = outputOfTx.size();
                tData = outputOfTx;
                txData += currentSize;

                outputOfTx.erase(outputOfTx.begin(),outputOfTx.begin()+currentSize);

            }else if(outputOfTx.size() < 1000 & isAllBlockDone){
                long currentSize = outputOfTx.size();
                tData = outputOfTx;
                txData += currentSize;

                outputOfTx.erase(outputOfTx.begin(),outputOfTx.begin()+currentSize);
            }
            mtxt1.unlock();

            if(!tData.empty()){
                dbConnectionTx.insertTxData(tData);
                tData.clear();
            }

            //check tx-index store
            mtxt2.lock();
            if(outputIndexOfTx.size() >= 1000){
                long currentSize = outputIndexOfTx.size();
                tIndex = outputIndexOfTx;
                txIndex += currentSize;

                outputIndexOfTx.erase(outputIndexOfTx.begin(),outputIndexOfTx.begin()+currentSize);

            }else if(outputIndexOfTx.size() < 1000 & isAllBlockDone){
                long currentSize = outputIndexOfTx.size();
                tIndex = outputIndexOfTx;
                txIndex += currentSize;

                outputIndexOfTx.erase(outputIndexOfTx.begin(),outputIndexOfTx.begin()+currentSize);
            }
            mtxt2.unlock();

            if(!tIndex.empty()){
                dbConnectionTx.insertTxIndex(tIndex);
                tIndex.clear();
            }

            //check break condition to end the while loop
            if(txHashIdVector.empty() && isAllBlockDone && outputOfTx.empty() && outputIndexOfTx.empty()){
                break;
            }
        }

        map2.close();
        dbConnectionTx.close();
        cout <<"TX ID-HASH STORING THREAD COMPLETED. STORED " << txHash << " HASHES" << endl;
        cout <<"TX DATA STORING THREAD COMPLETED. STORED " << txData <<" TXES"<< endl;
        cout <<"TX INDEX STORING THREAD COMPLETED. STORED " << txIndex << " TX INDEXES" << endl;
    }

    void runSAIdHashMappingThread(){
        hashmapper::idHashMapperDB map4 ("blockchain-core", "hash-id-mapping", "stealth-address");
        int i=0;

        while (true){
            if(!saHashIdVector.empty()){
                std::vector<std::vector<string>> h1;

                mtxh1.lock();
                h1.push_back(saHashIdVector[0]);
                saHashIdVector.erase (saHashIdVector.begin());
                mtxh1.unlock();
                string sa_hash = h1[0][0];
                string lastSAId = h1[0][1];

                map4.insertKey(sa_hash,lastSAId);
                h1.erase(h1.begin());
                i++;
            }else if(saHashIdVector.empty() && isAllBlockDone){
                break;
            }
        }

        map4.close();
        cout <<"STEALTH-ADDRESS ID-HASH STORING THREAD COMPLETED. STORED " <<i << " HASHES" << endl;
    }
    void runSaDataStoreThread(){
        time_t Start,End;
        bool oneTime = true;
        bool is_begining = false;

        checker.lock();
        if(isFromBegining){
            is_begining = true;
        }
        checker.unlock();

        indexMapper::indexes dbConnectionSA ("blockchain-core", "-data", "stealth-address" ,is_begining );    //init database instance globally
        long i = 0;

        if(is_begining){
            //create data table for tx details
            dbConnectionSA.createTable(saDetailTable);
        }

        while (true){
            std::vector<json> temp;

            mtx.lock();
            if(outputOfStealthAddresses.size() >= 1000){
                long currentSize = outputOfStealthAddresses.size();
                temp = outputOfStealthAddresses;
                i += currentSize;

                outputOfStealthAddresses.erase(outputOfStealthAddresses.begin(),outputOfStealthAddresses.begin()+currentSize);
            }else if(outputOfStealthAddresses.size() < 1000 & isAllBlockDone){
                long currentSize = outputOfStealthAddresses.size();
                temp = outputOfStealthAddresses;
                i += currentSize;

                outputOfStealthAddresses.erase(outputOfStealthAddresses.begin(),outputOfStealthAddresses.begin()+currentSize);
            }
            mtx.unlock();

            if(!temp.empty()){
                dbConnectionSA.insertSAData(temp);
                temp.clear();

                if(isAllBlockDone){
                    time (& End);
                    if(oneTime){
                        time (& Start);
                        oneTime = false;
                    }
                    double dif= difftime (End, Start);
                    if(dif > 90){
                        cout<<"STORED STEALTH-ADDRESS DATA COUNT -" << i <<"/"<<lastStealthAddressId << endl;
                        time (& Start);

                    }
                }
            }

            if(outputOfStealthAddresses.empty() && isAllBlockDone){
                break;
            }

        }
        dbConnectionSA.close();
        cout << "SA DATA STORING THREAD COMPLETED. STORED " << i << " STEALTH-ADDRESSES" << endl;
    }
    void runSAIndexStoreThread(){
        time_t Start,End;
        bool oneTime = true;
        bool is_begining = false;

        checker.lock();
        if(isFromBegining){
            is_begining = true;
        }
        checker.unlock();

        int i = 0;
        indexMapper::indexes dbConnectionSAIndex ("blockchain-core", "stealth-address",is_begining);    //init database instance globally

        if(is_begining){
            dbConnectionSAIndex.createTable(saIndexTable);
        }


        while (true){
            std::vector<std::vector<int>> tempAr;

            mtx2.lock();
            if(outputIndexOfStealthAddresses.size() >= 1000){
                long currentSize = outputIndexOfStealthAddresses.size();
                tempAr = outputIndexOfStealthAddresses;
                i += currentSize;

                outputIndexOfStealthAddresses.erase(outputIndexOfStealthAddresses.begin(),outputIndexOfStealthAddresses.begin()+currentSize);

            }else if(outputIndexOfStealthAddresses.size() < 1000 & isAllBlockDone){
                long currentSize = outputIndexOfStealthAddresses.size();
                tempAr = outputIndexOfStealthAddresses;
                i += currentSize;

                outputIndexOfStealthAddresses.erase(outputIndexOfStealthAddresses.begin(),outputIndexOfStealthAddresses.begin()+currentSize);
            }
            mtx2.unlock();

            if(!tempAr.empty()){
                dbConnectionSAIndex.insertSAIndex(tempAr);
                tempAr.clear();

                if(isAllBlockDone){
                    time (& End);
                    if(oneTime){
                        time (& Start);
                        oneTime = false;
                    }
                    double dif= difftime (End, Start);
                    if(dif > 90){
                        cout <<"STORED STEALTH-ADDRESS INDEX COUNT -" << i <<"/"<<lastStealthAddressId << endl;
                        time (& Start);

                    }
                }
            }

            if(outputIndexOfStealthAddresses.empty() && isAllBlockDone){
                break;
            }
        }
        dbConnectionSAIndex.close();
        cout <<"SA INDEX STORING THREAD COMPLETED. STORED " <<i << " SA INDEXES" << endl;
    }

    void runRingMemberStoreThread(){
        time_t Start,End;
        bool oneTime = true;
        bool is_begining = false;

        checker.lock();
        if(isFromBegining){
            is_begining = true;
        }
        checker.unlock();

        int i = 0;

        if(is_begining){
            //create data table for tx details
            dbConnectionRM.createTable(rmDetailTable);
        }

        while (true){
            std::vector<json> tempInp;

            mtx3.lock();
            if(outputOfRingMembers.size() >= 1000){
                long currentSize = outputOfRingMembers.size();
                tempInp = outputOfRingMembers;
                i += currentSize;

                outputOfRingMembers.erase(outputOfRingMembers.begin(),outputOfRingMembers.begin()+currentSize);

            }else if(outputOfRingMembers.size() < 1000 & isAllBlockDone){
                long currentSize = outputOfRingMembers.size();
                tempInp = outputOfRingMembers;
                i += currentSize;

                outputOfRingMembers.erase(outputOfRingMembers.begin(),outputOfRingMembers.begin()+currentSize);
            }
            mtx3.unlock();

            if(!tempInp.empty()){
                dbConnectionRM.insertRMData(tempInp);
                tempInp.clear();

                if(isAllBlockDone){
                    time (& End);
                    if(oneTime){
                        time (& Start);
                        oneTime = false;
                    }
                    double dif= difftime (End, Start);
                    if(dif > 90){
                        cout <<"STORED DATA COUNT -" << i <<"/"<<lastStealthAddressId << endl;
                        time (& Start);

                    }
                }
            }
            if(outputOfRingMembers.empty() && isAllBlockDone){
                break;
            }
        }
        dbConnectionRM.close();
    }
    void runRMIndexStoreThread(){
        time_t Start,End;
        bool oneTime = true;
        bool is_begining = false;

        checker.lock();
        if(isFromBegining){
            is_begining = true;
        }
        checker.unlock();

        int i = 0;

        if(is_begining){
            dbConnectionRMIndex.createTable(rmIndexTable);
        }

        while (true){
            std::vector<std::vector<int>> tempArRI;

            mtx4.lock();
            if(outputIndexOfRingMembers.size() >= 1000){
                long currentSize = outputIndexOfRingMembers.size();
                tempArRI = outputIndexOfRingMembers;
                i += currentSize;

                outputIndexOfRingMembers.erase(outputIndexOfRingMembers.begin(),outputIndexOfRingMembers.begin()+currentSize);

            }else if(outputIndexOfRingMembers.size() < 1000 & isAllBlockDone){
                long currentSize = outputIndexOfRingMembers.size();
                tempArRI = outputIndexOfRingMembers;
                i += currentSize;

                outputIndexOfRingMembers.erase(outputIndexOfRingMembers.begin(),outputIndexOfRingMembers.begin()+currentSize);
            }
            mtx4.unlock();

            if(!tempArRI.empty()){
                dbConnectionRMIndex.insertRMIndex(tempArRI);
                tempArRI.clear();

                if(isAllBlockDone){
                    time (& End);
                    if(oneTime){
                        time (& Start);
                        oneTime = false;
                    }
                    double dif= difftime (End, Start);
                    if(dif > 90){
                        cout <<"STORED INDEX COUNT -" << i <<"/"<<lastStealthAddressId << endl;
                        time (& Start);

                    }
                }
            }

            if(outputIndexOfRingMembers.empty() && isAllBlockDone){
                break;
            }
        }
        dbConnectionRMIndex.close();
        cout <<"RM INDEX STORING THREAD COMPLETED. STORED " <<i << " RM INDEXES" << endl;
    }
    void runRMIdHashMappingThread(){
        int i = 0;
        while (true){
            if(!rmHashIdVector.empty()){
                string rm_hash;
                int lastRMId;
                mtxh5.lock();
                rm_hash = rmHashIdVector.begin()->first;
                lastRMId = rmHashIdVector.begin()->second;
                rmHashIdVector.erase(rmHashIdVector.begin());
                mtxh5.unlock();

                ringMemberHashMap.insertKey(rm_hash,to_string(lastRMId));
                i++;
            }else if(rmHashIdVector.empty() && isAllBlockDone){
                break;
            }
        }
    }

    //RUN-TIME, CPU Utilization and Memeroy Usage by Processors
    void init(unsigned long long lastTotalUser, unsigned long long lastTotalUserLow, unsigned long long lastTotalSys, unsigned long long lastTotalIdle){
        FILE* file = fopen("/proc/stat", "r");
        fscanf(file, "cpu %llu %llu %llu %llu", &lastTotalUser, &lastTotalUserLow, &lastTotalSys, &lastTotalIdle);
        fclose(file);
    }
    void performanceAnalyser(double timeUsage){
        //Virtual and Physical Memory usage
        struct sysinfo memInfo;
        sysinfo (&memInfo);

        if(pRamTotalSize == 0){
            long long totalPhysMem = memInfo.totalram;
            //Multiply in next statement to avoid int overflow on right hand side...
            totalPhysMem *= memInfo.mem_unit;
            pRamTotalSize = totalPhysMem;
        }

        long long physMemUsed = memInfo.totalram - memInfo.freeram;
        //Multiply in next statement to avoid int overflow on right hand side...
        physMemUsed *= memInfo.mem_unit;

        if(vRamTotalSize == 0){
            long long totalVirtualMem = memInfo.totalram;
            //Add other values in next statement to avoid int overflow on right hand side...
            totalVirtualMem += memInfo.totalswap;
            totalVirtualMem *= memInfo.mem_unit;
            vRamTotalSize = totalVirtualMem;
        }

        long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
        //Add other values in next statement to avoid int overflow on right hand side...
        virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
        virtualMemUsed *= memInfo.mem_unit;

        //CPU utilization performance
        static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;
        init(lastTotalUser,lastTotalUserLow, lastTotalSys, lastTotalIdle);

        double percent;
        FILE* fileName;
        unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;

        fileName = fopen("/proc/stat", "r");
        fscanf(fileName, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow,
               &totalSys, &totalIdle);
        fclose(fileName);

        if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
            totalSys < lastTotalSys || totalIdle < lastTotalIdle){
            //Overflow detection. Just skip this value.
            percent = -1.0;
        }
        else{
            total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
                    (totalSys - lastTotalSys);
            percent = total;
            total += (totalIdle - lastTotalIdle);
            percent /= total;
            percent *= 100;
        }

        //        cout << "Physical Memory Usage (bytes): " << physMemUsed <<"/"<< totalPhysMem << endl;
        //        cout << "Virtual Memory Usage (bytes) : " << virtualMemUsed <<"/"<< totalVirtualMem << endl;
        //        cout << "Processors Run Time (seconds): " << timeUsage << endl;
        //        cout << "CPU Utilization (percentage) : " << percent << "%"<< endl;

        //append data to vectors
        timeMarker.push_back(timeUsage);
        cpuMarker.push_back(percent);
        vRamMarker.push_back(virtualMemUsed);
        pRamMarker.push_back(physMemUsed);

    }
    void saveBenchmarks(string s1, string s2, string s3, string s4){
        std::ofstream file("benchmark/01.txt", std::ios::out);
        file << "PHYSICAL RAM USAGE (bytes)        - | " << s1  << endl;
        file << "VIRTUAL RAM USAGE (bytes)         - | " << s2  << endl;
        file << "RUN TIME DURATION PER 100/blocks  - | " << s3  << endl;
        file << "CPU UTILIZATION (percentage)      - | " << s4   << endl;
    }
    void printPerformance(){
        string timeMarkerString,vRamMarkerString,pRamMarkerString,cpuMarkerString;
        for(int x =0; x < timeMarker.size() ;x++){
            timeMarkerString += to_string((int)timeMarker[x]) + " | ";
            vRamMarkerString += to_string(vRamMarker[x]) + " | ";
            pRamMarkerString += to_string(pRamMarker[x]) + " | ";
            cpuMarkerString  += to_string(cpuMarker[x])  + " | ";
        }

        cout << "" << endl;
        cout << "----------------------------------------------------------"  << endl;
        cout << " PERFORMANCE OF MONEROSCI PARSER DURING PARSING "            << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
        cout << "PHYSICAL RAM USAGE (bytes)        - | " << pRamMarkerString  << endl;
        cout << "VIRTUAL RAM USAGE (bytes)         - | " << vRamMarkerString  << endl;
        cout << "RUN TIME DURATION PER 100/blocks  - | " << timeMarkerString  << endl;
        cout << "CPU UTILIZATION (percentage)      - | " << cpuMarkerString   << endl;
        cout << "----------------------------------------------------------"  << endl;
        cout << "" << endl;

        saveBenchmarks(pRamMarkerString,vRamMarkerString,timeMarkerString,cpuMarkerString);
    }

    //MAIN FUNCTION
    void showCurrentStatus(int currentBlockHeight){
        cout << "" << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << currentBlockHeight-1 << " - BLOCK DATA HAS LOADED TO THE MAIN MEMORY" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
        cout << "TOTAL BLOCKS            -" << lastBlockId -1 << endl;
        cout << "TOTAL TRANSACTIONS      -" << lastTransactionId -1 << endl;
        cout << "TOTAL STEALTH ADDRESSES -" << lastStealthAddressId -1 << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << "" << endl;
    }
    void mainFunction(page& monerosci,int start,int end, uint64_t current_blockchain_height){
        //load last ids to global variables
        getLastIdList();
        time_t Start, End;
        time (& Start);

        int x;
        for(x = start; x <= end; x++){
            coreProcessor(monerosci, to_string(x));
            cout << "MoneroSci-parser has parsed blockchain data of "+ std::to_string(x)+ "/" << current_blockchain_height << endl;

            if(x%1000 == 0){
                time (& End);
                double timeUsage = difftime (End, Start);
                performanceAnalyser(timeUsage);
            }
        }

        //store the last id in rocksdb hash-id mapping
        storeLastIdList();
        ringMemberHashMap.close();

        showCurrentStatus(x);
        printPerformance();
        isAllBlockDone = true;

    }

}


















