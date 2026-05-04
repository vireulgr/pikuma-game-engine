#ifndef __ECS_HPP__
#define __ECS_HPP__
#include <bitset>
#include <vector>

unsigned int const MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> Signature;

struct BaseComponent {
  protected: 
  static int nextId;
};

template <typename TComponent>
class Component: public BaseComponent {
  static int GetID() {
    static int myId = nextId;
    nextId += 1;
    return myId;
  }
};

class Entity {
  int id;
  public:
  Entity(int id): id(id) {}
  Entity(Entity const & other) = default;
  int GetId() const { return id; }
  Entity & operator=(Entity const & other) = default;

  bool operator==(Entity const & other) const {
    //if (this == &other) {
    //  return true;
    //}
    return id == other.id;
  }
};

class System {
  Signature componentSignature;
  std::vector<Entity> entities;
  public:
  void AddEntityToSystem(Entity);
  void RemoveEntityFromSystem(Entity);
  std::vector<Entity> GetSystemEntities() const;
  Signature GetComponentSignature() const;

  template<typename T>
    void RequireComponent();
};

template<typename TComponent>
void System::RequireComponent() {
  int componentId = Component<TComponent>::GetID();
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

class Registy {
  int numEntities;
  std::vector<IPool *> componentPools;
};

#endif
