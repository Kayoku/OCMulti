#ifndef TSP_SCALAR_DEFINE
#define TSP_SCALAR_DEFINE

#include "TSP.h"

class TSP_Scalar : public TSP
{
 private:
  int max_weight_step;
  int time_stop;
  bool is_random;

 public:
  TSP_Scalar(std::vector<Instance> &instances,
             std::string name,
             int stop,
             bool is_random,
             int step = -1):
   TSP(instances, name),
   max_weight_step(-1),
   time_stop(-1),
   is_random(is_random)
  {
   if (is_random)
    time_stop = stop;
   else
    max_weight_step = stop;
    
   set_following(step);
  }

 Sol loop_k_opt(Sol sol, std::vector<float> weights);

 Archive solution() override;
 void solution_time() override;
 void solution_value() override;
 std::string get_name() override;
};

#endif
