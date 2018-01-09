#ifndef TSP_SCALAR_DEFINE
#define TSP_SCALAR_DEFINE

#include "TSP.h"

class TSP_Scalar : public TSP
{
 private:
  int limit;
  bool is_time;

 public:
  TSP_Scalar(std::vector<Instance> &instances,
             std::string name,
             bool is_time,
             int limit,
             int step = -1):
   TSP(instances, name),
   limit(limit),
   is_time(is_time)
  {
   set_following(step);
  }

 Sol loop_k_opt(Sol sol, std::vector<float> weights);

 Archive solution() override;
 void solution_time() override;
 void solution_value() override;
 std::string get_name() override;
};

#endif
