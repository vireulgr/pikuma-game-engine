#include "simple-object.hpp"
#include <SDL_render.h>
#include "../resources/resource-manager.hpp"
#include "../resources/image-resource.hpp"
#include "glm/ext/vector_float2.hpp"
#include <iostream>

BaseObject::~BaseObject() {}

bool TankObject::initialize(ResourceManager * resMan, SDL_Renderer * renderer) {
  m_pos = glm::vec2(20.0, 40.0);
  m_velocity = glm::vec2(12.0, 3.0);
  ImageResource * tankImage = static_cast<ImageResource*>(resMan->getResource("tank-tiger-right"));
  if (tankImage == nullptr) {
    std::cerr << "tank image is null" << std::endl;
    return false;
  }

  if (!tankImage->load()) {
    return false;
  }
  m_texture = tankImage->getTexture(renderer);
  delete tankImage;

  if (NULL == m_texture) {
    std::cerr << "Error loading tank texture" << std::endl;
    std::cerr << SDL_GetError() << std::endl;
    return false;
  }
  return true;
}

void TankObject::render(SDL_Renderer* renderer) {
  SDL_Rect destRect;
  destRect.x = static_cast<int>(m_pos.x);
  destRect.y = static_cast<int>(m_pos.y);
  destRect.h = 32;
  destRect.w = 32;
  // std::cout << "x: " << destRect.x << "; y: " << destRect.y << std::endl;
  SDL_RenderCopy(renderer, m_texture, nullptr, &destRect);
}

void TankObject::update(double dt) {
  m_pos.x += m_velocity.x * dt;
  m_pos.y += m_velocity.y * dt;
}

TankObject::~TankObject() {}
