#ifndef ANALYSIS_LIBRARY_BLOCKCHAIN_PY_H
#define ANALYSIS_LIBRARY_BLOCKCHAIN_PY_H

#include "Tx_py.h"
#include "../addresses/Address_py.h"

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

    int block_count();

    int tx_count();

    Tx tx_with_hash(std::string hash);

    Tx tx_with_index(int index);
};

#endif //ANALYSIS_LIBRARY_BLOCKCHAIN_PY_H
