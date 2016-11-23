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
#include <string.h>

using namespace std;


/**
*   Function to test only the selection sort process
*   @param inputFileName The placeholder for the file for input. This can contain any data because it will be overwritten
*   @param outputFileName The output file
*   @param direction_flag True = sort ascending
*/

template <typename T>
void test(string input, string output, bool direction_flag, string typeUsed);

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
*   Generate random floats
*   @param outfile file to write random floats to
*/
void generateTestFileFloat(ostream& outfile);

int main(int argc, char* argv[])
{
    srand(11);


    if(argc > 1){


        switch(argv[1][1]){

            case 's':if(argc > 2) { //string && ascending



                            string inputFileName = "randomStringTest_in.txt";
                            string outputFileName = "ascending_randomStringTest_out";
                            cout << "starting\n"<<std::flush;
                            ofstream testFile(inputFileName);
                            cout << "Creating test file of Strings\n"<<std::flush;
                            randomStrings(testFile);
                            testFile.close();

                            ifstream inputFile(inputFileName);
                            bool ascending = true;
                            ofstream otemp("temp.txt");
                            cout<<"replacement selection\n"<<std::flush;
                            ReplacementSelectionSort<string> sortedRuns(10, inputFile, otemp, ascending);
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
                            myfile.open ("output.txt", ios::app);
                            for(int i = 0; i < tournament.finalVector.size()-1; i++)
                            {
                                myfile << tournament.finalVector[i]<<"\n";

                            }

                            myfile << "\n------------------------------------------------\n";
                            myfile << "\nEnd of test\n";
                            myfile.close();



                      }else{// string && descending





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
                            ReplacementSelectionSort<string> sortedRuns(10, inputFile, otemp, ascending);
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
                            myfile.open ("output.txt", ios::app);
                            for(int i = 0; i < tournament.finalVector.size()-1; i++)
                            {
                                myfile << tournament.finalVector[i]<<"\n";

                            }

                            myfile << "\n------------------------------------------------\n";
                            myfile << "\nEnd of test\n";
                            myfile.close();



                        }//END ELSE
                        break;

        case 'i':if(argc > 2){ //INT && ASCENDING

                    test<int>("randomIntTest_in.txt", "ascending_randomIntTest_out", true, "integers"); //NOT WORKING
                }else{
                    test<int>("randomIntTest_in.txt", "descending_randomIntTest_out", false, "integers");
                }
                break;
        case 'f':if(argc > 2){ //FLOAT && ASCENDING

                     test<float>("randomFloatTest_in.txt", "ascending_randomFloatTest_out", true, "floats"); //NOT WORKING
                }else{
                     test<float>("randomFloatTest_in.txt", "descending_randomFloatTest_out", false, "floats");
                }
                break;
        case 'd':if(argc > 2){ //DOUBLE && ASCENDING

                    test<double>("randomDoubleTest_in.txt", "ascending_randomDoubleTest_out", true, "doubles");
                }else{
                    test<double>("randomDoubleTest_in.txt", "descending_randomDoubleTest_out", false, "doubles");
                }
                break;
        case 'a': // RUN ALL TESTS



                            for(int i = 0 ; i < 1; i++){ //Keep variables in an isolated scope

                            string inputFileName = "randomStringTest_in.txt";
                            string outputFileName = "ascending_randomStringTest_out";
                            cout << "starting\n"<<std::flush;
                            ofstream testFile(inputFileName);
                            cout << "Creating test file of Strings\n"<<std::flush;
                            randomStrings(testFile);
                            testFile.close();

                            ifstream inputFile(inputFileName);
                            bool ascending = true;
                            ofstream otemp("temp.txt");
                            cout<<"replacement selection\n"<<std::flush;
                            ReplacementSelectionSort<string> sortedRuns(10, inputFile, otemp, ascending);
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
                            myfile.open ("output.txt", ios::app);
                            for(int i = 0; i < tournament.finalVector.size()-1; i++)
                            {
                                myfile << tournament.finalVector[i]<<"\n";

                            }
                            myfile << "\n------------------------------------------------\n";
                            myfile << "\nEnd of test\n";
                            myfile.close();

                            }


                            /////////////////////////////////////////





                            for(int i = 0 ; i < 1; i++){ //Keep variables in an isolated scope

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
                            ReplacementSelectionSort<string> sortedRuns(10, inputFile, otemp, ascending);
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
                            myfile.open ("output.txt", ios::app);
                            for(int i = 0; i < tournament.finalVector.size()-1; i++)
                            {
                                myfile << tournament.finalVector[i]<<"\n";

                            }
                            myfile << "\n------------------------------------------------\n";
                            myfile << "\nEnd of test\n";
                            myfile.close();

                            }




                            /////////////////////////////////////////




//                            string inputFileName1 = "randomStringTest_in.txt";
//                            string outputFileName1 = "descending_randomStringTest_out";
//                            cout << "starting\n"<<std::flush;
//                            ofstream testFile1(inputFileName1);
//                            cout << "Creating test file of Strings\n"<<std::flush;
//                            randomStrings(testFile1);
//                            testFile1.close();
//
//                            ifstream inputFile1(inputFileName1);
//                            ascending = false;
//                            ofstream otemp1("temp.txt");
//                            cout<<"replacement selection\n"<<std::flush;
//                            ReplacementSelectionSort<string> sortedRuns1(10, inputFile1, otemp1, ascending);
//                            ofstream outputFile1(outputFileName1);
//                            sortedRuns1.sort(inputFile1, otemp1);
//                            otemp1.close();
//
//                            cout << "checking runs\n"<<std::flush;
//                            ifstream itemp1("temp.txt");
//                             /ofstream outputFile(outputFileName);
//                            vector<vector<string>> listOfLists1;
//
//                            listOfLists1 = checkRuns<string> (itemp1, outputFile1, ascending);
//                            cout << "got the list\n"<<std::flush;
//                            vector<vector<string>> listOfLists = {second, third, first, fourth, seventh, sixth, fifth};
//                            vector<string> final1 = {};
//                            TournamentSort<string> tournament1;
//
//                            std::priority_queue<TournamentSort<string>::Node,
//                            std::vector<TournamentSort<string>::Node>,TournamentSort<string>::compare> 		PQ1;
//
//                            cout<<"about to initialize\n"<<std::flush;
//                            PQ1 = tournament1.initPQ(PQ1, listOfLists1);
//                            cout<<"about to sortmerge\n"<<std::flush;
//                            tournament1.pushToFinal(PQ1, final1, listOfLists1);
//                            cout<<"about to write\n"<<std::flush;
//                            ofstream myfile1;
//                            myfile1.open ("output.txt");
//                            for(int i = 0; i < tournament1.finalVector.size()-1; i++)
//                            {
//                                myfile1 << tournament1.finalVector[i]<<"\n";
//
//                            }
//                            myfile1 << "\n------------------------------------------------\n";
//                            myfile1 << "\nEnd of test\n";
//                            myfile1.close();



                        test<int>("randomIntTest_in.txt", "ascending_randomIntTest_out", true, "integers");
                        test<int>("randomIntTest_in.txt", "descending_randomIntTest_out", false, "integers");
                        test<float>("randomFloatTest_in.txt", "ascending_randomFloatTest_out", true, "floats");
                        test<float>("randomFloatTest_in.txt", "descending_randomFloatTest_out", false, "floats");
                        test<double>("randomDoubleTest_in.txt", "ascending_randomDoubleTest_out", true, "doubles");
                        test<double>("randomDoubleTest_in.txt", "descending_randomDoubleTest_out", false, "doubles");

                        break;




        }//END SWITCH


    } // END IF ARGC > 1

    //stringTest("randomStringTest_in.txt", "ascending_randomStringTest_out", true);
    //test<string>("ascending_randomStringTest_out", "output.txt", true, "strings");
    //test<int>("randomTest_in.txt", "descending_randomTest_out", false, "integers");
    //test<float>("randomTest_in.txt", "descending_randomTest_out", false, "integers");
    //test<double>("randomDoubleTest_in.txt", "descending_randomDoubleTest_out", false, "integers");





	return (0);
}



