#include <fstream>

#include "BinarySearchTree.h"
#include "Statistics.h"

struct Node {
    std::string value;
    Node* left;
    Node* right;
    Node* parent;
};

BinarySearchTree::BinarySearchTree() {
    this->root = nullptr;
}

void BinarySearchTree::insert(std::string elem) {
    Statistics::insertAmount++;

    elem = this->cleanElem(elem);

    if (elem.empty())
        return;

    Node* newNode = new Node{.value = elem, .left = nullptr, .right = nullptr, .parent = nullptr};
    Node* currNode = this->root;

    while (currNode != nullptr) {
        newNode->parent = currNode;
        currNode = (newNode->value < currNode->value) ? currNode->left : currNode->right;
    }

    currNode = newNode;

    if (newNode->parent == nullptr) {
        this->root = newNode;
    } else if (newNode->value < newNode->parent->value) {
        newNode->parent->left = currNode;
    } else {
        newNode->parent->right = currNode;
    }

    this->maxSize = std::max(++this->size, this->maxSize);
}

void BinarySearchTree::load(std::string filename) {
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

void BinarySearchTree::deleteElem(std::string elem) {
    Statistics::deleteAmount++;

    Node* node = this->findNode(elem);

    if (node == nullptr)
        return;

    Node* nodeToDelete = (node->left == nullptr || node->right == nullptr) ? node : this->successorNode(node);
    Node* son = (nodeToDelete->left != nullptr) ? nodeToDelete->left : nodeToDelete->right;

    if (son != nullptr)
        son->parent = nodeToDelete->parent;

    if (nodeToDelete->parent == nullptr) {
        this->root = son;
    } else if (nodeToDelete == nodeToDelete->parent->left) {
        nodeToDelete->parent->left = son;
    } else {
        nodeToDelete->parent->right = son;
    }

    if (node != nodeToDelete)
        node->value = nodeToDelete->value;

    free(nodeToDelete);
    this->size--;
}

bool BinarySearchTree::find(std::string elem) {
    return (this->findNode(elem) != nullptr);
}

std::string BinarySearchTree::min() {
    return this->minNode(this->root)->value;
}

std::string BinarySearchTree::max() {
    Statistics::maxAmount++;

    Node* currNode = this->root;

    if (currNode == nullptr)
        return "";

    while (currNode->right != nullptr)
        currNode = currNode->right;

    return currNode->value;
}

std::string BinarySearchTree::successor(std::string elem) {
    Node* currNode = this->findNode(elem);
    return this->successorNode(currNode)->value;
}

void BinarySearchTree::inorder() {
    Statistics::inorderAmount++;

    this->inorderRecursive(this->root);
    printf("\n");
}

void BinarySearchTree::inorderRecursive(Node* node) {
    if (node != nullptr) {
        inorderRecursive(node->left);
        printf("%s ", node->value.c_str());
        inorderRecursive(node->right);
    }
}

Node *BinarySearchTree::minNode(Node *node) {
    Statistics::minAmount++;

    if (node == nullptr)
        return new Node{"", nullptr, nullptr, nullptr};

    while (node->left != nullptr)
        node = node->left;

    return node;
}

Node *BinarySearchTree::findNode(const std::string& elem) {
    Statistics::findAmount++;

    Node* currNode = this->root;
    Node* node = new Node{.value = elem, .left = nullptr, .right = nullptr, .parent = nullptr};

    while (currNode != nullptr) {
        Statistics::compareAmount++;
        if (currNode->value == node->value)
            return currNode;

        currNode = (node->value < currNode->value) ? currNode->left : currNode->right;
        Statistics::compareAmount++;
    }

    free(node);
    return currNode;
}

Node *BinarySearchTree::successorNode(Node *node) {
    Statistics::successorAmount++;

    if (node->right != nullptr)
        return this->minNode(node->right);

    while (node->parent != nullptr && node == node->parent->right)
        node = node->parent;

    if (node->parent == nullptr)
        return new Node{"", nullptr, nullptr, nullptr};

    return node->parent;
}
