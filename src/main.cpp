#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include "SDL2/SDL.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <ctime>

int main()  {
  int WINDOW_HEIGHT = 600;
  int WINDOW_WIDTH = 900;

  srand(time(NULL));
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    return -1;
  }

  SDL_Window* window = SDL_CreateWindow("my window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if(!window) {
    return -1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
  if(!renderer) {
    return -1;
  }

  int running = 1;

  const float PADDLE_WIDTH = 20.0f;
  const float PADDLE_HEIGHT = 150.0f;

  int left_paddle_direction = -1;
  float left_paddle_y  = (WINDOW_HEIGHT / 2.0f) - PADDLE_HEIGHT;

  int right_paddle_direction = 1;
  float right_paddle_y = (WINDOW_HEIGHT / 2.0f) - PADDLE_HEIGHT;

  float paddle_velocity = 8.0f;

  const int FPS = 60;
  const int MS_FRAME_DELAY = 1000 / FPS;
  Uint32 frame_start;
  int frame_time;

  // ball logic 
  float BALL_SIZE = 10.0f;
  float ball_y = (WINDOW_HEIGHT / 2.0f) - BALL_SIZE;
  float ball_x = (WINDOW_WIDTH / 2.0f) - BALL_SIZE;
  float ball_x_vel = 10.0f;
  float ball_y_vel = 7.0f;

  const int left_paddle_x = 20;
  const int right_paddle_x = WINDOW_WIDTH - left_paddle_x - PADDLE_WIDTH;

  SDL_Event event;
  while(running) {
    frame_start = SDL_GetTicks();
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT: {
          running = false;
          std::cout << "Quitting \n";
        }

        case SDL_KEYDOWN: {
          if(event.key.keysym.sym == SDLK_UP) right_paddle_direction = -1;
          if(event.key.keysym.sym == SDLK_DOWN) right_paddle_direction = 1;

          if(event.key.keysym.sym == SDLK_w) left_paddle_direction = -1;
          if(event.key.keysym.sym == SDLK_s) left_paddle_direction = 1;
          break;
        }
      }
    }
    right_paddle_y += right_paddle_direction *  paddle_velocity;
    left_paddle_y += left_paddle_direction *  paddle_velocity;
    ball_x += ball_x_vel;
    ball_y += ball_y_vel;


    if(ball_y < 0 || ball_y + BALL_SIZE >= WINDOW_HEIGHT) {
      ball_y_vel *= -1;
    }

    if(ball_x < 0 || ball_x > WINDOW_WIDTH) {
      ball_x = WINDOW_WIDTH / 2.0f;
      ball_y = WINDOW_HEIGHT / 2.0f;
      ball_y_vel = 5.0f;
      ball_x_vel *= -1;
    }

    if(ball_x <= left_paddle_x + PADDLE_WIDTH &&
      ball_x >= left_paddle_x && 
      ball_y + BALL_SIZE >= left_paddle_y &&
      ball_y <= left_paddle_y + PADDLE_HEIGHT) {
      float hit_pos = (ball_y + BALL_SIZE/2.0f) - (left_paddle_y + PADDLE_HEIGHT/2.0f);
      float normalized_hit_pos = hit_pos / (PADDLE_HEIGHT/2.0f); // -1 (top) → +1 (bottom)
      float MAX_BOUNCE_ANGLE = 75.0f * (M_PI / 180.0f);

      float bounce_angle = normalized_hit_pos * MAX_BOUNCE_ANGLE;

      float speed = sqrt(pow(ball_x_vel,2) + pow(ball_y_vel,2));
      ball_x_vel = cos(bounce_angle) * speed;
      ball_y_vel = sin(bounce_angle) * speed;
    }

    if(ball_x <= right_paddle_x + PADDLE_WIDTH &&
      ball_x >= right_paddle_x && 
      ball_y + BALL_SIZE >= right_paddle_y &&
      ball_y <= right_paddle_y + PADDLE_HEIGHT) {
      float hit_pos = (ball_y + BALL_SIZE/2.0f) - (right_paddle_y + PADDLE_HEIGHT/2.0f);
      float normalized_hit_pos = hit_pos / (PADDLE_HEIGHT/2.0f); // -1 (top) → +1 (bottom)
      float MAX_BOUNCE_ANGLE = 75.0f * (M_PI / 180.0f);

      float bounce_angle = normalized_hit_pos * MAX_BOUNCE_ANGLE;

      float speed = sqrt(pow(ball_x_vel,2) + pow(ball_y_vel,2));
      ball_x_vel = (cos(bounce_angle) * speed) * -1;
      ball_y_vel = sin(bounce_angle) * speed;
    }

    if(right_paddle_y < 0 || right_paddle_y + PADDLE_HEIGHT >= WINDOW_HEIGHT) {
      right_paddle_direction *= -1;
    }

    if(left_paddle_y < 0 || left_paddle_y + PADDLE_HEIGHT >= WINDOW_HEIGHT) {
      left_paddle_direction *= -1;
    }

    SDL_Rect left_paddle = {left_paddle_x, (int)left_paddle_y, (int)PADDLE_WIDTH, (int)PADDLE_HEIGHT};
    SDL_Rect right_paddle = {right_paddle_x, (int)right_paddle_y, (int)PADDLE_WIDTH, (int)PADDLE_HEIGHT};
    SDL_Rect ball = {(int)ball_x, (int)ball_y, (int)BALL_SIZE, (int)BALL_SIZE};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &right_paddle);

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(renderer, &left_paddle);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &ball);

    SDL_RenderPresent(renderer);

    frame_time = SDL_GetTicks() - frame_start;
    if(MS_FRAME_DELAY > frame_time) {
      SDL_Delay(MS_FRAME_DELAY - frame_time);
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

