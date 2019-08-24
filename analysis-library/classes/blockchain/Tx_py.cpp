#include <iostream>
#include <string>
#include "Input_py.h"
#include "Output_py.h"
#include "Block_py.h"
#include "Tx_py.h"
#include "../../rocks_db/connection.h"
#include "../../sqlite_db/Tx_db.h"
#include "../Globals_py.h"

using namespace std;

Tx::Tx() {}

Tx::Tx(string hashVal) {
    rocksdb_mapping::connectDB txHashMap (parserOutputLocation, "hash-id-mapping", "tx");
    string hashID = txHashMap.getValueFromKey(hashVal);
    txHashMap.close();

    if(hashID != "null"){
        int index = atoi(hashID.c_str());
        TxData::TxData txIndex (parserOutputLocation, "blockchain-data", "tx");
        map<string, string> tx_map = txIndex.getTxDetails(index);

        is_coinbase = (atoi(tx_map.find("COIN_BASE")->second.c_str()) == 1 ? true:false);
        block_height = atoi(tx_map.find("HEIGHT")->second.c_str());
        hash = tx_map.find("HASH")->second;
        input_count = atoi(tx_map.find("INPUT_COUNT")->second.c_str());
        output_count = atoi(tx_map.find("OUTPUT_COUNT")->second.c_str());
        fee = stod(tx_map.find("TX_FEE")->second);
        timestamp = atoi(tx_map.find("TIMESTAMP")->second.c_str());
        timestamp_utc = tx_map.find("TIMESTAMP_UTC")->second;
        size = stod(tx_map.find("SIZE")->second);
        tx_index = index;
    }
}

Tx::Tx(std::map <string, string> txData) {
    is_coinbase = (atoi(txData.find("COIN_BASE")->second.c_str()) == 1 ? true:false);
    block_height = atoi(txData.find("HEIGHT")->second.c_str());
    hash = txData.find("HASH")->second;
    input_count = atoi(txData.find("INPUT_COUNT")->second.c_str());
    output_count = atoi(txData.find("OUTPUT_COUNT")->second.c_str());
    fee = stod(txData.find("TX_FEE")->second);
    timestamp = atoi(txData.find("TIMESTAMP")->second.c_str());
    timestamp_utc = txData.find("TIMESTAMP_UTC")->second;
    size = stod(txData.find("SIZE")->second);
    tx_index = atoi(txData.find("DATA_ID")->second.c_str());
}

Tx::Tx(int index) {
    TxData::TxData txIndex (parserOutputLocation, "blockhchain-data", "tx");
    map<string, string> tx_map = txIndex.getTxDetails(index);

    is_coinbase = (atoi(tx_map.find("COIN_BASE")->second.c_str()) == 1 ? true:false);
    block_height = atoi(tx_map.find("HEIGHT")->second.c_str());
    hash = tx_map.find("HASH")->second;
    input_count = atoi(tx_map.find("INPUT_COUNT")->second.c_str());
    output_count = atoi(tx_map.find("OUTPUT_COUNT")->second.c_str());
    fee = stod(tx_map.find("TX_FEE")->second);
    timestamp = atoi(tx_map.find("TIMESTAMP")->second.c_str());
    timestamp_utc = tx_map.find("TIMESTAMP_UTC")->second;
    size = stod(tx_map.find("SIZE")->second);
    tx_index = index;
}

//methods
string Tx::str() {
    return "Tx (numInputs="+ to_string(input_count) +", block_height="+ to_string(block_height)+", header_hash="+hash+", ""timestamp="+to_string(timestamp)+", bits="+to_string(size)+", numOutputs="+to_string(output_count)+", is_coinbase="+to_string(is_coinbase)+")";
}

boost::python::list Tx::outputs() {
    boost::python::list outputObjList;

    TxData::TxData txSAIndex (parserOutputLocation, "blockchain-indexes", "stealth-address");
    std::vector<int> sa_id = txSAIndex.getOutputsOfTX(tx_index);

    for(int x=0; x <sa_id.size(); x++ ){
        int sa_cur_id = sa_id[x];
        Output *outObj = new Output(tx_index,sa_cur_id);
        outputObjList.append(*outObj);
    }

    return outputObjList;
}

boost::python::list Tx::inputs() {
    boost::python::list inputObjList;

    //TODO
    return inputObjList;
}

Block Tx::blockObj() {
    TxData::TxData getBlockIndex (parserOutputLocation, "blockchain-data", "tx");
    int blockIndex = getBlockIndex.getBlockIndexFromTxIndex(tx_index);

    Block *blk = new Block(blockIndex);

    return *blk;
}
