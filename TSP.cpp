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
 nb_compute_cost++;

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
 std::vector<floatt> weights
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
 Archive &ar
)
{
 size_t i = 0;

 do
 {
  auto elem = ar[i];
  int current_size = ar.size();

  ar.erase(std::remove_if(ar.begin(),
                          ar.end(),
                          [&](const std::vector<int> &s)
                          { return compare(elem, s) == SOL1_DOMINATION; }),
                ar.end());
  ar.push_back(elem);
  int new_size = ar.size();

  if (current_size != new_size)
   i=0;
  else
   i++;

 } while (i < ar.size());
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
  Domination dom = compare(archive[i], new_sol);

  // new sol est dominé
  if (dom == SOL1_DOMINATION)
   return;
  // new sol domine au moins une fois, donc elle peut être ajouté
  else if (dom == SOL2_DOMINATION)
  {
   archive.erase(std::remove_if(archive.begin(),
                                archive.end(),
                                [&](const std::vector<int> &s)
                                { return compare(new_sol, s) == SOL1_DOMINATION; }),
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
 std::reverse(sol.begin()+id1, sol.begin()+id2+1);
 return sol;
}

////////////////////////////////////////////////////////////////////////////
void TSP::do_following
////////////////////////////////////////////////////////////////////////////
(
 int value
)
{
 if (follow_step > 0 && value > next_step)
 {
  write_archive(archive, get_name()+"-"+name+"-"+std::to_string(next_step)+".dat");
  next_step += follow_step;
 }
}
