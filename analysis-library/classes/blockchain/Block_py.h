#ifndef ANALYSIS_LIBRARY_BLOCK_PY_H
#define ANALYSIS_LIBRARY_BLOCK_PY_H

class Block {

public:

    //attributes
    int height;
    std::string hash;
    int timestamp;
    int size;
    int tx_count;
    int block_index;
    int nonce;
    std::string prev_block_hash;
    std::string next_block_hash;
    int input_count;
    int output_count;

    // Constructor
    Block();

    //constructor for Block from index
    Block(int index);

    //constructor for Block from hash
    Block(std::string hash);

    // Methods
    std::string str();

    Block next_block();

    Block prev_block();

    boost::python::list coinbase_tx();

    long int fee();

    boost::python::list txes();

};

#endif //ANALYSIS_LIBRARY_BLOCK_PY_H
