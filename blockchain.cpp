#include "blockchain.hpp"
#include <string>

Block::Block(const uint64_t& id, const std::string& prev_hash,
             const std::string& details)
    : id_(id), prev_hash_(prev_hash), tran_details_(details) {
    tran_time_ =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto out = mine(id, prev_hash, details, tran_time_);
    tran_hash_ = out.first;
    nonce_ = out.second;
}

std::string Block::hash(const uint64_t& id, const uint64_t& nonce,
                        const std::string& prev_hash,
                        const std::string& details, uint64_t time_point) {
    std::string coded = std::to_string(id) + prev_hash +
                        std::to_string(time_point) + details +
                        std::to_string(nonce);
    std::stringstream tmp_ss;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha;
    SHA256_Init(&sha);
    SHA256_Update(&sha, coded.c_str(), coded.size());
    SHA256_Final(hash, &sha);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        tmp_ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return tmp_ss.str();
}

std::pair<std::string, uint64_t> Block::mine(const uint64_t& id,
                                             const std::string& prev_hash,
                                             const std::string& details,
                                             uint64_t time_point) {
    uint64_t nonce = 0;

    // need to finish this
    for (;;) {
        std::string hash_sha = hash(id, nonce, prev_hash, details, time_point);
        return std::pair<std::string, uint64_t>(hash_sha, nonce);
    }
}

std::string Block::toString() const {
    std::string retStr = std::to_string(id_) + "|" + prev_hash_ + "|" +
                         std::to_string(tran_time_) + "|" + tran_details_ +
                         "|" + std::to_string(nonce_) + "|" + tran_hash_;

    return retStr;
}
