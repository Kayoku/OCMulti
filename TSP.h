#ifndef TSP_DEFINE
#define TSP_DEFINE

#include "Instance.h"
#include <iostream>
#include <vector>
#include <random>

typedef std::vector<std::vector<int>> Archive;
typedef std::vector<int> Sol;

/* Permet de savoir qui domine qui */
enum Domination
{
 SOL1_DOMINATION,
 SOL2_DOMINATION,
 NO_DOMINATION
};

class TSP
{
 protected:
  std::vector<Instance> &instances;
  std::string name;
  Archive archive;
  std::random_device rd;
  std::mt19937 g;
  int follow_step;
  int next_step;
  long nb_compute_cost;

 public:
  TSP(std::vector<Instance> &instances,
      std::string name):
   instances(instances),
   name(name),
   rd(),
   g(rd()),
   follow_step(-1),
   next_step(-1),
   nb_compute_cost(0)
  {
   // for std::random_shuffle
   srand(time(0));
  }

  /* Fonctions utiles */
  Sol random_solution(); // génère une solution aléatoire
  Sol greedy_solution(std::vector<float> weights = {1, 1});
  Domination compare(Sol sol1, Sol sol2); // compare deux solutions
  void write_archive(Archive &archive, std::string filename);
  long get_compute_cost() { return nb_compute_cost; }
  void reset_cost() { nb_compute_cost = 0; }

  /* Fonctions de voisinage */
  Sol two_opt(Sol sol, int id1, int id2);

  /* Fonctions de filtre */
  void filter_online(Archive &archive,
                      Sol sol);
  void filter_offline(Archive &archive);

  /* Fonctions d'évaluation */
  std::vector<int> evaluations(Sol solution);
  int evaluations_weight(Sol solution, std::vector<float> weights);
  int evaluation(int i, Sol solution, float weight=1);

  /* Fonctions de suivi */
  void set_following(int step) {follow_step = step; next_step = step; }
  void do_following(int value);

  // Fonction à override renvoyant une archive d'un front 
  virtual Archive solution() = 0;
  virtual void solution_time() = 0;
  virtual void solution_value() = 0;
  virtual std::string get_name() = 0;
};

#endif
