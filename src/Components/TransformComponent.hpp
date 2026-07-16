#ifndef __TRANSFORM_COMPONENT_HPP__
#define __TRANSFORM_COMPONENT_HPP__
#include "glm/ext/vector_float2.hpp"

struct TransformComponent {
  glm::vec2 position;
  glm::vec2 scale;
  double rotation;
  TransformComponent(glm::vec2 _pos = glm::vec2(0.0, 0.0), glm::vec2 _scale = glm::vec2(1.0, 1.0), double _rotation = 0.0)
    : position(_pos)
    , scale(_scale)
    , rotation(_rotation)
  {}
};
#endif
