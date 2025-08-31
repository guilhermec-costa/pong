#include "../include/game_window.hpp"

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <stdexcept>

GameWindow::GameWindow(int width, int height) : m_width(width), m_height(height) {
  m_window =
      SDL_CreateWindow("My game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  if (!m_window) {
    std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
    throw std::runtime_error("Failed to create window");
  }
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
