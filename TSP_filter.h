#ifndef TSP_FILTER_DEFINE
#define TSP_FILTER_DEFINE

#include "TSP_random.h"

class TSP_filter : public TSP_Random
{
 public:
  TSP_filter(std::vector<Instance> &instances):
   TSP_Random(instances)
  {}

  void solutions_on(std::vector<std::vector<int>> &archive,
                    std::vector<int> new_sol);
  void solutions_off(std::vector<std::vector<int>> &archive);

  int dominating(std::vector<int> sol1, std::vector<int> sol2);
};

#endif
