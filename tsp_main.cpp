#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <memory>

#include "Instance.h"
#include "TSP.h"
#include "TSP_Random.h"
#include "TSP_Scalar.h"
#include "TSP_GenPareto.h"
#include "TSP_GreedyPareto.h"

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
void usage()
////////////////////////////////////////////////////////////////////////////
{
 std::cerr << "usage: ./tsp <AB/CD/EF> <scalar/gen/greedy/hybrid> <time/value> limit step-follow" << std::endl;
 std::cerr << "       ./tsp AB scalar time 100\n" 
           << "       ./tsp AB pareto value 1000 10\n";
 exit(-1);
}

////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
////////////////////////////////////////////////////////////////////////////
{
 if (argc != 5 && argc != 6)
  usage();

 std::string instance_name(argv[1]); 
 std::string algo_str(argv[2]);
 std::string run_type(argv[3]);
 int limit = std::stoi(argv[4]);
 int step_follow = -1;
 if (argc == 6)
  step_follow = std::stoi(argv[5]);

 // Récupération des instances

 std::vector<Instance> to_optimize;

 {
  for (auto letter : instance_name)
  {
   std::string name = "instances/random"+std::string(1, letter)+"100.tsp";
   to_optimize.push_back(Instance(name));
  }
 }

 // Choix de l'algo
 std::unique_ptr<TSP> algo;
 bool is_time = false;
 if (run_type == "time")
  is_time = true;

 {
  if (algo_str == "scalar")
   algo = std::unique_ptr<TSP>(new TSP_Scalar(to_optimize, "", is_time, limit, step_follow)); 
  else if (algo_str == "gen")
   algo = std::unique_ptr<TSP>(new TSP_GenPareto(to_optimize, "", is_time, 1000, limit, 200, 5, step_follow));
  else if (algo_str == "greedy")
   algo = std::unique_ptr<TSP>(new TSP_GreedyPareto(to_optimize, "", is_time, 1, limit, step_follow));
  else
   usage();
 }

 // Lancement de l'algorithme
 auto archive = algo->solution();
 std::ofstream file(algo_str+".dat");
 write_archive(file, archive, *algo);
 file.close();

 /*TSP_GreedyPareto tsp_simplepareto(to_optimize, 100, 2000);
 auto archive = tsp_simplepareto.solution();
 std::ofstream file_random("simplepareto.dat");
 write_archive(file_random, archive, tsp_simplepareto);
 file_random.close();*/

/* TSP_Random tsp_random(to_optimize, 100);
 TSP_Scalar tsp_scalar(to_optimize, 0.1);
 TSP_Pareto tsp_pareto(to_optimize, 100, 100, 10, 1);

 std::cout << "Start of random..." << std::endl;
 auto archive_r = tsp_random.solution();
 std::cout << "Start of scalar..." << std::endl;
 auto archive_s = tsp_scalar.solution();
 std::cout << "Start of pareto..." << std::endl;
 auto archive_p = tsp_pareto.solution();

 TSP_Pareto tsp_hybrid(to_optimize, archive_s, 100, 1000, 50, 1);
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
*/
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
