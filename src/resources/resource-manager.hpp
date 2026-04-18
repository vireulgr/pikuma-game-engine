#ifndef __RESOURCE_MANAGER_HPP__
#define __RESOURCE_MANAGER_HPP__

#include <string>

struct ResourceBase;

class ResourceManager {
  public:
  ResourceBase * getResource(std::string id);
};

#endif
