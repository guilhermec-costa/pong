#pragma once

#include "shared.hpp"
#include "game_context.hpp"

class GameEntity {
private:
  Vector2   m_position;
  Vector2   m_velocity;
  Dimension m_dimension;
  int       m_direction;
  GameContext* m_ctx;

public:
  GameEntity() = delete;
  GameEntity(GameEntity&) = delete;
  GameEntity(GameContext* ctx): m_ctx(ctx) {};
  GameEntity(Vector2 pos, Vector2 vel) : m_position(pos), m_velocity(vel), m_direction(0) {}
  inline void set_pos(Vector2 pos) { m_position = pos; };
  inline void set_velocity(Vector2 vel) { m_velocity = vel; };
  inline void set_dimension(Dimension dim) { m_dimension = Dimension(dim.get_w(), dim.get_h()); };
  inline void set_direction(int dir) { m_direction = dir; };
  inline Vector2   position() { return m_position; };
  inline Vector2   velocity() { return m_velocity; };
  inline Dimension dimension() { return m_dimension; };
  inline int       direction() { return m_direction; };
  inline GameContext* get_ctx() const { return m_ctx; }

  virtual void update(float dt) = 0;
};