#include "blockchain.hpp"
#include <cstdint>
#include <string>

const std::string DIFFICULTY_PREFIX = "00000";

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

    for (;;) {
        std::string hash_sha = hash(id, nonce, prev_hash, details, time_point);

        if (hash_sha.starts_with(DIFFICULTY_PREFIX)) {
            std::cout << "Block " << id << " was mined!\n";
            return std::pair<std::string, uint64_t>(hash_sha, nonce);
        }

        nonce++;
    }
}

const uint64_t& Block::getId() const {
    return id_;
}

const std::string& Block::getHash() const {
    return tran_hash_;
}

const std::string& Block::getPrevHash() const {
    return prev_hash_;
}

std::string Block::toString() const {
    std::string retStr = std::to_string(id_) + "|" + prev_hash_ + "|" +
                         std::to_string(tran_time_) + "|" + tran_details_ +
                         "|" + std::to_string(nonce_) + "|" + tran_hash_;

    return retStr;
}

inline Block Blockchain::createGenesis() const {
    return Block(0, "0000", "genesis");
}

Blockchain::Blockchain() {
    chain.push_back(this->createGenesis());
}

bool Blockchain::isBlockValid(const Block& currBlock,
                              const Block& prevBlock) const {
    if (currBlock.getId() == prevBlock.getId() + 1 &&
        currBlock.getPrevHash() == prevBlock.getHash()) {
        std::cout << "Block " << currBlock.getId() << " is valid\n";
        return true;
    } else {
        std::cout << "Block " << currBlock.getId() << " is invalid\n";
        return false;
    }
}

bool Blockchain::isChainValid() const {
    auto previousBlock = chain.begin();
    auto currentBlock = ++chain.begin();

    std::cout << "Checking validity of chain:\n";

    for (uint64_t i = 1; i < chain.size(); i++) {
        if (!isBlockValid(*currentBlock, *previousBlock)) {
            return false;
        }

        ++previousBlock;
        ++currentBlock;
    }

    return true;
}

bool Blockchain::tryAddNewBlock(const Block& block) {
    Block last = this->getLast();

    if (isBlockValid(block, last)) {
        chain.push_back(block);
        std::cout << "Block was succesfully added to blockchain\n";
        return true;
    } else {
        std::cout << "Can\'t add block " << block.getId() << " - invalid\n";
        return false;
    }
}

const Block& Blockchain::getLast() const {
    return chain.back();
}

const uint64_t Blockchain::getChainLen() const {
    return chain.size();
}
