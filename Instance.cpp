#include "Instance.h"
#include <iostream>
#include <fstream>
#include <string>

////////////////////////////////////////////////////////////////////////////
Instance::Instance
////////////////////////////////////////////////////////////////////////////
(
 std::string filename
)
{
 std::ifstream file(filename);
 if (!file.good())
 {
  std::cerr << "Erreur d'ouverture de l'instance " << filename << std::endl;
  exit(-1);
 }

 // Création de toutes les maps
 for (int i = 0 ; i < 100 ; i++)
  distances.push_back(std::map<short, int>());

 // On remplit la map
 int inter;
 for (int i = 0 ; i < 100 ; i++)
 {
  for (int j = i ; j < 100 ; j++)
  {
   file >> inter;
   distances[i][j] = inter;
   distances[j][i] = inter;
  }
 }
}
