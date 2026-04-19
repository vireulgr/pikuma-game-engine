#ifndef __SIMPLE_OBJECT_HPP__
#define __SIMPLE_OBJECT_HPP__
#include "glm/ext/vector_float2.hpp"
#include <glm/glm.hpp>

struct SDL_Texture;
struct SDL_Renderer;
class ResourceManager;

class BaseObject {
protected:
  SDL_Texture * m_texture;
  float m_posx;
  float m_posy;
  glm::vec2 m_pos;
  glm::vec2 m_velocity;
public:
  virtual bool initialize(ResourceManager *, SDL_Renderer *) = 0;
  virtual void render(SDL_Renderer *) = 0;
  virtual void update(double dt) = 0;
  virtual ~BaseObject();
};

class TankObject: public BaseObject {
public:
  virtual bool initialize(ResourceManager *, SDL_Renderer * ) override;
  virtual void render(SDL_Renderer *) override;
  virtual void update(double dt) override;
  virtual ~TankObject() override;
};

#endif
