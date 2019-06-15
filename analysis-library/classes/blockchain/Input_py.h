#ifndef ANALYSIS_LIBRARY_INPUT_PY_H
#define ANALYSIS_LIBRARY_INPUT_PY_H

#include "../addresses/Address_py.h"

class Input {

public:
    int block_index;
    int tx_index;
    double amount;
    int age;

    Input(int index);

    // Methods
    std::string str();

    Address address();

    Block block();

    Tx tx();

    boost::python::list spent_tx();
};


#endif //ANALYSIS_LIBRARY_INPUT_PY_H
