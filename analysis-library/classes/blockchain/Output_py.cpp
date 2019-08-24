#include <thread>
#include <mutex>
#include "Output_py.h"
#include "Tx_py.h"
#include "Block_py.h"

Output::Output(std::map <string, string> output_data_map) {
    block_index = atoi(output_data_map.find("BLOCK_ID")->second.c_str());
    tx_index = atoi(output_data_map.find("TX_ID")->second.c_str());
    amount = (output_data_map.find("AMOUNT")->second != "?" ? stod(output_data_map.find("AMOUNT")->second):0);
}