#include "C:\cygwin64\home\ghislain\newCode\CSCI331Project2\TournamentSort.h"
#include <queue>
#include <functional>
#include <string>

#include <vector>
using namespace std;
int main()
{
	///*
	
	vector<string> first = {"a","b","c"};
	vector<string> second = {"d","e","f"};
	vector<string> third = {"g","h","i"};
	vector<string> fourth = {"a","b","c"};
	vector<string> fifth = {"g","h","i"};
	vector<string> sixth = {"d","e","f"};
	vector<string> seventh = {"a","b","c"};

	vector<vector<string>> listOfLists = {second, third, first, fourth, seventh, sixth, fifth};
	vector<string> final= {};
 	TournamentSort<string> tournament;
	
	
	std::priority_queue<TournamentSort<string>::Node, 		
	std::vector<TournamentSort<string>::Node>,TournamentSort<string>::compare> 		PQ;
	//*/
	//PQ = tournament.initPQ(PQ, listOfLists);
	/*
	vector<int> first = {1,2,3,4,5,6,7,8,9};
	vector<int> second = {21,22,23,24,25,26,27,28,29};
	vector<int> third = {31,32,33,34,35,36,37,38,39};
	vector<int> fourth = {41,42,43,44,45,46,47,48,49};
	vector<int> fifth = {51,52,53,54,55,56,57,58,59};
	vector<int> sixth = {61,62,63,64,65,66,67,68,69};
	vector<int> seventh = {71,72,73,74,75,76,78,79};

	vector<vector<int>> listOfLists = {second, third, first, fourth, seventh, sixth, fifth};
	vector<int> final= {};
 	TournamentSort<int> tournament;
	
	
	std::priority_queue<TournamentSort<int>::Node, 		
	std::vector<TournamentSort<int>::Node>,TournamentSort<int>::compare> 		PQ;
	//PQ = tournament.initPQ(PQ, listOfLists);
	*/
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
	return(0);

}
