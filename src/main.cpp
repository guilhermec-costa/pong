#include "../include/game_context.hpp"
#include "../include/game_state.hpp"
#include "../include/paddle_entity.hpp"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <memory>

int main() {
  GameState game_state(900, 600);
  if (game_state.init_resources() < 0) {
    return -1;
  };
  game_state.create_renderer();
  GameContext   ctx(&game_state.window());
  SDL_Renderer* renderer = game_state.renderer();

  const int   WINDOW_HEIGHT = game_state.window().get_height();
  const int   WINDOW_WIDTH  = game_state.window().get_width();
  const float PADDLE_WIDTH  = 25.0f;
  const float PADDLE_HEIGHT = 100.0f;

  PaddleEntity right_paddle("right_paddle", std::make_unique<RightPaddleController>(), &ctx);
  right_paddle.set_side(PaddleSide::RIGHT);
  right_paddle.set_velocity({12.0f, 12.0f});
  right_paddle.set_dimension({25.0f, 100.0f});
  right_paddle.set_pos({WINDOW_WIDTH - 20 - right_paddle.dimension().get_h(),
                        (WINDOW_HEIGHT / 2.0f) - right_paddle.dimension().get_h()});
  right_paddle.set_direction(1);

  PaddleEntity left_paddle("left_paddle", std::make_unique<LeftPaddleController>(), &ctx);
  left_paddle.set_velocity({12.0f, 12.0f});
  left_paddle.set_dimension({25.0f, 100.0f});
  left_paddle.set_pos({20, (WINDOW_HEIGHT / 2.0f) - left_paddle.dimension().get_h()});
  left_paddle.set_direction(-1);

  game_state.add_entity(&right_paddle);
  game_state.add_entity(&left_paddle);

  int running = 1;

  const int FPS            = 120;
  const int MS_FRAME_DELAY = 1000 / FPS;
  Uint32    frame_start;
  int       frame_time;

  // ball logic
  float BALL_SIZE  = 20.0f;
  float ball_y     = (WINDOW_HEIGHT / 2.0f) - BALL_SIZE;
  float ball_x     = (WINDOW_WIDTH / 2.0f) - BALL_SIZE;
  float ball_x_vel = 9.0f;
  float ball_y_vel = 5.0f;

  const int left_paddle_x = 20;

  SDL_Event event;
  while (game_state.is_running()) {
    frame_start = SDL_GetTicks();
    game_state.handle_events();
    right_paddle.update(0);
    left_paddle.update(0);

    // ball_x += ball_x_vel;
    // ball_y += ball_y_vel;

    // if (ball_y < 0 || ball_y + BALL_SIZE >= WINDOW_HEIGHT) {
    //   ball_y_vel *= -1;
    // }

    // if (ball_x < 0 || ball_x > WINDOW_WIDTH) {
    //   ball_x     = WINDOW_WIDTH / 2.0f;
    //   ball_y     = WINDOW_HEIGHT / 2.0f;
    //   ball_y_vel = 5.0f;
    //   ball_x_vel *= -1;
    // }

    // if (ball_x <= left_paddle_x + PADDLE_WIDTH && ball_x >= left_paddle_x &&
    //     ball_y + BALL_SIZE >= left_paddle_y && ball_y <= left_paddle_y + PADDLE_HEIGHT) {
    //   float hit_pos = (ball_y + BALL_SIZE / 2.0f) - (left_paddle_y + PADDLE_HEIGHT / 2.0f);
    //   float normalized_hit_pos = hit_pos / (PADDLE_HEIGHT / 2.0f); // -1 (top) → +1 (bottom)
    //   float MAX_BOUNCE_ANGLE   = 75.0f * (M_PI / 180.0f);

    //   float bounce_angle = normalized_hit_pos * MAX_BOUNCE_ANGLE;

    //   float speed = sqrt(pow(ball_x_vel, 2) + pow(ball_y_vel, 2));
    //   ball_x_vel  = cos(bounce_angle) * speed;
    //   ball_y_vel  = sin(bounce_angle) * speed;
    // }

    // if (ball_x <= right_paddle_x + PADDLE_WIDTH && ball_x >= right_paddle_x &&
    //     ball_y + BALL_SIZE >= right_paddle_y && ball_y <= right_paddle_y + PADDLE_HEIGHT) {
    //   float hit_pos = (ball_y + BALL_SIZE / 2.0f) - (right_paddle_y + PADDLE_HEIGHT / 2.0f);
    //   float normalized_hit_pos = hit_pos / (PADDLE_HEIGHT / 2.0f); // -1 (top) → +1 (bottom)
    //   float MAX_BOUNCE_ANGLE   = 75.0f * (M_PI / 180.0f);

    //   float bounce_angle = normalized_hit_pos * MAX_BOUNCE_ANGLE;

    //   float speed = sqrt(pow(ball_x_vel, 2) + pow(ball_y_vel, 2));
    //   ball_x_vel  = (cos(bounce_angle) * speed) * -1;
    //   ball_y_vel  = sin(bounce_angle) * speed;
    // }

    SDL_Rect left_paddle_rect  = {(int)left_paddle.position().x, (int)left_paddle.position().y,
                                  (int)left_paddle.dimension().get_w(),
                                  (int)left_paddle.dimension().get_h()};
    SDL_Rect right_paddle_rect = {(int)right_paddle.position().x, (int)right_paddle.position().y,
                                  (int)right_paddle.dimension().get_w(),
                                  (int)right_paddle.dimension().get_h()};
    // SDL_Rect ball         = {(int)ball_x, (int)ball_y, (int)BALL_SIZE, (int)BALL_SIZE};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &right_paddle_rect);

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(renderer, &left_paddle_rect);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // SDL_RenderFillRect(renderer, &ball);

    SDL_RenderPresent(renderer);

    frame_time = SDL_GetTicks() - frame_start;
    if (MS_FRAME_DELAY > frame_time) {
      SDL_Delay(MS_FRAME_DELAY - frame_time);
    }
  }
  return 0;
}
