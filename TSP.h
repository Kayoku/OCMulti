#ifndef TSP_DEFINE
#define TSP_DEFINE

#include "Instance.h"
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
  Archive archive;
  std::random_device rd;
  std::mt19937 g;

 public:
  TSP(std::vector<Instance> &instances):
   instances(instances),
   rd(),
   g(rd())
  {
   // for std::random_shuffle
   srand(time(0));
  }

  /* Fonctions utiles */
  Sol random_solution(); // génère une solution aléatoire
  Sol greedy_solution(std::vector<float> weights = {1, 1});
  Domination compare(Sol sol1, Sol sol2); // compare deux solutions
  void write_archive(Archive &archive, std::string filename);

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

  // Fonction à override renvoyant une archive d'un front 
  virtual Archive solution() = 0;
};

#endif
