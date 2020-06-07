#ifndef GRAPH_H
#define GRAPH_H


#include <vector>

#include "Node.h"

class GraphDijkstra {
public:
    explicit GraphDijkstra(int nodes);
    void getEdgesFromStdin();

    void dijkstra(int startNode);
    void showDijkstraAnswer();

private:
    int nodesAmount;
    int startNode;

    std::vector<Node*> nodes;
    std::vector<double> dijkstraDistance;
    std::vector<double> dijkstraPathValue;
    std::vector<int> dijkstraPath;
};


#endif //GRAPH_H
