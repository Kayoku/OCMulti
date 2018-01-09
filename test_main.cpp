#include <iostream>
#include <fstream>
#include <algorithm>
#include "Instance.h"
#include "TSP.h"
#include "TSP_Random.h"
#include "TSP_Scalar.h"
#include "TSP_GreedyPareto.h"
#include "TSP_GenPareto.h"

////////////////////////////////////////////////////////////////////////////
void write_archive(std::ostream &out, Archive &archive, TSP &tsp)
////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
////////////////////////////////////////////////////////////////////////////
{
 if (argc == 1)
 {
  std::cerr << "Bad args." << std::endl;
  return -1;
 }

 std::vector<Instance> to_optimize;

 // Récupération des instances
 for (int i = 0 ; i < argc-1 ; i++)
  to_optimize.push_back(Instance("instances/random"+std::string(argv[i+1])+"100.tsp"));

 int temps = 300;
 int nb_run = 2;

 ////////////////////////////////
 // Test du scalaire (10minutes)
 ////////////////////////////////

 for (int i = 0 ; i < nb_run ; i++)
 {
  TSP_Scalar tsp_scalar(to_optimize, "", true, temps);
  auto archive = tsp_scalar.solution();
  std::ofstream file_random("scalar-"+std::to_string(i+1)+".dat");
  write_archive(file_random, archive, tsp_scalar);
  file_random.close(); 
 }

 //////////////////////////////
 // Gen pareto (40min)
 //////////////////////////////

 for (int i = 0 ; i < nb_run ; i++) 
 {
  TSP_GenPareto tsp_gen(to_optimize, "", true, 1000, temps, 200, 5);
  auto archive = tsp_gen.solution();
  std::ofstream file_random("gen-"+std::to_string(i+1)+".dat");
  write_archive(file_random, archive, tsp_gen);
  file_random.close(); 
 }

 for (int i = 0 ; i < nb_run ; i++)
 {
  TSP_GenPareto tsp_gen(to_optimize, "", true, 10000, temps, 200, 5);
  auto archive = tsp_gen.solution();
  std::ofstream file_random("gen-"+std::to_string(i+1)+"p.dat");
  write_archive(file_random, archive, tsp_gen);
  file_random.close();
 }

 for (int i = 0 ; i < nb_run ; i++)
 {
  TSP_GenPareto tsp_gen(to_optimize, "", true, 1000, temps, 500, 5);
  auto archive = tsp_gen.solution();
  std::ofstream file_random("gen-"+std::to_string(i+1)+"m.dat");
  write_archive(file_random, archive, tsp_gen);
  file_random.close();
 }

 for (int i = 0 ; i < nb_run ; i++)
 {
  TSP_GenPareto tsp_gen(to_optimize, "", true, 1000, temps, 200, 10);
  auto archive = tsp_gen.solution();
  std::ofstream file_random("gen-"+std::to_string(i+1)+"i.dat");
  write_archive(file_random, archive, tsp_gen);
  file_random.close();
 } 

 /////////////////////////////
 // Greedy (20min)
 ///////////////////////////// 

 for (int i = 0 ; i < nb_run ; i++)
 {
  TSP_GreedyPareto tsp_greedy(to_optimize, "", true, 1, temps);
  auto archive = tsp_greedy.solution();
  std::ofstream file_random("greedy1-"+std::to_string(i+1)+".dat");
  write_archive(file_random, archive, tsp_greedy);
  file_random.close();
 }

 for (int i = 0 ; i < nb_run ; i++)
 { 
  TSP_GreedyPareto tsp_greedy(to_optimize, "", true, 10, temps);
  auto archive = tsp_greedy.solution();
  std::ofstream file_random("greedy10-"+std::to_string(i+1)+".dat");
  write_archive(file_random, archive, tsp_greedy);
  file_random.close();
 }

 ////////////////////////////
 // Hybrid (20min+scalar)
 ////////////////////////////

 TSP_Scalar tsp_scalar(to_optimize, "", false, 10);
 auto s_archive = tsp_scalar.solution();

 for (int i = 0 ; i < nb_run ; i++)
 {
  TSP_GenPareto tsp_gen(to_optimize, "", s_archive, true, 1000, temps, 200, 5);
  auto archive = tsp_gen.solution();
  std::ofstream file_random("gen-sc-"+std::to_string(i+1)+".dat");
  write_archive(file_random, archive, tsp_gen);
  file_random.close();
 }

 for (int i = 0 ; i < nb_run ; i++)
 { 
  TSP_GreedyPareto tsp_greedy(to_optimize, "", s_archive, true, 1000, temps);
  auto archive = tsp_greedy.solution();
  std::ofstream file_random("gen-sc-"+std::to_string(i+1)+".dat");
  write_archive(file_random, archive, tsp_greedy);
  file_random.close();
 }
}
