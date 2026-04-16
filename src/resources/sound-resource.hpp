#ifndef __SOUND_RESOURCE_HPP__
#define __SOUND_RESOURCE_HPP__
#include "resource.hpp"
#include <string>

struct MIX_Audio;

struct SoundResource : public ResourceBase {
protected:
  MIX_Audio * m_audio;
public:
  explicit SoundResource(std::string path);
  virtual ~SoundResource() override;
  virtual bool load() override;
  virtual void dispose() override;
};
#endif
