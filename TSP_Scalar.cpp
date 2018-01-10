#include "TSP_Scalar.h"
#include <algorithm>
#include <iostream>
#include <chrono>

////////////////////////////////////////////////////////////////////////////
Sol TSP_Scalar::loop_k_opt
////////////////////////////////////////////////////////////////////////////
(
 Sol sol,
 std::vector<float> weights
)
{
 Sol best_sol = sol;
 Sol new_sol;
 int best_sol_cost = evaluations_weight(best_sol, weights);
 int new_sol_cost;
 
 for (size_t i = 0 ; i < sol.size() ; i++)
 {
  for (size_t j = i+1 ; j < sol.size() ; j++)
  {
   new_sol = two_opt(sol, i, j);   

   new_sol_cost = evaluations_weight(new_sol, weights);
   if (new_sol_cost < best_sol_cost)
   {
    best_sol_cost = new_sol_cost;
    best_sol = new_sol;
   }
  }
 }

 return best_sol;
}

////////////////////////////////////////////////////////////////////////////
void TSP_Scalar::solution_time()
////////////////////////////////////////////////////////////////////////////
{
 int rd1, cpt = 0;
 std::vector<float> weights;
 Sol new_sol, new_sol2;
 auto time_init = std::chrono::high_resolution_clock::now();
 auto time_it = std::chrono::high_resolution_clock::now();
 auto diff = std::chrono::duration_cast<std::chrono::seconds>(time_it-time_init).count();

 while (diff < limit)
 {
  cpt++;
  // Génère un poids aléatoire
  rd1 = g()%1001;
  weights = {(float)rd1, (float)(1000 - rd1)};

  // Tant qu'on converge pas on continue 
  new_sol2 = random_solution();
  while (new_sol != new_sol2)
  {
   new_sol = new_sol2;
   new_sol2 = loop_k_opt(new_sol, weights);
  }

  filter_online(archive, new_sol);

  time_it = std::chrono::high_resolution_clock::now();
  diff = std::chrono::duration_cast<std::chrono::seconds>(time_it-time_init).count();
  std::cout << '\r' << diff << "s/" << limit << "s (" << archive.size() << ")" << std::flush;

  do_following(diff);
 }
 std::cout << std::endl;
}

////////////////////////////////////////////////////////////////////////////
void TSP_Scalar::solution_value()
////////////////////////////////////////////////////////////////////////////
{
 int cpt = 0;
 for (int w = 0; w <= limit ; w++)
 {
  cpt++;
  std::vector<float> weights = {(float)w,(float)(limit - w)};
  Sol new_sol; 
  Sol new_sol2 = random_solution(); 
  
  while (new_sol != new_sol2)
  {
   new_sol = new_sol2;
   new_sol2 = loop_k_opt(new_sol, weights);
  }
  
  filter_online(archive, new_sol);
  
  do_following(cpt);

  std::cout << '\r' << cpt << "/" << limit << " (" << archive.size() << ")" << std::flush;
 }
 std::cout << std::endl;
}

////////////////////////////////////////////////////////////////////////////
Archive TSP_Scalar::solution()
////////////////////////////////////////////////////////////////////////////
{
 if (is_time)
  solution_time();
 else
  solution_value();

 return archive;
}

////////////////////////////////////////////////////////////////////////////
std::string TSP_Scalar::get_name()
////////////////////////////////////////////////////////////////////////////
{
 return "scalar";
}

