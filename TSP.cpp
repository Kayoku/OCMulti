#include "TSP.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////
std::vector<int> TSP::evaluations
////////////////////////////////////////////////////////////////////////////
(
 std::vector<int> solution
)
{
 std::vector<int> evals;
 for (size_t i = 0 ; i < instances.size() ; i++)
  evals.push_back(evaluation(i, solution));

 return evals;
}


////////////////////////////////////////////////////////////////////////////
int TSP::evaluation
////////////////////////////////////////////////////////////////////////////
(
 int i,
 std::vector<int> solution
)
{
 int value = 0; 

 for (size_t j = 0 ; j < solution.size() ; j++)
  value += instances[i].distances[j][solution[j]];

 if (value == 0)
 {
  std::cout << "VALUE 0: " << std::endl;
  for (size_t j = 0 ; j < solution.size() ; j++)
   std::cout << solution[j] << "-";
 }

 return value;
}
