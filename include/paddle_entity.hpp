#pragma once

#include "game_entity.hpp"

#include <SDL2/SDL_ttf.h>
#include <memory>

enum PaddleSide {
  LEFT,
  RIGHT,
};

class PaddleController;

class PaddleEntity : public GameEntity {
private:
  std::unique_ptr<PaddleController> m_controller;
  SDL_Rect                          m_score_rect;
  TTF_Font*                         m_font = nullptr;

public:
  PaddleEntity(const char* id, std::unique_ptr<PaddleController> controller, PaddleSide side,
               GameContext* ctx);
  ~PaddleEntity();
  void        update(float dt) override;
  void        render() override;
  inline void set_side(PaddleSide s) { side = s; }
  inline void increment_score() { m_score++; };
  void        increment_score_text();
  void        reset();
  void        score();

public:
  SDL_Texture* m_text_texture = nullptr;
  PaddleSide   side;
  int          m_score = 0;
};

class PaddleController {
public:
  PaddleController() {};
  ~PaddleController() = default;
  void update(PaddleEntity& paddle, float dt);
};