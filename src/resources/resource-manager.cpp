#include "resource-manager.hpp"
#include "image-resource.hpp"
#include "sound-resource.hpp"
#include "font-resource.hpp"
#include "../logger/logger.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstdio>

struct ResourceEntry {
  ResourceType type;
  std::string id;
  std::string path; 
};

ResourceEntry const PATHS_TABLE[] = {
  ResourceEntry{ResourceType::image, std::string("tank-tiger-right"), std::string("./assets/images/tank-tiger-right.png")},
  ResourceEntry{ResourceType::image, std::string("tank-tiger-left"), std::string("./assets/images/tank-tiger-left.png")},
  ResourceEntry{ResourceType::image, std::string("tank-tiger-up"), std::string("./assets/images/tank-tiger-up.png")},
  ResourceEntry{ResourceType::image, std::string("tank-tiger-down"), std::string("./assets/images/tank-tiger-down.png")},
};

ResourceBase * ResourceManager::getResource(std::string id) {
  auto const endIter = std::cend(PATHS_TABLE);
  auto res = std::find_if(std::cbegin(PATHS_TABLE), endIter, [&id](ResourceEntry const & item) {return item.id == id;});
  if (res == endIter) {
    std::cerr << "Resource with id " << id << " not found" << std::endl;
  }
  ResourceBase * tmp = nullptr;
  switch (res->type) {
    case ResourceType::image: {
       tmp = new ImageResource(res->path);
    };
    break;
    case ResourceType::sound: {
      tmp = new SoundResource(res->path);
    };
    break;
    case ResourceType::font: {
      tmp = new FontResource(res->path);
    };
    break;
    default: {
      const size_t bufSize = 100;
      char buf[bufSize] = {};
      errno_t err = sprintf_s(buf, bufSize, "Unknown resource type: %d", res->type);
      if (err == 0) {
        Logger::Error(buf);
      }
    }
  }
  return tmp;
}

