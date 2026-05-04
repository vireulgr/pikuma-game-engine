#ifndef __MOVEMENT_SYSTEM_HPP__
#define  __MOVEMENT_SYSTEM_HPP__
#include "../ECS/ECS.hpp"
#include "../Components/TransformComponent.hpp"


class MovementSystem: public System {
public:
  MovementSystem(): System() {
    // TODO: Required systems
    RequireComponent<TransformComponent>();
    //RequireComponent<SpeedComponent>();
  }
  void Update() {
    for (auto entity: GetSystemEntities()) {
      entity.GetComponent<TransformComponent>().Update();
    }
  }
};

#endif
