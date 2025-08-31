#pragma once

#include "game_entity.hpp"
#include "paddle_entity.hpp"

class BallEntity : public GameEntity {
private:
  PaddleEntity* right_paddle;
  PaddleEntity* left_paddle;

public:
  BallEntity(const char* id, GameContext* ctx);
  inline void set_left_paddle(PaddleEntity* paddle) { left_paddle = paddle; };
  inline void set_right_paddle(PaddleEntity* paddle) { right_paddle = paddle; };
  void        update(float dt) override;
  void        render() override;
  void        reset(float current_direction);
};