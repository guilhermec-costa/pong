#include "../include/ball_entity.hpp"

BallEntity::BallEntity(const char* id, GameContext* ctx) : GameEntity(id, ctx) {
  reset(1.0f);
};

void BallEntity::update(float dt) {
  auto window = get_ctx()->window();

  position.x += velocity.x * direction * dt;
  position.y += velocity.y * direction * dt;

  if (position.y < 5 || position.y + dimension.get_h() >= window->get_height() - 5) {
    velocity.y *= -1;
  }

  if (position.x <= 2 || position.x >= window->get_width() - 2) {
    left_paddle->reset();
    right_paddle->reset();

    if (direction == -1) {
      right_paddle->score();
    } else {
      left_paddle->score();
    }
    reset(-direction);
  }

  auto check_collision = [&](PaddleEntity* paddle, bool invert_x = false) {
    Vector2&   paddle_pos = paddle->get_position();
    Dimension& paddle_dim = paddle->get_dimension();

    if (position.x <= paddle_pos.x + paddle_dim.get_w() && position.x >= paddle_pos.x &&
        position.y + dimension.get_h() >= paddle_pos.y &&
        position.y <= paddle_pos.y + paddle_dim.get_h()) {

      float hit_pos =
          (position.y + dimension.get_h() / 2.0f) - (paddle_pos.y + paddle_dim.get_h() / 2.0f);
      float normalized_hit_pos = hit_pos / (paddle_dim.get_h() / 2.0f);
      float MAX_BOUNCE_ANGLE   = 50.0f * (M_PI / 180.0f);

      float bounce_angle = normalized_hit_pos * MAX_BOUNCE_ANGLE;
      float speed        = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));

      velocity.x = cos(bounce_angle) * speed;
      velocity.y = sin(bounce_angle) * speed;

      if (direction == 1) {
        position.x = paddle_pos.x - 1;
      } else {
        position.x = paddle_pos.x + paddle_dim.get_w() + 1;
      }
      direction *= -1;
    }
  };

  check_collision(left_paddle, false);
  check_collision(right_paddle, true);
}

void BallEntity::render() {
  SDL_Renderer* renderer = get_ctx()->renderer();
  SDL_Rect      ball     = {(int)position.x, (int)position.y, (int)dimension.get_w(),
                            (int)dimension.get_h()};
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderFillRect(renderer, &ball);
}

void BallEntity::reset(float new_direction) {
  auto window = this->get_ctx()->window();
  position.x  = window->get_width() / 2.0f;
  position.y  = window->get_height() / 2.0f;
  velocity.y  = 500.0f;
  velocity.x  = 500.0f;
  direction   = new_direction;
}