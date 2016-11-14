
#ifndef REPLACEMENT_SELECTION_SORT
#define REPLACEMENT_SELECTION_SORT
#include <vector>
#include <iostream>
#include <fstream>
#include <functional>
#include <typeinfo>


using namespace std;
template <class T>
class ReplacementSelectionSort{
private:


	bool activeLeftHeap,
         direction_flag;

	int size,
        leftHeapStart,
        leftHeapEnd,
        rightHeapStart,
        rightHeapEnd;


	vector<T> dualHeap;



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


	void sort(istream& infile, ostream& outputfile);

public:

	ReplacementSelectionSort(const int _size = 10, istream& _infile = new ifstream("input.txt"), ostream& _outputfile = cout,  const bool _sort = true);
};
#endif
