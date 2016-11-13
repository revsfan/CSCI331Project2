#include <iostream>
#include <vector>
#include "ReplacementSelectionSort.h"
#include "DualHeap.h"
//#include "ReplacementSelectionSort.cpp"

using namespace std;

template <typename T>
void replacementSelectionSortRun( const std::vector<T> SAMPLE_DATA, const int HEAP_SIZE);

std::vector< std::vector <int> > makeSortedLists()
{

    std::vector< std::vector<int> > *outputVector = new std::vector< std::vector<int> >;
    std::vector <int> *row = new std::vector<int>;

    row->push_back( 16 );
    row->push_back( 13 );
    row->push_back( 10 );
    row->push_back( 7 );
    row->push_back( 4 );
    row->push_back( 1 );

    outputVector->push_back( *row );
    row = new std::vector<int>;


    row->push_back( 20 );
    row->push_back( 17 );
    row->push_back( 14 );
    row->push_back( 11 );
    row->push_back( 8 );
    row->push_back( 5 );
    row->push_back( 2 );



    outputVector->push_back( *row );
    row = new std::vector<int>;

    row->push_back( 24 );
    row->push_back( 21 );
    row->push_back( 18 );
    row->push_back( 15 );
    row->push_back( 12 );
    row->push_back( 9 );
    row->push_back( 6 );
    row->push_back( 3 );







    outputVector->push_back( *row );
    row = new std::vector<int>;


    return *outputVector;

}


template <typename T>
std::vector<T> *mergeTwoLists(vector<T> list1, vector<T> list2)
{
    int firstListSize = list1.size();
    int secondListSize = list2.size();
    cout<<endl<<"list1.size(): "<<list1.size()<<"  list2.size(): "<<list2.size()<<endl;

    bool SmallestFirst = false;

    if(firstListSize>0&&firstListSize>0)
    {
        if(list1[0]<list1[firstListSize-1]||list2[0]<list2[firstListSize-1])
            SmallestFirst = true;
    }

    int firstPos = 0;
    int secondPos = 0;

    std::vector <T> *mergedList = new std::vector<int>;

    while(firstPos<firstListSize&&secondPos<secondListSize)
    {
        if(SmallestFirst)
        {
            if(list1[firstPos]<list2[secondPos])
            {
                mergedList->push_back( list1[firstPos] );
                firstPos++;
            }
            else
            {
                mergedList->push_back( list2[secondPos] );
                secondPos++;
            }
        }
        else
        {
            if(list1[firstPos]>list2[secondPos])
            {
                mergedList->push_back( list1[firstPos] );
                firstPos++;
            }
            else
            {
                mergedList->push_back( list2[secondPos] );
                secondPos++;
            }
        }
    }

    //cout<<endl<<"firstPos"<<firstPos<<"firstListSize"<<firstListSize<<"secondPos"<<secondPos<<"secondListSize"<<secondListSize;

    while(firstPos<firstListSize)
    {
        mergedList->push_back( list1[firstPos]);

        firstPos++;
    }
    while(secondPos<secondListSize)
    {
        mergedList->push_back( list2[secondPos]);

        secondPos++;
    }

    return mergedList;

}

template <typename T>
vector< std::vector<T> > SubVector(vector< std::vector<T> > allLists,int startVector, int endVector)
{
    std::vector< std::vector<T> > *splitVector = new std::vector< std::vector<T> >;
    for(int i = startVector; i < endVector;i++)
    {
        splitVector->push_back( allLists[i] );
    }
    return *splitVector;
}


template <typename T>
std::vector <T> mergeSortedLists(vector< std::vector<T> > allLists)
{
    std::vector< std::vector<T> > *splitVector1 = new std::vector< std::vector<T> >;
    std::vector< std::vector<T> > *splitVector2 = new std::vector< std::vector<T> >;
    std::vector< std::vector<T> > *splitVector3 = new std::vector< std::vector<T> >;

    std::vector<T> mergeVector1;
    std::vector<T> mergeVector2;
    std::vector<T> *mergedList = new std::vector<T>;

    std::vector< std::vector<T> > splitVector1a;
    std::vector< std::vector<T> > splitVector2b;


    if(allLists.size()==0)
    {
        return *mergedList;
    }
    if(allLists.size()==1)
    {
        return allLists[0];
    }
    else if(allLists.size()==2)
    {
        mergedList = mergeTwoLists(allLists[0],allLists[1]);
        return *mergedList;
    }
    else
    {
        /*for(int i = 0; i < allLists.size()/2;i++)
        {
            splitVector1->push_back( allLists[i] );
        }*/
        mergeVector1 = mergeSortedLists(SubVector(allLists,0,allLists.size()/2));

        //mergeVector1=mergeSortedLists( splitVector1);
        /*
        for(int i = allLists.size()/2; i < allLists.size();i++)
        {
            splitVector2->push_back( *allLists[i] );

        }*/
        //mergeVector2=mergeSortedLists(splitVector2);
        mergeVector2 = mergeSortedLists(SubVector(allLists,allLists.size()/2,allLists.size()));

        splitVector3->push_back( mergeVector1 );
        splitVector3->push_back( mergeVector2 );
        return mergeSortedLists(*splitVector3);
    }
    return *mergedList;
}

