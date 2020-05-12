#include <fstream>

#include "RedBlackTree.h"
#include "Statistics.h"

enum Color {red, black};

struct Node {
    std::string value;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
};

RedBlackTree::RedBlackTree() {
    this->null = new Node{.value = "", .color = black, .left = this->null, .right = this->null, .parent = this->null};
    this->root = this->null;
    this->size = 0;
}

void RedBlackTree::insert(std::string elem) {
    Statistics::insertAmount++;

    elem = this->cleanElem(elem);

    if (elem.empty())
        return;

    this->maxSize = std::max(++this->size, this->maxSize);

    Node* newNode = new Node{.value = elem, .color = red, .left = this->null, .right = this->null, .parent = this->null};
    Node* currNode = this->root;

    while (currNode != this->null) {
        newNode->parent = currNode;
        currNode = (newNode->value < currNode->value) ? currNode->left : currNode->right;
    }

    currNode = newNode;

    if (newNode->parent == this->null) {
        this->root = newNode;
    } else if (newNode->value < newNode->parent->value) {
        newNode->parent->left = currNode;
    } else {
        newNode->parent->right = currNode;
    }

    while (newNode != this->root && newNode->parent->color == red) {
        if (newNode->parent == newNode->parent->parent->left) {
            Node* uncle = newNode->parent->parent->right;
            if (uncle->color == red) { // case 1
                newNode->parent->color = black;
                uncle->color = black;
                newNode->parent->parent->color = red;
                newNode = newNode->parent->parent;
            } else {
                if (newNode == newNode->parent->right) {
                    newNode = newNode->parent;
                    this->leftRotate(newNode);
                }

                newNode->parent->color = black;
                newNode->parent->parent->color = red;
                this->rightRotate(newNode->parent->parent);
            }
        } else {
            Node* uncle = newNode->parent->parent->left;
            if (uncle->color == red) {
                newNode->parent->color = black;
                uncle->color = black;
                newNode->parent->parent->color = red;
                newNode = newNode->parent->parent;
            } else {
                if (newNode == newNode->parent->left) {
                    newNode = newNode->parent;
                    this->rightRotate(newNode);
                }

                newNode->parent->color = black;
                newNode->parent->parent->color = red;
                this->leftRotate(newNode->parent->parent);
            }
        }
    }
    this->root->color = black;
}

