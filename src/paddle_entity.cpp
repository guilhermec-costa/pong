#include "../include/paddle_entity.hpp"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <string>

PaddleEntity::PaddleEntity(const char* id, std::unique_ptr<PaddleController> controller,
                           PaddleSide side, GameContext* ctx)
    : GameEntity(id, ctx), m_controller(std::move(controller)), side(side) {
  reset();
#ifdef PROJECT_SOURCE_DIR
  std::string font_path = std::string(PROJECT_SOURCE_DIR) + "/assets/fonts/OpenSans-Regular.ttf";
  m_font                = TTF_OpenFont(font_path.c_str(), 12);
  if (m_font == nullptr) {
    std::cerr << "SDL TTF Error: " << TTF_GetError() << std::endl;
    throw std::runtime_error("Failed to create font");
  }
#else
#error "PROJECT_SOURCE_DIR not defined. Cannot locate assets/fonts/OpenSans-Regular.ttf"
#endif
  increment_score_text();
}

void PaddleEntity::update(float dt) {
  m_controller->update(*this, dt);
}

void RightPaddleController::update(PaddleEntity& paddle, float dt) {
  Vector2&   pos = paddle.get_position();
  Dimension& dim = paddle.get_dimension();
  int&       dir = paddle.get_direction();

  if (pos.y < 10 || pos.y + dim.get_h() >= paddle.get_ctx()->window()->get_height() - 10) {
    paddle.get_direction() *= -1;
  }

  pos.y += paddle.get_velocity().y * paddle.get_direction() * dt;
}

void LeftPaddleController::update(PaddleEntity& paddle, float dt) {
  Vector2&   pos = paddle.get_position();
  Dimension& dim = paddle.get_dimension();
  int&       dir = paddle.get_direction();

  if (pos.y <= 2 || pos.y + dim.get_h() >= paddle.get_ctx()->window()->get_height() - 2) {
    paddle.get_direction() *= -1;
  }

  pos.y += paddle.get_velocity().y * paddle.get_direction() * dt;
}

void PaddleEntity::render() {
  SDL_Renderer* renderer = get_ctx()->renderer();
  if (m_text_texture) {
    SDL_RenderCopy(renderer, m_text_texture, nullptr, &m_score_rect);
  }
  SDL_Rect rect = {(int)position.x, (int)position.y, (int)dimension.get_w(),
                   (int)dimension.get_h()};
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &rect);
}

void PaddleEntity::increment_score_text() {
  const auto window = get_ctx()->window();
  if (m_text_texture) {
    SDL_DestroyTexture(m_text_texture);
  }
  SDL_Surface* sfc = TTF_RenderText_Blended(m_font, std::to_string(m_score).c_str(), {255, 255, 255});
  m_text_texture   = SDL_CreateTextureFromSurface(get_ctx()->renderer(), sfc);
  if (!m_text_texture) {
    std::cerr << "Failed to initiate font texture: " << TTF_GetError() << std::endl;
    throw std::runtime_error("Error initiating font");
  }
  if (side == PaddleSide::LEFT) {
    m_score_rect = {window->get_width() / 4, 100, 80, 80};
  } else {
    m_score_rect = {window->get_width() / 4 * 3, 100, 80, 80};
  }
  SDL_FreeSurface(sfc);
}

PaddleEntity::~PaddleEntity() {
  if (m_text_texture) {
    SDL_DestroyTexture(m_text_texture);
  }
}

void PaddleEntity::reset() {
  const auto window = get_ctx()->window();
  velocity          = Vector2({0.0f, 780.0f});
  dimension         = Dimension({25.0f, 180.0f});

  if (side == PaddleSide::LEFT) {
    position  = Vector2({20, (window->get_height() / 2.0f) - dimension.get_h()});
    direction = -1;
  } else {
    position  = Vector2({window->get_width() - 20 - dimension.get_w(),
                         (window->get_height() / 2.0f) - dimension.get_h()});
    direction = 1;
  }
}

void PaddleEntity::score() {
  increment_score();
  increment_score_text();
}