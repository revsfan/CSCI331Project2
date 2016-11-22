/**
*	@file TournamentSort.h 
*	@brief A class that applies a TournamentSort with the use of a priority 
*	Queue to the Vector of vector that is created  and prints it to a output file
*
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


template <class T>
class TournamentSort
{
	public:
	/**
	*	@param completed Run's represents the runs that are completed
	*	@param final vetor is a vector item that will be pushed to the priority queue
	*/
	int completedRuns;
	vector<T> finalVector;
	/** 
	*	@brief Is a class that set's that creates a helper node.
	*	@param position is a int, is one variable that is used to hold the information from the vectors of vectors
	*	@param rn is an int, which is another variable that is used to hold the infromation from the vectors of vectors.
	*	@param values is typename T, which is the final variable that is used to hold the last bit of information from the vectors of vectors. 
	*/
	class Node
	{
		public:

		int position;
		int rn;
		T value ;
		/** 
		*	@brief is a Constructor that creates the node that will be used
		*	@param position is a int, is one variable that is used to hold the information from the vectors of vectors
		*	@param rn is an int, which is another variable that is used to hold the infromation from the vectors of vectors.
		*	@param values is typename T, which is the final variable that is used to hold the last bit of information from the vectors of vectors. 
		*/
		Node(int x, int y, T z){position = x; rn = y; value = z;}
		/**
		* 	Default Deconstructor
		*/
		virtual ~Node(){}


	};

	
	/** 
	*	@brief compare is a struct that is used to Compare the Node to the vector to the vector of vector
    *	@return the const lhs.value < rhs.value.
	*/
	struct compare
	{
		bool operator()(const Node& lhs, const Node& rhs)
		{
  			return lhs.value < rhs.value;
		}

	};
	
	/**
	*	Constructor
	*	@brief intializes Tournament Sort Class
	*/
	TournamentSort(){}
	
	/**
	*	Default Deconstructor
	*/
	virtual ~TournamentSort(){}

	/**
	*	@brief this function initializes the priority queue 
	*	@param completed Runs which is a int is set to zero
	*	@return PQ. 
	*/
	std::priority_queue<Node, std::vector<Node>,compare> initPQ(std::priority_queue
					 				<Node,std::vector<Node>,
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
	*	@brief this function pushes the smallest item in the priority queue and repopulates it
	*	
	*/
	pushToFinal(std::priority_queue
					 <Node,
					  std::vector<Node>,
					  compare
					 > PQ, vector<T> final,
					  std::vector<vector<T> > sortedLists)
	{
		std::sort( final.begin(), final.end());
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