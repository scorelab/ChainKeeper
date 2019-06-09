#include <iostream>
#include <string>
#include <boost/python.hpp>
#include <Python.h>
#include "classes/blockchain/Blockchain_py.h"
#include "classes/blockchain/Block_py.h"
#include "classes/blockchain/Tx_py.h"
#include "classes/blockchain/Input_py.h"
#include "classes/blockchain/Output_py.h"

#include "classes/addresses/Address_py.h"

using namespace boost::python;

// Defines a python module which will be named "chainkeeper_analysis"
BOOST_PYTHON_MODULE(chainkeeper_analysis) {

    class_<Blockchain>("Blockchain", init<std::string>())
            .enable_pickling();
}
