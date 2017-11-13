#include <iostream>
#include "Instance.h"
#include "TSP_filter.h"

int main(int argc, char *argv[])
{
 if (argc == 1)
 {
  std::cerr << "Bad args." << std::endl;
  return -1;
 }

 std::vector<Instance> to_optimize;

 for (int i = 0 ; i < argc-1 ; i++)
  to_optimize.push_back(Instance("../../instances/random"+std::string(argv[i+1])+"100.tsp"));

 TSP_filter tsp(to_optimize);
 auto sols = tsp.solutions_off(500);

 for (size_t i = 0 ; i < sols.size() ; i++)
 {
  auto evals = tsp.evaluations(sols[i]);
  std::cout << i << " ";
  for (size_t j = 0 ; j < evals.size() ; j++)
   std::cout << evals[j] << " ";
  std::cout << std::endl;
 }

 return 0;
}
