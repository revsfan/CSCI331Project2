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
#include <queue>
#include <time.h>
#include <algorithm>

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

template <typename T>
void makeVector(std::vector < std::vector<T> > listVector);

int stringToNumber(string inString);


// Functionality:
// To randomly populate a given number of sorted integers.
// This can be used as input data set.
// Input:
//   vector<int>& v  - Vector on which sorted integers will be populated
//   size         - Number of integers to populate
// Output:
//   void

void populateSortedVector(vector<int>& v, int size)
{
   if (size <= 0) {
      return;
   }

   v.clear();
   for(int i = 0; i < size; i++) {
      v.push_back(rand());
   }

   sort(v.begin(), v.end());
}


//   Functionality:
//      Merge K sorted arrays using TOURNAMENT TREE
//
//   Input:
//      vector <vector<int>>& sortedArrays - K sorted arrays
//   Output:
//      vector <vector<int>>& sortedArrays - One array which is result of merging K sorted arrays
//

void mergeSortedArraysUsingTournamentTree(vector <vector<int>>& sortedArrays)
{
   if (sortedArrays.size() == 0) {
      return;
   }

   removeEmptyVectors<int>(sortedArrays);

   vector<int> mergedSortedArray;
   vector<elementIndex<int, int>> tournamentTree;
   int firstLeaf = 0, vIndex = 0, numOfPlayers = sortedArrays.size();

   buildTournamentTree(tournamentTree, firstLeaf, sortedArrays);
   playTournament(tournamentTree, firstLeaf);

   while (numOfPlayers) {
      int vIndex = tournamentTree[0].arrayIndex, curPos = -1, value;
      elementIndex<int, int> tournamentWinner = tournamentTree[0];

      //   1) Get winner and add that to output array
      mergedSortedArray.push_back(tournamentWinner.value);
      //   2) Fetch next data
      curPos = tournamentWinner.position;
      if (fetchNextData(sortedArrays[vIndex], curPos, value)) {
         elementIndex<int, int> newPlayer(value, vIndex, curPos, tournamentWinner.metaData);
         // Add this new player at the position of the last Game's winner
         addPlayerAt(tournamentTree, newPlayer);
      }
      else { // If no more elements in the current vector then make this player an automatic loser
         --numOfPlayers;
         tournamentTree[tournamentWinner.metaData].arrayIndex = -1;
         elementIndex<int, int> newPlayer(value, -1, -1, tournamentWinner.metaData);
         addPlayerAt(tournamentTree, newPlayer);
      }
   }

   sortedArrays.clear();
   sortedArrays.push_back(mergedSortedArray);
}



void testTournamentTreeMethod()
{
   vector<int> v;
   int i = 0, count = 5;
   vector <vector<int>> vectorOfSortedArrays;

   srand((unsigned)time(NULL));
   for (; i < 25; i++, count+=15) {
      populateSortedVector(v, count);
      vectorOfSortedArrays.push_back(v);
   }

   mergeSortedArraysUsingTournamentTree(vectorOfSortedArrays);
   if (is_sorted(vectorOfSortedArrays[0])) {
      cout<<"K Sorted Arrays are successfully merged using TOURNAMENT TREE mehtod, complexity is NLOGK"<<endl;
   }
}







/ Functionality:
//   Creates a tournament tree. Internal representation is using array/vector.
//   Represents the complete binary tree using array.
//
//   Input:
//      vector<elementIndex<int, int>>& tournamentTree - Tournament tree to be populated
//      int& firstLeaf   - Index of the first player in the last level
//      const vector<vector<int>>& sortedArrays - vector of sorted arrays
//

void buildTournamentTree(vector<elementIndex<int, int>>& tournamentTree, int& firstLeaf, const vector<vector<int>>& sortedArrays)
{
   if (sortedArrays.size() == 0) {
      return;
   }

   int size = 1, tournamentTreeSize = 0, vIndex = 0;

   while (size < sortedArrays.size()) {
      size*=2;
   }

   firstLeaf = size - 1;
   tournamentTreeSize = (2 * size) - 1;
   tournamentTree.resize(tournamentTreeSize);

   for (int i = firstLeaf; vIndex < sortedArrays.size(); i++) {
      tournamentTree[i].value = sortedArrays[vIndex].at(0);
      tournamentTree[i].arrayIndex = vIndex;
      tournamentTree[i].position = 1;
      tournamentTree[i].metaData = i;
      ++vIndex;
   }
}




//   Functionality:
//      Assumption:
//         The given tournament tree is expected to be the complete binary tree
//   Given a Tournament tree and the index of the first player, conducts a tournament
//   A match is played against a pair of players and the winner is promoted to the next level.
//   Input:
//      vector<elementIndex<int, int>>& tournamentTree - Tournament tree containing players information
//      int firstLeaf                           - Index of the first player in the leaf level of the complete Binary tree
//
//   Output:
//      void

