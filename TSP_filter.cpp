#include "TSP_filter.h"
#include <algorithm>
#include <iostream>

////////////////////////////////////////////////////////////////////////////
std::vector<std::vector<int>> TSP_filter::solutions_off(int nb_base)
////////////////////////////////////////////////////////////////////////////
{
 std::vector<std::vector<int>> sols;
 std::vector<std::vector<int>> domination_sols;

 // Génère toutes les solutions
 for (int i = 0 ; i < nb_base ; i++)
  sols.push_back(solution());

 // Ne garde que les dominantes
 for (size_t i = 0 ; i < sols.size() ; i++)
 {
  bool is_equal = true;
  for (size_t j = 0 ; j < domination_sols.size() ; j++)
  {
   if (domination_sols[j].size() == 0 || sols[i].size() == 0)
   {
    std::cout << "WTF: " << std::endl;
    std::cout << "j: " << j << std::endl;
    std::cout << "j size: " << domination_sols.size() << std::endl; 
    std::cout << "i: " << i << std::endl;
    std::cout << "i size: " << sols.size() << std::endl; 
    exit(-1);
   }
   int dom = dominating(domination_sols[j], sols[i]);
   if (dom == 0)
   {
    is_equal = false;
    break;
   }
   else if (dom == 2)
   {
    // On ajoute sols et on supprime tous les dominés dont j
    domination_sols.erase(std::remove_if(domination_sols.begin(),
                   domination_sols.end(),
                   [&](const std::vector<int> &s)
                   { return dominating(sols[i], s) == 0; }),
                         domination_sols.end());
    domination_sols.push_back(sols[i]);
    is_equal = false;
    break;
   }
  }

  if (is_equal)
   domination_sols.push_back(sols[i]);
 }

 return domination_sols;
}

// 0 si sol1 domine sol2 
// 1 si sol1 et sol2 ne se domine pas
// 2 si sol2 domine sol1
////////////////////////////////////////////////////////////////////////////
int TSP_filter::dominating
////////////////////////////////////////////////////////////////////////////
(
 std::vector<int> sol1,
 std::vector<int> sol2
)
{
 int cpt = 0;
 for (size_t i = 0 ; i < instances.size() ; i++)
  if (evaluation(i, sol1) < evaluation(i, sol2))
   cpt++;

 // sol1 domine
 if (cpt == (int)instances.size())
  return 0;
 // sol2 domine
 else if (cpt == 0)
  return 2;
 // pas de dominant
 else
  return 1;
}