void RedBlackTree::load(std::string filename) {
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

void RedBlackTree::deleteElem(std::string elem) {
    Statistics::deleteAmount++;

    Node* node = this->findNode(elem);

    if (node == this->null)
        return;

    this->size--;

    Node* nodeToDelete = (node->left == this->null || node->right == this->null) ? node : this->successorNode(node);
    Node* son = (nodeToDelete->left != this->null) ? nodeToDelete->left : nodeToDelete->right;
    son->parent = nodeToDelete->parent;

    if (nodeToDelete->parent == this->null) {
        this->root = son;
    } else if (nodeToDelete == nodeToDelete->parent->left) {
        nodeToDelete->parent->left = son;
    } else {
        nodeToDelete->parent->right = son;
    }

    if (node != nodeToDelete)
        node->value = nodeToDelete->value;

    if (nodeToDelete->color == black)
        this->deleteElemFixup(son);

    free(nodeToDelete);
}

bool RedBlackTree::find(std::string elem) {
    return (this->findNode(elem) != this->null);
}

std::string RedBlackTree::min() {
    return this->minNode(this->root)->value;
}

std::string RedBlackTree::max() {
    Statistics::maxAmount++;

    Node* currNode = this->root;

    if (currNode == this->null)
        return this->null->value;

    while (currNode->right != this->null)
        currNode = currNode->right;

    return currNode->value;
}

std::string RedBlackTree::successor(std::string elem) {
    Node* currNode = this->findNode(elem);
    return this->successorNode(currNode)->value;
}

void RedBlackTree::inorder() {
    Statistics::inorderAmount++;

    this->inorderRecursive(this->root);
    printf("\n");
}

std::vector<std::string> RedBlackTree::removeAllElements() {
    std::vector<std::string> elements(this->size);

    int sizeForLoop = this->size;
    for (int i = 0; i < sizeForLoop; i++) {
        elements[i] = this->root->value;
        this->deleteElem(this->root->value);
    }

    return elements;
}

void RedBlackTree::leftRotate(Node *node) {
    Node* swapNode = node->right;
    node->right = swapNode->left;

    if (swapNode->left != this->null)
        swapNode->left->parent = node;

    swapNode->parent = node->parent;

    if (node->parent == this->null) {
        this->root = swapNode;
    } else if (node == node->parent->left) {
        node->parent->left = swapNode;
    } else {
        node->parent->right = swapNode;
    }

    swapNode->left = node;
    node->parent = swapNode;
}

void RedBlackTree::rightRotate(Node *node) {
    Node* swapNode = node->left;
    node->left = swapNode->right;

    if (swapNode->right != this->null)
        swapNode->right->parent = node;

    swapNode->parent = node->parent;

    if (node->parent == this->null) {
        this->root = swapNode;
    } else if (node == node->parent->left) {
        node->parent->left = swapNode;
    } else {
        node->parent->right = swapNode;
    }

    swapNode->right = node;
    node->parent = swapNode;
}

void RedBlackTree::inorderRecursive(Node *node) {
    if (node != this->null) {
        inorderRecursive(node->left);
        printf("%s ", node->value.c_str());
        inorderRecursive(node->right);
    }
}

Node *RedBlackTree::minNode(Node *node) {
    Statistics::minAmount++;

    if (node == this->null)
        return node;

    while (node->left != this->null)
        node = node->left;

    return node;
}

Node *RedBlackTree::findNode(const std::string &elem) {
    Statistics::findAmount++;

    Node* currNode = this->root;
    Node* node = new Node{.value = elem, .color = black, .left = this->null, .right = this->null, .parent = this->null};

    while (currNode != this->null) {
        Statistics::compareAmount++;
        if (currNode->value == elem)
            return currNode;

        currNode = (node->value < currNode->value) ? currNode->left : currNode->right;
        Statistics::compareAmount++;
    }

    free(node);
    return currNode;
}

Node *RedBlackTree::successorNode(Node *node) {
    Statistics::successorAmount++;

    if (node == this->null)
        return node;

    if (node->right != this->null)
        return this->minNode(node->right);

    while (node->parent != this->null && node == node->parent->right)
        node = node->parent;

    return node->parent;
}

void RedBlackTree::deleteElemFixup(Node *node) {
    while (node != this->root && node->color == black) {
        if (node == node->parent->left) {
            Node* brother = node->parent->right;

            if (brother->color == red) {
                brother->color = black;
                node->parent->color = red;
                this->leftRotate(node->parent);
                brother = node->parent->right;
            }

            if (brother->left->color == black && brother->right->color == black) {
                brother->color = red;
                node = node->parent;
            } else {
                if (brother->right->color == black) {
                    brother->left->color = black;
                    brother->color = red;
                    this->rightRotate(brother);
                    brother = node->parent->right;
                }

                brother->color = node->parent->color;
                node->parent->color = black;
                brother->right->color = black;
                this->leftRotate(node->parent);
                node = this->root;
            }
        } else {
            Node* brother = node->parent->left;

            if (brother->color == red) {
                brother->color = black;
                node->parent->color = red;
                this->rightRotate(node->parent);
                brother = node->parent->left;
            }

            if (brother->right->color == black && brother->left->color == black) {
                brother->color = red;
                node = node->parent;
            } else {
                if (brother->left->color == black) {
                    brother->right->color = black;
                    brother->color = red;
                    this->leftRotate(brother);
                    brother = node->parent->left;
                }

                brother->color = node->parent->color;
                node->parent->color = black;
                brother->left->color = black;
                this->rightRotate(node->parent);
                node = this->root;
            }
        }
    }

    node->color = black;
}
