#ifndef ANALYSIS_LIBRARY_BLOCKCHAIN_PY_H
#define ANALYSIS_LIBRARY_BLOCKCHAIN_PY_H

#include "Tx_py.h"

class Blockchain {

public:
    // Constructor
    Blockchain(std::string url);

    //Methods
    int address_count();

    Address address_from_string(std::string address);

    Address address_from_index(int index);

    boost::python::list blocks();

    boost::python::list block_range(int startBlock, int endBlock);

    int tx_count();

    Tx transaction_with_hash(std::string hash);

    Tx transaction_with_index(int index);

    boost::python::list filter_tx(std::string query);

    boost::python::list all_outputs(int startBlock, int endBlock);

    boost::python::list all_inputs(int startBlock, int endBlock);
};

#endif //ANALYSIS_LIBRARY_BLOCKCHAIN_PY_H
