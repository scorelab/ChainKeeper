#ifndef ANALYSIS_LIBRARY_INPUT_PY_H
#define ANALYSIS_LIBRARY_INPUT_PY_H

#include <map>
#include "../addresses/Address_py.h"

using namespace std;
class Block;
class Tx;

using namespace std;

class Input {

public:
    int block_index;
    int tx_index;
    double amount;
    int age;

    Input(std::__1::map<string, string> inputData);

    // Methods
    std::string str();

    Address address();
};


#endif //ANALYSIS_LIBRARY_INPUT_PY_H
