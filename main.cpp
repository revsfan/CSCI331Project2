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






int main()
{

    srand(8);

    //test ints
	//test<int> ("randomIntTest_in.txt","ascending_randomIntTest_out", true);
    //test<int> ("randomIntTest_in.txt", "descending_randomIntTest_out", false);

	//test doubles
	//test<double> ("randomDoubleTest_in.txt", "descending_randomDoubleTest_out.txt", false);

    //test floats
    //test<float> ("randomfloatTest_in.txt", "ascending_randomfloatTest_out", true);
	//test<float> ("randomfloatTest_in.txt", "descending_randomfloatTest_out", false);

    //test Strings
    stringTest ("randomStringTest_in.txt", "descending_randomStringTest_out", false);


return 0;
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

		strlength = 2;

		T num = (rand() % 89) + 10;


		outfile << num << " ";

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
	int minLength = 0;

	int maxRunLength = 0;
	int minRunLength = 0;


	int totalObj = 0;

	int totalRuns = 0;

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
		if(runLength < maxRunLength){
            minRunLength = runLength;
		}
	}

	outfile
			<<"averageRunLength = " << totalObj / totalRuns
			<<"\nthe file is sorted: "<< (isSorted? "True" : "False")
			<<"\nMax run length: " << maxRunLength
			<<"\nMin run length: " << minRunLength - 1
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

		strlength = 2;
		char* str = (char*) malloc(strlength * (sizeof(char)));
		gen_random(str,strlength);

		outfile << str << " ";

		if( i % 5 == 0 )
		{
			outfile << "\n";
		}

	}

}

void gen_random(char *s, const int len)
{

    static const char alphanum[] =

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
        int mid = (startIndex + (startIndex + endIndex))/2;
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
