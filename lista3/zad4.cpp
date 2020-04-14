#include <cstring>
#include <fstream>
#include <random>

int compareAmount = 0;
int swapAmount = 0;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> randInt(1, 1000);

int getMedianUsingInsertionSort(int* tab, int left, int right);

void quickSort(int* tab, int size, bool ascending);
void quickSortRecursion(int* tab, int left, int right, bool ascending);
void dualPivotQuickSortCount(int* tab, int size, bool ascending);
void dualPivotQuickSortCountRecursion(int* tab, int left, int right, bool ascending);

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

void quickSort(int* tab, int size, bool ascending) {
    quickSortRecursion(tab, 0, size - 1, ascending);
}

void quickSortRecursion(int* tab, int left, int right, bool ascending) {
    if (right <= left)
        return;

    char sortChar = ((ascending) ? '>' : '<');
    char negSortChar = ((ascending) ? '<' : '>');

    int median;
    int size = right - left + 1;
    if (size >= 5) {
        int* temp = (int*)malloc(5 * sizeof(int));
        for (int i = 0; i < 5; i++)
            temp[i] = tab[left + randInt(gen) % (right - left + 1)];

        median = getMedianUsingInsertionSort(temp, 0, 4);
    } else {
        median = tab[left];
    }

    int lower = left;
    int middle = left;
    int upper = right;

    while (middle <= upper) {
        fprintf(stderr, "Compare %d and %d\n", tab[middle], median);
        if ((ascending && tab[middle] < median) || (!ascending && tab[middle] > median)) {
            fprintf(stderr, "%d %c %d, swap %d and %d\n", tab[middle], sortChar, median, tab[lower], tab[middle]);
            std::swap(tab[lower], tab[middle]);
            lower++;
            middle++;
            swapAmount++;
        } else if ((ascending && tab[middle] > median) || (!ascending && tab[middle] < median)) {
            fprintf(stderr, "%d %c %d, swap %d and %d\n", tab[middle], negSortChar, median, tab[middle], tab[upper]);
            std::swap(tab[middle], tab[upper]);
            upper--;
            swapAmount++;
        } else {
            fprintf(stderr, "%d = %d\n", tab[middle], median);
            middle++;
        }
        compareAmount++;
    }

    quickSortRecursion(tab, left, lower - 1, ascending);
    quickSortRecursion(tab, upper + 1, right, ascending);
}

void dualPivotQuickSortCount(int* tab, int size, bool ascending) {
    dualPivotQuickSortCountRecursion(tab, 0, size - 1, ascending);
}

void dualPivotQuickSortCountRecursion(int* tab, int left, int right, bool ascending) {
    if (right <= left)
        return;

    char sortChar = ((ascending) ? '>' : '<');
    char negSortChar = ((ascending) ? '<' : '>');

    if (right - left + 1 >= 32) {
        int temp;
        for (int i = left + 1; i < left + 8; i++) {
            temp = tab[i];
            int j = i - 1;

            while (j >= left && ((ascending && tab[j] > temp) || (!ascending && tab[j] < temp))) {
                fprintf(stderr, "check %d %c %d, swap\n", temp, sortChar, tab[j]);
                tab[j + 1] = tab[j];
                swapAmount++;
                compareAmount++;
                j--;
            }

            fprintf(stderr, "check %d %c %d\n", temp, sortChar, tab[j]);
            compareAmount++;
            tab[j + 1] = temp;
        }

        std::swap(tab[left + 2], tab[left]);
        std::swap(tab[left + 5], tab[right]);
    } else if ((ascending && tab[left] > tab[right]) || (!ascending && tab[left] < tab[right])) {
        std::swap(tab[left], tab[right]);
    }

    int p = tab[left];
    int q = tab[right];
    int i = left + 1;
    int j = left + 1;
    int k = right - 1;
    int choosePivot = 0;

    while (j <= k) {
        if (choosePivot >= 0) {
            fprintf(stderr, "check %d %c %d or %d %c %d\n", tab[j], sortChar, p, tab[j], negSortChar, q);
            if ((ascending && tab[j] < p) || (!ascending && tab[j] > p)) {
                fprintf(stderr, "swap %d and %d\n", tab[j], tab[i]);
                std::swap(tab[i], tab[j]);
                i++;
                j++;
                choosePivot++;
                swapAmount++;
            } else if ((ascending && tab[j] > q) || (!ascending && tab[j] < q)) {
                fprintf(stderr, "swap %d and %d\n", tab[j], tab[k]);
                std::swap(tab[j], tab[k]);
                k--;
                choosePivot--;
                swapAmount++;
            } else {
                j++;
            }
        } else {
            fprintf(stderr, "check %d %c %d or %d %c %d\n", tab[j], negSortChar, p, tab[j], sortChar, q);
            if ((ascending && tab[j] > q) || (!ascending && tab[j] < q)) {
                fprintf(stderr, "swap %d and %d\n", tab[j], tab[k]);
                std::swap(tab[j], tab[k]);
                k--;
                choosePivot--;
                swapAmount++;
            } else if ((ascending && tab[j] < p) || (!ascending && tab[j] > p)) {
                fprintf(stderr, "swap %d and %d\n", tab[j], tab[i]);
                std::swap(tab[i], tab[j]);
                i++;
                j++;
                choosePivot++;
                swapAmount++;
            } else {
                j++;
            }
        }
        compareAmount++;
    }

    fprintf(stderr, "swap %d and %d\n", tab[left], tab[i - 1]);
    fprintf(stderr, "swap %d and %d\n", tab[right], tab[k + 1]);
    std::swap(tab[left], tab[i - 1]);
    std::swap(tab[right], tab[k + 1]);
    swapAmount += 2;

    dualPivotQuickSortCountRecursion(tab, left, i - 2, ascending);
    dualPivotQuickSortCountRecursion(tab, i, k, ascending);
    dualPivotQuickSortCountRecursion(tab, k + 2, right, ascending);
}

