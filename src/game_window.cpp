#include "../include/game_window.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdexcept>

GameWindow::GameWindow() {}

GameWindow::GameWindow(int width, int height): m_width(width), m_height(height) {
  SDL_Window* window = SDL_CreateWindow("My game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  if(!window) {
    std::runtime_error("Failed to create window");
  }
  m_window = window;
};

SDL_Window* GameWindow::window() {
  return m_window;
}

int GameWindow::get_width() {
  return m_width;
}

int GameWindow::get_height() {
  return m_height;
}

GameWindow::~GameWindow() {
  SDL_DestroyWindow(m_window);
}