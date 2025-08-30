#pragma once

#include "game_window.hpp"

class GameContext {
private:
  GameWindow* m_window;

public:
  GameContext(GameContext&) = delete;
  GameContext() : m_window(nullptr) {};
  GameContext(GameWindow* window) : m_window(window) {};
  inline GameWindow* window() const { return m_window; }
};