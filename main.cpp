#include "ReplacementSelectionSort.h"
#include <fstream>
#include <iostream>
#include <string>
#include <typeinfo>
#include <random>
#include <cmath>
#include <sstream>
#include <conio.h>
#include <stdio.h>

using namespace std;

template <typename T>
void test(string inputFileName, string outputFileName, bool direction_flag);


template<typename T>
void generateTestFile(ostream& outfile);

template <typename T>
void checkRuns(istream& infile,ostream& outfile, bool direction_flag);


int main(){

    srand(2);


	test<int> ("randomIntTest_in.txt","ascending_randomIntTest_out", true);


	return 0;
}

template <typename T>
void test(string inputFileName, string outputFileName, bool direction_flag){

	ofstream randomTestFile(inputFileName);

	cout << "Creating test file\n";
	generateTestFile<T>(randomTestFile);
	randomTestFile.close();

	ifstream inputFile(inputFileName);
	ofstream otemp("temp.txt");
	cout << "rs\n";

	ReplacementSelectionSort<T> sortedRuns(15, inputFile ,otemp, direction_flag);
	otemp.close();

	ifstream itemp("temp.txt");
	ofstream outputFile(outputFileName);

	cout << "out\n";
	checkRuns<T>(itemp, outputFile, direction_flag);
}

template<typename T>
void generateTestFile(ostream& outfile){

	int strlength;
	int fileLen;
	fileLen = rand() % (rand() % 1000);

	for(int i = 0; i < fileLen; i++){

		strlength = 1 + rand()% 3;

		T num = rand() % (int)(pow(10,strlength));

		outfile << num <<" ";
		if(i % 5 == 0){
			outfile << "\n";
			}

		}
}


template <typename T>
void checkRuns(istream& infile,ostream& outfile, bool direction_flag){


	int runLength = 0;

	int maxRunLength = 0;


	int totalObj = 0;

	int totalRuns = 0;

	bool isSorted = true;

	T prevObj;
	T curObj;

	string curLine;

	while(getline(infile, curLine)){

		runLength = 0;
		outfile << curLine<<"\n";
		totalRuns++;
		istringstream stringStream(curLine);
		stringStream >> prevObj;
		runLength++;
		totalObj++;

		while(!stringStream.eof()){

			stringStream>>curObj;
			runLength++;
			totalObj++;
			if(direction_flag){

				if(curObj < prevObj){

					isSorted = false;
				}
			}else{

				if(curObj > prevObj){
					isSorted = false;
				}

			}
		}
		if(runLength > maxRunLength){
			maxRunLength = runLength;
		}
	}

	outfile <<"\n\n-----------------------------------\n"
			<<"averageRunLength = " << totalObj / totalRuns
			<<"\nthe file is sorted: "<< (isSorted? "True" : "False")
			<<"\nMax run length: " << maxRunLength
			<<"\ntotal Runs: " << totalRuns
			<<"\ntotal items: " << totalObj
			<<"\n---------------------------------------\n\n";
}
