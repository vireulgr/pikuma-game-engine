#include "game.hpp"
#include <iostream>
#include "SDL.h"
#include "SDL_render.h"
#include "SDL_video.h"

Game::Game(int argc, char * argv[]) {
  if (argc >= 1) {
    puts(argv[0]);
  }
}

Game::~Game() {
}

void Game::initialize() {
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    std::cerr << "error initializing SDL" << std::endl;
    return;
  }
  int width = 800;
  int height = 600;
  m_window = SDL_CreateWindow(
      NULL,
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      width,
      height,
      SDL_WINDOW_BORDERLESS);

  if (!m_window) {
    std::cerr << "error creating window" << std::endl;
    return;
  }
  m_renderer = SDL_CreateRenderer(m_window, -1, 0);
  if (!m_window) {
    std::cerr << "error creating renderer" << std::endl;
    return;
  }
}

void Game::run() {
  isRunning = true;
  while (isRunning) {
    processEvents();
    update();
    render();
  }
}

void Game::dispose() {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void Game::processEvents() {
  SDL_Event evt;
  SDL_PollEvent(&evt);
  switch (evt.type) {
    case SDL_QUIT: break;
    case SDL_KEYDOWN:
       if (evt.key.keysym.sym == SDLK_ESCAPE) {
         this->isRunning = false;
       }
     break;
    default: break;
  }
}

void Game::update() {
}

void Game::render() {
  SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
  SDL_RenderClear(m_renderer);
  SDL_RenderPresent(m_renderer);
}
