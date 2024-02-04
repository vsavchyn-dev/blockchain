cmake_minimum_required(VERSION 3.10)

SET(CMAKE_CXX_FLAGS "-std=c++2b")

project(Simplified-blockchain)

find_package(OpenSSL REQUIRED)

add_executable(main main.cpp blockchain.cpp)

target_link_libraries(main PRIVATE OpenSSL::SSL OpenSSL::Crypto)