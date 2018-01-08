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
             int start_population, 
             int generation,
             int nb_mutation,
             int mutation_intensity):
   TSP(instances),
   start_population(start_population),
   generation(generation),
   nb_mutation(nb_mutation),
   mutation_intensity(mutation_intensity),
   current_generation(0)
  {}

  TSP_Pareto(std::vector<Instance> &instances,
             Archive archive,
             int start_population,
             int generation,
             int nb_mutation,
             int mutation_intensity):
   TSP(instances),
   start_population(start_population),
   generation(generation),
   nb_mutation(nb_mutation),
   mutation_intensity(mutation_intensity),
   current_generation(0)
  { archive = archive; }

  Archive solution() override;

  Archive mutation();
  Archive reproduction();
  Sol order_crossover(Sol parent1, Sol parent2);
};

#endif
