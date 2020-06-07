#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H


#include <vector>
#include <string>

template<class T>
struct QueueNode;

template <class T>
class PriorityQueue {
public:
    PriorityQueue();
    void insert(T value, double key);
    bool empty();
    T top() noexcept(false);
    T pop();
    void priority(T value, double key);
    void decreaseKey(int index);
    void print();

private:
    std::vector<QueueNode<T>*> array;
    int size;

    void fix(int index);
};


#endif //PRIORITYQUEUE_H
