#pragma once

#include "game_context.hpp"
#include "shared.hpp"

class GameEntity {
private:
  const char*  m_id;
  GameContext* m_ctx;

public:
  GameEntity()            = delete;
  GameEntity(GameEntity&) = delete;
  GameEntity(const char* id, GameContext* ctx) : m_id(id), m_ctx(ctx) {};
  GameEntity(Vector2 pos, Vector2 vel) : position(pos), velocity(vel), direction(0) {}
  inline GameContext* get_ctx() const { return m_ctx; }

  virtual void update(float dt) = 0;

public:
  Vector2      position;
  Vector2      velocity;
  Dimension    dimension;
  int          direction;

};