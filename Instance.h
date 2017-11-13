#ifndef INSTANCE_DEFINE
#define INSTANCE_DEFINE

#include <vector>
#include <map>

struct Instance
{
 std::vector<std::map<short, int>> distances; 

 Instance(std::string filename);
};

#endif
