#ifndef __GAME_H__
#define __GAME_H__

struct SDL_Window;
struct SDL_Renderer;

class Game {
public:
  Game(int argc, char * argv[]);
  ~Game();
  void initialize();
  void run();
  void dispose();

protected:
  int color;
  bool isRunning;
  SDL_Window * m_window;
  SDL_Renderer * m_renderer;
  void processEvents();
  void update();
  void render();
};
#endif
