#ifndef __ECS_HPP__
#define __ECS_HPP__
#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>

unsigned int const MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> Signature;

struct BaseComponent {
  protected: 
  static int nextId;
};

template <typename TComponent>
class Component: public BaseComponent {
  static int GetID() {
    static int myId = nextId += 1;
    return myId;
  }
};

class Entity {
  int id;
  public:
  Entity(int id): id(id) {}
  Entity(Entity const & other) = default;
  int getId() const { return id; }
  Entity & operator=(Entity const & other) = default;

  bool operator==(Entity const & other) const {
    //if (this == &other) {
    //  return true;
    //}
    return id == other.id;
  }

  bool operator<(Entity const & other) const {
    return id < other.id;
  }
};

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

template<typename TComponent>
void System::RequireComponent() {
  auto const componentId = Component<TComponent>::GetID();
  componentSignature.set(componentId);
}

class IPool {
  public:
    virtual ~IPool() {}
};

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

class Registry {
  unsigned int numEntities = 0;
  // each pool object contains
  std::vector<IPool *> componentPools;
  // entity id => signature
  std::vector<Signature> entityComponentSigntures;
  std::unordered_map<std::type_index, System *> systems;

  std::set<Entity> entitiesToBeAdded;
  std::set<Entity> entitiesToBeKilled;


public:
  Registry() = default;

  void update();

  Entity createEntity();
  void killEntity(Entity);

  void addEntityToSystem(Entity);

  template <typename T, typename ...Rest>
  void addComponent(Entity entity, Rest && ...args);

  template <typename T>
  void removeComponent(Entity entity);

  template <typename T>
  bool hasComponent(Entity entity) const;

  template <typename T>
  T& getComponent(Entity entity) const;

  // AddSystem
  // removeSystem
  // hasSystem
  // getSystem
};

template<typename T, typename ...Rest>
void Registry::addComponent(Entity entity, Rest && ...args) {
  auto const componentId = Component<T>::GetID();
  auto const entityId = entity.getId();

  if (componentId >= componentPools.size()) {
    componentPools.resize(componentId + 1, nullptr);
  }

  if (nullptr == componentPools[componentId]) {
    Pool<T>* componentPool = new Pool<T>();
    componentPools[componentId] = componentPool;
  }

  Pool<T>* curPool = static_cast<Pool<T>*>(componentPools[componentId]);

  if (entityId >= curPool->getSize()) {
    curPool->resize(numEntities);
  }

  T component = T(std::forward<Rest>(args)...);
  curPool->set(entityId, component);

  entityComponentSigntures[entityId].set(componentId);
}

#endif
