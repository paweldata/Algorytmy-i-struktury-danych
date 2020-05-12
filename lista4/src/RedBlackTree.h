#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H


#include <vector>
#include "DataStructure.h"

struct Node;

class RedBlackTree : public DataStructure {
public:
    RedBlackTree();
    void insert(std::string elem) override;
    void load(std::string filename) override;
    void deleteElem(std::string elem) override;
    bool find(std::string elem) override;
    std::string min() override;
    std::string max() override;
    std::string successor(std::string elem) override;
    void inorder() override;

    //function for changing RedBlackTree to LinkedList in HashMap
    std::vector<std::string> removeAllElements();

private:
    Node* root;
    Node* null;

    void leftRotate(Node* node);
    void rightRotate(Node* node);
    void inorderRecursive(Node* node);
    Node* minNode(Node* node);
    Node* findNode(const std::string& elem);
    Node* successorNode(Node* node);
    void deleteElemFixup(Node* node);

};


#endif //REDBLACKTREE_H
