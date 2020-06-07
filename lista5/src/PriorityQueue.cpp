#include <stdexcept>

#include "PriorityQueue.h"
#include "Node.h"

template<class T>
struct QueueNode {
    T value;
    double key;
};

template<class T>
PriorityQueue<T>::PriorityQueue() {
    this->array = std::vector<QueueNode<T>*>(16, nullptr);
    this->size = 0;
}

template <class T>
void PriorityQueue<T>::insert(T value, double key) {
    int index = this->size;
    this->size++;

    if (this->array.size() < this->size)
        this->array.resize(this->size + 10, nullptr);

    while (index > 0 && this->array[index / 2]->key > key) {
        this->array[index] = this->array[index / 2];
        index /= 2;
    }

    this->array[index] = new QueueNode<T>{.value = value, .key = key};
}

template <class T>
bool PriorityQueue<T>::empty() {
    return this->size == 0;
}

template <class T>
T PriorityQueue<T>::top() noexcept(false) {
    if (this->size == 0)
        throw std::out_of_range("Queue is empty\n");
    return this->array[0]->value;
}

template <class T>
T PriorityQueue<T>::pop() {
    if (this->size == 0)
        throw std::out_of_range("Queue is empty\n");

    T result = this->array[0]->value;
    this->array[0] = this->array[this->size - 1];
    this->size--;
    this->fix(0);

    return result;
}

template <class T>
void PriorityQueue<T>::priority(T value, double key) {
    for (int i = 0; i < this->size; i++) {
        if (this->array[i]->value == value && this->array[i]->key > key) {
            this->array[i]->key = key;
            this->decreaseKey(i);
        }
    }
}

template <class T>
void PriorityQueue<T>::decreaseKey(int index) {
    if (index >= size)
        return;

    QueueNode<T>* temp = this->array[index];

    while (index > 0 && this->array[index / 2]->key > temp->key) {
        this->array[index] = this->array[index / 2];
        index /= 2;
    }

    this->array[index] = temp;
}

template <>
void PriorityQueue<int>::print() {
    for (int i = 0; i < this->size; i++)
        printf("(%d, %d), ",this->array[i]->value, (int)this->array[i]->key);
    printf("\n");
}

template <class T>
void PriorityQueue<T>::fix(int index) {
    int left = 2 * index;
    int right = left + 1;

    if (right > this->size)
        return;

    int min = (this->array[index]->key <= this->array[left]->key) ? index : left;
    min = (this->array[min]->key <= this->array[right]->key) ? min : right;

    if (min != index) {
        std::swap(this->array[min], this->array[index]);
        this->fix(min);
    }
}

template class PriorityQueue<int>;
template class PriorityQueue<Node*>;
