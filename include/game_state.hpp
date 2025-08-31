#pragma once

#include "game_entity.hpp"
#include "game_window.hpp"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <string>
#include <vector>

class GameState {

private:
  GameWindow               m_window;
  SDL_Renderer*            m_renderer;
  bool                     m_running;
  SDL_Event                m_event;
  std::vector<GameEntity*> m_entities;
  TTF_Font*                m_font;
  SDL_Texture*             m_text_texture = nullptr;
  SDL_Rect                 m_text_rect;

public:
  GameState(int window_width, int window_height);
  ~GameState();
  GameState(GameState&) = delete;
  void          create_window(int window_width, int window_height);
  void          create_renderer();
  int           init_resources();
  void          handle_events();
  void          update(float dt);
  void          render();
  GameWindow&   window();
  SDL_Renderer* renderer();
  bool          is_running();
  inline void   stop() { m_running = false; }
  void          add_entity(GameEntity* entity);
  void          init_text(const std::string& str, int x, int y);
};