TODO:


* Open the output file from the replacement selection sort and apply merge sort. This function should be a function inside main. No need for a new class.

* Numbers for Total Runs and Total Items in the output file are wrong and need to be corrected.



mergeInt: templated
ie: remember to template the declaration of the function too.

template<typename T>
vector<T> mergeInt(const vector< vector<T> > &multiList)
{

  vector<T> finalList;
  vector<vector<int>::const_iterator> iterators(multiList.size());

  // Set all iterators to the beginning of their corresponding vectors in multiList
  for (int i = 0; i < multiList.size(); ++i) iterators[i] = multiList[i].begin();



  int k = 0, minValueIndex;
  T minValue;

  while (1)
  {
    if ( typeid(iterators[0]) == typeid(std::string) )
    minValue = CHAR_MAX;
    else
    minValue = INT_MAX;

    for (int i = 0; i < iterators.size(); ++i)
	{
      if (iterators[i] == multiList[i].end()) continue;

      if (*iterators[i] < minValue)
	  {
        minValue = *iterators[i];
        minValueIndex = i;
      }
    }

    iterators[minValueIndex]++;

    if ( typeid(iterators[0]) == typeid(std::string) )
        {if (minValue == CHAR_MAX) break;}
    else
        {if (minValue == INT_MAX) break;}
    finalList.push_back(minValue);
  }

  return finalList;
}


