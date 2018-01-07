#include "TSP_scalar.h"
#include <algorithm>
#include <iostream>
#include <fstream>

////////////////////////////////////////////////////////////////////////////
void k_opt
////////////////////////////////////////////////////////////////////////////
(
 Sol &sol,
 int index1,
 int index2 
)
{
 if (index1 > index2)
 {
  int new_index = index2;
  index2 = index1;
  index1 = new_index;
 }

 while (index1 < index2)
 {
  std::iter_swap(sol.begin()+index1, sol.begin()+index2);
  index1++;
  index2--;
 }
}

////////////////////////////////////////////////////////////////////////////
void TSP_Scalar::write_front
////////////////////////////////////////////////////////////////////////////
(
 Archive &sol
)
{
 std::ofstream file("test-"+std::to_string(current_generation)+".dat"); 

 for (size_t i = 0 ; i < sol.size() ; i++)
 {
  auto evals = evaluations(sol[i]);
  for (size_t j = 0 ; j < evals.size() ; j++)
   file << evals[j] << " ";
  file << std::endl;
 }
}

////////////////////////////////////////////////////////////////////////////
Archive TSP_Scalar::solution()
////////////////////////////////////////////////////////////////////////////
{
 /*
 filter_scalar();

 int rd1 = 0;
 int rd2 = 0;

 while (current_generation < generation)
 {
  if (current_generation%10 == 0)
   write_front(archive);

  std::cerr << '\r' << current_generation;
  current_generation++;

  // Génération des voisins
  Archive neighbours;
  for (auto parent: archive)
  {
   for (int i = 0 ; i < neighbours_by_parent ; i++)
   {
    auto child = parent;

    rd1 = g()%child.size();
    rd2 = g()%child.size();
    while (rd2 == rd1)
     rd2 = (g()+1)%child.size();
    k_opt(child, rd1, rd2);

    neighbours.push_back(child);
   }
  }

  for (auto n: neighbours)
   archive.push_back(n);

  filter_scalar();
 }

 return archive;*/

 // Génération des points liés à un poids
 int nb_points = 1/ + 1;

 // k-opt sur chaque points jusqu'à tant de temps ou 
 // tant d'itération

 // Filtre off

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