template <typename T>
std::vector< std::vector <T> > mergeFirstTwoSortedLists(vector< std::vector<T> > allLists)
{
    int firstListSize = allLists[0].size();
    int secondListSize = allLists[1].size();

    std::vector< std::vector<int> > *outputVector = new std::vector< std::vector<int> >;

    int firstPos = 0;
    int secondPos = 0;

    std::vector <T> *mergedList = new std::vector<int>;

    while(firstPos<firstListSize&&secondPos<secondListSize)
    {
        if(allLists[0][firstPos]<allLists[1][secondPos])
        {
            mergedList->push_back( allLists[0][firstPos] );
            //cout<<endl<<"add : "<<allLists[0][firstPos];
            firstPos++;
        }
        else
        {
            mergedList->push_back( allLists[1][secondPos] );
            //cout<<endl<<"add : "<<allLists[1][secondPos];
            secondPos++;
        }
    }

    //cout<<endl<<"firstPos"<<firstPos<<"firstListSize"<<firstListSize<<"secondPos"<<secondPos<<"secondListSize"<<secondListSize;

    while(firstPos<firstListSize)
    {
        mergedList->push_back( allLists[0][firstPos]);

        //cout<<endl<<"add : "<<allLists[0][firstPos];
        firstPos++;
    }
    while(secondPos<firstListSize)
    {
        mergedList->push_back( allLists[1][secondPos]);

        //cout<<endl<<"add : "<<allLists[1][secondPos];
        secondPos++;
    }

    outputVector->push_back( *mergedList );
    return *outputVector;
}


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

    cout <<"123234345456456";
    std::vector< std::vector<int> > sortedLists= makeSortedLists();
    cout <<"sdfhfdghfghdf";

    cout <<sortedLists.size() << endl;
        for (int i = 0; i < sortedLists.size(); i++)
        {
            cout << "Array number: " << i <<" Size: "<< sortedLists[i].size() << endl;

            for (int j = 0; j < sortedLists[i].size(); j++)
            {
                std::cout << "sortedLists" << "[" << i << "]" << "[" << j << "]: " <<sortedLists[i][j] << endl;

            }
        }
    //std::vector< std::vector<int> > mergedLists=mergeSortedLists(sortedLists);
    std::vector<int>mergedLists=mergeSortedLists(sortedLists);

        cout<< endl<<"Size: "<<mergedLists.size()<< endl;
    for (int i = 0; i < mergedLists.size(); i++)
    {
        cout << mergedLists[i] << endl;
    }

/*
    cout <<mergedLists.size() << endl;
        for (int i = 0; i < mergedLists.size(); i++)
        {
            cout << "Array number: " << i <<" Size: "<< mergedLists[i].size() << endl;

            for (int j = 0; j < mergedLists[i].size(); j++)
            {
                std::cout << "mergedLists" << "[" << i << "]" << "[" << j << "]: " <<mergedLists[i][j] << endl;

            }
        }
        */
    /*
    for (int i = 0; i < sampleData.size(); i++){
        cout << sampleData[i] << endl;
    }

    replacementSelectionSortRun(sampleData, 10);

    cout<< endl;
    for (int i = 0; i < sampleData.size(); i++){
        cout << sampleData[i] << endl;
    }
*/
    return 0;
}

    template <typename T>
    void replacementSelectionSortRun( const std::vector<T> SAMPLE_DATA, const int HEAP_SIZE)
    {

        std::vector< std::vector<T> > results = ReplacementSelectionSort<T>::sort( SAMPLE_DATA, HEAP_SIZE, true );

        cout<< endl;
        for (int i = 0; i < results.size(); i++)
        {
            //cout << i <<": "<< results[i].size() << endl;

            for (int j = 0; j < results[i].size(); j++)
            {
                cout << "results" << "[" << i << "]" << "[" << j << "]" <<results[i][j] << endl;

            }
        }

    }

