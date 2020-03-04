//Circular doubly linked list implementation
//By Paweł Data
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>

typedef struct Node {
    int value;
    struct Node* next;
    struct Node* previous;
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
int getSize(List l);
List merge(List list1, List list2);
void showList(List list);
void showListReverse(List list);

void pushBack(List* list, int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;

    if (list->head == NULL) {
        newNode->next = newNode;
        newNode->previous = newNode;
        list->head = malloc(sizeof(Node));
        list->head = newNode;
    }
    else {
        newNode->next = list->head;
        newNode->previous = list->head->previous;
        newNode->previous->next = newNode;
        newNode->next->previous = newNode;
    }

    list->size++;
}

void pushFront(List* list, int value) {
    pushBack(list, value);
    list->head = list->head->previous;
}

bool pushOnIndex(List* list, int value, int index) {
    int size = getSize((*list));
    if (index < 0 || size < index)
        return false;
    if (index == 0) {
        pushFront(list, value);
        return true;
    }

    Node* temp = list->head;

    if (index < size / 2) {
        while (index-- > 0)
            temp = temp->next;
    } else {
        while (index++ < size)
            temp = temp->previous;
    }

    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = temp;
    newNode->previous = temp->previous;
    newNode->next->previous = newNode;
    newNode->previous->next = newNode;

    list->size++;
    return true;
}

int popBack(List* list) {
    if (list->head == NULL)
        return -1;

    int value = list->head->previous->value;

    Node* previous = list->head->previous->previous;
    free(list->head->previous);
    list->head->previous = previous;
    previous->next = list->head;

    list->size--;
    return value;
}

int popFront(List* list) {
    if (list->head == NULL)
        return -1;

    int value = list->head->value;

    Node* newBegin = list->head->next;
    newBegin->previous = list->head->previous;
    list->head->previous->next = newBegin;
    free(list->head);
    list->head = newBegin;

    list->size--;
    return value;
}

int popOnIndex(List* list, int index) {
    int size = getSize(*list);
    if (index < 0 || size <= index)
        return false;
    if (index == 0)
        return popFront(list);
    if (index == size)
        return  popBack(list);

    Node* temp = list->head;

    if (index < size / 2) {
        while (index-- > 0)
            temp = temp->next;
    } else {
        while (index++ < size)
            temp = temp->previous;
    }

    int value = temp->value;

    Node* toDelete = temp;
    temp->previous->next = temp->next;
    temp->next->previous = temp->previous;
    free(toDelete);

    list->size--;
    return value;
}

int getValueByIndex(List list, int index) {
    if (index < 0 || index >= list.size)
        return false;

    if (index < list.size / 2) {
        while (index-- > 0)
            list.head = list.head->next;
    } else {
        while (index++ < list.size)
            list.head = list.head->previous;
    }

    return list.head->value;
}

int getSize(List list) {
    return list.size;
}

List merge(List list1, List list2) {
    if (list1.head == NULL)
        return list2;
    if (list2.head == NULL)
        return list1;

    list1.head->previous->next = list2.head;
    list2.head->previous->next = list1.head;
    Node* temp = list1.head->previous;
    list1.head->previous = list2.head->previous;
    list2.head->previous = temp;

    return list1;
}

void showList(List list) {
    Node* temp = list.head;

    if (temp != NULL) {
        do {
            printf("%d ", temp->value);
            temp = temp->next;
        } while (temp != list.head);
    }

    printf("\n");
}

void showListReverse(List list) {
    Node* temp = list.head;

    if (temp != NULL) {
        do {
            temp = temp->previous;
            printf("%d ", temp->value);
        } while (temp != list.head);
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

    return 0;
}
