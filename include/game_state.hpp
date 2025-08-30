#pragma once

#include "game_window.hpp"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

class GameState {

private:
  GameWindow    m_window;
  SDL_Renderer* m_renderer;
  bool          m_running;

public:
  GameState(int window_width, int window_height);
  ~GameState();
  GameState(GameState&) = delete;
  void          create_window(int window_width, int window_height);
  void          create_renderer();
  int           init_resources();
  void          handle_events();
  void          update();
  void          render();
  GameWindow&   window();
  SDL_Renderer* renderer();
  bool          is_running();
  inline void stop() {
    m_running = false;
  }
};