#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

////////////////////////////////////////////////////////////////////////////
std::vector<int> two_opt(std::vector<int> sol, int id1, int id2)
////////////////////////////////////////////////////////////////////////////
{
 while (id1 < id2)
 {
  std::iter_swap(sol.begin()+id1, sol.begin()+id2);
  id1++;
  id2--;
 }
 return sol;
}

////////////////////////////////////////////////////////////////////////////
std::vector<int> two_opt_(std::vector<int> sol, int id1, int id2)
////////////////////////////////////////////////////////////////////////////
{
 std::reverse(sol.begin()+id1, sol.begin()+id2+1);
 return sol;
}


int main()
{
 std::vector<int> a(200, 0);

 std::chrono::high_resolution_clock::time_point t1;
 std::chrono::high_resolution_clock::time_point t2;

 t1 = std::chrono::high_resolution_clock::now();
 for (size_t i = 0 ; i < a.size() ; i++)
  for (size_t j = i+1 ; j < a.size(); j++)
   two_opt(a, i, j);
 t2 = std::chrono::high_resolution_clock::now();
 std::cout << "with no reverse: " << std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count() << std::endl;

 t1 = std::chrono::high_resolution_clock::now();
 for (size_t i = 0 ; i < a.size() ; i++)
  for (size_t j = i+1 ; j < a.size(); j++)
   two_opt_(a, i, j);
 t2 = std::chrono::high_resolution_clock::now();
 std::cout << "with reverse: " << std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count() << std::endl;

 return 0;
}
