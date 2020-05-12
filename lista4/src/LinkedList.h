#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <vector>
#include "DataStructure.h"

class LinkedList : public DataStructure {
public:
    LinkedList();
    void insert(std::string elem) override;
    void load(std::string filename) override;
    void deleteElem(std::string elem) override;
    bool find(std::string elem) override;
    std::string min() override;
    std::string max() override;
    std::string successor(std::string elem) override;
    void inorder() override;

    //function for changing LinkedList to RedBlackTree in HashMap
    std::vector<std::string> removeAllElements();

private:
    Node* head;
};


#endif //LINKEDLIST_H
