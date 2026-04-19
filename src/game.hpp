#ifndef __GAME_H__
#define __GAME_H__
#include <memory>
#include <vector>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
class BaseObject;

class Game {
public:
  Game(int argc, char * argv[]);
  ~Game();
  bool initialize();
  void run();
  void dispose();

  int windowWidth;
  int windowHeight;

protected:
  int color;
  bool isRunning;
  int millisecsPrevFrame;

  std::vector<std::shared_ptr<BaseObject>> m_objects;

  SDL_Window * m_window;
  SDL_Renderer * m_renderer;

  void processEvents();
  void update();
  void render();
};
#endif
