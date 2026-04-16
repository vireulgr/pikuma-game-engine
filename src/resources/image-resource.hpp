#ifndef __IMAGE_RESOURCE_HPP__
#define __IMAGE_RESOURCE_HPP__
#include <string>
#include "resource.hpp"

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

struct ImageResource : public ResourceBase {
protected:
  SDL_Surface * m_surface;
public:
  explicit ImageResource(std::string path);
  virtual ~ImageResource() override;
  virtual bool load() override;
  virtual void dispose() override;

  SDL_Texture * getTexture(SDL_Renderer* renderer);
};
#endif
