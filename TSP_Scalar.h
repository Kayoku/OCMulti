#ifndef TSP_SCALAR_DEFINE
#define TSP_SCALAR_DEFINE

#include "TSP.h"

class TSP_Scalar : public TSP
{
 private:
  float step;

 public:
  TSP_Scalar(std::vector<Instance> &instances,
             float step):
   TSP(instances),
   step(step)
  {}

 Sol loop_k_opt(Sol sol, std::vector<float> weights);
 void write_front(Archive &sol);

 Archive solution() override;
};

#endif
