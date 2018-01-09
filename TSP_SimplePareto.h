#ifndef TSP_SIMPLE_PARETO_DEFINE
#define TSP_SIMPLE_PARETO_DEFINE

#include "TSP.h"

class TSP_SimplePareto : public TSP
{
 private:
  int start_population;
  int generation;
  int current_generation;

 public:
  TSP_SimplePareto(std::vector<Instance> &instances,
             std::string name,
             int start_population, 
             int generation):
   TSP(instances, name),
   start_population(start_population),
   generation(generation),
   current_generation(0)
  {}

  TSP_SimplePareto(std::vector<Instance> &instances,
             std::string name,
             Archive ar,
             int start_population,
             int generation):
   TSP(instances, name),
   start_population(start_population),
   generation(generation),
   current_generation(0)
  { archive = ar; }

  Archive solution() override;
  std::string get_name() override;
  void full_two_opt(Sol sol);
};

#endif
