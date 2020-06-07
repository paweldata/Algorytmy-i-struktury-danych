#include <cstdio>
#include <ctime>

#include "src/GraphDijkstra.h"

int main() {
    clock_t start = clock();
    int nodesAmount;
    scanf("%d", &nodesAmount);

    GraphDijkstra graph(nodesAmount);
    graph.getEdgesFromStdin();

    int startNode;
    scanf("%d", &startNode);

    graph.dijkstra(startNode);
    graph.showDijkstraAnswer();

    clock_t stop = clock();
    fprintf(stderr, "Time : %f milliseconds\n", (double)(stop-start) / CLOCKS_PER_SEC * 1000);

    return 0;
}
