/**
*	@file TournamentSort.h
*	@brief A class to apply tournament sort on a series of sorted lists
*/

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

/**
*   Main TournamentSort class
*/
template <class T>
class TournamentSort
{
	public:
	int completedRuns; /**< Number of completed runs */
	vector<T> finalVector; /**< The final vector containing a single sorted list */

	//helper node class

	/**
	*   This Node is to help preserve meta data of the value
	*/
	class Node
	{
		public:

		int position; /**< What position the value is in its respective list */
		int rn; /**< Relative record number */
		T value ; /**< The raw data that is being sorted */

		Node(int x, int y, T z){position = x; rn = y; value = z;}
		virtual ~Node(){}


	};

    /**
    *   Sorts the values
    */
	struct compare
	{
		bool operator()(const Node& lhs, const Node& rhs)
		{


                return lhs.value < rhs.value;

		}

	};

	TournamentSort(){} /**< Default constructor */
	virtual ~TournamentSort(){} /**< Default destructor */


	/**
	*   Initializes the priority queue
	*   @param
	*/
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

    /**
    *   Pushes the smallest (unless sorting is changed) item in the priority queue and repopulates it
    */
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
