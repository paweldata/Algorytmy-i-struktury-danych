#ifndef BLOOM_H
#define BLOOM_H


#include <vector>
#include <bitset>

#include "DataStructure.h"

struct Hash;

class Bloom : public DataStructure {
public:
    Bloom();
    void insert(std::string elem) override;
    void load(std::string filename) override;
    void deleteElem(std::string elem) override;
    bool find(std::string elem) override;
    std::string min() override;
    std::string max() override;
    std::string successor(std::string elem) override;
    void inorder() override;

    int getSize() override;
    int getMaxSize() override;

private:
    static const int arraySize = 2000000;
    const int hashAmount = 6;

    std::vector<Hash> hashFunctions;
    std::bitset<arraySize> array;
};


#endif //BLOOM_H
