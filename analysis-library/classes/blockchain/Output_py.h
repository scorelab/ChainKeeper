#ifndef ANALYSIS_LIBRARY_OUTPUT_PY_H
#define ANALYSIS_LIBRARY_OUTPUT_PY_H

#include <boost/python/list.hpp>
#include "../addresses/Address_py.h"
#include "Block_py.h"
#include "Tx_py.h"

class Output {

public:

    bool is_spent;
    int block_index;
    int tx_index;
    double amount;

    Output(std::map <string, string> outputData);

    // Methods
    std::string str();

    Address address();

    Block block();

    Tx tx();

    boost::python::list spending_tx();
};


#endif //ANALYSIS_LIBRARY_OUTPUT_PY_H
