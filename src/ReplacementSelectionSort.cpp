

#include "ReplacementSelectionSort.h"
#include <string>
template <typename T>
ReplacementSelectionSort<T>::ReplacementSelectionSort(const int _size, istream& _infile, ostream& _outputfile,  const bool _sort){

		size = _size;
		direction_flag = _sort;
		activeLeftHeap = true;
		leftHeapStart = 0;
		leftHeapEnd = 0;
		rightHeapStart = size - 1;
		rightHeapEnd = size;
		dualHeap.resize(size);
		sort(_infile, _outputfile);

}

template <typename T>
T ReplacementSelectionSort<T>::initHeap(istream& infile){

	T newElement;


	infile >> newElement;

	for(unsigned int i = 0; i<size && !infile.eof(); i++){

		dualHeap[i ]= newElement;
		leftHeapEnd = i;
		heapify(true);
		infile >> newElement;

	}
	return newElement;
}

template <typename T>
void ReplacementSelectionSort<T>::sort(std::istream& infile, std::ostream& outputfile){

	std::vector<vector<T> >sortedLists;
	std::vector<T> currentList;

	T newElement;
	T lastElement;
	bool pendingFull=false;
	bool activeHeapOpen;


	newElement = initHeap(infile);

	while(!infile.eof()){

		lastElement = pop();


		currentList.push_back(lastElement);


		if(direction_flag){

			if(newElement >= lastElement){

				activeHeapOpen = true;
			}else{

				activeHeapOpen=false;
			}

		}else{

			if(newElement <= lastElement){

				activeHeapOpen = true;

			}else{

				activeHeapOpen = false;
			}
		}

		if(activeHeapOpen){

					current_dualHeap_push(newElement);
        }else{




			pending_dualHeap_push(newElement);


			if(activeLeftHeap){

				if(leftHeapStart > leftHeapEnd){
					pendingFull = true;
				}

			}else{

				if(rightHeapStart < rightHeapEnd){
					pendingFull = true;
				}

			}

			if(pendingFull){

				sortedLists.push_back(currentList);
				currentList.resize(0);

				swapActive();
				pendingFull = false;
			}
		}

		infile >> newElement;

	} //END WHILE

	if(activeLeftHeap){

		while(leftHeapStart <= leftHeapEnd){

			currentList.push_back(pop());
			leftHeapEnd--;

		}
	}else{


		while(rightHeapStart >= rightHeapEnd){
			currentList.push_back(pop());
			rightHeapEnd++;

		}
	}

	sortedLists.push_back(currentList);
	currentList.resize(0);
	swapActive();


	if(activeLeftHeap){

		while(leftHeapStart <= leftHeapEnd){

			currentList.push_back(pop());
			leftHeapEnd--;

		}
	}else{

		while(rightHeapStart >= rightHeapEnd){

			currentList.push_back(pop());
			rightHeapEnd++;

		}
	}

	sortedLists.push_back(currentList);


	for(int i = 0; i<sortedLists.size(); i++){

		for(int j = 0; j<sortedLists[i].size(); j++){

			outputfile<<sortedLists[i][j]<<" ";
		}

		outputfile << endl;
	}

}

template <typename T>
void ReplacementSelectionSort<T>::heapify(bool leftSide){

	int index;

	if(leftSide){

		index = parent(leftHeapEnd, leftSide);

		while(index >= leftHeapStart){
			siftDown(index, leftSide);
			index -= 1;
		}

	}else{

		index = parent(rightHeapEnd,leftSide);

		while(index<=rightHeapStart){

			siftDown(index,leftSide);
			index += 1;
		}
	}
}

template <typename T>
void ReplacementSelectionSort<T>::siftUp(int index, bool leftSide){

	int p = parent(index, leftSide);

	int toSwap = index;

	if(leftSide && direction_flag){

		if((p >= leftHeapStart) && (dualHeap[index] < dualHeap[p]))
			toSwap=p;
	}

	else if(leftSide){

		if((p >= leftHeapStart) && (dualHeap[index] > dualHeap[p]))
			toSwap = p;
	}
	else if(direction_flag){

		if((p <= rightHeapStart) && (dualHeap[index] < dualHeap[p]))
			toSwap = p;
	}else{

		if((p <= rightHeapStart) && (dualHeap[index] > dualHeap[p]))
			toSwap = p;
	}


	if(toSwap != index){

		swap(index,toSwap);
		siftUp(toSwap,leftSide);
	}
}

