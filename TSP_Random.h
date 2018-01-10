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
 bool online;

 public:
  TSP_Random(std::vector<Instance> &instances,
             std::string name,
             int nb_random):
   TSP(instances, name),
   nb_random(nb_random)
  {}

  void solution_time() override;
  void solution_value() override;
  Archive solution() override;
  std::string get_name() override;
};

#endif
