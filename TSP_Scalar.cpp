#include "TSP_Scalar.h"
#include <algorithm>
#include <iostream>

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
 int new_sol_cost, id1, id2;
 
 for (size_t i = 0 ; i < sol.size() ; i++)
 {
  for (size_t j = i+1 ; j < sol.size() ; j++)
  {
   id1 = i;
   id2 = j;
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
Archive TSP_Scalar::solution()
////////////////////////////////////////////////////////////////////////////
{
 // Génération des points liés à un poids
 int cpt = 0;
 for (float w = 0.0f ; w <= 2.0f ; w+=step*2)
 {
  std::vector<float> weights = {w, 2.0f - w};
  Sol new_sol;
  Sol new_sol2 = random_solution(); 

  while (new_sol != new_sol2)
  {
   new_sol = new_sol2;
   new_sol2 = loop_k_opt(new_sol, weights);
  }

  archive.push_back(new_sol);
  std::cout << "cpt: " << cpt << std::endl;
  cpt++;
 }

 Archive final_archive;
 for (auto s : archive)
  filter_online(final_archive, s);

 return final_archive;
}
