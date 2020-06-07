#include <cstdio>
#include <limits>
#include <utility>

#include "GraphMST.h"
#include "PriorityQueue.h"

GraphMST::GraphMST(int nodesAmount) {
    this->nodesAmount = nodesAmount;
    this->edgesAmount = 0;
    this->nodes = std::vector<Node*>(nodesAmount + 1);
    this->edges = std::vector<Edge*>();
    this->edgesMst = std::vector<Edge*>(this->nodesAmount - 1);
    this->parents = std::vector<Node*>(nodesAmount + 1);
    this->ranks = std::vector<int>(nodesAmount + 1, 0);
    this->bestEdge = std::vector<Edge*>(nodesAmount + 1);
    this->cost = std::vector<double>(nodesAmount + 1, std::numeric_limits<double>::infinity());

    for (int i = 1; i <= this->nodesAmount; i++) {
        this->nodes[i] = new Node{.index = i, .edgeList = std::vector<Edge *>()};
        this->parents[i] = this->nodes[i];
    }
}

void GraphMST::getDataFromStdin() {
    scanf("%d", &this->edgesAmount);

    this->edges = std::vector<Edge*>(this->edgesAmount);

    int node1;
    int node2;
    double value;

    for (int i = 0; i < this->edgesAmount; i++) {
        scanf("%d %d %lf", &node1, &node2, &value);
        this->nodes[node1]->edgeList.emplace_back(new Edge(this->nodes[node1], this->nodes[node2], value));
        this->nodes[node2]->edgeList.emplace_back(new Edge(this->nodes[node2], this->nodes[node1], value));

        this->edges[i] = new Edge(this->nodes[node1], this->nodes[node2], value);
    }
}

void GraphMST::setNodes(std::vector<Node *> nodeList, int edgesAmount) {
    this->edgesAmount = edgesAmount;
    this->edges = std::vector<Edge*>(this->edgesAmount);
    this->nodes = std::move(nodeList);
    int i = 0;

    for (Node* node : this->nodes) {
        if (node != nullptr) {
            for (Edge *edge : node->edgeList) {
                if (edge->node1->index < edge->node2->index)
                    this->edges[i++] = edge;
            }
        }
    }
}

void GraphMST::kruskal() {
    this->edgesMergeSort();
    int i = 0;

    for (Edge* edge : this->edges) {
        if (this->getRoot(edge->node1) != this->getRoot(edge->node2)) {
            this->edgesMst[i++] = edge;
            this->unionNodes(edge->node1, edge->node2);
        }
    }
}

void GraphMST::prim() {
    this->cost[1] = 0;
    int j = 0;
    PriorityQueue<Node*> queue;
    queue.insert(this->nodes[1], 0);

    for (int i = 2; i <= this->nodesAmount; i++) {
        queue.insert(this->nodes[i], std::numeric_limits<double>::infinity());
    }

    while (!queue.empty()) {
        Node* node = queue.pop();
        if (node->index != 1)
            this->edgesMst[j++] = this->bestEdge[node->index];
        for (Edge* edge : node->edgeList) {
            if (this->cost[edge->node2->index] > edge->value) {
                this->cost[edge->node2->index] = edge->value;
                this->bestEdge[edge->node2->index] = edge;
                queue.priority(edge->node2, edge->value);
            }
        }
    }
}

void GraphMST::showMstOnStdout() {
    double sum = 0;

    for (Edge* edge : this->edgesMst) {
        int minIndex = std::min(edge->node1->index, edge->node2->index);
        int maxIndex = std::max(edge->node1->index, edge->node2->index);
        printf("%d %d %f\n", minIndex, maxIndex, edge->value);
        sum += edge->value;
    }

    printf("Sum = %f\n", sum);
}

std::vector<Edge*> GraphMST::getMst() {
    return this->edgesMst;
}

Node *GraphMST::getRoot(Node *node) {
    while (this->parents[node->index] != node)
        node = this->parents[node->index];
    return node;
}

void GraphMST::unionNodes(Node *node1, Node *node2) {
    Node* root1 = GraphMST::getRoot(node1);
    Node* root2 = GraphMST::getRoot(node2);

    if (root1 == root2)
        return;

    if (this->ranks[root1->index] > this->ranks[root2->index]) {
        this->parents[root2->index] = root1;
    } else {
        this->parents[root1->index] = root2;
        if (this->ranks[root1->index] == this->ranks[root2->index])
            this->ranks[root2->index]++;
    }
}

void GraphMST::edgesMergeSort() {
    std::vector<Edge *> temp(this->edgesAmount);
    this->edgesMergeSortRecursion(temp, 0, this->edgesAmount - 1);
}

void GraphMST::edgesMergeSortRecursion(std::vector<Edge *> temp, int left, int right) {
    if (left >= right)
        return;

    int tab1Index = left;
    int mid = left + (right - left) / 2;
    int tab2Index = mid + 1;
    int index = left;

    this->edgesMergeSortRecursion(temp, tab1Index, tab2Index - 1);
    this->edgesMergeSortRecursion(temp, tab2Index, right);

    while(tab1Index <= mid && tab2Index <= right) {
        if (this->edges[tab1Index]->value < this->edges[tab2Index]->value) {
            temp[index++] = this->edges[tab1Index++];
        } else {
            temp[index++] = this->edges[tab2Index++];
        }
    }

    while (tab1Index <= mid)
        temp[index++] = this->edges[tab1Index++];

    while (tab2Index <= right)
        temp[index++] = this->edges[tab2Index++];

    for (int i = left; i <= right; i++)
        this->edges[i] = temp[i];
}
