//Queue implementation
//By Paweł Data
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* back;
} Queue;

bool isEmpty(Queue queue);
int getSize(Queue queue);
void push(Queue* queue, int value);
void pop(Queue* queue);
int front(Queue queue);
int back(Queue queue);
void showQueue(Queue queue);

bool isEmpty(Queue queue) {
    if (queue.front == NULL && queue.back == NULL)
        return true;
    return false;
}

int getSize(Queue queue) {
    int counter = 0;
    Node* temp = queue.front;

    while (temp != NULL) {
        temp = temp->next;
        counter++;
    }

    return counter;
}

void push(Queue* queue, int value) {
    Node* newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    if (isEmpty((*queue))) {
        queue->front = newNode;
        queue->back = newNode;
    } else {
        queue->back->next = newNode;
        queue->back = newNode;
    }
}

void pop(Queue* queue) {
    if (isEmpty((*queue)))
        return;

    Node* toDelete = queue->front;
    queue->front = queue->front->next;
    free(toDelete);

    if (queue->front == NULL)
        queue->back = NULL;
}

int front(Queue queue) {
    return queue.front->value;
}

int back(Queue queue) {
    return queue.back->value;
}

void showQueue(Queue queue) {
    Node* temp = queue.front;

    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }

    printf("\n");
}

int main() {
    Queue queue;
    queue.front = NULL;
    queue.back = NULL;

    for (int i = 0; i < 5; i++)
        push(&queue, i);

    showQueue(queue);

    printf("Front : %d, back : %d\n", front(queue), back(queue));
    printf("Size : %d\n", getSize(queue));

    printf("Queue after pop : \n");
    pop(&queue);
    showQueue(queue);

    return 0;
}
