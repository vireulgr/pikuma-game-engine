#include "game.hpp"

Game::Game() {
}

Game::~Game() {
}

void Game::initialize() {
}

void Game::run() {
  while (true) {
    processEvents();
    update();
    render();
  }
}

void Game::dispose() {
}

void Game::processEvents() {
}

void Game::update() {
}

void Game::render() {
}
