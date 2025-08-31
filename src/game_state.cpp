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
  m_renderer = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
  #ifdef PROJECT_SOURCE_DIR
    std::string font_path = std::string(PROJECT_SOURCE_DIR) + "/assets/fonts/OpenSans-Regular.ttf";
    m_font = TTF_OpenFont(font_path.c_str(), 12);
    std::cout << "Font: " << m_font << "\n";
    if (m_font == nullptr) {
      std::cerr << "SDL TTF Error: " << TTF_GetError() << std::endl;
      throw std::runtime_error("Failed to create font");
      return -1;
    }
    init_text("Testing text", 100, 100);
  #else
    #error "PROJECT_SOURCE_DIR not defined. Cannot locate assets/fonts/OpenSans-Regular.ttf"
  #endif
  return 0;
}

GameWindow& GameState::window() {
  return m_window;
}

SDL_Renderer* GameState::renderer() {
  return m_renderer;
}

GameState::~GameState() {
  if (m_text_texture) {
    SDL_DestroyTexture(m_text_texture);
  }
  if(m_font) {
    TTF_CloseFont(m_font);
  }
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

void GameState::init_text(const std::string& str, int x, int y) {
  SDL_Surface* sfc = TTF_RenderText_Solid(m_font, str.c_str(), {255, 255, 255});
  m_text_texture   = SDL_CreateTextureFromSurface(m_renderer, sfc);
  if(!m_text_texture) {
    std::cerr << "Failed to initiate font texture: " << TTF_GetError() << std::endl;
    throw std::runtime_error("Error initiating font");
  }
  m_text_rect      = {x, y, 100, 100};
  SDL_FreeSurface(sfc);
}

void GameState::render() {
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
  SDL_RenderClear(m_renderer);
  if (m_text_texture) {
    SDL_RenderCopy(m_renderer, m_text_texture, nullptr, &m_text_rect);
  }
  for (auto entity : m_entities) {
    entity->render();
  }
  SDL_RenderPresent(m_renderer);
}