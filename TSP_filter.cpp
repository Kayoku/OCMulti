#include "TSP_filter.h"
#include <algorithm>
#include <iostream>

////////////////////////////////////////////////////////////////////////////
void TSP_filter::solutions_off
////////////////////////////////////////////////////////////////////////////
(
 std::vector<std::vector<int>> &archive
)
{
 std::vector<std::vector<int>> new_archive;

 // Garde uniquement les solutions dominantes
 for (size_t i = 0 ; i < archive.size() ; i++)
 {
  bool is_not_dominated = true;
  for (size_t j = 0 ; j < archive.size() ; j++)
  {
   if (i==j)
    continue;

   int dom = dominating(archive[i], archive[j]);
   if (dom == 2)
   {
    is_not_dominated = false;
    break; 
   }
  } 
  if (is_not_dominated)
   new_archive.push_back(archive[i]);
 }

 archive = new_archive;
}

////////////////////////////////////////////////////////////////////////////
void TSP_filter::solutions_on
////////////////////////////////////////////////////////////////////////////
(
 std::vector<std::vector<int>> &archive,
 std::vector<int> new_sol 
)
{
 for (size_t i = 0 ; i < archive.size() ; i++)
 {
  int dom = dominating(archive[i], new_sol);

  // new sol est dominé
  if (dom == 0)
   return;
  // new sol domine au moins une fois, donc elle peut être ajouté
  else if (dom == 2)
  {
   archive.erase(std::remove_if(archive.begin(),
                                archive.end(),
                                [&](const std::vector<int> &s)
                                { return dominating(new_sol, s) == 0; }),
                 archive.end());
   break;
  }
 }

 // On l'ajoute à l'archive
 archive.push_back(new_sol);
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
