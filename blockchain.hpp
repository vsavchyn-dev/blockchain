#include <chrono>
#include <iomanip>
#include <list>
#include <openssl/sha.h>
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

    std::string toString() const;
};

// need to finish blockchain on it's own
struct Blockchain {
    std::list<Block> chain;
};
