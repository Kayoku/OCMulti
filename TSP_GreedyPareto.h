#ifndef TSP_SIMPLE_PARETO_DEFINE
#define TSP_SIMPLE_PARETO_DEFINE

#include "TSP.h"

class TSP_GreedyPareto : public TSP
{
 private:
  int start_population;
  int limit;
  int current_generation;
  bool is_time;

 public:
  TSP_GreedyPareto(std::vector<Instance> &instances,
             std::string name,
             bool is_time,
             int start_population, 
             int limit,
             int step = -1):
   TSP(instances, name),
   start_population(start_population),
   limit(limit),
   current_generation(0),
   is_time(is_time)
  {
   set_following(step);
  }

  TSP_GreedyPareto(std::vector<Instance> &instances,
             std::string name,
             Archive ar,
             bool is_time,
             int start_population,
             int limit,
             int step = -1):
   TSP(instances, name),
   start_population(start_population),
   limit(limit),
   current_generation(0),
   is_time(is_time)
  { 
   set_following(step);
   archive = ar;
  }

  void solution_time() override;
  void solution_value() override;
  Archive solution() override;
  std::string get_name() override;
  void full_two_opt(Sol sol);
};

#endif
