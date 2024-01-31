#include <list>
#include <iomanip>
#include <string>
#include <sstream>
#include <chrono>
// format is used only in C++20 and later, then why the hell this shit doesn't wrok with stock complier on mac?
#include <format>
// include doesn't unless vcpkg works
#include <openssl/sha.h>

class Block {
    uint64_t id_;
    uint64_t nonce_;
    std::string prev_hash_;
    std::string tran_details_;
    std::chrono::time_point<std::chrono::system_clock> tran_time_;
    std::string tran_hash_;
    
    std::string hash(const uint64_t& id, const uint64_t& nonce, const std::string& prev_hash, const std::string& details, uint64_t time_point);
    std::pair<std::string, uint64_t> mine(const uint64_t& id, const std::string& prev_hash, const std::string& details, uint64_t time_point);
public:
    Block(const uint64_t& id, const std::string& prev_hash, const std::string& details);

    std::string toString() const;
};

// need to finish blockchain on it's own
struct Blockchain {
    std::list<Block> chain;
};