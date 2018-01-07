#ifndef TSP_SCALAR_DEFINE
#define TSP_SCALAR_DEFINE

#include "TSP_filter.h"

class TSP_Scalar : public TSP_filter
{
 private:
  Archive archive;  
  float step;
  int generation;
  int neighbours_by_parent;
  int depth;

 public:
  TSP_Scalar(std::vector<Instance> &instances,
             float step,
             int generation,
             int neighbours_by_parent,
             int depth):
   TSP_filter(instances),
   step(step),
   generation(generation),
   neighbours_by_parent(neighbours_by_parent),
   depth(depth)
  {
   for (int i = 0 ; i < 1000 ; i++)
    archive.push_back(random_solution());
  }

 Archive solution();
 void filter_scalar();
};

#endif
