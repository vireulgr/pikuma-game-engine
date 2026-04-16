#ifndef __FONT_RESOURCE_HPP__
#define __FONT_RESOURCE_HPP__
#include <string>
#include "resource.hpp"

struct _TTF_Font;

struct FontResource : public ResourceBase {
protected:
  _TTF_Font * m_font;
public:
  explicit FontResource(std::string path);
  virtual ~FontResource() override;
  virtual bool load() override;
  virtual void dispose() override;
};
#endif
