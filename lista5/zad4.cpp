#include <cstdio>
#include "src/GraphTravel.h"


int main(int argc, char** argv) {
    int nodesAmount;
    scanf("%d", &nodesAmount);
    GraphTravel graph(nodesAmount);

    graph.getEdgesFromStdin();
    graph.randomTravel();
    graph.minEdgeTravel();
    graph.mstEulerTravel();

    return 0;
}
