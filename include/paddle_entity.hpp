#include "game_entity.hpp"

#include <memory>

class PaddleController;

class PaddleEntity : public GameEntity {
private:
  std::unique_ptr<PaddleController> m_controller;

public:
  PaddleEntity(std::unique_ptr<PaddleController> controller, GameContext* ctx);
  void update(float dt) override;
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