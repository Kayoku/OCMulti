#ifndef TSP_FILTER_DEFINE
#define TSP_FILTER_DEFINE

#include "TSP_random.h"

class TSP_filter : public TSP_Random
{
 public:
  TSP_filter(std::vector<Instance> &instances):
   TSP_Random(instances)
  {}

  std::vector<std::vector<int>> solutions_off(int nb_base);
  int dominating(std::vector<int> sol1, std::vector<int> sol2);
};

#endif
