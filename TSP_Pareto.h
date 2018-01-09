#ifndef TSP_PARETO_DEFINE
#define TSP_PARETO_DEFINE

#include "TSP.h"

class TSP_Pareto : public TSP
{
 private:
  int start_population;
  int generation;
  int nb_mutation;
  int mutation_intensity;
  int current_generation;

 public:
  TSP_Pareto(std::vector<Instance> &instances,
             std::string name,
             int start_population, 
             int generation,
             int nb_mutation,
             int mutation_intensity):
   TSP(instances, name),
   start_population(start_population),
   generation(generation),
   nb_mutation(nb_mutation),
   mutation_intensity(mutation_intensity),
   current_generation(0)
  {}

  TSP_Pareto(std::vector<Instance> &instances,
             std::string name,
             Archive ar,
             int start_population,
             int generation,
             int nb_mutation,
             int mutation_intensity):
   TSP(instances, name),
   start_population(start_population),
   generation(generation),
   nb_mutation(nb_mutation),
   mutation_intensity(mutation_intensity),
   current_generation(0)
  { archive = ar; }

  Archive solution() override;
  std::string get_name() override;

  Archive mutation();
  Archive reproduction();
  Sol order_crossover(Sol parent1, Sol parent2);
};

#endif
