#include "game.hpp"

int main(int argc, char * argv []) {
  Game game;
  game.initialize();
  game.run();
  game.dispose();
  return 0;
}
