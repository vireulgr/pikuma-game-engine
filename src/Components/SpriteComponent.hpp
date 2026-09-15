#ifndef __SPRITE_COMPONENT_HPP__
#define __SPRITE_COMPONENT_HPP__
#include <string>

struct SpriteComponent {
  std::string assetId;
  int width;
  int height;
  SpriteComponent() = default;
  SpriteComponent(std::string const & assetId, int _width, int _height)
    : assetId(assetId)
    , width(_width)
    , height(_height)
  {}
};

#endif
