#include "sound-resource.hpp"

SoundResource::SoundResource(std::string path)
  : ResourceBase(ResourceType::sound, path)
  , m_audio(nullptr)
{
}

SoundResource::~SoundResource() {
}

bool SoundResource::load() {
  return true;
}

void SoundResource::dispose() {
}
