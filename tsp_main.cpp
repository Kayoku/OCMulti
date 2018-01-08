#include <iostream>
#include <fstream>
#include <algorithm>
#include "Instance.h"
#include "TSP.h"
#include "TSP_Random.h"
#include "TSP_Scalar.h"
#include "TSP_Pareto.h"

void write_archive(std::ostream &out, Archive &archive, TSP &tsp)
{
 // Tri l'archive
 std::sort(archive.begin(), archive.end(),
           [&](const Sol &s1, const Sol &s2)
           { return tsp.evaluations(s1)[0] < tsp.evaluations(s2)[0]; });

 for (size_t i = 0 ; i < archive.size() ; i++)
 {
  auto evals = tsp.evaluations(archive[i]);
  for (size_t j = 0 ; j < evals.size() ; j++)
   out << evals[j] << " ";
  out << std::endl;
 }
}

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

 TSP_Random tsp_random(to_optimize, 100);
 TSP_Scalar tsp_scalar(to_optimize, 0.01);
 TSP_Pareto tsp_pareto(to_optimize, 100, 100, 10, 1);

 std::cout << "Start of random..." << std::endl;
 auto archive_r = tsp_random.solution();
 std::cout << "Start of scalar..." << std::endl;
 auto archive_s = tsp_scalar.solution();
 std::cout << "Start of pareto..." << std::endl;
 auto archive_p = tsp_pareto.solution();

 TSP_Pareto tsp_hybrid(to_optimize, archive_s, 100, 100, 10, 1);
 std::cout << "Start of hybrid..." << std::endl;
 auto archive_h = tsp_hybrid.solution();
 std::cout << "End" << std::endl;
 
 std::ofstream file_random("random.dat");
 write_archive(file_random, archive_r, tsp_random);
 file_random.close();

 std::ofstream file_scalar("scalar.dat");
 write_archive(file_scalar, archive_s, tsp_scalar);
 file_scalar.close();

 std::ofstream file_pareto("pareto.dat");
 write_archive(file_pareto, archive_p, tsp_pareto);
 file_pareto.close();

 std::ofstream file_hybrid("hybrid.dat");
 write_archive(file_hybrid, archive_h, tsp_hybrid);
 file_hybrid.close();

 /*
 // Création du TSP filter
 TSP_Scalar tsp(to_optimize, 0.01);
 auto archive = tsp.solution();

 // Affichage archive
 for (size_t i = 0 ; i < archive.size() ; i++)
 {
  auto evals = tsp.evaluations(archive[i]);
  for (size_t j = 0 ; j < evals.size() ; j++)
   std::cout << evals[j] << " ";
  std::cout << std::endl;
 }

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