void playTournament(vector<elementIndex<int, int>>& tournamentTree, int firstLeaf)
{
   int thisLevelLeftMostPlayer = firstLeaf;

   while (thisLevelLeftMostPlayer > 0) {
      int left = thisLevelLeftMostPlayer, thisLevelRigthMostPlayer = 0, winner = -1, parent = 0;
      thisLevelRigthMostPlayer = 2 * left;

      while (left < thisLevelRigthMostPlayer) {
         winner = playMatch(tournamentTree[left], tournamentTree[left+1]);
         if (winner <= 0) {
            break;
         }
         parent = left/2;
         tournamentTree[parent] = tournamentTree[winner];
         left+=2;
      }
      thisLevelLeftMostPlayer = (thisLevelLeftMostPlayer - 1)/2;
   }

}





//   Functionality:
//      Assumption:
//         The given tournament tree is expected to be the complete binary tree
//
//      Given a tournament tree, insert a new player at certain position (indicated by newPlayer.metaData)
//      and play the tournament with the rest of the players
//      This will promote the winner to the next level along the path till it reaches the root
//      At the most log n matches (considering there are n players)
//
//      Input:
//         vector<elementIndex<int, int>>& tournamentTree - Tournament tree with players information
//         const elementIndex<int, int>& newPlayer        - New player information

void addPlayerAt(vector<elementIndex<int, int>>& tournamentTree, const elementIndex<int, int>& newPlayer)
{
   if(tournamentTree.size() == 0) {
      return;
   }

   int playerPosition = newPlayer.metaData;

   tournamentTree[newPlayer.metaData] = newPlayer;
   while (playerPosition > 0) {
      int player1, player2, winner, parent;
      player1 = (playerPosition % 2 ? playerPosition : playerPosition - 1);
      player2 = player1 + 1;
      parent = player1/2;
      winner = playMatch(tournamentTree[player1], tournamentTree[player2]);
      tournamentTree[parent] = ((winner != -1) ? tournamentTree[winner] : tournamentTree[player1]);
      playerPosition = parent;
   }

}



/ Functionality:
//   Given two player's meta data, finds the winner
//
//   Input:
//      elementIndex& player1 - Player 1's data
//      elementIndex& player2 - Player 2's data
//   Output:
//      Player (array) index in the tournament tree who is the Winner
//   Caution:
//      If both the players are Automatic losers, then the player index will be returned as negative value
//      Callers should check the return value before directly accessing the tournament tree using this player index

int playMatch(const elementIndex<int, int>& player1, const elementIndex<int, int>& player2)
{
   if ((player1.arrayIndex >= 0) && (player2.arrayIndex >= 0)) {
      return player1.value < player2.value ? player1.metaData : player2.metaData;
   }
   else if (player1.arrayIndex < 0) {
      return player2.metaData;
   }

   return player1.metaData;
}




void testTournamentTreeMethod()
{
   vector<int> v;
   int i = 0, count = 5;
   vector <vector<int>> vectorOfSortedArrays;

   srand((unsigned)time(NULL));
   for (; i < 25; i++, count+=15) {
      populateSortedVector(v, count);
      vectorOfSortedArrays.push_back(v);
   }

   mergeSortedArraysUsingTournamentTree(vectorOfSortedArrays);
   if (is_sorted(vectorOfSortedArrays[0])) {
      cout<<"K Sorted Arrays are successfully merged using TOURNAMENT TREE mehtod, complexity is NLOGK"<<endl;
   }
}




int main(){

    srand(33);

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




vector<Run> runVector = initRuns<int> ("out.txt");





	return 0;
}


vector<int> mergeDivideAndConquer(vector<vector<int> > multiList) {
  int l = 0, r = multiList.size()-1;

  while (multiList.size() > 1) {
    multiList[l] = mergeLists(multiList[l], multiList[r]);
    multiList.pop_back();

    l++;
    r = multiList.size()-1;

    if (r <= l) l = 0;
  }

  return multiList[0];
}





//int stringToNumber(string inString){
//
//    int Number;
//
//    if ( ! (istringstream(inString) >> Number) ) Number = 0;
//    return Number;
//
//}
//
//
//template <typename T>
//void makeVector(std::vector < std::vector<T> > listVector){
//
//    ifstream inFile("out.txt");
//    std::string element;
//    std::vector <T> temp;
//    int intElement;
//
//    std::vector < std::vector <T> > listVector;
//
//        while(getline(inFile, element)){
//
//
//        }
//
//
//}

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
void checkRuns(istream& infile, ostream& outfile, bool direction_flag){


	int runLength = 0;

	int maxRunLength = 0;


	int totalObj = 0;

	int totalRuns = 0;

	bool isSorted = true;

	T prevObj;
	T curObj;

	string curLine;

	ofstream outClean("out.txt");

	while(getline(infile, curLine)){

		runLength = 0;
		outfile << curLine << "\n";
		outClean << curLine << "\n";
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
    if((i<=mid) && (a[i] < a[j]))
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
