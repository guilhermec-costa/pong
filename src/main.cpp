#include "../include/ball_entity.hpp"
#include "../include/game_context.hpp"
#include "../include/game_state.hpp"
#include "../include/paddle_entity.hpp"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <memory>

int main() {
  GameState game_state(1440, 900);
  SDL_Renderer* renderer = game_state.renderer();

  GameContext ctx(&game_state.window(), renderer);
  const int   WINDOW_HEIGHT = game_state.window().get_height();
  const int   WINDOW_WIDTH  = game_state.window().get_width();

  PaddleEntity right_paddle("right_paddle", std::make_unique<RightPaddleController>(), &ctx);
  right_paddle.set_side(PaddleSide::RIGHT);
  right_paddle.velocity  = Vector2({0.0f, 500.0f});
  right_paddle.dimension = Dimension({25.0f, 180.0f});
  right_paddle.position  = Vector2({WINDOW_WIDTH - 20 - right_paddle.dimension.get_w(),
                                    (WINDOW_HEIGHT / 2.0f) - right_paddle.dimension.get_h()});
  right_paddle.direction = 1;

  PaddleEntity left_paddle("left_paddle", std::make_unique<LeftPaddleController>(), &ctx);
  left_paddle.set_side(PaddleSide::LEFT);
  left_paddle.velocity  = Vector2({0.0f, 500.0f});
  left_paddle.dimension = Dimension({25.0f, 180.0f});
  left_paddle.position  = Vector2({20, (WINDOW_HEIGHT / 2.0f) - left_paddle.dimension.get_h()});
  left_paddle.direction = -1;

  BallEntity ball("ball", &ctx);
  ball.dimension = Dimension({15.0f, 15.0f});
  ball.velocity  = Vector2({450.0f, 450.0f});
  ball.position  = Vector2({(WINDOW_HEIGHT / 2.0f) - ball.dimension.get_w(),
                            (WINDOW_WIDTH / 2.0f) - ball.dimension.get_h()});
  ball.set_left_paddle(&left_paddle);
  ball.set_right_paddle(&right_paddle);

  game_state.add_entity(&right_paddle);
  game_state.add_entity(&left_paddle);
  game_state.add_entity(&ball);

  SDL_Rect  text_rect      = {100, 100, 100, 100};
  const int FPS            = 60;
  const int MS_FRAME_DELAY = 1000 / FPS;

  Uint32 frame_start;
  Uint32 last_time = SDL_GetTicks();
  int    frame_time;
  while (game_state.is_running()) {
    frame_start = SDL_GetTicks();
    float dt    = (frame_start - last_time) / 1000.0f;
    last_time   = frame_start;

    game_state.handle_events();
    game_state.update(dt);
    game_state.render();

    frame_time = SDL_GetTicks() - frame_start;
    if (MS_FRAME_DELAY > frame_time) {
      SDL_Delay(MS_FRAME_DELAY - frame_time);
    }
  }
  TTF_Quit();
  return 0;
}
