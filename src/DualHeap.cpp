#include "DualHeap.h"
#include <stdlib.h>
#include <cstdlib>
#include <cmath>

template <typename T>
DualHeap<T>::DualHeap(const int totalcap, const bool sortDir, const bool heapDir)
{
    cap = totalcap;
    resultsVector.reserve(cap);


    active_heap_head = pending_heap_head = 1;
    active_heap_tail = pending_heap_tail = 0;

    sortDirection = sortDir; //true = right
    heapDirection = heapDir; //left heap first = right

}

template <typename T>
int DualHeap<T>::get_cap() {
    return cap;
}

template <typename T>
int DualHeap<T>::get_size(){
    return active_heap_size() + pending_heap_size();
}

template <typename T>
int DualHeap<T>::active_heap_size(){

    if(active_heap_tail == 0)
        return 0;
    else return (std::abs(pending_heap_head - pending_heap_tail) + 1);
}

template <typename T>
int DualHeap<T>::pending_heap_size(){

    if (pending_heap_tail == 0)
        return 0;
    else return std::abs( (pending_heap_head - pending_heap_tail) + 1 );

}

template <typename T>
void DualHeap<T>::swapHeaps(){

    int temp;

    temp = active_heap_head;
    active_heap_head = pending_heap_head;
    pending_heap_head = temp;

    temp = active_heap_tail;
    active_heap_tail = pending_heap_tail;
    pending_heap_tail;
}

template <typename T>
void DualHeap<T>::changeDirection(){

    heapDirection = !heapDirection;
    swapHeaps();
}

template <typename T>
void DualHeap<T>::pendingHeapPush(const T element){

    changeDirection();
    activeHeapPush(element);
    changeDirection();
}

template <typename T>
int DualHeap<T>::leftHeapIndex(const int onePlusIndex){

    return onePlusIndex - 1;
}

template <typename T>
int DualHeap<T>::rightHeapIndex(const int onePlusIndex){

    return cap - onePlusIndex;
}

template <typename T>
int DualHeap<T>::leftHeapTailIndex(){

    if (heapDirection)
        return leftHeapIndex(active_heap_tail);
    else
        return leftHeapIndex(pending_heap_tail);
}

template <typename T>
int DualHeap<T>::rightHeapTailIndex(){

    if(heapDirection)
        return rightHeapIndex(pending_heap_tail);
    else
        return rightHeapIndex(active_heap_tail);
}

template <typename T>
bool DualHeap<T>::isInLeftHeap(const int index){

    return (index <= leftHeapTailIndex());
}

template <typename T>
bool DualHeap<T>::isInRightHeap(const int index){

    return (index >= rightHeapTailIndex());
}

template <typename T>
int DualHeap<T>::onePlusLeftHeapIndex(const int index){

    return index + 1;
}

template <typename T>
int DualHeap<T>::onePlusRightHeapIndex(const int index){

    return cap - index;
}

template <typename T>
bool DualHeap<T>::shouldSwapByIndex(const int childIndex, const int parentIndex){

    if(sortDirection){
        return resultsVector[childIndex] < resultsVector[parentIndex];
    }else{
        return resultsVector[childIndex] > resultsVector[childIndex];
    }
}

template <typename T>
void DualHeap<T>::swapByIndex(const int index1, const int index2){

    T temp = resultsVector[index1];
    resultsVector[index1] = resultsVector[index2];
    resultsVector[index2] = temp;
}

template <typename T>
void DualHeap<T>::heapifyUp(const int index){

    int childIndex = index;
    int trueParentIndex = parentIndex(childIndex);

    if (trueParentIndex != -1){

        if(shouldSwapByIndex(childIndex, trueParentIndex)){
            swapByIndex(childIndex, trueParentIndex);
            heapifyUp(trueParentIndex);
        }
    }
}

template <typename T>
int DualHeap<T>::onePlusIndex(const int index){

    if(isInLeftHeap(index)){
        return onePlusLeftHeapIndex(index);
    }else if(isInRightHeap(index)){
        return onePlusRightHeapIndex(index);
    }else{
        //this would be an error because it is out of range
    }
}

template <typename T>
bool DualHeap<T>::hasChildren(const int parentIndex){

    if(isInLeftHeap(parentIndex)){
        return (onePlusIndex(parentIndex) * 2 <= onePlusIndex(leftHeapTailIndex()) );
    } else if (isInRightHeap(parentIndex)){
        return (onePlusIndex(parentIndex) * 2 <= onePlusIndex(rightHeapTailIndex()) );
    }else{
        return false;
    }
}

