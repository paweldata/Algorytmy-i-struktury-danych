#include <algorithm>

#include "DataStructure.h"

struct Node {
    std::string value;
};

std::string DataStructure::cleanElem(std::string elem) {
    while (!elem.empty() && (elem[0] < 'A' || (elem[0] > 'Z' && elem[0] < 'a') || elem[0] > 'z'))
        elem.erase(0, 1);

    int size = elem.size();

    while (size > 0 && (elem[size - 1] < 'A' || (elem[size - 1] > 'Z' && elem[size - 1] < 'a') || elem[size - 1] > 'z')) {
        elem.erase(size - 1);
        size--;
    }

    return elem;
}

bool DataStructure::isLower(const Node *node1, const Node *node2) {
    std::string v1 = node1->value;
    std::string v2 = node2->value;
    std::transform(v1.begin(), v1.end(),v1.begin(), ::tolower);
    std::transform(v2.begin(), v2.end(),v2.begin(), ::tolower);
    return (v1 < v2);
}

int DataStructure::getSize() {
    return this->size;
}

int DataStructure::getMaxSize() {
    return this->maxSize;
}
