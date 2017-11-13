#ifndef TSP_RANDOM_DEFINE
#define TSP_RANDOM_DEFINE

#include "TSP.h"

class TSP_Random : public TSP
{
 public:
  TSP_Random(std::vector<Instance> &instances):
   TSP(instances)
  {
   srand(time(0));
  }

  std::vector<int> solution() override;
};

#endif
