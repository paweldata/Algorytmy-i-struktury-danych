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
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> randInt(0, this->edgesAmount - 1);
    this->nodeIfVisited = std::vector<bool>(nodesAmount + 1, false);

    int currNodesAmount = 0;
    int currNodeIndex = 1;
    int counter = 0;

    while (currNodesAmount < this->nodesAmount) {
        if (!this->nodeIfVisited[currNodeIndex]) {
            this->nodeIfVisited[currNodeIndex] = true;
            currNodesAmount++;
        }

        int size = this->nodes[currNodeIndex]->edgeList.size();
        currNodeIndex = this->nodes[currNodeIndex]->edgeList[randInt(generator) % size]->node2->index;
        counter++;
    }

    for (auto && i : this->nodeIfVisited)
        printf(i ? "true " : "false ");
    printf("\n");
    printf("counter : %d\n", counter);
}

void GraphTravel::minEdgeTravel() {
    this->nodeIfVisited = std::vector<bool>(nodesAmount + 1, false);

    int currNodeIndex = 1;
    int currNodesAmount = 1;
    int counter = 0;
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
    }

    for (auto && i : this->nodeIfVisited)
        printf(i ? "true " : "false ");
    printf("\n");
    printf("counter : %d\n", counter);
}

void GraphTravel::mstEulerTravel() { //TODO
    this->nodeIfVisited = std::vector<bool>(nodesAmount + 1, false);
    std::map<Edge*, int> edgesVisitAmount;
    //std::map<std::pair<int, int>, int> edgesVisitAmount;

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
                currNodeIndex = this->nodes[currNodeIndex]->edgeList[i]->node2->index;
                break;
            }
            i++;
        }

        if (i == size) {
            int i = 0;
            while (i < size) {
                if (edgesVisitAmount[this->nodes[currNodeIndex]->edgeList[i]] == 0) {
                    edgesVisitAmount[this->nodes[currNodeIndex]->edgeList[i]]++;
                    currNodeIndex = this->nodes[currNodeIndex]->edgeList[i]->node2->index;
                    break;
                }
                i++;
            }
        }

        counter++;

        /*if (i == size) {
            printf("Lipa\n");
            Edge* minEdge = this->nodes[currNodeIndex]->edgeList[0];

            for (Edge* edge : this->nodes[currNodeIndex]->edgeList) {
                if (edgesVisitAmount[edge] < edgesVisitAmount[minEdge])
                    minEdge = edge;
            }

            currNodeIndex = minEdge->node2->index;
            edgesVisitAmount[minEdge]++;
        }*/
    }

    for (auto && i : this->nodeIfVisited)
        printf(i ? "true " : "false ");
    printf("\n");
    printf("counter : %d\n", counter);
}
