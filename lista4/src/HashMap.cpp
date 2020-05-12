#include <fstream>

#include "HashMap.h"
#include "Statistics.h"

HashMap::HashMap() {
    this->map = std::map<uint64_t, DataStructure*>();
    this->hash = std::hash<std::string>();
}

void HashMap::insert(std::string elem) {
    elem = this->cleanElem(elem);

    if (elem.empty())
        return;

    uint64_t hashValue = this->hash(elem);

    if (this->map[hashValue] == nullptr)
        this->map[hashValue] = new LinkedList();

    if (auto* list = dynamic_cast<LinkedList*>(this->map[hashValue])) {
        if (list->getSize() == this->maxListSize) {
            this->LinkedListToRedBlackTree(hashValue);
        }
    }

    this->map[hashValue]->insert(elem);

    this->maxSize = std::max(++this->size, this->maxSize);
}

void HashMap::load(std::string filename) {
    Statistics::loadAmount++;

    std::ifstream file(filename);
    std::string elem;

    if (!file.is_open()) {
        printf("File %s not exists\n", filename.c_str());
        return;
    }

    while (file >> elem)
        this->insert(elem);
}

void HashMap::deleteElem(std::string elem) {
    uint64_t hashValue = this->hash(elem);

    if (this->map[hashValue] == nullptr) {
        Statistics::deleteAmount++;
        return;
    }

    this->map[hashValue]->deleteElem(elem);

    if (auto *tree = dynamic_cast<RedBlackTree*>(this->map[hashValue]))
        if (tree->getSize() == this->maxListSize)
            this->RedBlackTreeToLinkedList(hashValue);

    this->size--;
}

bool HashMap::find(std::string elem) {
    uint64_t hashValue = this->hash(elem);

    if (this->map[hashValue] == nullptr) {
        Statistics::findAmount++;
        return false;
    }

    return this->map[hashValue]->find(elem);
}

std::string HashMap::min() {
    Statistics::minAmount++;
    return "";
}

std::string HashMap::max() {
    Statistics::maxAmount++;
    return "";
}

std::string HashMap::successor(std::string elem) {
    Statistics::successorAmount++;
    return "";
}

void HashMap::inorder() {
    Statistics::inorderAmount++;
    printf("\n");
}

void HashMap::LinkedListToRedBlackTree(uint64_t hashValue) {
    auto* list = dynamic_cast<LinkedList*>(this->map[hashValue]);
    std::vector<std::string> elements = list->removeAllElements();
    free(list);
    this->map[hashValue] = new RedBlackTree();

    for (const std::string& elem : elements)
        this->map[hashValue]->insert(elem);
}

void HashMap::RedBlackTreeToLinkedList(uint64_t hashValue) {
    auto* tree = dynamic_cast<RedBlackTree*>(this->map[hashValue]);
    std::vector<std::string> elements = tree->removeAllElements();
    free(tree);
    this->map[hashValue] = new LinkedList();

    for (const std::string& elem : elements)
        this->map[hashValue]->insert(elem);
}
