#include "game.hpp"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

Game::Game(int argc, char * argv[]) {
  if (argc >= 1) {
    puts(argv[0]);
  }
  // TODO
  fakeFullscreen = false;
  windowWidth = 800;
  windowHeight = 600;
}

Game::~Game() {
}

bool Game::initialize() {

  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    std::cerr << "error initializing SDL" << std::endl;
    return false;
  }

  if (fakeFullscreen) {
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = displayMode.w;
    windowHeight = displayMode.h;
  }

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
  if (!m_window) {
    std::cerr << "error creating renderer" << std::endl;
    return false;
  }

  SDL_Surface * tmpSurface = IMG_Load("./assets/images/tank-tiger-right.png");
  if (NULL == tmpSurface) {
    std::cerr << "error loading tank texture" << std::endl;
    std::cerr << SDL_GetError() << std::endl;
    return false;
  }
  tigerTankTxt = SDL_CreateTextureFromSurface(m_renderer, tmpSurface);
  SDL_FreeSurface(tmpSurface);

  if (NULL == tigerTankTxt) {
    std::cerr << "error loading tank texture" << std::endl;
    std::cerr << SDL_GetError() << std::endl;
    return false;
  }


  if (!fakeFullscreen) {
    SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
  }

  return true;
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
  SDL_SetRenderDrawColor(m_renderer, 31, 31, 31, 255);
  SDL_RenderClear(m_renderer);

  SDL_SetRenderDrawColor(m_renderer, 31, 250, 250, 255);
  SDL_Rect rect = { 380, 280, 40, 40};
  SDL_RenderFillRect(m_renderer, &rect);


  SDL_Rect destRect = { 20, 20, 32, 32 };
  SDL_RenderCopy(m_renderer, tigerTankTxt, /*srcRect*/NULL, &destRect);

  SDL_RenderPresent(m_renderer);
}
