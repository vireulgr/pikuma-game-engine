#include "simple-object.hpp"
#include <SDL_render.h>
#include "../resources/resource-manager.hpp"
#include "../resources/image-resource.hpp"
#include <iostream>

BaseObject::~BaseObject() {}

bool TankObject::initialize(ResourceManager * resMan, SDL_Renderer * renderer) {
  m_posx = 40;
  m_posy = 90;
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
  destRect.x = m_posx;
  destRect.y = m_posy;
  destRect.h = 32;
  destRect.w = 32;

  SDL_RenderCopy(renderer, m_texture, nullptr, &destRect);
}

void TankObject::update() {
}

TankObject::~TankObject() {}
