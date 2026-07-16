#include "game/game.hpp"

int main(int argc, char * argv []) {
  Game game(argc, argv);
  if (!game.initialize()) {
    return 0;
  }
  game.run();
  game.dispose();
  return 0;
}

