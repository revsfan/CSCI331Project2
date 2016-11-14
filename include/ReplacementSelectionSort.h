
#ifndef REPLACEMENT_SELECTION_SORT
#define REPLACEMENT_SELECTION_SORT
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
