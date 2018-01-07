#ifndef TSP_SCALAR_DEFINE
#define TSP_SCALAR_DEFINE

#include "TSP_filter.h"

class TSP_Scalar : public TSP_filter
{
 private:
  Archive archive;  
  float step;
  int generation;
  int current_generation;
  int neighbours_by_parent;

 public:
  TSP_Scalar(std::vector<Instance> &instances,
             float step,
             int generation,
             int neighbours_by_parent):
   TSP_filter(instances),
   step(step),
   generation(generation),
   current_generation(0),
   neighbours_by_parent(neighbours_by_parent)
  {
   /*
   for (int i = 0 ; i < 1000 ; i++)
    archive.push_back(random_solution());
   */
  }

 Archive solution();
 void filter_scalar();
 void write_front(Archive &sol);
};

#endif
