#include <cstdio>
#include <random>
#include <cstring>
#include <cmath>

//globas variables
int compareAmount = 0;
int swapAmount = 0;

int randomizedSelect(int* tab, int size, int number);
int randomizedSelectRecursion(int* tab, int left, int right, int number);
int select(int* tab, int size, int number);
int selectRecursion(int* tab, int left, int right, int number);
int getMedianUsingInsertionSort(int* tab, int left, int right);

int* getRandomTable(int size);
int* getRandomPermutation(int size);
int* copyTable(const int* tab, int size);

int randomizedSelect(int* tab, int size, int number) {
    return randomizedSelectRecursion(tab, 0, size - 1, number);
}

int randomizedSelectRecursion(int* tab, int left, int right, int number) {
    if (left == right)
        return tab[left];

    fprintf(stderr, "RS:Table: ");
    for (int i = left; i <= right; i++)
        fprintf(stderr, "%d ", tab[i]);

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> randInt(left, right);

    int pivot = tab[randInt(generator)];
    fprintf(stderr, ", pivot = %d, number = %d\n", pivot, number - left);

    int lower = left;
    int middle = left;
    int upper = right;

    while (middle <= upper) {
        fprintf(stderr, "RS:Compare %d and %d\n", tab[middle], pivot);
        if (tab[middle] < pivot) {
            fprintf(stderr, "RS: %d < %d, swap %d and %d\n", tab[middle], pivot, tab[lower], tab[middle]);
            std::swap(tab[lower], tab[middle]);
            lower++;
            middle++;
            swapAmount++;
        } else if (tab[middle] > pivot) {
            fprintf(stderr, "RS: %d > %d, swap %d and %d\n", tab[middle], pivot, tab[middle], tab[upper]);
            std::swap(tab[middle], tab[upper]);
            upper--;
            swapAmount++;
        } else {
            fprintf(stderr, "RS: %d = %d\n", tab[middle], pivot);
            middle++;
        }
        compareAmount++;
    }

    if (number <= lower)
        return selectRecursion(tab, left, lower - 1, number);
    if (number >= upper + 2)
        return selectRecursion(tab, upper + 1, right, number);
    return tab[lower];
}

int select(int* tab, int size, int number) {
    return selectRecursion(tab, 0, size - 1, number);
}

int selectRecursion(int* tab, int left, int right, int number) {
    if (left == right)
        return tab[left];

    fprintf(stderr, "S:Table: ");
    for (int i = left; i <= right; i++)
        fprintf(stderr, "%d ", tab[i]);
    fprintf(stderr, "\n");

    int size = ceil((right - left + 1) / 5.0);
    int* temp = (int*)malloc(size * sizeof(int));

    for (int i = left, j = 0; i <= right; i+= 5, j++)
        temp[j] = getMedianUsingInsertionSort(tab, i, std::min(i + 4, right));

    int median = selectRecursion(temp, 0, size - 1, (size % 2 == 0) ? size / 2 + 1 : (size + 1) / 2);
    fprintf(stderr, "S: median = %d\nindex : %d\n", median, number - left);

    int lower = left;
    int middle = left;
    int upper = right;

    while (middle <= upper) {
        fprintf(stderr, "S:Compare %d and %d\n", tab[middle], median);
        if (tab[middle] < median) {
            fprintf(stderr, "S: %d < %d, swap %d and %d\n", tab[middle], median, tab[lower], tab[middle]);
            std::swap(tab[lower], tab[middle]);
            lower++;
            middle++;
            swapAmount++;
        } else if (tab[middle] > median) {
            fprintf(stderr, "S: %d > %d, swap %d and %d\n", tab[middle], median, tab[middle], tab[upper]);
            std::swap(tab[middle], tab[upper]);
            upper--;
            swapAmount++;
        } else {
            fprintf(stderr, "S: %d = %d\n", tab[middle], median);
            middle++;
        }
        compareAmount++;
    }

    if (number <= lower)
        return selectRecursion(tab, left, lower - 1, number);
    if (number >= upper + 2)
        return selectRecursion(tab, upper + 1, right, number);
    return tab[lower];
}

int getMedianUsingInsertionSort(int* tab, int left, int right) {
    int temp;
    int j;

    fprintf(stderr, "S:Calculate Median of ");
    for (int i = left; i <= right; i++)
        fprintf(stderr, "%d ", tab[i]);
    fprintf(stderr, "\n");

    for (int i = left + 1; i <= right; i++) {
        temp = tab[i];
        j = i - 1;

        while (j >= left && tab[j] > temp) {
            fprintf(stderr, "S:check %d > %d, swap\n", tab[j], temp);
            tab[j + 1] = tab[j];
            swapAmount++;
            compareAmount++;
            j--;
        }

        fprintf(stderr, "S:check %d > %d\n", tab[j], temp);
        compareAmount++;
        tab[j + 1] = temp;
    }

    if ((right - left + 1) % 2 == 1)
        return tab[left + (right - left) / 2];
    return tab[left + (right - left + 1) / 2];
}

int* getRandomTable(int size) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> randInt(0, size);

    int* tab = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
        tab[i] = randInt(generator);

    return tab;
}

int* getRandomPermutation(int size) {
    int* permutation = (int*)malloc(size * sizeof(int));
    int* temp = (int*)malloc(size * sizeof(int));

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> randInt(1, size);

    int value;
    int currSize = size;

    for (int i = 0; i < size; i++)
        temp[i] = i + 1;

    for (int i = 0; i < size; i++) {
        value = randInt(generator) % currSize;
        permutation[i] = temp[value];
        std::swap(temp[value], temp[currSize - 1]);
        currSize--;
    }

    return permutation;
}

int* copyTable(const int* tab, int size) {
    int* newTab = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        newTab[i] = tab[i];
    return newTab;
}

int main(int argc, char *argv[]) {
    int* (*tableType)(int) = nullptr;

    if (argc >= 2 && strcmp(argv[1], "-p") == 0) {
        tableType = &getRandomPermutation;
    } else if (argc >= 2 && strcmp(argv[1], "-r") == 0) {
        tableType = &getRandomTable;
    }

    if (tableType == nullptr) {
        printf("Give parameters\n"
               "-r (program works on random integers)\n"
               "or\n"
               "-p (program works on random permutation)\n");
        return 0;
    }

    int size;
    int number;
    printf("Size : ");
    scanf("%d", &size);
    printf("Number : ");
    scanf("%d", &number);

    int* tab1 = tableType(size);
    int* tab2 = copyTable(tab1, size);
    bool numberPrint = false;

    int result1 = randomizedSelect(tab1, size, number);
    printf("Randomized Select:\n");
    for (int i = 0; i < size; i++) {
        if (!numberPrint && tab1[i] == result1) {
            printf("[%d] ", result1);
            numberPrint = true;
        } else {
            printf("%d ", tab1[i]);
        }
    }
    printf("\n");

    fprintf(stderr, "RS: Compare : %d\n", compareAmount);
    fprintf(stderr, "RS: Swap : %d\n", swapAmount);

    compareAmount = 0;
    swapAmount = 0;
    numberPrint = false;

    int result2 = select(tab2, size, number);
    printf("Select:\n");
    for (int i = 0; i < size; i++) {
        if (!numberPrint && tab2[i] == result2) {
            printf("[%d] ", result2);
            numberPrint = true;
        } else {
            printf("%d ", tab2[i]);
        }
    }
    printf("\n");

    fprintf(stderr, "S: Compare : %d\n", compareAmount);
    fprintf(stderr, "S: Swap : %d\n", swapAmount);

    return 0;
}
