#include "AssetStore.hpp"
#include "../logger/logger.hpp"
#include "SDL_error.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "SDL_surface.h"

AssetStore::AssetStore() {
  Logger::Log("Asset store ctor called");
}
AssetStore::~AssetStore() {
  Logger::Log("Asset store dtor called");
  clearAssets();
}


void AssetStore::clearAssets() {
  Logger::Log("Asset store clear");
  for (auto const & pair : textures) {
    SDL_DestroyTexture(pair.second);
  }
  textures.clear();
}

void AssetStore::addTexture(SDL_Renderer * renderer, std::string const & assetId, std::string const & path) {
  Logger::Log("Asset store add texture " + assetId);
  SDL_Surface * tmpSurface = IMG_Load(path.c_str());
  if (NULL == tmpSurface) {
    Logger::Error("Error loading tank texture");
    Logger::Error(SDL_GetError());
    return;
  }

  SDL_Texture * tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
  SDL_FreeSurface(tmpSurface);

  //textures[assetId] = tex;
  textures.emplace(assetId, tex);
}

SDL_Texture* AssetStore::getTexture(std::string const & id) {
  return textures[id];
}
