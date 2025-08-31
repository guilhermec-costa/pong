#pragma once

#include "game_window.hpp"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

class GameContext {
private:
  GameWindow*   m_window   = nullptr;
  SDL_Renderer* m_renderer = nullptr;
  TTF_Font*     font       = nullptr;

public:
  GameContext(GameContext&) = delete;
  GameContext() : m_window(nullptr), m_renderer(nullptr) {};
  GameContext(GameWindow* window, SDL_Renderer* renderer)
      : m_window(window), m_renderer(renderer) {};
  inline GameWindow*   window() const { return m_window; }
  inline SDL_Renderer* renderer() const { return m_renderer; }
};