cmake_minimum_required(VERSION 3.5)
project(chain_parser)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

set(ChainParser_VERSION 0.1.0)

add_subdirectory(external)


find_package(OpenSSL REQUIRED)
find_package(Sparsehash REQUIRED)

find_package( Boost 1.58 COMPONENTS serialization iostreams filesystem REQUIRED )

file(GLOB PARSER_HEADERS "*.hpp")
file(GLOB PARSER_SOURCES "*.cpp")

set_source_files_properties(main.cpp PROPERTIES COMPILE_FLAGS "-Wno-reserved-id-macro -Wno-sign-conversion -Wno-extra-semi -Wno-undefined-func-template")

add_executable(chain_parser ${PARSER_SOURCES} ${PARSER_HEADERS})

target_compile_options(chain_parser PRIVATE -Wall -Wextra -Wpedantic)

if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
target_compile_options(chain_parser PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-old-style-cast -Wno-documentation-unknown-command -Wno-documentation -Wno-shadow -Wno-covered-switch-default -Wno-missing-prototypes -Wno-weak-vtables -Wno-unused-macros -Wno-padded)
endif()

source_group(chain_parser FILES ${PARSER_SOURCES} ${PARSER_HEADERS})

target_link_libraries( chain_parser OpenSSL::Crypto )
target_link_libraries( chain_parser bitcoinapi_static)
target_link_libraries( chain_parser clipp)
target_link_libraries( chain_parser Boost::serialization Boost::iostreams Boost::filesystem)
target_link_libraries( chain_parser secp256k1)
target_link_libraries( chain_parser sparsehash)

install(TARGETS chain_parser DESTINATION bin)