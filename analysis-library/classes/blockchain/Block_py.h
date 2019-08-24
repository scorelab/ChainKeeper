#ifndef ANALYSIS_LIBRARY_BLOCK_PY_H
#define ANALYSIS_LIBRARY_BLOCK_PY_H

#include <string>
#include <boost/python/list.hpp>

class Block {

public:

    //attributes
    int height;
    std::string hash;
    std::string timestamp;
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

    //constructor for Block from map data
    Block(std::map<std::string,std::string> blockData);

    // Methods
    std::string str();

    Block next_block();

    Block prev_block();

    boost::python::list coinbase_tx();

    long double fee();

    boost::python::list txes();

};

#endif //ANALYSIS_LIBRARY_BLOCK_PY_H
