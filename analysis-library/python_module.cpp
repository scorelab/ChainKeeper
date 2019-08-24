#include <iostream>
#include <string>
#include <boost/python.hpp>
#include <Python.h>
#include "classes/Globals_py.h"

#include "classes/blockchain/Blockchain_py.h"
#include "classes/blockchain/Block_py.h"
#include "classes/blockchain/Tx_py.h"
#include "classes/blockchain/Input_py.h"
#include "classes/blockchain/Output_py.h"

#include "classes/addresses/Address_py.h"

using namespace boost::python;
using namespace std;

// Defines a python module which will be named "chainkeeper_analysis"
BOOST_PYTHON_MODULE(chainkeeper_analysis) {

    class_< Blockchain >("Blockchain", init<std::string>())
            .enable_pickling()
            .def("__len__", &Blockchain::block_count)
            .def("tx_count", &Blockchain::tx_count)
            .def("blocks", &Blockchain::blocks)
            .def("range", &Blockchain::block_range)
            .def("tx_with_hash", &Blockchain::tx_with_hash)
            .def("tx_with_index", &Blockchain::tx_with_index);

    class_< Block >("Block",init<string>())
            .enable_pickling()
            .def(init<int>())
            .def_readonly("timestamp", & Block::timestamp)
            .def_readonly("hash", & Block::hash)
            .def_readonly("prev_block_hash", & Block::prev_block_hash)
            .def_readonly("next_block_hash", & Block::next_block_hash)
            .def_readonly("height", & Block::height)
            .def_readonly("size", & Block::size)
            .def_readonly("tx_count", & Block::tx_count)
            .def_readonly("nonce", & Block::nonce)
            .def_readonly("block_index", & Block::block_index)
            .def("next_block", &Block::next_block)
            .def("prev_block", &Block::prev_block)
            .def("coinbase_tx", &Block::coinbase_tx)
            .def("fee", &Block::fee)
            .def("txes", &Block::txes)
            .def("__str__", &Block::str);


    class_< Tx >("Tx")
            .enable_pickling()
            .def(init<string>())
            .def(init<int>())
            .def_readonly("timestamp", &Tx::timestamp)
            .def_readonly("is_coinbase", &Tx::is_coinbase)
            .def_readonly("hash", &Tx::hash)
            .def_readonly("block_height", &Tx::block_height)
            .def_readonly("timestamp_utc", &Tx::timestamp_utc)
            .def_readonly("size", &Tx::size)
            .def_readonly("input_count", &Tx::input_count)
            .def_readonly("output_count", &Tx::output_count)
            .def_readonly("fee", &Tx::fee)
            .def_readonly("tx_index", &Tx::tx_index)
            .def("block", &Tx::blockObj)
            .def("outputs", &Tx::outputs)
            .def("inputs", &Tx::inputs)
            .def("__str__", &Tx::str);

    class_< Output >("Output", init<int,int>())
            .enable_pickling()
            .def_readonly("block_index", &Output::block_index)
            .def_readonly("amount", &Output::amount)
            .def_readonly("tx_index", &Output::tx_index)
            .def("__str__", &Output::str);

    class_< Input >("Input", init<int>())
            .enable_pickling()
            .def(init<string>())
            .def_readonly("block_index", &Input::block_index)
            .def_readonly("tx_index", &Input::tx_index)
            .def("__str__", &Input::str)

}
