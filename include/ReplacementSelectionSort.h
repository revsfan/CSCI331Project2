/**
*	@file ReplacementSelectionSort.h
*	@brief A class to apply Replacement Selection Sort to a file of unsorted items
*/

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

        /**
        *   Construcor
        *   @param _size represents the fixed memory size
        *   @param _infile input file that is to be sorted
        *   @param _outputfile output file after the process is complete
        *   @param _sort direction of the sorting True = ascending
        */
        ReplacementSelectionSort(const int _size, istream& _infile, ostream& _outputfile,  const bool _sort);

        /**
        * Default destructor
        */
        virtual ~ReplacementSelectionSort();

    protected:
    private:
        bool activeLeftHeap; /**< True = left heap is the active heap*/
        bool direction_flag; /**< Sorting order True = ascending */
        int size;            /**< Fixed memory size */
        int leftHeapStart;   /**< Position of the begining of the left heap */
        int leftHeapEnd;     /**< Position of the ending of the left heap */
        int rightHeapStart;  /**< Position of the begining of the right heap */
        int rightHeapEnd;    /**< Position of the ending of the right heap */


		vector<T> dualHeap;  /**< A vector that will serve as the dual heap ADT */


        /**
        *   Uses replacement selection sort to create multiple sorted lists
        *   @param infile A file of records to be sorted
        *   @param outputfile A file to put the multiple sorted records
        */
		void sort(istream& infile, ostream& outputfile);

		/**
		*   Builds the heap structure
		*   @param leftSide which side of the dual heap to be heapified
		*/
		void heapify (bool leftSide);

		/**
		*   Operation to help build the heap
		*   @param  index Index of the item to be sifted up
		*   @param leftSide which side of the dual heap to look at
		*/
		void siftUp(int index, bool leftSide);

		/**
		*   Operation to help build the heap
		*   @param index Index of the item to be sifted down
		*   @param leftSide which side of the dual heap to look at
		*/
		void siftDown (int index, bool leftSide);



        /**
        *   Return left indice of a given element
        *   @param index Index of given element
        *   @param leftSide which side of the dual heap to look at
        *   @return Return left indice of a given element
        */
		int left(int index, bool leftSide);

		/**
		*   Return right indice of a given alement
		*   @param index Index of a given element
		*   @param leftSide which side of the dual heap to look at
		*   @return Return right indice of a given element
		*/
		int right(int index, bool leftSide);

		/**
		*   Return parent idicie of a given element
		*   @param index Index of a given element
		*   @param leftSide which side of the dual heap to loo at
		*   @return Return parent indie of a given element
		*/
		int parent(int index, bool leftSide);

		/**
		*   Swaps two elements
		*   @param index1 index of the first element to be swapped
		*   @param index2 index of the second element to be swapped
		*/
		void swap(int index1, int index2);



        /**
        *   Pops the top element in the heap
        *   @return Returns the value of the poped element
        */
		T pop();

		/**
		*   Initializes the heap
		*   @param infile Input file to grab records from
		*   @return T Returns the element grabed from the file
		*/
		T initHeap(istream& infile);



        /**
        *   Pushes an element onto the active/current side of the dual heap
        *   @param entry Item to be pushed onto the active side of the dual heap
        */
		void current_dualHeap_push(const T entry);

		/**
		*   Pushes an element onto the pending side of the dual heap
		*   @param entry Item to be pushed onto the pending side of the dual heap
		*/
		void pending_dualHeap_push (const T entry);

		/**
		*   Swaps which active and pending sides
		*/
		void swapActive();


        /**
        *   Helper function for sorting using the replacement selection sort algorithm
        *   @param infile Inputfile to be read
        *   @param outputfile Outputfile to be writen to
        */
		void sortPreMerge(istream& infile, ostream& outputfile);

};

#endif // REPLACEMENTSELECTIONSORT_H
