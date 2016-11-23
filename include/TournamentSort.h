#ifndef TOURNAMENT_SORT
#define TOURNAMENT_SORT
#include <vector>
#include <iostream>
#include <fstream>
#include <functional>
#include <typeinfo>
#include <string>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;


template <class T>
class TournamentSort
{
	public:
	int completedRuns;
	vector<T> finalVector;

	//helper node class
	class Node
	{
		public:

		int position;
		int rn;
		T value ;

		Node(int x, int y, T z){position = x; rn = y; value = z;}
		virtual ~Node(){}


	};

	struct compare
	{
		bool operator()(const Node& lhs, const Node& rhs)
		{


                return lhs.value < rhs.value;

		}

	};

	TournamentSort(){}
	virtual ~TournamentSort(){}

	//this function initializes the prioroty queue
	std::priority_queue<Node, std::vector<Node>,compare> initPQ(std::priority_queue
					 				<Node,
					  				std::vector<Node>,
					 				 compare
									 > PQ,
								   std::vector<vector<T> > sortedLists)
	{
		completedRuns = 0;


		for (int i = 0; i< sortedLists.size(); i++)
		{
			vector<T> run = sortedLists[i];
			T v = run[0];
			Node n(0, i, v);
			PQ.push(n);

		}


		return PQ;

	}

	//this function pushes the smallest item in the priority queue and repopulates it
	void pushToFinal(std::priority_queue
					 <Node,
					  std::vector<Node>,
					  compare
					 > PQ, vector<T> final,
					  std::vector<vector<T> > sortedLists)
	{
		//std::sort( final.begin(), final.end());
		Node smallest = PQ.top();

		PQ.pop();

		final.push_back(smallest.value);

		//replace the element popped from PQ if there is another item in that run
		std::vector<T> run = sortedLists[smallest.rn];
		if(smallest.position < run.size()-1)
		{
			Node newNode = {(smallest.position + 1), smallest.rn, run[smallest.position + 1]};

			PQ.push(newNode);

		}
		else
		{
		completedRuns++;
		}
		if(completedRuns < sortedLists.size())
		{

			pushToFinal(PQ, final, sortedLists);

		}

		else
		{

			finalVector = final;
		}



	}

};

#endif // TOURNAMENT_SORT
