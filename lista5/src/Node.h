#ifndef NODE_H
#define NODE_H


#include <vector>

struct Edge;

struct Node {
    int index;
    std::vector<Edge*> edgeList;
};

struct Edge {
    Node* node1;
    Node* node2;
    double value;

    Edge(Node* n1, Node* n2, double v) {
        this->node1 = n1;
        this->node2 = n2;
        this->value = v;
    }
};

#endif //NODE_H
