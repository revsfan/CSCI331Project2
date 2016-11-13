#ifndef REPLACEMENTSELECTIONSORT_H
#define REPLACEMENTSELECTIONSORT_H

#include <vector>
#include <iostream>
#include <fstream>
#include <functional>
#include <typeinfo>


using namespace std;
template <class T>
class ReplacementSelectionSort
{
    public:
        ReplacementSelectionSort(const int _size, istream& _infile, ostream& _outputfile,  const bool _sort);
        virtual ~ReplacementSelectionSort();
        bool GetactiveLeftHeap() { return activeLeftHeap; }
        void SetactiveLeftHeap(bool val) { activeLeftHeap = val; }
        bool Getdirection_flag() { return direction_flag; }
        void Setdirection_flag(bool val) { direction_flag = val; }
        int Getsize() { return size; }
        void Setsize(int val) { size = val; }
        int GetleftHeapStart() { return leftHeapStart; }
        void SetleftHeapStart(int val) { leftHeapStart = val; }
        int GetleftHeapEnd() { return leftHeapEnd; }
        void SetleftHeapEnd(int val) { leftHeapEnd = val; }
        int GetrightHeapStart() { return rightHeapStart; }
        void SetrightHeapStart(int val) { rightHeapStart = val; }
        int GetrightHeapEnd() { return rightHeapEnd; }
        void SetrightHeapEnd(int val) { rightHeapEnd = val; }
    protected:
    private:
        bool activeLeftHeap;
        bool direction_flag;
        int size;
        int leftHeapStart;
        int leftHeapEnd;
        int rightHeapStart;
        int rightHeapEnd;


	vector<T> dualHeap;


    void sort(istream& infile, ostream& outputfile);
	void heapify (bool leftSide);
	void siftUp(int index, bool leftSide);
	void siftDown (int index, bool leftSide);


	int left(int index, bool leftSide);
	int right(int index, bool leftSide);
	int parent(int index, bool leftSide);
	void swap(int index1, int index2);


	T pop();
	T initHeap(istream& infile);


	void current_dualHeap_push(const T entry);
	void pending_dualHeap_push (const T entry);
	void swapActive();

	//void printHeap();//prints the dualHeap to cout for monitoring purposes

	void sortPreMerge(istream& infile,ostream& outputfile);

};

#endif // REPLACEMENTSELECTIONSORT_H