template <typename T>
int DualHeap<T>::leftChildIndex(const int parentIndex){

    int leftChildIndex = -1;
    int candidateLeftChild;

    if (isInLeftHeap(parentIndex)){
        candidateLeftChild = leftHeapIndex(onePlusLeftHeapIndex(parentIndex) * 2);

        if(isInLeftHeap(candidateLeftChild)){
            leftChildIndex = candidateLeftChild;
        }
    }else if (isInRightHeap(parentIndex)){
        candidateLeftChild = rightHeapIndex(onePlusRightHeapIndex(parentIndex) * 2);

        if(isInRightHeap(candidateLeftChild)){
            leftChildIndex = candidateLeftChild;
        }
    }
    return leftChildIndex;
}

template <typename T>
int DualHeap<T>::rightChildIndex(const int parentIndex){

    int rightChildIndex = -1;
    int candidateRightChild;

    if(isInLeftHeap(parentIndex)){

        candidateRightChild = leftHeapIndex( onePlusLeftHeapIndex(parentIndex) * 2 + 1);

        if (isInLeftHeap(candidateRightChild)){

            rightChildIndex = candidateRightChild;
        }
    }else if(isInRightHeap(parentIndex)){

        candidateRightChild = rightHeapIndex(onePlusRightHeapIndex(parentIndex) * 2 + 1);

        if (isInRightHeap(candidateRightChild)){
            rightChildIndex = candidateRightChild;
        }
    }

    return rightChildIndex;
}

template <typename T>
void DualHeap<T>::heapifyDown(const int index){

    if(hasChildren(index)){

        int parentIndex = index;
        int trueLeftChildIndex = leftChildIndex (index);
        int trueRightChildIndex =rightChildIndex(index);
        int tempSwapIndex = -1;


        if(trueLeftChildIndex != -1){
            if(trueRightChildIndex != -1){

                if(sortDirection){

                    if( resultsVector[trueLeftChildIndex] < resultsVector[trueRightChildIndex])
                        tempSwapIndex = trueLeftChildIndex;
                    else
                        tempSwapIndex = trueRightChildIndex;
                    if( resultsVector[trueLeftChildIndex] > resultsVector[trueRightChildIndex])
                        tempSwapIndex = trueLeftChildIndex;
                    else
                        tempSwapIndex = trueRightChildIndex;
                }
            }else{
                tempSwapIndex = trueLeftChildIndex;
            }

            if(shouldSwapByIndex(tempSwapIndex, parentIndex)){
                swapByIndex(tempSwapIndex, parentIndex);
                heapifyDown(tempSwapIndex);
            }
        }
    }
}

template <typename T>
int DualHeap<T>::parentIndex(const int childIndex){

    int parentIndex = -1;

    if(isInLeftHeap(childIndex) && onePlusLeftHeapIndex(childIndex) != 1){
        parentIndex = leftHeapIndex(onePlusLeftHeapIndex(childIndex) / 2);
    }else if (isInRightHeap(childIndex) && onePlusRightHeapIndex(childIndex) != 1){
        parentIndex = rightHeapIndex(onePlusRightHeapIndex(childIndex) / 2);
    }else{
        return parentIndex;
    }
}


template <typename T>
void DualHeap<T>::activeHeapPush(const T element){

    if ( (active_heap_size() + pending_heap_size()) < cap) {

        int tailIndex = -1;

        active_heap_tail += 1;

        if(heapDirection){
            tailIndex = leftHeapIndex(active_heap_tail);
        }else{
            tailIndex = rightHeapIndex(active_heap_tail);
        }

        resultsVector[tailIndex] = element;

        heapifyUp(tailIndex);
    }
}

template <typename T>
T DualHeap<T>::current_heap_pop(){

    if (active_heap_size() > 0){

        T outputElement;

        if(heapDirection){

            outputElement = resultsVector[leftHeapIndex(active_heap_head)];

            resultsVector[leftHeapIndex(active_heap_head)] = resultsVector[leftHeapIndex(active_heap_tail)];

            active_heap_tail -= 1;

            heapifyDown(leftHeapIndex(active_heap_head));


        }else{

            outputElement = resultsVector[rightHeapIndex(active_heap_head)];

            resultsVector[rightHeapIndex(active_heap_head)] = resultsVector[rightHeapIndex(active_heap_tail)];

            active_heap_tail -= 1;

            heapifyDown(rightHeapIndex(active_heap_head));
        }

        return outputElement;
    }else{

        //error empty heap
    }
}
