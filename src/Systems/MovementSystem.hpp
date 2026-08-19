#ifndef __MOVEMENT_SYSTEM_HPP__
#define  __MOVEMENT_SYSTEM_HPP__
#include "../ECS/ECS.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"


class MovementSystem: public System {
public:
  MovementSystem(): System() {
    RequireComponent<TransformComponent>();
    RequireComponent<RigidBodyComponent>();
  }
  void update(double const dt) {
    for (auto entity: GetSystemEntities()) {
      TransformComponent& transform = entity.getComponent<TransformComponent>();
      RigidBodyComponent& rigidBody = entity.getComponent<RigidBodyComponent>();
      //entity.GetComponent<TransformComponent>().Update();
      transform.position.x += rigidBody.velocity.x * dt;
      transform.position.y += rigidBody.velocity.y * dt;
      Logger::Log("moving entity " + std::to_string(entity.getId()) + "; x:" + std::to_string(transform.position.x) + "; y:" + std::to_string(transform.position.y));
    }
  }
};

#endif
