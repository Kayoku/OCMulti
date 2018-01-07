#include "TSP_scalar.h"
#include <algorithm>
#include <iostream>

////////////////////////////////////////////////////////////////////////////
Archive TSP_Scalar::solution()
////////////////////////////////////////////////////////////////////////////
{
 filter_scalar();

 int rd1 = 0;
 int rd2 = 0;

 for (int cur_gen = 0 ; cur_gen < generation ; cur_gen++)
 {
  std::cerr << '\r' << cur_gen;
  // Génération des voisins
  Archive neighbours;
  for (auto parent: archive)
  {
   for (int i = 0 ; i < 10 ; i++)
   {
    auto child = parent;
    rd1 = g()%child.size();
    rd2 = g()%child.size();
    while (rd2 == rd1)
     rd2 = (g()+1)%child.size();
    std::iter_swap(child.begin()+rd1, child.begin()+rd2);
    neighbours.push_back(child);
   }
  }

  for (auto n: neighbours)
   archive.push_back(n);

  filter_scalar();
 }

 return archive;
}

////////////////////////////////////////////////////////////////////////////
void TSP_Scalar::filter_scalar()
////////////////////////////////////////////////////////////////////////////
{
 Archive new_archive;
 std::vector<int> indexs_best;

 for (float w = 0 ; w <= 2.0f ; w+=step)
 {
  std::vector<float> weights = {w, 2.0f-w};
  int best_index = 0;
  int best_cost = evaluations_weight(archive[0], weights); 
  int new_cost = 0;

  for (size_t i = 1; i < archive.size() ; i++)
  {
   new_cost = evaluations_weight(archive[i], weights);
   if (new_cost < best_cost)
   {
    best_index = i;
    best_cost = new_cost;
   }
  }

  if (std::find(indexs_best.begin(), indexs_best.end(), best_index) == indexs_best.end())
  {
   indexs_best.push_back(best_index);
   new_archive.push_back(archive[best_index]);
  }
 }

 archive = new_archive;
}
