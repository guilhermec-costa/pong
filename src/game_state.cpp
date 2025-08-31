#include "../include/game_state.hpp"

#include "../include/game_window.hpp"
#include "../include/paddle_entity.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <stdexcept>

GameState::GameState(int window_width, int window_height)
    : m_window(window_width, window_height), m_running(true) {
  m_event = SDL_Event();
  create_renderer();
  if (init_resources() < 0) {
    throw std::runtime_error("Failed to initiate resources");
  };
}

void GameState::create_renderer() {
  SDL_Window* w = m_window.window();
  if (!w) {
    throw std::runtime_error("Window not initialized");
  }
  m_renderer = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
  if (!m_renderer) {
    std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
    throw std::runtime_error("Failed to create renderer");
  }
}

int GameState::init_resources() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    return -1;
  }
  if (TTF_Init() < 0) {
    return -1;
  }
  return 0;
}

GameWindow& GameState::window() {
  return m_window;
}

SDL_Renderer* GameState::renderer() {
  return m_renderer;
}

GameState::~GameState() {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window.window());
  SDL_Quit();
}

bool GameState::is_running() {
  return m_running;
}

void GameState::update(float dt) {
  for (auto entity : m_entities) {
    entity->update(dt);
  }
}

void GameState::handle_events() {
  while (SDL_PollEvent(&m_event)) {
    switch (m_event.type) {
      case SDL_QUIT: {
        std::cout << "Quitting \n";
        stop();
        break;
      }

      case SDL_KEYDOWN: {
        for (auto entity : m_entities) {
          if (auto paddle = dynamic_cast<PaddleEntity*>(entity)) {
            if (paddle->side == PaddleSide::RIGHT) {
              if (m_event.key.keysym.sym == SDLK_UP) {
                paddle->direction = -1;
              }
              if (m_event.key.keysym.sym == SDLK_DOWN) {
                paddle->direction = 1;
              }
            } else {
              if (m_event.key.keysym.sym == SDLK_w)
                paddle->direction = -1;
              if (m_event.key.keysym.sym == SDLK_s)
                paddle->direction = 1;
            }
          }
        }
        break;
      }
    }
  }
}

void GameState::add_entity(GameEntity* entity) {
  m_entities.push_back(entity);
}

void GameState::render() {
  const int win_height = m_window.get_height();
  const int win_width  = m_window.get_width();
  const int rect_w     = 6;
  const int rect_h     = 40;
  const int gap        = 10;

  std::vector<SDL_Rect> rects;
  int                   y = 10;
  while (y + rect_h <= win_height) {
    rects.push_back({(win_width / 2) - (rect_w / 2), y, rect_w, rect_h});
    y += rect_h + gap;
  }

  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
  SDL_RenderClear(m_renderer);
  SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
  for (const auto& r : rects) {
    SDL_RenderFillRect(m_renderer, &r);
  }
  for (auto entity : m_entities) {
    entity->render();
  }
  SDL_RenderPresent(m_renderer);
}