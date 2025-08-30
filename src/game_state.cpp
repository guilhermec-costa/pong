#include "../include/game_state.hpp"
#include "../include/game_window.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdexcept>

GameState::GameState() {}

void GameState::create_window(int window_width, int window_height) {
  m_window = GameWindow(window_width, window_height);
}

void GameState::create_renderer() {
  SDL_Renderer* renderer = SDL_CreateRenderer(m_window.window(), 0, SDL_RENDERER_ACCELERATED);
  if(!renderer) {
    std::runtime_error("Failed to create renderer");
  }
  m_renderer = renderer;
}

int GameState::init_resources() {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    return -1;
  }
  return 0;
}

GameWindow GameState::window() {
  return m_window;
}

SDL_Renderer* GameState::renderer() {
  return m_renderer;
}

GameState::~GameState() {
  SDL_DestroyRenderer(m_renderer);
  SDL_Quit();
}