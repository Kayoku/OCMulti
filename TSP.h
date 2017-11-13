#ifndef TSP_DEFINE
#define TSP_DEFINE

#include "Instance.h"
#include <vector>

class TSP
{
 protected:
  std::vector<Instance> &instances;

 public:
  TSP(std::vector<Instance> &instances):
   instances(instances)
  {}

  std::vector<int> evaluations(std::vector<int> solution);
  int evaluation(int i, std::vector<int> solution);

  virtual std::vector<int> solution() = 0;
};

#endif
