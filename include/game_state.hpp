#pragma once

#include "game_window.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

class GameState {

private:
  GameWindow m_window;
  SDL_Renderer* m_renderer;
public:
  GameState();
  ~GameState();
  GameState(GameState&) = delete;
  void create_window(int window_width, int window_height);
  void create_renderer();
  int init_resources();
  GameWindow window();
  SDL_Renderer* renderer();
};