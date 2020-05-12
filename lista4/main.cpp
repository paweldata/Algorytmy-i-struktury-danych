#include <cstdio>
#include <string>
#include <iostream>
#include <cstring>

#include "src/BinarySearchTree.h"
#include "src/RedBlackTree.h"
#include "src/HashMap.h"
#include "src/Bloom.h"
#include "src/Statistics.h"

DataStructure* getDataStructure(int argc, char** argv);
void showStatistics(DataStructure* dataStructure);

int main(int argc, char** argv) {
    DataStructure* dataStructure = getDataStructure(argc, argv);
    std::hash<std::string> str_hash1;
    std::hash<std::string> str_hash2;

    Statistics::startTimer = clock();

    int commandNumber;
    std::string command;
    std::string argument;

    scanf("%d", &commandNumber);

    for (int i = 0; i < commandNumber; i++) {
        std::cin >> command;

        if (command == "insert") {
            std::cin >> argument;
            dataStructure->insert(argument);
        } else if (command == "load") {
            std::cin >> argument;
            dataStructure->load(argument);
        } else if (command == "delete") {
            std::cin >> argument;
            dataStructure->deleteElem(argument);
        } else if (command == "find") {
            std::cin >> argument;
            printf("%d\n", dataStructure->find(argument));
        } else if (command == "min") {
            printf("%s\n", dataStructure->min().c_str());
        } else if (command == "max") {
            printf("%s\n", dataStructure->max().c_str());
        } else if (command == "successor") {
            std::cin >> argument;
            printf("%s\n", dataStructure->successor(argument).c_str());
        } else if (command == "inorder") {
            dataStructure->inorder();
        } else {
            printf("Wrong commmand\n");
            exit(0);
        }
    }

    Statistics::stopTimer = clock();
    showStatistics(dataStructure);
    return 0;
}

DataStructure* getDataStructure(int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        if (std::strcmp(argv[i], "--type") == 0) {
            if (++i < argc) {
                if (std::strcmp(argv[i], "bst") == 0)
                    return new BinarySearchTree();
                if (std::strcmp(argv[i], "rbt") == 0)
                    return new RedBlackTree();
                if (std::strcmp(argv[i], "hmap") == 0)
                    return new HashMap();
                if (std::strcmp(argv[i], "bloom") == 0)
                    return new Bloom();
            }
        }
    }

    printf("Give data structure type as argument\n"
           "--type bst | rbt | hmap | bloom\n"
           "bst - BinarySearchTree\n"
           "rbt - RedBlackTree\n"
           "hmap - HashMap\n"
           "bloom - Bloom filter\n");
    exit(0);
}

void showStatistics(DataStructure* dataStructure) {
    fprintf(stderr, "Time in seconds : %f\n", (double)(Statistics::stopTimer - Statistics::startTimer)/CLOCKS_PER_SEC);
    fprintf(stderr, "Insert: %d\n", Statistics::insertAmount);
    fprintf(stderr, "Load: %d\n", Statistics::loadAmount);
    fprintf(stderr, "Delete: %d\n", Statistics::deleteAmount);
    fprintf(stderr, "Find: %d\n", Statistics::findAmount);
    fprintf(stderr, "Min: %d\n", Statistics::minAmount);
    fprintf(stderr, "Max: %d\n", Statistics::maxAmount);
    fprintf(stderr, "Succesor: %d\n", Statistics::successorAmount);
    fprintf(stderr, "inorder: %d\n", Statistics::inorderAmount);
    fprintf(stderr, "Max elemensts: %d\n", dataStructure->getMaxSize());
    fprintf(stderr, "Current elemensts: %d\n", dataStructure->getSize());
}
