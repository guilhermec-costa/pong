#pragma once

#include <SDL2/SDL_video.h>

class GameWindow {
private:
  int         m_width;
  int         m_height;
  SDL_Window* m_window;

public:
  GameWindow();
  GameWindow(int width, int height);
  GameWindow(const GameWindow&)            = delete;
  GameWindow& operator=(const GameWindow&) = delete;

  int         get_width();
  int         get_height();
  SDL_Window* window();
};