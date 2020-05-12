#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H


#include "DataStructure.h"

struct Node;

class BinarySearchTree : public DataStructure {
public:
    BinarySearchTree();
    void insert(std::string elem) override;
    void load(std::string filename) override;
    void deleteElem(std::string elem) override;
    bool find(std::string elem) override;
    std::string min() override;
    std::string max() override;
    std::string successor(std::string elem) override;
    void inorder() override;

private:
    Node* root;
    void inorderRecursive(Node* node);
    Node* minNode(Node* node);
    Node* findNode(const std::string& elem);
    Node* successorNode(Node* node);
};


#endif //BINARYSEARCHTREE_H
