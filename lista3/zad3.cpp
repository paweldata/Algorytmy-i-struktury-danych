#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <cmath>

//tej funkcji uzylem, by policzyc O(1)
//teraz nie jest uzywana w programie
double statistics();

bool binarySearch(int* tab, int left, int right, int value) {
    if (left == right)
        return (tab[left] == value);

    int middle = (left + right) / 2;

    if (tab[middle] == value)
        return true;
    if (tab[middle] > value)
        return binarySearch(tab, left, middle, value);
    return binarySearch(tab, middle + 1, right, value);
}

int main() {
    int size;
    int number;
    printf("Size : ");
    scanf("%d", &size);

    int* tab = (int*)malloc(size * sizeof(int));

    printf("Sorted elements : ");
    for (int i = 0; i < size; i++)
        scanf("%d", &tab[i]);

    printf("Number to find : ");
    scanf("%d", &number);

    if (binarySearch(tab, 0, size - 1, number)) {
        printf("%d is in array\n", number);
    } else {
        printf("%d isn't in array\n", number);
    }

    return 0;
}

double statistics() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> randInt(1, 1000);

    double averageTime = 0;

    for (int size = 1000; size <= 100000; size += 1000) {
        int* tab = (int*)malloc(size * sizeof(int));

        for (int i = 0; i < size; i++)
            tab[i] = randInt(generator);
        std::sort(tab, tab + size);

        clock_t start = clock();
        binarySearch(tab, 0, size - 1, tab[randInt(generator) % size]);
        clock_t stop = clock();

        averageTime  += (double)(stop - start) / CLOCKS_PER_SEC * 1000 / log2(size);

        free(tab);
    }

    return averageTime / 100;
}
