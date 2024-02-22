#include "blockchain.hpp"

int main() {
    Blockchain* blc = new Blockchain();

    for (int i = 0; i < 100; i++) {
        Block prevBlock = blc->getLast();
        Block newBlock = Block(prevBlock.getId() + 1, prevBlock.getHash(),
                               "Very Very important shit");

        blc->tryAddNewBlock(newBlock);

        if (!(blc->getChainLen() % 10)) {
            blc->isChainValid();
        }
    }

    return 0;
}