template <typename T>
void ReplacementSelectionSort<T>::siftDown(int index, bool leftSide){

	int l,
        r,
        toSwap;


	l = left(index,leftSide);
	r = right(index,leftSide);

	if(leftSide && direction_flag){

		if(l <= leftHeapEnd && dualHeap[l] < dualHeap[index])
			toSwap = l;
		else
			toSwap = index;

		if(r <= leftHeapEnd && dualHeap[r] < dualHeap[toSwap])
			toSwap = r;
	}

	else if(leftSide){

		if(l <= leftHeapEnd && dualHeap[l] > dualHeap[index])
			toSwap = l;
		else
			toSwap=index;

		if(r <= leftHeapEnd && dualHeap[r] > dualHeap[toSwap])
			toSwap = r;
	}
	else if(direction_flag){

		if(l >= rightHeapEnd && dualHeap[l] < dualHeap[index])
			toSwap = l;
		else
			toSwap = index;

		if(r >= rightHeapEnd && dualHeap[r] < dualHeap[toSwap])
			toSwap = r;
	}
	else {

		if(l >= rightHeapEnd && dualHeap[l] > dualHeap[index])
			toSwap = l;
		else
			toSwap = index;

		if(r >= rightHeapEnd && dualHeap[r] > dualHeap[toSwap])
			toSwap = r;
	}

	if(toSwap != index){
		swap(index,toSwap);
		siftDown(toSwap, leftSide);
	}
}

template <typename T>
T ReplacementSelectionSort<T>::pop(){

	T output;

	if(activeLeftHeap){

		output = dualHeap[leftHeapStart];
		swap(leftHeapStart, leftHeapEnd);
		leftHeapEnd--;

		siftDown(leftHeapStart, activeLeftHeap);
		leftHeapEnd++;
	}else{


		output = dualHeap[rightHeapStart];
		swap(rightHeapStart, rightHeapEnd);
		rightHeapEnd++;

		siftDown(rightHeapStart, activeLeftHeap);
		rightHeapEnd--;
	}

	return output;
}

template <typename T>
void ReplacementSelectionSort<T>::current_dualHeap_push(T entry){

	if(activeLeftHeap){

		dualHeap[leftHeapEnd] = entry;
		siftUp(leftHeapEnd, activeLeftHeap);

	}else{

		dualHeap[rightHeapEnd] = entry;
		siftUp(rightHeapEnd, activeLeftHeap);
	}
}

template <typename T>
void ReplacementSelectionSort<T>::pending_dualHeap_push(T entry){

	if(activeLeftHeap){
		leftHeapEnd--;
		rightHeapEnd--;
		dualHeap[rightHeapEnd]=entry;
		siftUp(rightHeapEnd,!activeLeftHeap);
	}
	else{
		leftHeapEnd++;
		rightHeapEnd++;
		dualHeap[leftHeapEnd]=entry;
		siftUp(leftHeapEnd,!activeLeftHeap);
	}
}

template <typename T>
void ReplacementSelectionSort<T>::swapActive(){

	activeLeftHeap =! activeLeftHeap;
}
template <typename T>
void ReplacementSelectionSort<T>::swap(int index1, int index2){

	T temp;
	temp = dualHeap[index1];
	dualHeap[index1] = dualHeap[index2];
	dualHeap[index2] = temp;
}

template <typename T>
int ReplacementSelectionSort<T>::left(int index, bool leftSide){

	return (leftSide? 2 * index + 1 : rightHeapStart - (rightHeapStart-index) * 2 - 1);
}

template <typename T>
int ReplacementSelectionSort<T>::right(int index, bool leftSide){

	return (leftSide? 2 * index + 2 : rightHeapStart - (rightHeapStart - index) * 2 - 2);
}

template <typename T>
int ReplacementSelectionSort<T>::parent(int index, bool leftSide){

	return (leftSide? (index - 1) / 2 : (index - rightHeapStart + 1) / 2 + rightHeapStart);
}

/**
*allows ints, strings, doubles, and floats to be used with the class.
*to allow more, add similar lines with desired types
**/
template class ReplacementSelectionSort<int>;
template class ReplacementSelectionSort<string>;
template class ReplacementSelectionSort<double>;
template class ReplacementSelectionSort<float>;
