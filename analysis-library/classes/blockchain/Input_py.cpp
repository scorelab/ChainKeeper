#include <iostream>
#include <string>
#include "Input_py.h"
#include "Output_py.h"
#include "Tx_py.h"
#include "Block_py.h"
#include "../../rocks_db/connection.h"
#include "../Globals_py.h"

using namespace std;


Input::Input(std::map<string, string> inputData) {
    block_index = atoi(inputData.find("BLOCK_ID")->second.c_str());
    tx_index = atoi(inputData.find("TX_ID")->second.c_str());
    amount = (inputData.find("INPUT_AMOUNT")->second != "?" ? stod(inputData.find("INPUT_AMOUNT")->second):0);
}