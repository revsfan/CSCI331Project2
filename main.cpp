/**
*	@file main.cpp
*	@author
*	@date
*	@brief Apply replacement selection sort to an unsorted list of records then merge them
*
*	The purpose of this program is to take an unsorted list of records and sort them into a
*	single list while using a fixed amount of memory to store records. The first process is
*	called replacement selection sort where it will fill the fixed amount of memeory then
*	process the list and sort it to a new record. This process is repeated until all of the records
*	from the initial list of records are all sorted. The second process is to merge the variable number
*	of indipendant sorted lists. This will result in a single list of sorted records using a fixed amount
*	of memeory.
*/

#include "ReplacementSelectionSort.h"
#include <fstream>
#include <iostream>
#include <string>
#include <typeinfo>
#include <random>
#include <cmath>
#include <sstream>
#include <stdio.h>
#include <queue>
#include <time.h>
#include <algorithm>
#include <iterator>
#include <climits>

using namespace std;


/**
*   Function to test only the selection sort process
*   @param inputFileName The placeholder for the file for input. This can contain any data because it will be overwritten
*   @param outputFileName The output file
*   @param direction_flag True = sort ascending
*/

template <typename T>
void test(string inputFileName, string outputFileName, bool direction_flag);

/**
*   Function to randomly generage numbers to a file
*   @param outfile File that will hold the randomly generated numbers
*/

template<typename T>
void generateTestFile(ostream& outfile);
/**
*   Evaluate various information about the selection sort after the selection sort process is complete
*   @param infile input file
*   @param outfile output file
*   @param direction_flag True = ascending
*/

template <typename T>
void checkRuns(istream& infile, ostream& outfile, bool direction_flag);

/**
*   Specific function to apply replacement selection sort on strings
*   @param inputFileName input file to be tested
*   @param outputFileName output file
*   @param ascending True = ascending
*/

void stringTest(string inputFileName, string outputFileName, bool ascending);

/**
*   Generates random strings
*   @param outfile output file
*/

void randomStrings(ostream& outfile);


/**
*   Generates random characters
*   @param s output character
*   @param len length of c-string
*/
void gen_random(char *s, const int len);

/**
*   Merge a 2d-vector containing sorted vectors
*   @param multiList A 2-d vector containing sorted vectors
*/


vector<int> mergeInt(const vector<vector<int> >& multiList);

/**
*   Applyies basic insertionsort
*   @param data vector to be sorted
*   @param n size of the vector
*/

void insertionSort (vector<int>& data, int n);






int main()
{

    srand(8);

    //test ints
	test<int> ("randomIntTest_in.txt","ascending_randomIntTest_out", true);
    //test<int> ("randomIntTest_in.txt", "descending_randomIntTest_out", false);

	//test doubles
	//test<double> ("randomDoubleTest_in.txt", "descending_randomDoubleTest_out.txt", false);

    //test floats
    //test<float> ("randomfloatTest_in.txt", "ascending_randomfloatTest_out", true);
	//test<float> ("randomfloatTest_in.txt", "descending_randomfloatTest_out", false);

    //test Strings
    //stringTest ("randomStringTest_in.txt", "descending_randomStringTest_out", false);




    std::vector < std::vector<int> > testVector;

    ifstream inFile("out.txt");
    string line;


    while(getline(inFile, line, ' '))
	{

        std::stringstream ss(line);

        std::vector<int> numbers;
        std::string in_line;
        int temp;
        while(getline (ss, in_line))
		{
            std::stringstream iss(in_line);
            iss >> temp;
            numbers.push_back(temp);
        }
        testVector.push_back(numbers);
    }



    for(int i = 0; i < testVector.size(); i++)
	{

        for (int j = 0; j < testVector[i].size(); j++)
		{

        cout << testVector[i][j];

        }

    }






 cout << endl << endl << endl;




vector<int> finalVector;

finalVector = mergeInt(testVector);

//BUG very small number of items are not sorted when merged. Insertion sort is very quick when most items are already sorted
insertionSort(finalVector, finalVector.size());

    for(int i = 0; i < finalVector.size(); i++)
	{

        cout << finalVector[i] << endl;
    }

	return 0;
}

void insertionSort (vector<int>& data, int n)
{

    int i, j, tmp;

     for (i = 1; i < n; i++)
	 {

         j = i;
         tmp = data[i];

         while (j > 0 && tmp < data[j - 1])
		 {

               data[j] = data[j - 1];
               j--;
         }

         data[j] = tmp;
    }
}


