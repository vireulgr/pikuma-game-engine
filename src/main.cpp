#include "game.hpp"
// #include <cstdlib>

int main(int argc, char * argv []) {
  // system("dir");
  Game game(argc, argv);
  if (!game.initialize()) {
    return 0;
  }
  game.run();
  game.dispose();
  return 0;
}

