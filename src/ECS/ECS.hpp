#ifndef __ECS_HPP__
#define __ECS_HPP__
#include <bitset>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>
#include <memory>
#include <set>

#include "../logger/logger.hpp"

unsigned int const MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> Signature;

/**
 */
struct BaseComponent {
  protected: 
    static int nextId;
};

/**
 */
template <typename TComponent>
class Component: public BaseComponent {
  public:
  static int getId() {
    static int myId = nextId++;
    return myId;
  }
};

/**
 */
class Entity {
  int id;
public:
  class Registry * registry;

  Entity(int id): id(id) {}
  Entity(Entity const & other) = default;
  Entity & operator=(Entity const & other) = default;

  bool operator==(Entity const & other) const { return id == other.id; }
  bool operator!=(Entity const & other) const { return id != other.id; }
  bool operator<(Entity const & other) const { return id < other.id; }
  bool operator>(Entity const & other) const { return id > other.id; }

  int getId() const { return id; }

  template <typename Component, typename ...CtorArgs>
    void addComponent(CtorArgs ...args);

  template <typename Component>
    void removeComponent();

  template <typename Component>
    bool hasComponent() const;

  template <typename Component>
    Component& getComponent() const;
};


/**
 */
class System {
  Signature componentSignature;
  std::vector<Entity> entities;
  public:
  void AddEntity(Entity);
  void RemoveEntity(Entity);
  std::vector<Entity> GetSystemEntities() const;
  Signature GetComponentSignature() const;

  template<typename T>
    void RequireComponent();
};

/**
 */
template<typename TComponent>
void System::RequireComponent() {
  int componentId = Component<TComponent>::getId();
  componentSignature.set(componentId);
}

/**
 */
class IPool {
  public:
    virtual ~IPool() {}
};

/**
 */
template <typename T>
class Pool: public IPool {
  std::vector<T> data; // each index contain component of type T of a specific entity
  public:
    Pool(int n = 100) { data.resize(n); }
    virtual ~Pool() = default;

    bool isEmpty() const { return data.empty(); }
    size_t getSize() const { return data.size(); }
    void resize(unsigned int n) { data.resize(n); }
    void clear() { data.clear(); }
    void add(T obj) { data.push_back(obj); } 
    void remove(T obj) {
      auto iter = std::remove_if(data.begin(), data.end(), [obj] (T const & item) { return item == obj; });
      data.erase(iter, data.end()); 
    }
    void set(unsigned int idx, T obj) { data[idx] = obj; }
    T& get(unsigned int idx) { return static_cast<T&>(data[idx]); }
    T& operator[](unsigned int idx) { return data[idx]; }
};

/**
 */
class Registry {
  int numEntities;
  // each pool object contains 
  std::vector<std::shared_ptr<IPool>> componentPools;
  // entity id => signature
  std::vector<Signature> entityComponentSignatures;
  // systems
  std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

  std::set<Entity> entitiesToBeAdded;
  std::set<Entity> entitiesToBeRemoved;
public:
  Registry() = default;
  ~Registry() = default;

  Entity createEntity();
  void killEntity(Entity);

  void addEntityToSystem(Entity);

  void update();

  // component management

  template<typename T, typename ...CtorParams>
    void addComponent(Entity, CtorParams&& ...args);

  template<typename T>
    void removeComponent(Entity entity); 

  template<typename T>
    bool hasComponent(Entity entity);

  template <typename Component>
    Component& getComponent(Entity entity) const;

  // system management

  template<typename T, typename ...CtorParmas>
    void addSystem(CtorParmas&& ...args);

  template<typename T>
    void removeSystem();

  template<typename T>
    bool hasSystem() const;

  template<typename T>
    T& getSystem() const;
};

// Registry methods implementation
/** */
template<typename T>
bool Registry::hasComponent(Entity entity) {
  const auto entityId = entity.getId();
  const auto componentId = Component<T>::getId();

  if (entityComponentSignatures.empty()) {
    return false;
  }
  if ((entityComponentSignatures.size() - 1) < static_cast<size_t>(entityId)) {
    return false;
  }

  return entityComponentSignatures[entityId].test(componentId);
}

/** */
template<typename T>
void Registry::removeComponent(Entity entity) {
  const auto componentId = Component<T>::getId();
  const auto entityId = entity.getId();

  entityComponentSignatures[entityId].set(componentId, false);
  Logger::Log("component " + std::to_string(componentId) + " was removed from entity " + std::to_string(entityId));
}


template <typename T>
T& Registry::getComponent(Entity entity) const {
  const auto componentId = Component<T>::getId();
  const auto entityId = entity.getId();

  auto componentPool = std::static_pointer_cast<Pool<T>>(componentPools[componentId]);
  return componentPool->get(entityId);
}

/** */
template<typename T, typename ...CtorParams>
void Registry::addComponent(Entity entity, CtorParams&& ...args) {

  const auto componentId = Component<T>::getId();
  const auto entityId = entity.getId();
  Logger::Log("add component id " + std::to_string(componentId) + " to entity id " + std::to_string(entityId));

  if (componentPools.size() <= static_cast<size_t>(componentId)) {
    componentPools.resize(componentId + 1, nullptr);
  }

  if (!componentPools[componentId]) {
    //componentTypePoolPtr = new Pool<T>(entityId);
    componentPools[componentId] = std::make_shared<Pool<T>>(entityId);
  }

  std::shared_ptr<Pool<T>> componentTypePoolPtr = std::static_pointer_cast<Pool<T>>(componentPools[componentId]);

  if (componentTypePoolPtr->getSize() <= static_cast<size_t>(entityId)) {
    componentTypePoolPtr->resize(numEntities); // numEntities must be incremented in the moment of entity creation
  }

  T newComponent(std::forward<CtorParams>(args)...);

  componentTypePoolPtr->set(entityId, newComponent);

  entityComponentSignatures[entityId].set(componentId);
}


/** */
template<typename T, typename ...CtorParmas>
void Registry::addSystem(CtorParmas&& ...args) {
  std::shared_ptr<T> newSystem = std::make_shared<T>(std::forward<CtorParmas>(args)...);
  //T* newSystem = new T(std::forward<CtorParmas>(args)...);
  systems.insert(std::make_pair(std::type_index(typeid(T)), newSystem));
}

/** */
template<typename T>
void Registry::removeSystem() {
  auto it = systems.find(std::type_index(typeid(T)));
  systems.erase(it);
}

/** */
template<typename T>
bool Registry::hasSystem() const {
  return systems.find(std::type_index(typeid(T))) != systems.end();
}

/** */
template<typename T>
T& Registry::getSystem() const {
  auto wasya = systems.find(std::type_index(typeid(T)));
  if (wasya != systems.end()) {
    return static_cast<T>(wasya->second);
  }
  return systems.at(std::type_index(typeid(T))); // will throw ????
}

// 
// Entity methods implementation
//
template <typename T, typename ...CtorArgs>
void Entity::addComponent(CtorArgs ...args) {
  registry->addComponent<T>(*this, std::forward<CtorArgs>(args)...);
}

template <typename T>
void Entity::removeComponent() {
  registry->removeComponent<T>(*this);
}

template <typename T>
bool Entity::hasComponent() const {
  return registry->hasComponent<T>(*this);
}

template <typename T>
T& Entity::getComponent() const {
  return registry->getComponent<T>(*this);
}
#endif
