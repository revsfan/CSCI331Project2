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

void stringTest(string inputFileName, string outputFileName, bool ascending);

void randomStrings(ostream& outfile);

void gen_random(char *s, const int len);

int main(){

    srand(2);

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


void stringTest(string inputFileName, string outputFileName, bool ascending){

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


void randomStrings(ostream& outfile){

	int strlength = 0;
	int fileLen;

	fileLen = rand() % (100 + rand() % 100);


	for(unsigned int i = 0; i < fileLen; i++){

		strlength = 6;
		char* str = (char*) malloc(strlength * (sizeof(char)));
		gen_random(str,strlength);

		outfile<<str<<" ";

		if( i % 5 ==0 ){
			outfile<<"\n";
		}

	}

}

void gen_random(char *s, const int len) {

    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}
