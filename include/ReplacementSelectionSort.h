#ifndef REPLACEMENTSELECTIONSORT_H
#define REPLACEMENTSELECTIONSORT_H

#include <vector>


template <typename T>
class ReplacementSelectionSort
{


private:

    std::vector<T> resultsVector;

public:

     static std::vector< std::vector<T> > sort(const std::vector<T> vectorToBeSorted, const int heapSize = 10, const bool sortDirection = true);



};
#include "ReplacementSelectionSort.cpp"
#endif // REPLACEMENTSELECTIONSORT_H
