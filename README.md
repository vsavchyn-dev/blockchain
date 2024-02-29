# Simplified Blockchain

This project is a simple implementation of a blockchain using C++ and OpenSSL's SHA256 algorithm.

## Prerequisites

Before you begin, ensure you have met the following requirements:

- You have installed the latest version of [CMake](https://cmake.org/download/).
- You have installed [vcpkg](https://github.com/microsoft/vcpkg), a C++ package manager.

## Building the Project

To build the project, follow these steps:

1. **Clone the repository**:

```sh
git clone https://github.com/vsavchyn-dev/blockchain
cd blockchain
```

2. **Install the projcet dependencies**:

This project depends on OpenSSL. You can install it using vcpkg in directory:

```sh
vcpkg install openssl
```

3. **Configure the project with CMake**:

```sh
cmake -B build . -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystem/vcpkg.cmake
```

4. **Build the project**:

```sh
cd ./build/ && make
```

## Running the project

After building the project, you can run it with:

```sh
./blockchain-exmp
```

This will start the blockchain simulation.