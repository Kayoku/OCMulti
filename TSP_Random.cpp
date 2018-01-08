#include "TSP_Random.h"
#include <algorithm>
#include <random>

////////////////////////////////////////////////////////////////////////////
Archive TSP_Random::solution()
////////////////////////////////////////////////////////////////////////////
{
 Archive new_archive;
 for (int i = 0 ; i < nb_random ; i++)
  new_archive.push_back(random_solution());

 for (auto sol: new_archive)
  filter_online(archive, sol);

 return archive;
}
