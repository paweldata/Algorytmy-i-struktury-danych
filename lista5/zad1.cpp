#include <cstdio>
#include <stdexcept>
#include <iostream>

#include "src/PriorityQueue.h"

int main() {
    PriorityQueue<int> queue;

    int commandNumber;
    std::string command;

    scanf("%d", &commandNumber);

    for (int i = 0; i < commandNumber; i++) {
        std::cin >> command;

        if (command == "insert") {
            int value, key;
            scanf("%d %d", &value, &key);
            queue.insert(value, key);
        } else if (command == "empty") {
            printf("%d\n", queue.empty());
        } else if (command == "top") {
            try {
                queue.top();
            } catch (std::out_of_range&) {
                printf("\n");
            }
        } else if (command == "pop") {
            try {
                printf("%d\n", queue.pop());
            } catch (std::out_of_range&) {
                printf("\n");
            }
        } else if (command == "priority") {
            int value, key;
            scanf("%d %d", &value, &key);
            queue.priority(value, key);
        } else if (command == "print") {
            queue.print();
        } else {
            printf("Wrong commmand\n");
            exit(0);
        }
    }

    return 0;
}
