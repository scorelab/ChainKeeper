#ifndef ANALYSIS_LIBRARY_OUTPUT_PY_H
#define ANALYSIS_LIBRARY_OUTPUT_PY_H

class Output {

public:

    bool is_spent;
    int block_index;
    int tx_index;
    double amount;

    Input(int index);

    // Methods
    std::string str();

    Address address();

    Block block();

    Tx tx();

    boost::python::list spending_tx();
};


#endif //ANALYSIS_LIBRARY_OUTPUT_PY_H
