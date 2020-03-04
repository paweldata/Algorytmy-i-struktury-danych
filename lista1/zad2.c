//Linked list implementation
//By Paweł Data
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
}  List;

void pushBack(List* list, int value);
void pushFront(List* list, int value);
bool pushOnIndex(List* list, int value, int index);
int popBack(List* list);
int popFront(List* list);
int popOnIndex(List* list, int index);
int getValueByIndex(List list, int index);
int getSize(List list);
List merge(List list1, List list2);
void showList(List list);

void pushBack(List* list, int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = malloc(sizeof(Node));
        list->head = newNode;
    } else {
        Node* temp = list->head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    list->size++;
}

void pushFront(List* list, int value) {
    Node* newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = list->head;

    list->head = newNode;
    list->size++;
}

bool pushOnIndex(List* list, int value, int index) {
    if (index < 0 || list->size < index)
        return false;
    if (index == 0) {
        pushFront(list, value);
        return true;
    }

    Node* previous = list->head;

    while (index-- > 1)
        previous = previous->next;

    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = previous->next;

    previous->next = newNode;
    list->size++;

    return true;
}

int popBack(List* list) {
    if (list->head == NULL)
        return -1;

    Node* temp = list->head;
    Node* previous = list->head;

    while (temp->next != NULL) {
        previous = temp;
        temp = temp->next;
    }

    int value = temp->value;
    free(previous->next);
    previous->next = NULL;
    list->size--;

    return value;
}

int popFront(List* list) {
    if (list->head == NULL)
        return -1;

    Node* toDelete = list->head;
    list->head = list->head->next;

    int value = toDelete->value;
    free(toDelete);
    list->size--;

    return value;
}

int popOnIndex(List* list, int index) {
    if (index < 0 || list->size <= index)
        return -1;
    if (index == 0)
        return popFront(list);

    Node* previous = list->head;

    while (index-- > 1)
        previous = previous->next;

    int value = previous->next->value;

    Node* temp = previous->next->next;
    free(previous->next);
    previous->next = temp;

    list->size--;

    return value;
}

int getValueByIndex(List list, int index) {
    if (index < 0 || index >= list.size)
        return -1;

    while (index-- > 0)
        list.head = list.head;

    return list.head->value;
}

int getSize(List list) {
    return list.size;
}

List merge(List list1, List list2) {
    if (list1.head == NULL)
        return list2;

    List newList = list1;
    while (list1.head->next != NULL)
        list1.head = list1.head->next;

    list1.head->next = list2.head;

    return newList;
}

void showList(List list) {
    while (list.head != NULL) {
        printf("%d ", list.head->value);
        list.head = list.head->next;
    }

    printf("\n");
}

int main() {
    time_t tt;
    int randomValue = time(&tt);
    srand(randomValue);

    List list;
    list.head = NULL;
    list.size = 0;

    for (int i = 0; i < 1000; i++)
        pushBack(&list, rand() % 100);

    int randomNode = rand() % 1000;
    double time = 0;

    for (int i = 0; i < 1000; i++) {
        clock_t start = clock();
        getValueByIndex(list, randomNode);
        clock_t stop = clock();

        time += (double)(stop-start)/CLOCKS_PER_SEC;
    }

    printf("Sredni czas do %d wierzcholka w milisekundach : %.5f\n", randomNode, time*1000);

    time = 0;

    for (int i = 0; i < 1000; i++) {
        randomNode = rand() % 1000;

        clock_t start = clock();
        getValueByIndex(list, randomNode);
        clock_t stop = clock();

        time += (double)(stop-start)/CLOCKS_PER_SEC;
    }

    printf("Sredni czas do losowego wierzcholka w milisekundach : %.5f\n", time*1000);

    List list1;
    list1.head = NULL;
    list1.size = 0;

    for (int i = 0 ; i < 5; i++)
        pushBack(&list1, i);

    showList(list1);
    pushOnIndex(&list1, -1, 1);
    showList(list1);

    return 0;
}