void sortTable(int size, bool ascending, void(*sortFunction)(int *, int, bool)) {
    printf("Size : ");
    scanf("%d", &size);
    int* tab = (int*)malloc(size * sizeof(int));

    printf("Elements : ");
    for (int i = 0; i < size; i++)
        scanf("%d", &tab[i]);

    clock_t start = clock();
    sortFunction(tab, size, ascending);
    clock_t stop = clock();

    fprintf(stderr, "Ilosc porownan : %d\n", compareAmount);
    fprintf(stderr, "Ilosc zamian : %d\n", swapAmount);
    fprintf(stderr, "Czas sortowania : %f sekund\n", (double)(stop-start)/CLOCKS_PER_SEC);

    for (int i = 0; i < size - 1; i++)
        if ((ascending && tab[i] > tab[i + 1]) || (!ascending && tab[i] < tab[i + 1])) {
            fprintf(stderr, "Blad sortowania\n");
            i = size;
        }

    printf("Size : %d\nElements : ", size);
    for (int i = 0; i < size; i++)
        printf("%d ", tab[i]);
}

void makeStatistics(FILE* file, int testNumber, bool ascending, void(*sortFunction)(int *, int, bool)) {
    fprintf(file, "size\tcompare amount \t swap amount \t time\n");

    for (int size = 100; size <= 10000; size += 100) {
        int* tab = (int*)malloc(size * sizeof(int));

        for (int count = 0; count < testNumber; count++) {
            for (int i = 0; i < size; i++)
                tab[i] = randInt(gen);

            compareAmount = 0;
            swapAmount = 0;

            clock_t start = clock();
            sortFunction(tab, size, ascending);
            clock_t stop = clock();

            for (int i = 0; i < size - 1; i++)
                if ((ascending && tab[i] > tab[i + 1]) || (!ascending && tab[i] < tab[i + 1]))
                    fprintf(stderr, "Blad sortowania\n");

            double time = (double)(stop - start) / CLOCKS_PER_SEC;
            fprintf(file, "%d\t%d\t%d\t%f\n", size, compareAmount, swapAmount, time * 1000);
        }

        free(tab);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    void (*sortFunction)(int *, int, bool) = nullptr;
    bool ascending = true;
    int size = 0;
    FILE* file = nullptr;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--type") == 0) {
            i++;
            if (strcmp(argv[i], "quick") == 0) {
                sortFunction = &quickSort;
            } else if (strcmp(argv[i], "dualQuick") == 0) {
                sortFunction = &dualPivotQuickSortCount;
            }
        } else if (strcmp(argv[i], "--comp") == 0) {
            i++;
            if (strcmp(argv[i], "<=") == 0) {
                ascending = true;
            } else if (strcmp(argv[i], ">=") == 0) {
                ascending = false;
            }
        } else if (strcmp(argv[i], "--stat") == 0) {
            file = fopen(argv[++i], "w");
            size = std::stoi(argv[++i]);
        }
    }

    if (sortFunction == nullptr) {
        printf("Give sort type as argument\n"
               "--type quick | dualQuick\n"
               "--comp <= | >=\n"
               "(optional) --stat 'filename' 'number_of_tests'\n");
        return 0;
    } else if (file == nullptr) {
        sortTable(size, ascending, sortFunction);
    } else {
        makeStatistics(file, size, ascending, sortFunction);
    }
}
