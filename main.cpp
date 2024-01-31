#include <iostream>
#include "blockchain.hpp"

int main() {
  uint64_t id = 0;
  uint64_t nonce = 1234;
  Block blc = Block(id, "123", "some det");
  std::cout << blc.toString();
  
  return 0;
}