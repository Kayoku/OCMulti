#include "TSP_Random.h"
#include <algorithm>
#include <random>

////////////////////////////////////////////////////////////////////////////
Archive TSP_Random::solution()
////////////////////////////////////////////////////////////////////////////
{
 for (int i = 0 ; i < nb_random ; i++)
  archive.push_back(random_solution());

 filter_offline(archive);
 return archive;
}
