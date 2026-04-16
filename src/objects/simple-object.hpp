#ifndef __SIMPLE_OBJECT_HPP__
#define __SIMPLE_OBJECT_HPP__

struct SDL_Texture;

class BaseObject {
  SDL_Texture * m_texture;

public:
  float m_posx;
  float m_posy;
  bool initialize();
  void render();
  void update();
};

#endif
