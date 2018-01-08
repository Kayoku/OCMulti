#include "TSP.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>

////////////////////////////////////////////////////////////////////////////
std::vector<int> TSP::evaluations
////////////////////////////////////////////////////////////////////////////
(
 std::vector<int> solution
)
{
 std::vector<int> evals;
 for (size_t i = 0 ; i < instances.size() ; i++)
  evals.push_back(evaluation(i, solution));

 return evals;
}

////////////////////////////////////////////////////////////////////////////
int TSP::evaluations_weight
////////////////////////////////////////////////////////////////////////////
(
 Sol solution,
 std::vector<float> weights
)
{
 if (weights.size() != instances.size())
 {
  std::cerr << "Erreur taille des poids."  << std::endl;
  exit(-1);
 }

 int evals = 0;
 for (size_t i = 0 ; i < instances.size(); i++)
  evals += evaluation(i, solution, weights[i]);

 return evals;
}


////////////////////////////////////////////////////////////////////////////
int TSP::evaluation
////////////////////////////////////////////////////////////////////////////
(
 int i,
 std::vector<int> solution,
 float weight
)
{
 int value = 0; 

 for (size_t j = 0 ; j < solution.size()-1 ; j++)
  value += weight * instances[i].distances[solution[j]][solution[j+1]];
 value += weight * instances[i].distances[solution[solution.size()-1]][solution[0]];

 return value;
}

////////////////////////////////////////////////////////////////////////////
Sol TSP::random_solution()
////////////////////////////////////////////////////////////////////////////
{
 Sol sol;

 for (int i = 0 ; i < 100 ; i++)
  sol.push_back(i);

 std::random_shuffle(sol.begin(), sol.end());

 return sol;
}

/*
////////////////////////////////////////////////////////////////////////////
Sol TSP::greedy_solution
////////////////////////////////////////////////////////////////////////////
(
 std::vector<float> weights
)
{
 int nb_city = instances[0].distances.size();
 Sol sol;
 int new_city;

 // On lui met une ville
 new_city = g()%nb_city;
 sol.push_back(new_city);

 // On ajoute les villes petit à petit selon laquelle est la plus proche
 

 return sol;
}*/

////////////////////////////////////////////////////////////////////////////
void TSP::filter_offline
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
                               { return compare(elem, s) == 0; }),
                archive.end());
  int new_size = archive.size();
  if (current_size != new_size)
   i=0;
  else
   i++;
 } while (i < archive.size());
}


////////////////////////////////////////////////////////////////////////////
void TSP::filter_online
////////////////////////////////////////////////////////////////////////////
(
 Archive &archive,
 Sol new_sol
)
{
 for (size_t i = 0 ; i < archive.size() ; i++)
 {
  int dom = compare(archive[i], new_sol);

  // new sol est dominé
  if (dom == 0)
   return;
  // new sol domine au moins une fois, donc elle peut être ajouté
  else if (dom == 2)
  {
   archive.erase(std::remove_if(archive.begin(),
                                archive.end(),
                                [&](const std::vector<int> &s)
                                { return compare(new_sol, s) == 0; }),
                 archive.end());
   break;
  }
 }

 // On l'ajoute à l'archive
 archive.push_back(new_sol);
}

////////////////////////////////////////////////////////////////////////////
Domination TSP::compare
////////////////////////////////////////////////////////////////////////////
(
 Sol sol1,
 Sol sol2
)
{
 int cpt = 0;
 for (size_t i = 0 ; i < instances.size() ; i++)
  if (evaluation(i, sol1) <= evaluation(i, sol2))
   cpt++;

 // sol1 domine
 if (cpt == (int)instances.size())
  return SOL1_DOMINATION;
 // sol2 domine
 else if (cpt == 0)
  return SOL2_DOMINATION;
 // pas de dominant
 else
  return NO_DOMINATION;
}


////////////////////////////////////////////////////////////////////////////
void TSP::write_archive
////////////////////////////////////////////////////////////////////////////
(
 Archive &a,
 std::string filename
)
{
 std::ofstream file(filename, std::ofstream::out);

 // Tri
 std::sort(a.begin(), a.end(),
           [&] (const Sol &s1, const Sol &s2)
           { return evaluations(s1)[0] < evaluations(s2)[0];});

 for (size_t i = 0 ; i < a.size() ; i++)
 {
  auto evals = evaluations(a[i]);
  for (size_t j = 0 ; j < evals.size() ; j++)
   file << evals[j] << " ";
  file << std::endl;
 }
}

////////////////////////////////////////////////////////////////////////////
Sol TSP::two_opt(Sol sol, int id1, int id2)
////////////////////////////////////////////////////////////////////////////
{
 while (id1 < id2)
 {
  std::iter_swap(sol.begin()+id1, sol.begin()+id2);
  id1++;
  id2--;
 }
 return sol;
}

