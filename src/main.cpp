#include "game.hpp"

int main(int argc, char * argv []) {
  Game game(argc, argv);
  game.initialize();
  game.run();
  game.dispose();
  return 0;
}
