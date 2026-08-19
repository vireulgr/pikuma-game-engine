#ifndef __RENDERING_SYSTEM_H__
#define __RENDERING_SYSTEM_H__
#include "../ECS/ECS.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "SDL_rect.h"
#include "SDL_render.h"

class RenderSystem : public System {
  SDL_Renderer * renderer = nullptr;
  public:
    RenderSystem(SDL_Renderer * _renderer) 
      : System() 
      , renderer(_renderer)
    {
      RequireComponent<SpriteComponent>();
      RequireComponent<TransformComponent>();
    }

    void render() {
      for (auto entity: GetSystemEntities()) {
        TransformComponent& transform = entity.getComponent<TransformComponent>();
        SpriteComponent& sprite = entity.getComponent<SpriteComponent>();
        SDL_Rect a;
        a.x = static_cast<int>(transform.position.x);
        a.y = static_cast<int>(transform.position.y);
        a.w = sprite.width;
        a.h = sprite.height;

        SDL_SetRenderDrawColor(renderer, 255, 20, 10, 255);
        SDL_RenderFillRect(renderer, &a);
      }
    }
};

#endif
