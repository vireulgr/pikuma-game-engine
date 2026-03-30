#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>


int main(int argc, char * argv []) {
  sol::state lua;
  lua.open_libraries(sol::lib::base);

  glm::vec2 velocity = glm::vec2(2.3, 12.3);
  printf("speed is %f, %f", velocity.x, velocity.y);

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Quit();
  return 0;
}
