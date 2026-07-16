#include "ECS.hpp"
#include "../logger/logger.hpp"
#include <algorithm>
#include <string>

int BaseComponent::nextId = 0;

/** */
void System::AddEntity(Entity e) { entities.push_back(e); }

/** */
void System::RemoveEntity(Entity e) {
  std::vector<Entity>::iterator iter =
      std::remove_if(entities.begin(), entities.end(),
                     [&e](Entity entity) { return e == entity; });
  entities.erase(iter, entities.end());
}

/** */
std::vector<Entity> System::GetSystemEntities() const { return entities; }

/** */
Signature System::GetComponentSignature() const { return componentSignature; }

/** */
void Registry::killEntity(Entity e) { entitiesToBeRemoved.insert(e); }

/** */
Entity Registry::createEntity() {
  unsigned int entityId = numEntities++;
  if (entityId >= entityComponentSignatures.size()) {
    entityComponentSignatures.resize(entityId + 1);
  }

  Entity entity((entityId));
  entity.registry = this;
  entitiesToBeAdded.insert(entity);

  Logger::Log("Entity created with id " + std::to_string(entityId));
  return entity;
}

/** */
void Registry::addEntityToSystem(Entity entity) {
  int const entityId = entity.getId();

  Signature const &entityComponentSignature =
      entityComponentSignatures[entityId];

  for (auto [key, system] : systems) {
    Signature const &systemSignature = system->GetComponentSignature();
    if ((systemSignature & entityComponentSignature) == systemSignature) {
      system->AddEntity(entity);
    }
  }
}

/** */
void Registry::update() {
  // add entites
  for (auto entity : entitiesToBeAdded) {
    addEntityToSystem(entity);
  }
  entitiesToBeAdded.clear();

  // remove entities TO BE DONE
  // for (auto entity : entitiesToBeRemoved) {
  //   removeEntity(entity);
  // }
  entitiesToBeRemoved.clear();
}
