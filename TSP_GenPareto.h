#ifndef TSP_GEN_PARETO_DEFINE
#define TSP_GEN_PARETO_DEFINE

#include "TSP.h"

class TSP_GenPareto : public TSP
{
 private:
  int start_population;
  int limit;
  int nb_mutation;
  int mutation_intensity;
  int current_generation;
  bool is_time;

 public:
  TSP_GenPareto(std::vector<Instance> &instances,
             std::string name,
             bool is_time,
             int start_population, 
             int limit,
             int nb_mutation,
             int mutation_intensity,
             int step = -1):
   TSP(instances, name),
   start_population(start_population),
   limit(limit),
   nb_mutation(nb_mutation),
   mutation_intensity(mutation_intensity),
   current_generation(0),
   is_time(is_time)
  {
   set_following(step);
  }

  TSP_GenPareto(std::vector<Instance> &instances,
             std::string name,
             Archive ar,
             bool is_time,
             int start_population,
             int limit,
             int nb_mutation,
             int mutation_intensity,
             int step = -1):
   TSP(instances, name),
   start_population(start_population),
   limit(limit),
   nb_mutation(nb_mutation),
   mutation_intensity(mutation_intensity),
   current_generation(0),
   is_time(is_time)
  {
   archive = ar;
   set_following(step);
  }

  void solution_value() override;
  void solution_time() override;
  Archive solution() override;
  std::string get_name() override;

  Archive mutation();
  Archive reproduction();
  Sol order_crossover(Sol parent1, Sol parent2);
};

#endif
