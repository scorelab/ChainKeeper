#ifndef ANALYSIS_LIBRARY_ADDRESS_PY_H
#define ANALYSIS_LIBRARY_ADDRESS_PY_H

class Address {

public:

    int balance;
    bool has_been_spent;

    //constructor
    Address(int index);

    // Methods
    std::string str();

    int in_txes_count();

    int out_txes_count();

    boost::python::list in_txes();

    boost::python::list out_txes();

    boost::python::list txes();
};

#endif //ANALYSIS_LIBRARY_ADDRESS_PY_H