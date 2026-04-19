#include "game.hpp"
#include <iostream>
#include <memory>
#include "SDL.h"
#include "SDL_timer.h"
#include "resources/resource-manager.hpp"
#include "objects/simple-object.hpp"

#ifdef FIXED_FRAME_RATE
int const FPS = 30;
int const MILLISEC_PER_FRAME = 1000./FPS;
#endif

Game::Game(int argc, char * argv[]) {
  if (argc >= 1) {
    puts(argv[0]);
  }

  windowWidth = 800;
  windowHeight = 600;
}

Game::~Game() {}

bool Game::initialize() {

  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    std::cerr << "error initializing SDL" << std::endl;
    return false;
  }

#ifdef FAKE_FULLSCREEN
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = displayMode.w;
    windowHeight = displayMode.h;
#endif

  m_window = SDL_CreateWindow(
      NULL,
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      windowWidth,
      windowHeight,
      SDL_WINDOW_BORDERLESS);

  if (!m_window) {
    std::cerr << "error creating window" << std::endl;
    return false;
  }
  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!m_renderer) {
    std::cerr << "error creating renderer" << std::endl;
    return false;
  }
  ResourceManager * resMan = new ResourceManager();

  std::shared_ptr<TankObject> tankObject = std::make_shared<TankObject>();
  m_objects.push_back(tankObject);

  for (auto ptr : m_objects) {
    ptr->initialize(resMan, m_renderer);
  }

  delete resMan;

#ifndef FAKE_FULLSCREEN
  SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
#endif

  return true;
}

void Game::run() {
  isRunning = true;
  millisecsPrevFrame = SDL_GetTicks();
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
  double deltaTime = (SDL_GetTicks() - millisecsPrevFrame) / 1000.0;
#ifdef FIXED_FRAME_RATE
  unsigned int timeToWait = MILLISEC_PER_FRAME - (SDL_GetTicks() - millisecsPrevFrame);
  if (timeToWait <= MILLISEC_PER_FRAME) {
    SDL_Delay(timeToWait);
  }
#endif

  // std::cout << "dt: " << deltaTime << std::endl;
  for (auto obj : m_objects) {
    obj->update(deltaTime);
  }
  millisecsPrevFrame = SDL_GetTicks();
}

void Game::render() {
  SDL_SetRenderDrawColor(m_renderer, 31, 31, 31, 255);
  SDL_RenderClear(m_renderer);

  //SDL_SetRenderDrawColor(m_renderer, 31, 250, 250, 255);
  //SDL_Rect rect = { 380, 280, 40, 40};
  //SDL_RenderFillRect(m_renderer, &rect);

  for (auto obj : m_objects) {
    obj->render(m_renderer);
  }

  SDL_RenderPresent(m_renderer);
}
