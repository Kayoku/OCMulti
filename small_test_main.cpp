#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>

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
 
 // Premier test 1000 solutions , on filtre
 {
  TSP_Random tsp_rand(to_optimize, "", 100);
  Archive new_solutions;
  for (int i = 0; i < 10000 ; i++)
   new_solutions.push_back(tsp_rand.random_solution());

  float diffs = 0.0f;
  float cost = 0.0f;
  for (int k = 0 ; k < 30 ; k++)
  {
   // Online
   TSP_Random tsp_online(to_optimize, "", 100);
   Archive ar;
   auto t1 = std::chrono::high_resolution_clock::now(); 
   for (auto sol: new_solutions)
    tsp_online.filter_online(ar, sol);
   auto t2 = std::chrono::high_resolution_clock::now();
   auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
   diffs += diff;
   cost += tsp_online.get_compute_cost();
  }

  std::cout << "online-1000: " << cost/10 << " " << diffs/10 << std::endl;

  diffs = 0.0f;
  cost = 0.0f;
  for (int k = 0 ; k < 30 ; k++)
  {
   // Offline
   TSP_Random tsp_offline(to_optimize, "", 100);
   auto ar = new_solutions;
   auto t1 = std::chrono::high_resolution_clock::now();
   tsp_offline.filter_offline(ar);
   auto t2 = std::chrono::high_resolution_clock::now();
   auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count(); 
   diffs += diff;
   cost += tsp_offline.get_compute_cost();
  }

  std::cout << "offline-1000: " << cost/10 << " " << diffs/10 << std::endl;
 }

 {
  TSP_Random tsp_rand(to_optimize, "", 100);
  std::vector<Archive> p_array;
  for (int i = 0; i < 10 ; i++)
  {
   Archive a;
   for (int i = 0 ; i < 1000 ; i++)
    a.push_back(tsp_rand.random_solution()); 
   p_array.push_back(a);
  }

  // Online
  float diffs = 0.0f;
  float cost = 0.0f;
  for (int k = 0 ; k < 30 ; k++)
  {
   TSP_Random tsp_online(to_optimize, "", 100);
   auto t1 = std::chrono::high_resolution_clock::now();
   Archive ar;
   for (auto a : p_array) 
    for (auto sol : a)
     tsp_online.filter_online(ar, sol);
   auto t2 = std::chrono::high_resolution_clock::now();
   auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
   diffs += diff;
   cost += tsp_online.get_compute_cost();
  }

  std::cout << "online-100: " << cost/10 << " " << diffs/10 << std::endl;

  // Offline
  diffs = 0.0f;
  cost = 0.0f;
  for (int k = 0 ; k < 30 ; k++)
  {
   TSP_Random tsp_offline(to_optimize, "", 100);
   auto t1 = std::chrono::high_resolution_clock::now();
   Archive ar;
   for (auto a : p_array)
   {
    for (auto sol : a)
     ar.push_back(sol); 
    tsp_offline.filter_offline(ar);
   }
   auto t2 = std::chrono::high_resolution_clock::now();
   auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
   diffs += diff;
   cost += tsp_offline.get_compute_cost();
  }

  std::cout << "offline-100: " << cost/10 << " " << diffs/10 << std::endl;
 }

/*
 for (auto init : {100, 500, 1000, 10000, 100000})
 {
  for (auto online : {true, false})
  {
   TSP_Random tsp_rand(to_optimize, "", init);
   auto archive = tsp_rand.solution();

   Archive archive_filter = archive;
   if (online)
   {
    for (auto sol : archive)
     tsp_rand.filter_online(archive_filter, sol);
   }
   else
    tsp_rand.filter_offline(archive_filter);
  }
 }
*/

 /* TSP_Random tsp_rnd(to_optimize, "", 500);
 auto archive = tsp_rnd.solution();
 std::ofstream file_random("random-no-filter.dat");
 write_archive(file_random, archive, tsp_rnd);
 file_random.close();

 // Offline
 auto copy_archive = archive;
 tsp_rnd.filter_offline(copy_archive);
 std::ofstream file_off("random-off.dat");
 write_archive(file_off, copy_archive, tsp_rnd);
 file_off.close();

 // Online
 Archive online_archive;
 for (auto sol : archive)
  tsp_rnd.filter_online(online_archive, sol);
 std::ofstream file_on("random-on.dat");
 write_archive(file_on, online_archive, tsp_rnd);
 file_on.close();
 */
}
