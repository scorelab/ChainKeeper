#ifndef ANALYSIS_LIBRARY_TX_PY_H
#define ANALYSIS_LIBRARY_TX_PY_H

class Tx {

    //Attributes
    bool is_coinbase;
    int block_height;
    std::string hash;
    int fee;
    int base_size;
    int input_count;
    int input_value;
    int output_count;
    int output_value;
    int timestamp;
    std::string timestamp_utc;
    double size;
    int tx_index;

    // Constructor
    Tx();

    //constructor for get Tx from index
    Tx(int index);

    //constructor for get Tx from hash
    Tx(std::string hash);

    // Methods
    std::string str();

    boost::python::list outputs();

    boost::python::list inputs();
};

#endif //ANALYSIS_LIBRARY_TX_PY_H
