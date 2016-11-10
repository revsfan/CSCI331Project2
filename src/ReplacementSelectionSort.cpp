#include "ReplacementSelectionSort.h"
#include "DualHeap.h"
#include <vector>

template <typename T>
std::vector< std::vector <T> > ReplacementSelectionSort<T>::sort(const std::vector<T> vectorToBeSorted, const int heapSize, const bool sortDirection){


    if (heapSize < 1) 
	{
        //error
    }

    std::vector< std::vector<T> > *outputVector = new std::vector< std::vector<T> >;
    DualHeap<T> *dualHeap = new DualHeap<T>( heapSize, sortDirection );

    T element;
    int totalCap = dualHeap -> get_cap();
    int nextItemToSort;

    for (int i = 1; i < totalCap && i < vectorToBeSorted.size(); i++)
	{
          element = vectorToBeSorted[i];
		  dualHeap ->activeHeapPush( element );
		  dualHeap = i + 1;
    }

    int currentList = 0;
    T lastElementPopped;
    T nextElement;

    std::vector <T> *row = new std::vector<T>;

    while (nextItemToSort < vectorToBeSorted.size() || dualHeap->get_size() > 0) 
	{
		lastElementPopped = dualHeap->current_heap_pop();
		row->push_back( lastElementPopped );
		if ( nextItemToSort < vectorToBeSorted.size() ) 
		{
			nextElement = vectorToBeSorted[nextItemToSort];
			nextItemToSort++;
			if (sortDirection) 
			{
				if (nextElement < lastElementPopped) 
				{
					dualHeap->pendingHeapPush( nextElement );
				} 
				else 
				{
					dualHeap->activeHeapPush( nextElement );
                }
            } 
			else 
			{
				if (nextElement > lastElementPopped) 
				{
					dualHeap->pendingHeapPush( nextElement );
                } 
				else 
				{
					dualHeap->activeHeapPush( nextElement );
				}
            }

        }

        if (dualHeap->active_heap_size() == 0) 
		{
			dualHeap->changeDirection();
            currentList++;
            outputVector->push_back( *row );
            row = new std::vector<T>;
        }
		
    }
        delete dualHeap;

        return *outputVector;

}