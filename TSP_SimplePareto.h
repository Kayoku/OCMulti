#ifndef TSP_SIMPLE_PARETO_DEFINE
#define TSP_SIMPLE_PARETO_DEFINE

#include "TSP.h"

class TSP_SimplePareto : public TSP
{
 private:
  int start_population;
  int generation;
  int current_generation;
  bool stop_with_time;

 public:
  TSP_SimplePareto(std::vector<Instance> &instances,
             std::string name,
             bool stop_with_time,
             int start_population, 
             int generation,
             int step = -1):
   TSP(instances, name),
   start_population(start_population),
   generation(generation),
   current_generation(0),
   stop_with_time(stop_with_time)
  {
   set_following(step);
  }

  TSP_SimplePareto(std::vector<Instance> &instances,
             std::string name,
             Archive ar,
             bool stop_with_time,
             int start_population,
             int generation,
             int step = -1):
   TSP(instances, name),
   start_population(start_population),
   generation(generation),
   current_generation(0),
   stop_with_time(stop_with_time)
  { 
   set_following(step);
   archive = ar;
  }

  Archive solution() override;
  std::string get_name() override;
  void full_two_opt(Sol sol);
};

#endif
