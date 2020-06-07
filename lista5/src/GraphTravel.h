#ifndef GRAPHTRAVEL_H
#define GRAPHTRAVEL_H


#include <vector>

#include "Node.h"

class GraphTravel {
public:
    explicit GraphTravel(int nodesAmount);
    void getEdgesFromStdin();
    void randomTravel();
    void minEdgeTravel();
    void mstEulerTravel();

private:
    int nodesAmount;
    int edgesAmount;
    std::vector<Node*> nodes;
    std::vector<bool> nodeIfVisited;
};


#endif //GRAPHTRAVEL_H
