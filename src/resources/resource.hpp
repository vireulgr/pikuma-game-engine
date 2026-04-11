#ifndef __RESOURCE_H__
#define __RESOURCE_H__
#include <string>

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

enum ResourceType {
  image,
  sound,
  font
};

struct Resource {
  virtual bool load() = 0;
  virtual void dispose() = 0;
  virtual ~Resource() {};
};

struct ResourceBase : public Resource {
  ResourceBase(ResourceType type, std::string path) {
    m_type = type;
    m_path = path;
  }
  virtual ~ResourceBase() override {}
protected:
  std::string m_path;
  ResourceType m_type;
};

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
