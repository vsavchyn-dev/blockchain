cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "--std=c++20")

project(Simplified-blockchain)

find_package(OpenSSL REQUIRED)

add_executable(main main.cpp blockchain.cpp)

target_link_libraries(main PRIVATE OpenSSL::SSL OpenSSL::Crypto)

