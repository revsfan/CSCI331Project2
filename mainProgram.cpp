#include "ReplacementSelectionSort.h"
#include "ReplacementSelectionSort.cpp"
#include "TournamentSort.h"
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
#include <queue>
#include <functional>
#include <string>

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
vector<vector<T>> checkRuns(istream& infile, ostream& outfile, bool direction_flag);

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
    srand(33);

	string inputFileName = "randomStringTest_in.txt";
	string outputFileName = "descending_randomStringTest_out";
	cout << "starting\n"<<std::flush;
	ofstream testFile(inputFileName);
	cout << "Creating test file of Strings\n"<<std::flush;
	randomStrings(testFile);
	testFile.close();

	ifstream inputFile(inputFileName);
	bool ascending = false;
	ofstream otemp("temp.txt");
	cout<<"replacement selection\n"<<std::flush;
	ReplacementSelectionSort<string> sortedRuns(15, inputFile, otemp, ascending);
	ofstream outputFile(outputFileName);
	sortedRuns.sort(inputFile, otemp);
	otemp.close();

	cout << "checking runs\n"<<std::flush;
	ifstream itemp("temp.txt");
	// /ofstream outputFile(outputFileName);
	vector<vector<string>> listOfLists;

	listOfLists = checkRuns<string> (itemp, outputFile, ascending);
	cout << "got the list\n"<<std::flush;
	//vector<vector<string>> listOfLists = {second, third, first, fourth, seventh, sixth, fifth};
	vector<string> final= {};
 	TournamentSort<string> tournament;

	std::priority_queue<TournamentSort<string>::Node,
	std::vector<TournamentSort<string>::Node>,TournamentSort<string>::compare> 		PQ;

	cout<<"about to initialize\n"<<std::flush;
	PQ = tournament.initPQ(PQ, listOfLists);
	cout<<"about to sortmerge\n"<<std::flush;
	tournament.pushToFinal(PQ, final, listOfLists);
	cout<<"about to write\n"<<std::flush;
	ofstream myfile;
 	myfile.open ("output.txt");
	for(int i = 0; i < tournament.finalVector.size()-1; i++)
	{
		myfile << tournament.finalVector[i]<<"\n";

	}
	myfile.close();

	return (0);
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
	sortedRuns.sort();
	otemp.close();

	ifstream itemp("temp.txt");
	ofstream outputFile(outputFileName);

	cout << "...Done\n";
	//checkRuns<T>(itemp, outputFile, direction_flag);

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
vector<vector<T>> checkRuns(istream& infile, ostream& outfile, bool direction_flag)
{

	cout << "in check run\n"<<std::flush;
	int runLength = 0;
	int minLength = 0;

	int maxRunLength = 0;
	int minRunLength = 0;
    int outRunNumber;

	int totalObj = 0;

	int totalRuns = 0;

	bool isSorted = true;

	int rn = 0;
	int size = 0;
	int runNum = 0;

	int prev_size = 0;

	int prevRN = 0;

	T prevObj;
	T curObj;

	string curLine;

	vector<vector<T>> listOfLists = {};

	ofstream outClean("out.txt");
	ofstream myfile;
        myfile.open("rrnFile.text");
	cout << "opened the file\n"<<std::flush;
	while(getline(infile, curLine))
	{
		cout << "got a line\n"<<std::flush;
		vector<string> currentRun = {};
		runLength = 0;
		outfile << curLine << "\n";
		outClean << curLine << "\n";
		totalRuns++;
		istringstream stringStream(curLine);
		stringStream >> prevObj;
		currentRun.push_back(prevObj);
		runLength++;
		//totalObj++;

		runNum++;

		while(!stringStream.eof())
		{

			stringStream >> curObj;
			currentRun.push_back(curObj);
			runLength++;
			totalObj++;
			rn = totalObj;
			size = runLength - 1;


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
		cout << "added one list\n"<<std::flush;
		listOfLists.push_back(currentRun);
		if(runLength > maxRunLength)
		{
			maxRunLength = runLength;
		}
		if(size < maxRunLength){
            minRunLength = size;
		}

		if(prevRN != rn){
                myfile << "rn:  " << rn << "  size:  " << size << "  runNum:  " << runNum << "\n";
                outRunNumber = runNum;
		}

		prevRN = rn;


	}



	outfile
			<<"averageRunLength = " << totalObj / (  outRunNumber)
			<<"\nthe file is sorted: "<< (isSorted? "True" : "False")
			<<"\nMax run length: " << maxRunLength - 1
			<<"\nMin run length: " << minRunLength
			<<"\ntotal Runs: " << outRunNumber
			<<"\ntotal items: " << totalObj;

	cout << "returning the list\n"<<std::flush;
	return listOfLists;

}

/*void stringTest(string inputFileName, string outputFileName, bool ascending)
{

	ofstream testFile(inputFileName);
	cout << "Creating test file of Strings\n";
	randomStrings(testFile);
	testFile.close();

	ifstream inputFile(inputFileName);
	ofstream otemp("temp.txt");
	cout<<"replacement selection\n";
	ReplacementSelectionSort<string> sortedRuns(15, inputFile, otemp, ascending);
	sortedRuns.sort();
	otemp.close();

	cout << "checking runs\n";
	ifstream itemp("temp.txt");
	ofstream outputFile(outputFileName);
	checkRuns<string> (itemp, outputFile, ascending);
}
*/

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
