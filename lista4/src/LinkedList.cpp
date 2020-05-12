#include <fstream>

#include "LinkedList.h"
#include "Statistics.h"

struct Node {
    std::string value;
    struct Node* next;
};

LinkedList::LinkedList() {
    this->head = nullptr;
    this->size = 0;
}

void LinkedList::insert(std::string elem) {
    Statistics::insertAmount++;
    elem = this->cleanElem(elem);

    if (elem.empty())
        return;

    Node *newNode = new Node{elem, nullptr};

    if (this->head == nullptr) {
        this->head = newNode;
    } else {
        Node* temp = this->head;

        while (temp->next != nullptr)
            temp = temp->next;

        temp->next = newNode;
    }

    this->maxSize = std::max(++this->size, this->maxSize);
}

void LinkedList::load(std::string filename) {
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

void LinkedList::deleteElem(std::string elem) {
    Statistics::deleteAmount++;
    elem = this->cleanElem(elem);

    if (elem.empty())
        return;

    if (this->head->value == elem) {
        Node* temp = this->head->next;
        free(this->head);
        this->head = temp;
        this->size--;
    } else {
        Node* previous = this->head;

        while (previous->next != nullptr) {
            if (previous->next->value == elem) {
                Node* temp = previous->next->next;
                free(previous->next);
                previous->next = temp;

                this->size--;
                return;
            }

            previous = previous->next;
        }
    }
}

bool LinkedList::find(std::string elem) {
    Statistics::findAmount++;
    Node* temp = this->head;

    while (temp != nullptr) {
        Statistics::compareAmount++;
        if (temp->value == elem)
            return true;

        temp = temp->next;
    }

    return false;
}

std::string LinkedList::min() {
    Statistics::minAmount++;
    return "";
}

std::string LinkedList::max() {
    Statistics::maxAmount++;
    return "";
}

std::string LinkedList::successor(std::string elem) {
    Statistics::successorAmount++;
    return "";
}

void LinkedList::inorder() {
    Statistics::insertAmount++;
    printf("\n");
}

std::vector<std::string> LinkedList::removeAllElements() {
    std::vector<std::string> elements(this->size);
    Node* node = this->head;

    for (int i = 0; i < this->size; i++) {
        elements[i] = node->value;
        node = node->next;
    }

    return elements;
}
