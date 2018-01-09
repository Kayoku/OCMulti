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
void TSP_SimplePareto::solution_value()
////////////////////////////////////////////////////////////////////////////
{
 while (current_generation < limit)
 {
  current_generation++;

  full_two_opt(archive[g()%archive.size()]); 

  do_following(current_generation); 
  std::cout << '\r' << current_generation << '/' << limit << " (" << archive.size() << ")" << std::flush;
 }
 std::cout << std::endl;
}

////////////////////////////////////////////////////////////////////////////
void TSP_SimplePareto::solution_time()
////////////////////////////////////////////////////////////////////////////
{
 auto time_init = std::chrono::high_resolution_clock::now();
 auto time_it = std::chrono::high_resolution_clock::now();
 auto diff = std::chrono::duration_cast<std::chrono::seconds>(time_it-time_init).count();

 while (diff < limit)
 { 
  current_generation++;

  full_two_opt(archive[g()%archive.size()]); 

  time_it = std::chrono::high_resolution_clock::now();
  diff = std::chrono::duration_cast<std::chrono::seconds>(time_it-time_init).count();
  do_following(diff); 
  std::cout << '\r' << diff << '/' << limit << " (" << archive.size() << ")" << std::flush;
 } 
 std::cout << std::endl;
}

////////////////////////////////////////////////////////////////////////////
Archive TSP_SimplePareto::solution()
////////////////////////////////////////////////////////////////////////////
{
 archive.push_back(random_solution());

 if (is_time)
  solution_time();
 else
  solution_value();

 return archive;
}

////////////////////////////////////////////////////////////////////////////
std::string TSP_SimplePareto::get_name()
////////////////////////////////////////////////////////////////////////////
{
 return "simple-pareto";
}

