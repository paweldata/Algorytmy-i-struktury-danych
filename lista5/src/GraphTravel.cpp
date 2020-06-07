#include <cstdio>
#include <random>
#include <map>

#include "GraphTravel.h"
#include "GraphMST.h"

GraphTravel::GraphTravel(int nodesAmount) {
    this->nodesAmount = nodesAmount;
    this->edgesAmount = nodesAmount * (nodesAmount - 1) / 2;
    this->nodes = std::vector<Node*>(nodesAmount + 1);
    this->nodeIfVisited = std::vector<bool>(nodesAmount + 1, false);

    for (int i = 1; i <= this->nodesAmount; i++)
        this->nodes[i] = new Node{.index = i, .edgeList = std::vector<Edge*>()};
}

void GraphTravel::getEdgesFromStdin() {
    int node1;
    int node2;
    double value;

    for (int i = 0; i < this->edgesAmount; i++) {
        scanf("%d %d %lf", &node1, &node2, &value);
        this->nodes[node1]->edgeList.emplace_back(new Edge(this->nodes[node1], this->nodes[node2], value));
        this->nodes[node2]->edgeList.emplace_back(new Edge(this->nodes[node2], this->nodes[node1], value));
    }
}

void GraphTravel::randomTravel() {
    clock_t start = clock();
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> randInt(0, this->edgesAmount - 1);
    this->nodeIfVisited = std::vector<bool>(nodesAmount + 1, false);

    int currNodesAmount = 0;
    int currNodeIndex = 1;
    int counter = 0;
    double sum = 0;

    while (currNodesAmount < this->nodesAmount) {
        if (!this->nodeIfVisited[currNodeIndex]) {
            this->nodeIfVisited[currNodeIndex] = true;
            currNodesAmount++;
        }

        int size = this->nodes[currNodeIndex]->edgeList.size();
        int randomIndex = randInt(generator) % size;
        sum += this->nodes[currNodeIndex]->edgeList[randomIndex]->value;
        currNodeIndex = this->nodes[currNodeIndex]->edgeList[randomIndex]->node2->index;
        counter++;
    }

    clock_t stop = clock();
    printf("Random:\n");
    printf("\tMoves = %d\n", counter);
    printf("\tSum = %f\n", sum);
    printf("\tTime : %f milliseconds\n", (double)(stop-start) / CLOCKS_PER_SEC * 1000);
}

void GraphTravel::minEdgeTravel() {
    clock_t start = clock();
    this->nodeIfVisited = std::vector<bool>(nodesAmount + 1, false);

    int currNodeIndex = 1;
    int currNodesAmount = 1;
    int counter = 0;
    double sum = 0;
    this->nodeIfVisited[currNodeIndex] = true;

    while (currNodesAmount < this->nodesAmount) {
        Edge* bestEdge = nullptr;

        for (Edge* edge : this->nodes[currNodeIndex]->edgeList) {
            if (!this->nodeIfVisited[edge->node2->index] && (bestEdge == nullptr || edge->value < bestEdge->value))
                bestEdge = edge;
        }

        currNodeIndex = bestEdge->node2->index;
        this->nodeIfVisited[currNodeIndex] = true;
        currNodesAmount++;
        counter++;
        sum += bestEdge->value;
    }

    clock_t stop = clock();
    printf("Min edge:\n");
    printf("\tMoves = %d\n", counter);
    printf("\tSum = %f\n", sum);
    printf("\tTime : %f milliseconds\n", (double)(stop-start) / CLOCKS_PER_SEC * 1000);
}

void GraphTravel::mstEulerTravel() {
    clock_t start = clock();
    this->nodeIfVisited = std::vector<bool>(nodesAmount + 1, false);
    std::map<Edge*, int> edgesVisitAmount;

    GraphMST graph(this->nodesAmount);
    graph.setNodes(this->nodes, this->edgesAmount);
    graph.prim();
    std::vector<Edge*> edges = graph.getMst();

    for (int i = 1; i <= this->nodesAmount; i++)
        this->nodes[i] = new Node{.index = i, .edgeList = std::vector<Edge*>()};

    for (Edge* edge : edges) {
        this->nodes[edge->node1->index]->edgeList.emplace_back(new Edge(
                this->nodes[edge->node1->index],
                this->nodes[edge->node2->index],
                edge->value));
        this->nodes[edge->node2->index]->edgeList.emplace_back(new Edge(
                this->nodes[edge->node2->index],
                this->nodes[edge->node1->index],
                edge->value));
    }

    int currNodesAmount = 0;
    int currNodeIndex = 1;
    int counter = 0;
    double sum = 0;

    while (currNodesAmount < this->nodesAmount) {
        if (!this->nodeIfVisited[currNodeIndex]) {
            this->nodeIfVisited[currNodeIndex] = true;
            currNodesAmount++;
        }

        int size = this->nodes[currNodeIndex]->edgeList.size();
        int i = 0;
        while (i < size) {
            if (edgesVisitAmount[this->nodes[currNodeIndex]->edgeList[i]] == 0
            && this->nodeIfVisited[this->nodes[currNodeIndex]->edgeList[i]->node2->index] == false) {
                edgesVisitAmount[this->nodes[currNodeIndex]->edgeList[i]]++;
                sum += this->nodes[currNodeIndex]->edgeList[i]->value;
                currNodeIndex = this->nodes[currNodeIndex]->edgeList[i]->node2->index;
                break;
            }
            i++;
        }

        if (i == size) {
            i = 0;
            while (i < size) {
                if (edgesVisitAmount[this->nodes[currNodeIndex]->edgeList[i]] == 0) {
                    edgesVisitAmount[this->nodes[currNodeIndex]->edgeList[i]]++;
                    sum += this->nodes[currNodeIndex]->edgeList[i]->value;
                    currNodeIndex = this->nodes[currNodeIndex]->edgeList[i]->node2->index;
                    break;
                }
                i++;
            }
        }

        counter++;
    }

    clock_t stop = clock();
    printf("MST graph:\n");
    printf("\tMoves = %d\n", counter);
    printf("\tSum = %f\n", sum);
    printf("\tTime : %f milliseconds\n", (double)(stop-start) / CLOCKS_PER_SEC * 1000);
}
