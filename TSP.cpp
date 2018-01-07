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
int TSP::evaluations_weight
////////////////////////////////////////////////////////////////////////////
(
 Sol solution,
 std::vector<float> weights
)
{
 if (weights.size() != instances.size())
 {
  std::cerr << "Erreur taille des poids."  << std::endl;
  exit(-1);
 }

 int evals = 0;
 for (size_t i = 0 ; i < instances.size(); i++)
  evals += evaluation(i, solution, weights[i]);

 return evals;
}


////////////////////////////////////////////////////////////////////////////
int TSP::evaluation
////////////////////////////////////////////////////////////////////////////
(
 int i,
 std::vector<int> solution,
 float weight
)
{
 int value = 0; 

 for (size_t j = 0 ; j < solution.size() ; j++)
  value += weight * instances[i].distances[j][solution[j]];

 return value;
}
