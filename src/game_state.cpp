#include "../include/game_state.hpp"
#include "../include/game_window.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <stdexcept>

GameState::GameState(int window_width, int window_height): m_window(window_width, window_height) {
}

void GameState::create_renderer() {
  SDL_Window* w = m_window.window();
  if (!w) {
    throw std::runtime_error("Window not initialized");
  }
  m_renderer = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!m_renderer) {
      std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
      throw std::runtime_error("Failed to create renderer");
  }
}

int GameState::init_resources() {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    return -1;
  }
  return 0;
}

GameWindow& GameState::window() {
  return m_window;
}

SDL_Renderer* GameState::renderer() {
  return m_renderer;
}

GameState::~GameState() {
  SDL_DestroyRenderer(m_renderer);
  SDL_Quit();
}