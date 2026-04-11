#ifndef __GAME_H__
#define __GAME_H__

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class Game {
public:
  Game(int argc, char * argv[]);
  ~Game();
  bool initialize();
  void run();
  void dispose();

  int windowWidth;
  int windowHeight;

  SDL_Texture * tigerTankTxt;

protected:
  bool fakeFullscreen;
  int color;
  bool isRunning;
  SDL_Window * m_window;
  SDL_Renderer * m_renderer;
  void processEvents();
  void update();
  void render();
};
#endif
