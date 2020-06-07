#ifndef GRAPHMST_H
#define GRAPHMST_H


#include <vector>

#include "Node.h"

class GraphMST {
public:
    explicit GraphMST(int nodesAmount);
    void getDataFromStdin();
    void setNodes(std::vector<Node*> nodeList, int edgesAmount);

    void kruskal();
    void prim();

    void showMstOnStdout();
    std::vector<Edge*> getMst();

private:
    int nodesAmount;
    int edgesAmount;

    std::vector<Node*> nodes;
    std::vector<Edge*> edges;
    std::vector<Edge*> edgesMst;

    //kruskal
    std::vector<Node*> parents;
    std::vector<int> ranks;

    Node* getRoot(Node* node);
    void unionNodes(Node* node1, Node* node2);
    void edgesMergeSort();
    void edgesMergeSortRecursion(std::vector<Edge*> temp, int left, int right);

    //prim
    std::vector<Edge*> bestEdge;
    std::vector<double> cost;
};


#endif //GRAPHMST_H
