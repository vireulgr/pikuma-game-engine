#ifndef __ASSET_STORE_H__
#define __ASSET_STORE_H__
#include "SDL_render.h"
#include <string>
#include <map>

class AssetStore {
  private:
    std::map<std::string, SDL_Texture*> textures;

  public:
    AssetStore();
    ~AssetStore();

    void clearAssets();
    void addTexture(SDL_Renderer* r, std::string const & assetId, std::string const & path);
    SDL_Texture* getTexture(std::string const & id);
};

#endif