vector<int> mergeInt(const vector<vector<int> >& multiList)
{

  vector<int> finalList;
  vector<vector<int>::const_iterator> iterators(multiList.size());

  // Set all iterators to the beginning of their corresponding vectors in multiList
  for (int i = 0; i < multiList.size(); ++i) iterators[i] = multiList[i].begin();

  int k = 0, minValue, minValueIndex;

  while (1)
  {
    minValue = INT_MAX;
    for (int i = 0; i < iterators.size(); ++i)
	{
      if (iterators[i] == multiList[i].end()) continue;

      if (*iterators[i] < minValue)
	  {
        minValue = *iterators[i];
        minValueIndex = i;
      }
    }

    iterators[minValueIndex]++;

    if (minValue == INT_MAX) break;
    finalList.push_back(minValue);
  }

  return finalList;
}


template <typename T>
void test(string inputFileName, string outputFileName, bool direction_flag)
{

	ofstream randomTestFile(inputFileName);

	cout << "Creating test file\n";
	generateTestFile<T>(randomTestFile);
	randomTestFile.close();

	ifstream inputFile(inputFileName);
	ofstream otemp("temp.txt");
	cout << "Running Replacement Selection Sort\n";

	ReplacementSelectionSort<T> sortedRuns(15, inputFile ,otemp, direction_flag);
	otemp.close();

	ifstream itemp("temp.txt");
	ofstream outputFile(outputFileName);

	cout << "...Done\n";
	checkRuns<T>(itemp, outputFile, direction_flag);

    itemp.close();
    std::remove("temp.txt");


}

template<typename T>
void generateTestFile(ostream& outfile)
{

	int strlength;
	int fileLen;
	fileLen = rand() % (rand() % 1000);

	for(int i = 0; i < fileLen; i++)
	{

		strlength = 1 + rand()% 3;

		T num = rand() % (int)(pow(10,strlength));

		outfile << num <<" ";
		if(i % 5 == 0)
		{
			outfile << "\n";
			}

		}
}


template <typename T>
void checkRuns(istream& infile, ostream& outfile, bool direction_flag)
{


	int runLength = 0;

	int maxRunLength = 0;


	int totalObj = 0;

	int totalRuns = -1;

	bool isSorted = true;

	T prevObj;
	T curObj;

	string curLine;

	ofstream outClean("out.txt");

	while(getline(infile, curLine))
	{

		runLength = 0;
		outfile << curLine << "\n";
		outClean << curLine << "\n";
		totalRuns++;
		istringstream stringStream(curLine);
		stringStream >> prevObj;
		runLength++;
		totalObj++;

		while(!stringStream.eof())
		{

			stringStream >> curObj;
			runLength++;
			totalObj++;

			if(direction_flag)
			{

				if(curObj < prevObj)
				{

					isSorted = false;
				}
			}
			else
			{

				if(curObj > prevObj)
				{
					isSorted = false;
				}

			}
		}
		if(runLength > maxRunLength)
		{
			maxRunLength = runLength;
		}
	}

	outfile
			<<"averageRunLength = " << totalObj / totalRuns
			<<"\nthe file is sorted: "<< (isSorted? "True" : "False")
			<<"\nMax run length: " << maxRunLength
			<<"\ntotal Runs: " << totalRuns
			<<"\ntotal items: " << totalObj;
}


void stringTest(string inputFileName, string outputFileName, bool ascending)
{

	ofstream testFile(inputFileName);
	cout << "Creating test file of Strings\n";
	randomStrings(testFile);
	testFile.close();

	ifstream inputFile(inputFileName);
	ofstream otemp("temp.txt");
	cout<<"replacement selection\n";
	ReplacementSelectionSort<string> sortedRuns(15, inputFile, otemp, ascending);
	otemp.close();

	cout << "checking runs\n";
	ifstream itemp("temp.txt");
	ofstream outputFile(outputFileName);
	checkRuns<string> (itemp, outputFile, ascending);
}


void randomStrings(ostream& outfile)
{

	int strlength = 0;
	int fileLen;

	fileLen = rand() % (100 + rand() % 100);


	for(unsigned int i = 0; i < fileLen; i++)
	{

		strlength = 6;
		char* str = (char*) malloc(strlength * (sizeof(char)));
		gen_random(str,strlength);

		outfile<<str<<" ";

		if( i % 5 == 0 )
		{
			outfile << "\n";
		}

	}

}

void gen_random(char *s, const int len)
{

    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i)
	{
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

void merge(int a[], int startIndex, int endIndex)
{

        int size = (endIndex - startIndex) + 1;
        int *b = new int [size]();

        int i = startIndex;
        int mid = (startIndex + endIndex)/2;
        int k = 0;
        int j = mid + 1;

    while (k < size)
	{

        if((i <= mid) && (a[i] < a[j]))
		{
            b[k++] = a[i++];

        }
		else
		{
            b[k++] = a[j++];
        }

    }

    for(k=0; k < size; k++)
	{

        a[startIndex+k] = b[k];
    }

    delete []b;

}
