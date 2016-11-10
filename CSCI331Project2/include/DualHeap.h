#ifndef DUALHEAP_H
#define DUALHEAP_H

#include <vector>

template <typename T>
class DualHeap
{
private:
    std::vector<T> resultsVector;
    int active_heap_head;
    int active_heap_tail;
    int pending_heap_head;
    int pending_heap_tail;
    int cap;

    bool heapDirection;
    bool sortDirection;

public:
    DualHeap(const int totalcap, const bool sortDir = true, const bool heapDir = true);

    int get_cap();

    int get_size();

    void activeHeapPush(const T element);

    void pendingHeapPush(const T element);

    T active_heap_pop();

    int onePlusIndex(const int index);

    bool hasChildren(const int parentIndex);

    void changeDirection();

    void swapHeaps();

    int active_heap_size();

    int pending_heap_size();

    int leftHeapIndex(const int onePlusIndex);

    int rightHeapIndex(const int onePlusIndex);

    void heapifyUp(const int index);

    void heapifyDown(const int index);

    int parentIndex(const int childIndex);

    int leftChildIndex(const int parentIndex);

    int rightChildIndex(const int parentIndex);

    bool isInLeftHeap(const int index);

    bool isInRightHeap(const int index);

    int leftHeapTailIndex();

    int rightHeapTailIndex();

    int onePlusLeftHeapIndex(const int index);

    int onePlusRightHeapIndex(const int index);

    bool shouldSwapByIndex(const int childIndex, const int parentIndex);

    void swapByIndex(const int index1, const int index2);
};
#include "DualHeap.cpp"
#endif // DUALHEAP_H
