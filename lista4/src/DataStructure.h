#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H


#include <string>

struct Node;

class DataStructure {
public:
    virtual void insert(std::string elem) = 0;
    virtual void load(std::string filename) = 0;
    virtual void deleteElem(std::string elem) = 0;
    virtual bool find(std::string elem) = 0;
    virtual std::string min() = 0;
    virtual std::string max() = 0;
    virtual std::string successor(std::string elem) = 0;
    virtual void inorder() = 0;

    virtual int getSize();
    virtual int getMaxSize();

protected:
    int size;
    int maxSize;

    std::string cleanElem(std::string elem);
    //return true, if node1 < node2, false otherwise
    bool isLower(const Node* node1, const Node* node2); //TODO usunac
};


#endif //DATASTRUCTURE_H
