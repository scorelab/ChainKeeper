cmake_minimum_required(VERSION 3.14)
include(ExternalProject)

# Adding customized cmake module for building boost
list(APPEND CMAKE_MODULE_PATH  "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(analysis_library)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

## Find default python libraries and interpreter
find_package(Boost COMPONENTS filesystem system date_time python27 REQUIRED)
#message("Include dirs of boost: " ${Boost_INCLUDE_DIRS} )
#message("Libs of boost: " ${Boost_LIBRARIES} )

find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
message("Include dirs of Python: " ${PYTHON_INCLUDE_DIRS} )
message("Libs of Python: " ${PYTHON_LIBRARIES} )
include(BuildBoost) # Custom module

include_directories(${Boost_INCLUDE_DIR} ${PYTHON_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIR})

set(LIBRARIES)

# Build and link the chainkeeper_analysis module
add_library(chainkeeper_analysis SHARED
        python_module.cpp
        classes/blockchain/Blockchain_py.h
        classes/Globals_py.h
        classes/blockchain/Tx_py.h
        classes/blockchain/Block_py.h
        classes/blockchain/Input_py.h
        classes/addresses/Address_py.h
        classes/addresses/Address_py.h rocks_db/connection.h memory-mapper/mmap.hpp memory-mapper/page.h memory-mapper/shared_mmap.h memory-mapper/string_util.h)
target_link_libraries(chainkeeper_analysis ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${LIBRARIES})
add_dependencies(chainkeeper_analysis Boost)

# Tweaks the name of the library to match what Python expects
set_target_properties(chainkeeper_analysis PROPERTIES  LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out SUFFIX .so)
set_target_properties(chainkeeper_analysis PROPERTIES  LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out PREFIX "")

# Note ---------------
# If Boost not work import it to the c++ usr/include file path in relevant OS type
# In MacOS - copy the /usr/local/include/boost folder to the /Library/Developer/CommandLineTools/usr/include path