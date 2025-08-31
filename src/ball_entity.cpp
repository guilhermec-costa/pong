#include "../include/ball_entity.hpp"

BallEntity::BallEntity(const char* id, GameContext* ctx) : GameEntity(id, ctx) {};

void BallEntity::update(float dt) {
  auto window = get_ctx()->window();
  PaddleEntity* left_paddle = this->left_paddle;
  PaddleEntity* right_paddle = this->right_paddle;
  position.x += velocity.x;
  position.y += velocity.y;

  if (position.y < 0 || position.y + dimension.get_w() >= window->get_height()) {
    velocity.y *= -1;
  }

  if (position.x < 0 || position.x > window->get_width()) {
    position.x     = window->get_width() / 2.0f;
    position.y     = window->get_height() / 2.0f;
    velocity.y = 5.0f;
    velocity.x *= -1;
  }

  if (position.x <= left_paddle->position.x + left_paddle->dimension.get_w() && position.x >= left_paddle->position.x &&
      position.y + dimension.get_w() >= left_paddle->position.y && position.y <= left_paddle->position.y + left_paddle->dimension.get_h()) {
    float hit_pos = (position.y + dimension.get_w() / 2.0f) - (left_paddle->position.y + left_paddle->dimension.get_h() / 2.0f);
    float normalized_hit_pos = hit_pos / (left_paddle->dimension.get_h() / 2.0f);
    float MAX_BOUNCE_ANGLE   = 75.0f * (M_PI / 180.0f);

    float bounce_angle = normalized_hit_pos * MAX_BOUNCE_ANGLE;

    float speed = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
    velocity.x  = cos(bounce_angle) * speed;
    velocity.y  = sin(bounce_angle) * speed;
  }

  if (position.x <= right_paddle->position.x + right_paddle->dimension.get_w() && position.x >= right_paddle->position.x &&
      position.y + dimension.get_w() >= right_paddle->position.y &&  position.y <= right_paddle->position.y + right_paddle->dimension.get_h()) {
    float hit_pos = (position.y + dimension.get_w() / 2.0f) - (right_paddle->position.y + right_paddle->dimension.get_h() / 2.0f);
    float normalized_hit_pos = hit_pos / (right_paddle->dimension.get_h() / 2.0f);
    float MAX_BOUNCE_ANGLE   = 75.0f * (M_PI / 180.0f);

    float bounce_angle = normalized_hit_pos * MAX_BOUNCE_ANGLE;

    float speed = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
    velocity.x  = (cos(bounce_angle) * speed) * -1;
    velocity.y  = sin(bounce_angle) * speed;
  }
}

void BallEntity::render() {
  SDL_Renderer* renderer = get_ctx()->renderer();
  SDL_Rect ball         = {(int)position.x, (int)position.y, (int)dimension.get_w(), (int)dimension.get_h()};
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_RenderFillRect(renderer, &ball);
}