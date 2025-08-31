#pragma once

#include "game_entity.hpp"

#include <memory>

enum PaddleSide {
  LEFT,
  RIGHT,
};

class PaddleController;

class PaddleEntity : public GameEntity {
private:
  std::unique_ptr<PaddleController> m_controller;

public:
  PaddleEntity(const char* id, std::unique_ptr<PaddleController> controller, GameContext* ctx);
  void        update(float dt) override;
  void        render() override;
  inline void set_side(PaddleSide s) { side = s; }

public:
  PaddleSide side;
  int score = 0;
};

class PaddleController {
public:
  PaddleController() {};
  virtual ~PaddleController()                         = default;
  virtual void update(PaddleEntity& paddle, float dt) = 0;
};

class LeftPaddleController : public PaddleController {
  void update(PaddleEntity& paddle, float dt) override;
};

class RightPaddleController : public PaddleController {
  void update(PaddleEntity& paddle, float dt) override;
};