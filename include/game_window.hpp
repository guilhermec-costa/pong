#pragma once

#include <SDL2/SDL_video.h>

class GameWindow {
private:
  int m_width;
  int m_height;

public:
  SDL_Window* m_window;
  GameWindow();
  GameWindow(int width, int height);
  ~GameWindow();

  int get_width();
  int get_height();
  SDL_Window* window();
};