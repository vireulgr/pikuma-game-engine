#include "font-resource.hpp"
#include <SDL_ttf.h>
#include <iostream>

FontResource::FontResource(std::string path)
  : ResourceBase(ResourceType::font, path)
  , m_font(nullptr) 
{
  std::cout << "font ctor NOT IMPLEMENTED YET!" << std::endl;
}

bool FontResource::load() {
  std::cout << "NOT IMPLEMENTED YET!" << std::endl; 
  return true;
}

void FontResource::dispose() {
  TTF_CloseFont(m_font);
  m_font = nullptr;
}

FontResource::~FontResource() {
  if (nullptr != m_font) {
    dispose();
  }
}
