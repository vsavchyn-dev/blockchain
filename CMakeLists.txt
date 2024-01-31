cmake_minimum_required(VERSION 3.10)

project(Simplified-blockchain)

find_package(OpenSSL REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE OpenSSL::SSL OpenSSL::Crypto)