#ifndef HASHMAP_H
#define HASHMAP_H


#include <map>
#include "DataStructure.h"
#include "RedBlackTree.h"
#include "LinkedList.h"

class HashMap : public DataStructure {
public:
    HashMap();
    void insert(std::string elem) override;
    void load(std::string filename) override;
    void deleteElem(std::string elem) override;
    bool find(std::string elem) override;
    std::string min() override;
    std::string max() override;
    std::string successor(std::string elem) override;
    void inorder() override;

private:
    std::map<uint64_t, DataStructure*> map;
    std::hash<std::string> hash;
    const int maxListSize = 5;

    void LinkedListToRedBlackTree(uint64_t hashValue);
    void RedBlackTreeToLinkedList(uint64_t hashValue);
};


#endif //HASHMAP_H
