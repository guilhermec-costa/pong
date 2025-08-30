#include "../include/paddle_entity.hpp"

PaddleEntity::PaddleEntity(const char* id, std::unique_ptr<PaddleController> controller,
                           GameContext* ctx)
    : GameEntity(id, ctx), m_controller(std::move(controller)) {}

void PaddleEntity::update(float dt) {
  m_controller->update(*this, dt);
}

void RightPaddleController::update(PaddleEntity& paddle, float dt) {
  Vector2 pos = paddle.position();
  if (pos.y < 0 || pos.y + paddle.dimension().get_h() >= paddle.get_ctx()->window()->get_height()) {
    paddle.set_direction(paddle.direction() * -1);
  };
  pos.y += paddle.velocity().y * paddle.direction();
  paddle.set_pos(pos);
}

void LeftPaddleController::update(PaddleEntity& paddle, float dt) {
  Vector2 pos = paddle.position();
  if (pos.y < 0 || pos.y + paddle.dimension().get_h() >= paddle.get_ctx()->window()->get_height()) {
    paddle.set_direction(paddle.direction() * -1);
  };
  pos.y += paddle.velocity().y * paddle.direction();
  paddle.set_pos(pos);
}