#include "TSP_GenPareto.h"
#include <algorithm>
#include <iostream>
#include <chrono>

////////////////////////////////////////////////////////////////////////////
Archive TSP_GenPareto::mutation()
////////////////////////////////////////////////////////////////////////////
{
 Archive mutants;
 int id1, id2, inter;

 for (int i = 0 ; i < nb_mutation ; i++)
 {
  auto new_mutant = archive[g()%archive.size()];

  for (int k = 0 ; k < mutation_intensity ; k++)
  {
   id1 = g()%new_mutant.size();
   id2 = g()%new_mutant.size();
   while (id1 == id2)
    id2 = (g()+1)%new_mutant.size();

   if (id2 > id1)
   {
    inter = id1;
    id1 = id2;
    id2 = id1; 
   }

   new_mutant = two_opt(new_mutant, id1, id2);
  }

  mutants.push_back(new_mutant);
 }

 return mutants;
}

////////////////////////////////////////////////////////////////////////////
Archive TSP_GenPareto::reproduction()
////////////////////////////////////////////////////////////////////////////
{
 Archive childs;
 for (int i = 0 ; i < (int)archive.size() ; i++)
 {
  int parent1 = g()%archive.size();
  int parent2 = g()%archive.size();
  while (parent1 == parent2)
   parent2 = (g()+1)%archive.size();

  auto new_child = order_crossover(archive[parent1], archive[parent2]); 
  childs.push_back(new_child);
 }
 return childs;
}

////////////////////////////////////////////////////////////////////////////
Sol TSP_GenPareto::order_crossover
////////////////////////////////////////////////////////////////////////////
(
 Sol parent1,
 Sol parent2
)
{
 Sol new_child(parent1.size(), 0);
 int offset = g()%25;
 int window = g()%75;

 // 1. On copie la suite génétique du premier parent
 std::copy(parent1.begin()+offset, parent1.begin()+offset+window, new_child.begin()+offset);

 // 2. On comble avec la suite de l'autre parent
 // 
 std::vector<long> gen_missing(parent1.size()-window, 0);
 std::copy(parent1.begin(), parent1.begin()+offset, gen_missing.begin());
 std::copy(parent1.begin()+offset+window, parent1.end(), gen_missing.begin()+  offset);

 std::vector<std::pair<long, int>> indexed_missing;
 for (auto gen: gen_missing)
  indexed_missing.push_back(std::pair<long, int>(
                    gen,
                    std::find(parent2.begin(), parent2.end(), gen)-parent2.begin()));

 // On trie puis on ajoute les gen manquant
 std::sort(indexed_missing.begin(), indexed_missing.end(),
           [&](const std::pair<long, int>& first, const std::pair<long, int>&second)
           { return first.second < second.second; });

 int ii = 0;
 for (int i = 0 ; i < (int)new_child.size() ; i++)
 {
  if (i == offset)
   i += window;

  new_child[i] = indexed_missing[ii].first;
  ii++;
 }

 return new_child;
}

////////////////////////////////////////////////////////////////////////////
void TSP_GenPareto::solution_time()
////////////////////////////////////////////////////////////////////////////
{
 // On remplit la population de départ si celle-ci n'est pas déjà
 // générée.
 if (archive.empty())
  for (int i = 0 ; i < start_population; i++)
   filter_online(archive, random_solution());
 
 auto time_init = std::chrono::high_resolution_clock::now();
 auto time_it = std::chrono::high_resolution_clock::now();
 auto diff = std::chrono::duration_cast<std::chrono::seconds>(time_it-time_init).count();

 while (diff < limit)
 {
  current_generation++;

  Archive childs;
  if (archive.size() >= 2)
   childs = reproduction(); 

  Archive mutants = mutation();
   
  for (auto c : childs)
   filter_online(archive, c);
   
  for (auto m : mutants)
   filter_online(archive, m);
 
  time_it = std::chrono::high_resolution_clock::now();
  diff = std::chrono::duration_cast<std::chrono::seconds>(time_it-time_init).count();
  do_following(diff);
  std::cout << '\r' << diff << "s/" << limit << "s (" << archive.size() << ")" << std::flush;
 }
 std::cout << std::endl;
}

////////////////////////////////////////////////////////////////////////////
void TSP_GenPareto::solution_value()
////////////////////////////////////////////////////////////////////////////
{
 // On remplit la population de départ si celle-ci n'est pas déjà
 // générée.
 if (archive.empty())
  for (int i = 0 ; i < start_population; i++)
   filter_online(archive, random_solution());
 
 while (current_generation < limit)
 {
  current_generation++;

  Archive childs;
  if (archive.size() >= 2)
   childs = reproduction(); 
  Archive mutants = mutation();
   
  for (auto c : childs)
   filter_online(archive, c);
   
  for (auto m : mutants)
   filter_online(archive, m);

  do_following(current_generation);
  std::cout << '\r' << current_generation << '/' << limit << " (" << archive.size() << ")" << std::flush;
 }
 std::cout << std::endl;
}

////////////////////////////////////////////////////////////////////////////
Archive TSP_GenPareto::solution()
////////////////////////////////////////////////////////////////////////////
{
 if (is_time)
  solution_time();
 else
  solution_value();

 return archive;
}

////////////////////////////////////////////////////////////////////////////
std::string TSP_GenPareto::get_name()
////////////////////////////////////////////////////////////////////////////
{
 return "pareto-s"+std::to_string(start_population)+"-m"+std::to_string(nb_mutation)+"-i"+std::to_string(mutation_intensity)+
         (is_time ? "-t": "-l")+std::to_string(limit);
}


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

 return archive;
}

////////////////////////////////////////////////////////////////////////////
void TSP_GenPareto::filter_scalar()
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
}*/
