#ifndef __SPRITE_COMPONENT_HPP__
#define __SPRITE_COMPONENT_HPP__

struct SpriteComponent {
  int width;
  int height;
  SpriteComponent() = default;
  SpriteComponent(int _width, int _height)
    : width(_width)
    , height(_height)
  {}
};

#endif
