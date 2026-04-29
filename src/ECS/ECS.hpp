#ifndef __ECS_HPP__
#define __ECS_HPP__
#include <bitset>
#include <vector>

unsigned int const MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> Signature;

class Component {};

class Entity {
  int id;
  public:
  Entity(int id): id(id) {}
  int GetId() const { return id; }
};

class System {
  Signature componentSignature;
  std::vector<Entity> entities;
  public:
  void AddEntityToSystem(Entity);
  void RemoveEntityFromSystem(Entity);
  std::vector<Entity> GetSystemEntities() const;
  Signature GetComponentSignature() const;
};

class Registy{};
#endif
