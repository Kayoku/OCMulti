#include "TSP_random.h"
#include <algorithm>
#include <random>

////////////////////////////////////////////////////////////////////////////
std::vector<int> TSP_Random::solution()
////////////////////////////////////////////////////////////////////////////
{
 std::vector<int> sol;

 for (int i = 0 ; i < 100 ; i++)
  sol.push_back(i);

 std::random_shuffle(sol.begin(), sol.end());

 return sol;
}
