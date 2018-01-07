#ifndef TSP_DEFINE
#define TSP_DEFINE

#include "Instance.h"
#include <vector>
#include <random>

typedef std::vector<std::vector<int>> Archive;
typedef std::vector<int> Sol;

class TSP
{
 protected:
  std::vector<Instance> &instances;
  std::random_device rd;
  std::mt19937 g;

 public:
  TSP(std::vector<Instance> &instances):
   instances(instances),
   rd(),
   g(rd())
  {}

  std::vector<int> evaluations(Sol solution);
  int evaluations_weight(Sol solution, std::vector<float> weights);
  int evaluation(int i, Sol solution, float weight=1);

  virtual Archive solution() = 0;
};

#endif
