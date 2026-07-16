#ifndef __RIGID_BODY_COMPONENT_HPP__
#define __RIGID_BODY_COMPONENT_HPP__
#include "glm/ext/vector_float2.hpp"

struct RigidBodyComponent {
  glm::vec2 velocity;
  RigidBodyComponent(glm::vec2 _v = glm::vec2(0.0, 0.0))
    : velocity(_v)
  {}
};
#endif
