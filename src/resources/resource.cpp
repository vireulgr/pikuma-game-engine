#include "resource.hpp"
#include <iostream>
#include <SDL_image.h>

ImageResource::ImageResource(std::string path)
  : ResourceBase(ResourceType::image, path)
  , m_surface(nullptr) 
{ std::cout << "image resource ctor" << std::endl; }

bool ImageResource::load() {
  std::cout << "image resource load" << std::endl; 
  SDL_Surface * tmpSurface = IMG_Load(m_path.c_str());
  if (NULL == tmpSurface) {
    std::cerr << "error loading tank texture" << std::endl;
    std::cerr << SDL_GetError() << std::endl;
    return false;
  }
  std::cout << "image resource after img load" << std::endl; 
  std::cout << tmpSurface << std::endl; 
  m_surface = tmpSurface;
  return true;
}

SDL_Texture * ImageResource::getTexture(SDL_Renderer * renderer) {
  return SDL_CreateTextureFromSurface(renderer, m_surface);
}

void ImageResource::dispose() {
  SDL_FreeSurface(m_surface);
  m_surface = nullptr;
}

ImageResource::~ImageResource() {
  if (nullptr != m_surface) {
    dispose();
  }
}
