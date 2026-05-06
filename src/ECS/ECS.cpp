#include "ECS.hpp"
#include <algorithm>
#include <string>
#include <typeindex>
#include "../logger/logger.hpp"

void System::AddEntity(Entity e) {
  entities.push_back(e);
}

void System::RemoveEntity(Entity e) {
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

void Registry::killEntity(Entity) {
}

Entity Registry::createEntity() {
  unsigned int entityId = numEntities += 1;
  if (entityId >= entityComponentSigntures.size()) {
    entityComponentSigntures.resize(entityId + 1);
  }

  Entity entity((entityId));
  entitiesToBeAdded.insert(entity);

  Logger::Log("Entity created with id " + std::to_string(entityId));
  return entity;
}

void Registry::addEntityToSystem(Entity) {
}

void Registry::update() {
  // add entites
  // remove entities
}
