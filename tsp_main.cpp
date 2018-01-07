#include <iostream>
#include "Instance.h"
#include "TSP_filter.h"
#include "TSP_scalar.h"

int main(int argc, char *argv[])
{
 if (argc == 1)
 {
  std::cerr << "Bad args." << std::endl;
  return -1;
 }

 std::vector<Instance> to_optimize;

 // Récupération des instances
 for (int i = 0 ; i < argc-1 ; i++)
  to_optimize.push_back(Instance("../../instances/random"+std::string(argv[i+1])+"100.tsp"));

 // Création du TSP filter
 TSP_Scalar tsp(to_optimize, 0.01, 1000, 40, 2);
 auto archive = tsp.solution();

 // Affichage archive
 for (size_t i = 0 ; i < archive.size() ; i++)
 {
  auto evals = tsp.evaluations(archive[i]);
  for (size_t j = 0 ; j < evals.size() ; j++)
   std::cout << evals[j] << " ";
  std::cout << std::endl;
 }

 /*
 // Création des 500 sols randoms
 std::vector<std::vector<int>> archive;
 for (int i = 0 ; i < 500 ; i++)
  archive.push_back(tsp.solution());

 std::vector<std::vector<int>> new_archive;
 for (size_t i = 0 ; i < archive.size() ; i++)
  tsp.solutions_on(new_archive, archive[i]);
 archive = new_archive;
  
// tsp.solutions_off(archive);

 for (size_t i = 0 ; i < archive.size() ; i++)
 {
  auto evals = tsp.evaluations(archive[i]);
  for (size_t j = 0 ; j < evals.size() ; j++)
   std::cout << evals[j] << " ";
  std::cout << std::endl;
 }*/

 return 0;
}
