#include <stdexcept>
#include <cstring>

#include "src/GraphMST.h"

bool check(int argc, char** argv);

int main(int argc, char** argv) {
    if (!check(argc, argv)) {
        printf("Give parameter:\n"
               "-k (kruscal)\n"
               "or\n"
               "-p (prim)\n");
        return 1;
    }

    int nodesAmount;
    scanf("%d", &nodesAmount);

    GraphMST graph(nodesAmount);
    graph.getDataFromStdin();

    if (strcmp(argv[1], "-k") == 0) {
        graph.kruskal();
    } else if (strcmp(argv[1], "-p") == 0) {
        graph.prim();
    }

    graph.showMstOnStdout();
    return 0;
}

bool check(int argc, char** argv) {
    if (argc != 2)
        return false;

    if (strcmp(argv[1], "-k") == 0) {
        return true;
    } else if (strcmp(argv[1], "-p") == 0) {
        return true;
    }

    return false;
}