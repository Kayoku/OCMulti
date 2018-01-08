#include "TSP_SimplePareto.h"
#include <algorithm>
#include <iostream>

////////////////////////////////////////////////////////////////////////////
void TSP_SimplePareto::full_two_opt
////////////////////////////////////////////////////////////////////////////
(
 Sol sol
)
{
 Sol new_sol;

 for (size_t i = 0 ; i < sol.size() ; i++)
 {
  for (size_t j = i+1 ; j < sol.size() ; j++)
  {
   new_sol = two_opt(sol, i, j); 
   filter_online(archive, new_sol); 
  }
 } 
}

////////////////////////////////////////////////////////////////////////////
Archive TSP_SimplePareto::solution()
////////////////////////////////////////////////////////////////////////////
{
 //for (int i = 0 ; i < start_population; i++)
 // filter_online(archive, random_solution());
 archive.push_back(random_solution());

 while (current_generation < generation)
 {
  std::cout << "gen: " << current_generation << "(" << archive.size()
                                             << ")" << std::endl;
  int choose_sol = g()%archive.size();
  full_two_opt(archive[choose_sol]);

  current_generation++;
 }

 return archive;
}
