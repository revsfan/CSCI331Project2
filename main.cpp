#include <iostream>
#include <vector>
#include "ReplacementSelectionSort.h"
#include "DualHeap.h"

using namespace std;

template <typename T>
void replacementSelectionSortRun( const std::vector<T> SAMPLE_DATA, const int HEAP_SIZE);



int main()
{
    //push sample data to vector
    std::vector<std::string> sampleData;
    sampleData.push_back("apples");
    sampleData.push_back("oranges");
    sampleData.push_back("bananas");
    sampleData.push_back("cucumbers");
    sampleData.push_back("ducks");
    sampleData.push_back("iguanas");
    sampleData.push_back("zebras");
    sampleData.push_back("porcupines");
    sampleData.push_back("quills");
    sampleData.push_back("fingers");
    sampleData.push_back("toes");
    sampleData.push_back("bows");
    sampleData.push_back("arrows");
    sampleData.push_back("swords");
    sampleData.push_back("helmets");
    sampleData.push_back("cheese");








    replacementSelectionSortRun(sampleData, 10);

    return 0;
}

    template <typename T>
    void replacementSelectionSortRun( const std::vector<T> SAMPLE_DATA, const int HEAP_SIZE){

    std::vector< std::vector<T> > results = ReplacementSelectionSort<T>::sort( SAMPLE_DATA, HEAP_SIZE, true );



    }

