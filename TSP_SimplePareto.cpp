#include "TSP_SimplePareto.h"
#include <algorithm>
#include <iostream>

#include <chrono>

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
 archive.push_back(random_solution());

 while (current_generation < generation)
 {
  int choose_sol = g()%archive.size();

  full_two_opt(archive[choose_sol]);

  std::cout << current_generation << ": " << archive.size() << std::endl;
  current_generation++;

  if (follow_step > 0 && current_generation%follow_step == 0)
   write_archive(archive, "tsp-simplepareto-"+std::to_string(current_generation)+".dat");
 }

 return archive;
}
