#ifndef __ECS_HPP__
#define __ECS_HPP__
#include <bitset>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <set>

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
  static int GetID() {
    static int myId = nextId;
    nextId += 1;
    return myId;
  }
};

/**
 */
class Entity {
  int id;
public:
  Entity(int id): id(id) {}
  Entity(Entity const & other) = default;
  Entity & operator=(Entity const & other) = default;

  bool operator==(Entity const & other) const { return id == other.id; }
  bool operator!=(Entity const & other) const { return id != other.id; }
  bool operator<(Entity const & other) const { return id < other.id; }
  bool operator>(Entity const & other) const { return id > other.id; }

  int getId() const { return id; }
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
  int componentId = Component<TComponent>::GetID();
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
  std::vector<IPool *> componentPools;
  // entity id => signature
  std::vector<Signature> entityComponentSignatures;
  // systems
  std::unordered_map<std::type_index, System*> systems;

  std::set<Entity> entitiesToBeAdded;
  std::set<Entity> entitiesToBeRemoved;
public:
  Registry() = default;

  Entity createEntity();
  void killEntity(Entity);

  void addEntityToSystem(Entity);

  void update();

  template<typename T, typename ...CtorParams>
    void addComponent(Entity, CtorParams&& ...args);
};


template<typename T, typename ...CtorParams>
void Registry::addComponent(Entity entity, CtorParams&& ...args) {

  const auto componentId = Component<T>::GetID();
  const auto entityId = entity.getId();

  if (componentPools.size() <= componentId) {
    componentPools.resize(componentId + 1, nullptr);
  }

  auto componentTypePoolPtr = componentPools[componentId];
  if (!componentTypePoolPtr) {
    componentTypePoolPtr = new Pool<T>(entityId);
  }

  if (componentTypePoolPtr->Size() <= entityId) {
    componentTypePoolPtr->Resize(numEntities); // numEntities must be imcremented in the moment of entity creation
  }

  T newComponent(std::forward<CtorParams>(args)...);

  componentTypePoolPtr->set(entityId, newComponent);

  entityComponentSignatures[entityId].set(componentId);
}
#endif
