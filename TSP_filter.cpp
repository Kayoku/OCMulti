#include "TSP_filter.h"
#include <algorithm>
#include <iostream>

////////////////////////////////////////////////////////////////////////////
void TSP_filter::solutions_off
////////////////////////////////////////////////////////////////////////////
(
 Archive &archive
)
{
 size_t i = 0;

 do
 {
  auto elem = archive[i];
  int current_size = archive.size();

  archive.erase(std::remove_if(archive.begin(),
                               archive.end(),
                               [&](const std::vector<int> &s)
                               { return dominating(elem, s) == 0; }),
                archive.end());
  int new_size = archive.size();
  if (current_size != new_size)
   i=0;
  else
   i++;
 } while (i < archive.size());
}

////////////////////////////////////////////////////////////////////////////
void TSP_filter::solutions_on
////////////////////////////////////////////////////////////////////////////
(
 Archive &archive,
 Sol new_sol
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
 Sol sol1,
 Sol sol2
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

