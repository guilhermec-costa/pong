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

class FPSCounter {
public:
    FPSCounter() : frame_count(0), fps(0), last_time(SDL_GetTicks()) {}

    void frame_rendered() {
        frame_count++;
        Uint32 current_time = SDL_GetTicks();

        if (current_time - last_time >= 1000) {
            fps = frame_count;
            frame_count = 0;
            last_time = current_time;
        }
    }

    int getFPS() const { return fps; }

private:
    int frame_count;
    int fps;
    Uint32 last_time;
};

int main() {
  GameState     game_state(1440, 900);
  SDL_Renderer* renderer = game_state.renderer();

  GameContext ctx(&game_state.window(), renderer);
  const int   WINDOW_HEIGHT = game_state.window().get_height();
  const int   WINDOW_WIDTH  = game_state.window().get_width();

  PaddleEntity right_paddle("right_paddle", std::make_unique<RightPaddleController>(),
                            PaddleSide::RIGHT, &ctx);
  PaddleEntity left_paddle("left_paddle", std::make_unique<LeftPaddleController>(),
                           PaddleSide::LEFT, &ctx);

  BallEntity ball("ball", &ctx);
  ball.dimension = Dimension(15, 15);
  ball.set_left_paddle(&left_paddle);
  ball.set_right_paddle(&right_paddle);

  game_state.add_entity(&right_paddle);
  game_state.add_entity(&left_paddle);
  game_state.add_entity(&ball);

  const int FPS            = 120;
  const int MS_FRAME_DELAY = 1000 / FPS;

  Uint32 frame_start;
  Uint32 last_time = SDL_GetTicks();
  int    frame_time;
  FPSCounter fps_counter;
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
    fps_counter.frame_rendered();
  }
  return 0;
}
