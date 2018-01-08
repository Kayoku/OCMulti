#ifndef TSP_RANDOM_DEFINE
#define TSP_RANDOM_DEFINE

#include "TSP.h"

/*
 * Cette classe permet de renvoyer
 * un front pareto à partir d'instance
 * générer aléatoirement 
 */

class TSP_Random : public TSP
{
 private:
 int nb_random;

 public:
  TSP_Random(std::vector<Instance> &instances,
             int nb_random):
   TSP(instances),
   nb_random(nb_random)
  {}

  Archive solution() override;
};

#endif