cmake_minimum_required(VERSION 3.14)
project(analysis_library)

set(CMAKE_CXX_STANDARD 14)

include_directories(classes)
include_directories(classes/addresses)
include_directories(classes/blockchain)
include_directories(memory-mapper)
include_directories(rocks_db)
include_directories(sqlite_db)

add_executable(analysis_library
        classes/addresses/Address_py.h
        classes/blockchain/Block_py.h
        classes/blockchain/Blockchain_py.h
        classes/blockchain/Input_py.h
        classes/blockchain/Output_py.h
        classes/blockchain/Tx_py.h
        classes/Globals_py.h
        memory-mapper/mmap.hpp
        memory-mapper/page.h
        memory-mapper/shared_mmap.h
        memory-mapper/string_util.h
        rocks_db/connection.h
        sqlite_db/sqlitecon.hpp
        python_module.cpp)
