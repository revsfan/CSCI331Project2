#include "C:\cygwin64\home\ghislain\newCode\CSCI331Project2\include\ReplacementSelectionSort.h"
#include "C:\cygwin64\home\ghislain\newCode\CSCI331Project2\src\ReplacementSelectionSort.cpp"
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
#include "C:\cygwin64\home\ghislain\newCode\CSCI331Project2\TournamentSort.h"
#include "C:\cygwin64\home\ghislain\newCode\CSCI331Project2\main.cpp"
#include <queue>
#include <functional>
#include <string>
using namespace std;
int main()
{
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