#ifndef __GAME_H__
#define __GAME_H__

class Game {
public:
  Game();
  ~Game();
  void initialize();
  void run();
  void dispose();

protected:
  void processEvents();
  void update();
  void render();
};
#endif
