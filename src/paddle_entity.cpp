#include "../include/paddle_entity.hpp"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

PaddleEntity::PaddleEntity(const char* id, std::unique_ptr<PaddleController> controller,
                           GameContext* ctx)
    : GameEntity(id, ctx), m_controller(std::move(controller)) {}

void PaddleEntity::update(float dt) {
  m_controller->update(*this, dt);
}

void RightPaddleController::update(PaddleEntity& paddle, float dt) {
    Vector2& pos = paddle.get_position();  // referência direta
    Dimension& dim = paddle.get_dimension();
    int& dir = paddle.get_direction();

    if (pos.y < 10 || pos.y + dim.get_h() >= paddle.get_ctx()->window()->get_height() - 10) {
        paddle.get_direction() = -dir;
    }

    pos.y += paddle.get_velocity().y * paddle.get_direction() * dt;
}

void LeftPaddleController::update(PaddleEntity& paddle, float dt) {
    Vector2& pos = paddle.get_position();
    Dimension& dim = paddle.get_dimension();
    int& dir = paddle.get_direction();

    if (pos.y < 10 || pos.y + dim.get_h() >= paddle.get_ctx()->window()->get_height() - 10) {
        paddle.get_direction() = -dir;
    }

    pos.y += paddle.get_velocity().y * paddle.get_direction() * dt;
}


void PaddleEntity::render() {
  SDL_Renderer* renderer = get_ctx()->renderer();
  SDL_Rect      rect     = {(int)position.x, (int)position.y, (int)dimension.get_w(),
                            (int)dimension.get_h()};
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &rect);
}