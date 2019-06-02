cmake_minimum_required(VERSION 3.14)
project(analysis_library)

include(ExternalProject)

# Adding customized cmake module for building boost
list(APPEND CMAKE_MODULE_PATH  "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find default python libraries and interpreter
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
include(BuildBoost) # Custom module

include_directories(${Boost_INCLUDE_DIR} ${PYTHON_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIR})

set(LIBRARIES
        )

# Build and link the monerosci module
add_library(chainkeeper_analysis SHARED python_module.cpp)
target_link_libraries(chainkeeper_analysis ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${LIBRARIES})
add_dependencies(chainkeeper_analysis Boost)

# Tweaks the name of the library to match what Python expects
set_target_properties(chainkeeper_analysis PROPERTIES  LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out SUFFIX .so)
set_target_properties(chainkeeper_analysis PROPERTIES  LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out PREFIX "")
