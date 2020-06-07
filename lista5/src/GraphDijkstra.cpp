#include <limits>

#include "GraphDijkstra.h"
#include "PriorityQueue.h"

GraphDijkstra::GraphDijkstra(int nodes) {
    this->nodesAmount = nodes;
    this->nodes = std::vector<Node*>(nodes + 1);

    for (int i = 1; i <= nodes; i++)
        this->nodes[i] = new Node{.index = i, .edgeList = std::vector<Edge*>()};
}

void GraphDijkstra::getEdgesFromStdin() {
    int edgesAmount;
    scanf("%d", &edgesAmount);

    int node1;
    int node2;
    double value;

    for (int i = 0; i < edgesAmount; i++) {
        scanf("%d %d %lf", &node1, &node2, &value);
        this->nodes[node1]->edgeList.emplace_back(new Edge(this->nodes[node1], this->nodes[node2], value));
    }
}


void GraphDijkstra::dijkstra(int startNode) {
    this->startNode = startNode;
    this->dijkstraDistance = std::vector<double>(this->nodesAmount + 1, std::numeric_limits<double>::infinity());
    this->dijkstraPathValue = std::vector<double>(this->nodesAmount + 1);
    this->dijkstraPath = std::vector<int>(this->nodesAmount + 1, -1);
    PriorityQueue<Node*> queue;

    for (int i = 1; i <= nodesAmount; i++) {
        queue.insert(this->nodes[i], std::numeric_limits<double>::infinity());
    }

    queue.priority(this->nodes[startNode], 0);
    this->dijkstraDistance[startNode] = 0;
    this->dijkstraPath[startNode] = startNode;

    while (!queue.empty()) {
        Node* node = queue.pop();
        for (Edge* edge : node->edgeList) {
            if (this->dijkstraDistance[edge->node2->index] > this->dijkstraDistance[edge->node1->index] + edge->value) {
                this->dijkstraDistance[edge->node2->index] = this->dijkstraDistance[edge->node1->index] + edge->value;
                this->dijkstraPath[edge->node2->index] = edge->node1->index;
                this->dijkstraPathValue[edge->node2->index] = edge->value;
                queue.priority(edge->node2, this->dijkstraDistance[edge->node2->index]);
            }
        }
    }
}

void GraphDijkstra::showDijkstraAnswer() {
    for (int i = 1; i <= this->nodesAmount; i++)
        printf("%d %f\n", i, this->dijkstraDistance[i]);

    for (int i = 1; i <= this->nodesAmount; i++) {
        if (this->dijkstraPath[i] > -1) {
            std::string answer = std::to_string(i);
            int j = i;

            while (j != this->startNode) {
                answer.insert(0,
                        std::to_string(this->dijkstraPath[j])
                        + " ("
                        + std::to_string(this->dijkstraPathValue[j])
                        + ") ");
                j = this->dijkstraPath[j];
            }
            fprintf(stderr, "%s\n", answer.c_str());
        } else {
            fprintf(stderr, "no path to %d\n", i);
        }
    }
}
