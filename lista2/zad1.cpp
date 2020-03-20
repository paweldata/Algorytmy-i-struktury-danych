//By Paweł Data
#include <cstring>
#include <fstream>
#include <random>

//globas variables
int compareAmount = 0;
int swapAmount = 0;

void insertionSort(int* tab, int size, bool ascending);
void mergeSort(int* tab, int size, bool ascending);
void mergeSortRecursion(int* tab, int* temp, int left, int right, bool ascending);
void quickSort(int* tab, int size, bool ascending);
void quickSortRecursion(int* tab, int left, int right, bool ascending);
void dualPivotQuickSortCount(int* tab, int size, bool ascending);
void dualPivotQuickSortCountRecursion(int* tab, int left, int right, bool ascending);
void quickSortAndInsertSort(int* tab, int size, bool ascending);
void quickSortAndInsertSortRecursion(int* tab, int left, int right, bool ascending);

void sortTable(int size, bool ascending, void(*sortFunction)(int *, int, bool));
void makeStatistics(FILE* file, int testNumber, bool ascending, void(*sortFunction)(int *, int, bool));

void insertionSort(int* tab, int size, bool ascending) {
    char sortChar = ((ascending) ? '>' : '<');
    int temp;

    for (int i = 1; i < size; i++) {
        temp = tab[i];
        int j = i - 1;

        while (j >= 0 && ((ascending && tab[j] > temp) || (!ascending && tab[j] < temp))) {
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
}

void mergeSort(int* tab, int size, bool ascending) {
    int* temp = (int*)malloc(size * sizeof(int));
    mergeSortRecursion(tab, temp, 0, size - 1 , ascending);
}

void mergeSortRecursion(int* tab, int* temp, int left, int right, bool ascending) {
    if (right <= left)
        return;

    char* sortFunction = (char*)((ascending) ? "min" : "max");
    int tab1Index = left;
    int mid = left + (right - left) / 2;
    int tab2Index = mid + 1;
    int index = left;

    mergeSortRecursion(tab, temp, tab1Index, tab2Index - 1, ascending);
    mergeSortRecursion(tab, temp, tab2Index, right, ascending);

    while(tab1Index <= mid && tab2Index <= right) {
        fprintf(stderr, "%s(%d, %d)", sortFunction, tab[tab1Index], tab[tab2Index]);
        if ((ascending && tab[tab1Index] < tab[tab2Index]) || (!ascending && tab[tab1Index] > tab[tab2Index])) {
            temp[index++] = tab[tab1Index++];
        } else {
            temp[index++] = tab[tab2Index++];
        }
        fprintf(stderr, " = %d\n", temp[index - 1]);
        compareAmount++;
        swapAmount++;
    }

    while (tab1Index <= mid) {
        temp[index++] = tab[tab1Index++];
        swapAmount++;
    }

    while (tab2Index <= right) {
        temp[index++] = tab[tab2Index++];
        swapAmount++;
    }

    for (int i = left; i <= right; i++) {
        tab[i] = temp[i];
        swapAmount++;
    }
}

void quickSort(int* tab, int size, bool ascending) {
    quickSortRecursion(tab, 0, size - 1, ascending);
}

void quickSortRecursion(int* tab, int left, int right, bool ascending) {
    if (right <= left)
        return;

    char sortChar = ((ascending) ? '>' : '<');
    char negSortChar = ((ascending) ? '<' : '>');
    int value = tab[right];
    int upper = right;
    int lower = left;

    while (lower <= upper) {

        fprintf(stderr, "check %d %c %d\n", tab[lower], sortChar, value);
        while ((ascending && tab[lower] < value) || (!ascending && tab[lower] > value)) {
            lower++;
            compareAmount++;
            fprintf(stderr, "check %d %c %d\n", tab[lower], sortChar, value);
        }

        fprintf(stderr, "check %d %c %d\n", tab[upper], negSortChar, value);
        while ((ascending && tab[upper] > value) || (!ascending && tab[upper] < value)) {
            upper--;
            compareAmount++;
            fprintf(stderr, "check %d %c %d\n", tab[upper], negSortChar, value);
        }

        compareAmount += 2;

        if (lower <= upper) {
            fprintf(stderr, "swap %d and %d\n", tab[lower], tab[upper]);
            std::swap(tab[lower++], tab[upper--]);
            swapAmount++;
        }
    }

    quickSortRecursion(tab, left, upper, ascending);
    quickSortRecursion(tab, upper + 1, right, ascending);
}

void dualPivotQuickSortCount(int* tab, int size, bool ascending) {
    dualPivotQuickSortCountRecursion(tab, 0, size - 1, ascending);
}

void dualPivotQuickSortCountRecursion(int* tab, int left, int right, bool ascending) {
    if (right <= left)
        return;

    if ((ascending && tab[left] > tab[right]) || (!ascending && tab[left] < tab[right]))
        std::swap(tab[left], tab[right]);
    swapAmount++;
    compareAmount++;

    char sortChar = ((ascending) ? '>' : '<');
    char negSortChar = ((ascending) ? '<' : '>');
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

void quickSortAndInsertSort(int* tab, int size, bool ascending) {
    quickSortAndInsertSortRecursion(tab, 0 , size - 1, ascending);
}

void quickSortAndInsertSortRecursion(int* tab, int left, int right, bool ascending) {
    if (right <= left)
        return;

    if (right - left < 16) {
	// insertSort
        char sortChar = ((ascending) ? '>' : '<');
        int temp;

        for (int i = left; i <= right; i++) {
            temp = tab[i];
            int j = i - 1;

            while (j >= 0 && ((ascending && tab[j] > temp) || (!ascending && tab[j] < temp))) {
                fprintf(stderr, "check %d %c %d, swap\n", temp, sortChar,tab[j]);
                tab[j + 1] = tab[j];
                swapAmount++;
                compareAmount++;
                j--;
            }

            fprintf(stderr, "check %d %c %d\n", temp, sortChar,tab[j]);
            compareAmount++;
            tab[j + 1] = temp;
        }
    } else {
	// quickSort
        char sortChar = ((ascending) ? '>' : '<');
        char negSortChar = ((ascending) ? '<' : '>');
        int value = tab[right];
        int upper = right;
        int lower = left;

        while (lower <= upper) {

            fprintf(stderr, "check %d %c %d\n", tab[lower], sortChar, value);
            while ((ascending && tab[lower] < value) || (!ascending && tab[lower] > value)) {
                lower++;
                compareAmount++;
                fprintf(stderr, "check %d %c %d\n", tab[lower], sortChar, value);
            }

            fprintf(stderr, "check %d %c %d\n", tab[upper], negSortChar, value);
            while ((ascending && tab[upper] > value) || (!ascending && tab[upper] < value)) {
                upper--;
                compareAmount++;
                fprintf(stderr, "check %d %c %d\n", tab[upper], negSortChar, value);
            }

            compareAmount += 2;

            if (lower <= upper) {
                fprintf(stderr, "swap %d and %d\n", tab[lower], tab[upper]);
                std::swap(tab[lower++], tab[upper--]);
                swapAmount++;
            }
        }

        quickSortAndInsertSortRecursion(tab, left, upper, ascending);
        quickSortAndInsertSortRecursion(tab, upper + 1, right, ascending);
    }
}

void sortTable(int size, bool ascending, void(*sortFunction)(int *, int, bool)) {
    scanf("%d", &size);
    int* tab = (int*)malloc(size * sizeof(int));

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

    printf("%d\n", size);
    for (int i = 0; i < size; i++)
        printf("%d ", tab[i]);
}

void makeStatistics(FILE* file, int testNumber, bool ascending, void(*sortFunction)(int *, int, bool)) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> randInt(1, 1000);

    fprintf(file, "size\tcompare amount \t swap amount \t time\n");

    for (int size = 100; size <= 10000; size += 100) {
        int* tab = (int*)malloc(size * sizeof(int));

        for (int count = 0; count < testNumber; count++) {
            for (int i = 0; i < size; i++)
                tab[i] = randInt(generator);

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
            if (strcmp(argv[i], "insert") == 0) {
                sortFunction = &insertionSort;
            } else if (strcmp(argv[i], "merge") == 0) {
                sortFunction = &mergeSort;
            } else if (strcmp(argv[i], "quick") == 0) {
                sortFunction = &quickSort;
            } else if (strcmp(argv[i], "dualQuick") == 0) {
                sortFunction = &dualPivotQuickSortCount;
            } else if (strcmp(argv[i], "hybrid") == 0) {
                sortFunction = &quickSortAndInsertSort;
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
               "--type quick | insert | merge | dualQuick | hybrid\n"
               "--comp <= | >=\n"
               "(optional) --stat 'filename' 'number_of_tests'\n");
    } else if (file == nullptr) {
        sortTable(size, ascending, sortFunction);
    } else {
        makeStatistics(file, size, ascending, sortFunction);
    }

    return 0;
}
