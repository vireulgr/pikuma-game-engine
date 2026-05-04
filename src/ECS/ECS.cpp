#include "ECS.hpp"
#include <algorithm>

void System::AddEntityToSystem(Entity e) {
  entities.push_back(e);
}

void System::RemoveEntityFromSystem(Entity e) {
  std::vector<Entity>::iterator iter = 
    std::remove_if(entities.begin(), entities.end(), [&e] (Entity entity) { return e == entity; });
  entities.erase(iter, entities.end());
}

std::vector<Entity> System::GetSystemEntities() const {
  return entities;
}

Signature System::GetComponentSignature() const {
  return componentSignature;
}