template <typename T>
void test(string input, string output, bool direction_flag, string typeUsed)
{
	string inputFileName = input;
	string outputFileName = output;
	cout << "starting\n"<<std::flush;
	ofstream testFile(inputFileName);

	cout << "Creating test file "<<typeUsed <<"\n"<<std::flush;
	if(typeUsed.compare("float") == 0){

        generateTestFileFloat(testFile);

	}else{

        generateTestFile<T>(testFile);
	}
	testFile.close();

	ifstream inputFile(input);
	bool ascending = direction_flag;
	ofstream otemp("temp.txt");
	cout<<"replacement selection\n"<<std::flush;
	ReplacementSelectionSort<string> sortedRuns(10, inputFile, otemp, ascending);
	ofstream outputFile(output);
	sortedRuns.sort(inputFile, otemp);
	otemp.close();

	cout << "checking runs\n"<<std::flush;
	ifstream itemp("temp.txt");
	// /ofstream outputFile(outputFileName);
	vector<vector<T>> listOfLists;

	listOfLists = checkRuns<T> (itemp, outputFile, ascending);
	cout << "got the list\n"<<std::flush;
	//vector<vector<string>> listOfLists = {second, third, first, fourth, seventh, sixth, fifth};
	vector<T> final= {};
 	TournamentSort<T> tournament;

	std::priority_queue<typename TournamentSort<T>::Node,
						std::vector<typename TournamentSort<T>::Node>,
						typename TournamentSort<T>::compare> 		PQ;


	cout<<"about to initialize\n"<<std::flush;
	PQ = tournament.initPQ(PQ, listOfLists);
	cout<<"about to sortmerge\n"<<std::flush;
	tournament.pushToFinal(PQ, final, listOfLists);
	cout<<"about to write\n"<<std::flush;
	ofstream myfile;
 	myfile.open ("output.txt", ios::app);
	for(int i = 0; i < tournament.finalVector.size()-1; i++)
	{
		myfile << tournament.finalVector[i]<<"\n";

	}

	myfile << "\n------------------------------------------------\n";
	myfile << "\nEnd of test\n";
	myfile.close();


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

void generateTestFileFloat(ostream& outfile){

	int strlength;
	int fileLen;
	fileLen = rand() % (rand() % 1000);

	for(int i = 0; i < fileLen; i++)
	{

		strlength = 2;

		float num = (rand() / (float)RAND_MAX * 99) + 1;


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
		vector<T> currentRun = {};
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
	sortedRuns.sort(inputFile,otemp);
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
