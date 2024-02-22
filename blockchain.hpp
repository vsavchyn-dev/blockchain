#include <openssl/sha.h>

#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

class Block {
    uint64_t id_;
    uint64_t nonce_;
    std::string prev_hash_;
    std::string tran_details_;
    uint64_t tran_time_;
    std::string tran_hash_;

    std::string hash(const uint64_t& id, const uint64_t& nonce,
                     const std::string& prev_hash, const std::string& details,
                     uint64_t time_point);
    std::pair<std::string, uint64_t> mine(const uint64_t& id,
                                          const std::string& prev_hash,
                                          const std::string& details,
                                          uint64_t time_point);

public:
    Block(const uint64_t& id, const std::string& prev_hash,
          const std::string& details);

    const uint64_t& getId() const;
    const std::string& getHash() const;
    const std::string& getPrevHash() const;
    std::string toString() const;
};

class Blockchain {
    std::list<Block> chain;
    inline Block createGenesis() const;

public:
    Blockchain();

    bool isBlockValid(const Block& currBlock, const Block& prevBlock) const;
    bool isChainValid() const;

    bool tryAddNewBlock(const Block& block);

    const Block& getLast() const;
    const uint64_t getChainLen() const;
};
