#ifndef __TRANSFORM_COMPONENT_HPP__
#define __TRANSFORM_COMPONENT_HPP__
#include "glm/ext/vector_float2.hpp"

struct TransformComponent {
  glm::vec2 position;
  glm::vec2 scale;
  double rotation;
};
#endif
